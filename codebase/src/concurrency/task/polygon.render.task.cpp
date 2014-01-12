/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Jeremy Othieno.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "polygon.render.task.hh"
#include "numerical.hh"


clockwork::concurrency::PolygonRenderTask::PolygonRenderTask
(
	const clockwork::physics::RigidBody& body,
	const clockwork::scene::Viewer& viewer
) :
RenderTask(body, viewer)
{}


void
clockwork::concurrency::PolygonRenderTask::primitiveAssembly
(
	std::array<const clockwork::graphics::Fragment*, 3>& triangle
)
{
	// Sort the fragments baed on their positions.
	std::sort
	(
		triangle.begin(),
		triangle.end(),
		[](const clockwork::graphics::Fragment* f0, const clockwork::graphics::Fragment* f1)
		{
			const double& y0 = f0->y;
			const double& y1 = f1->y;

			if (y0 > y1)
				return false;
			else if (clockwork::fequal(y0, y1))
			{
				const double& x0 = f0->x;
				const double& x1 = f1->x;

				if (x0 > x1)
					return false;
				else if (clockwork::fequal(x0, x1))
				{
					const double& z0 = f0->z;
					const double& z1 = f1->z;

					return (z0 > z1) ? false : true;
				}
				else
					return true;
			}
			else
				return true;
		}
	);
	// The three fragments will make up our triangle.
	const auto& f0 = *triangle[0];
	const auto& f1 = *triangle[1];
	const auto& f2 = *triangle[2];

	// If the triangle primitive is not correctly formed for this algorithm, tessellate two
	// new triangle primitives. If it is, proceed with the scan conversion.
	const auto shouldTessellate = !clockwork::fequal(f0.y, f1.y) && !clockwork::fequal(f1.y, f2.y);
	if (shouldTessellate)
	{
		// Interpolate the new fragment.
		const double p = (f1.y - f0.y) / (f2.y - f0.y);
		auto fi = clockwork::graphics::Fragment::interpolate(f2, f0, p);
		fi.y = f1.y;

		// Tesselate! Create two new triangle primitives from the previous one.
		std::array<const clockwork::graphics::Fragment*, 3> t0 = {&f0, &f1, &fi};
		std::array<const clockwork::graphics::Fragment*, 3> t1 = {&f1, &fi, &f2};
		primitiveAssembly(t0);
		primitiveAssembly(t1);
	}
	else
		scanConversion(f0, f1, f2);
}


void
clockwork::concurrency::PolygonRenderTask::scanConversion
(
	const clockwork::graphics::Fragment& f0,
	const clockwork::graphics::Fragment& f1,
	const clockwork::graphics::Fragment& f2
)
{
	const auto fragmentOP = getFragmentOperation();

	double xd0, xd1, xf0, xf1;
	double yd0, yd1, yf0, yf1;
	double zd0, zd1, zf0, zf1;

	double rd0, rd1, rf0, rf1;
	double gd0, gd1, gf0, gf1;
	double bd0, bd1, bf0, bf1;
	double ad0, ad1, af0, af1;

	double ud0, ud1, uf0, uf1;
	double vd0, vd1, vf0, vf1;

	double nxd0, nyd0, nzd0;
	double nxd1, nyd1, nzd1;
	double nxf0, nyf0, nzf0;
	double nxf1, nyf1, nzf1;


	// The value of the interpolated fragment.
	clockwork::graphics::Fragment fi;

	if (clockwork::fequal(f0.y, f1.y))
	{
		// Triangle type A:
		xd0  = f0.x;				xd1  = f2.x;				xf0  = f1.x;				xf1  = xd1;
		yd0  = f0.y;				yd1  = f2.y;				yf0  = f1.y;				yf1  = yd1;
		zd0  = f0.z;				zd1  = f2.z;				zf0  = f1.z;				zf1  = zd1;
		ad0  = f0.color.alpha;	ad1  = f2.color.alpha;	af0  = f1.color.alpha;	af1  = ad1;
		rd0  = f0.color.red;		rd1  = f2.color.red;		rf0  = f1.color.red;		rf1  = rd1;
		gd0  = f0.color.green;	gd1  = f2.color.green;	gf0  = f1.color.green;	gf1  = gd1;
		bd0  = f0.color.blue;	bd1  = f2.color.blue;	bf0  = f1.color.blue;	bf1  = bd1;
		ud0  = f0.u;				ud1  = f2.u;				uf0  = f1.u;				uf1  = ud1;
		vd0  = f0.v;				vd1  = f2.v;				vf0  = f1.v;				vf1  = vd1;
		nxd0 = f0.i;				nxd1 = f2.i;				nxf0 = f1.i;				nxf1 = nxd1;
		nyd0 = f0.j;				nyd1 = f2.j;				nyf0 = f1.j;				nyf1 = nyd1;
		nzd0 = f0.k;				nzd1 = f2.k;				nzf0 = f1.k;				nzf1 = nzd1;
	}
	else
	{
		// Triangle type B:
		xd0  = f1.x;				xd1  = f0.x;				xf0  = f2.x;				xf1  = xd1;
		yd0  = f1.y;				yd1  = f0.y;				yf0  = f2.y;				yf1  = yd1;
		zd0  = f1.z;				zd1  = f0.z;				zf0  = f2.z;				zf1  = zd1;
		ad0  = f1.color.alpha;	ad1  = f0.color.alpha;	af0  = f2.color.alpha;	af1  = ad1;
		rd0  = f1.color.red;		rd1  = f0.color.red;		rf0  = f2.color.red;		rf1  = rd1;
		gd0  = f1.color.green;	gd1  = f0.color.green;	gf0  = f2.color.green;	gf1  = gd1;
		bd0  = f1.color.blue;	bd1  = f0.color.blue;	bf0  = f2.color.blue;	bf1  = bd1;
		ud0  = f1.u;				ud1  = f0.u;				uf0  = f2.u;				uf1  = ud1;
		vd0  = f1.v;				vd1  = f0.v;				vf0  = f2.v;				vf1  = vd1;
		nxd0 = f1.i;				nxd1 = f0.i;				nxf0 = f2.i;				nxf1 = nxd1;
		nyd0 = f1.j;				nyd1 = f0.j;				nyf0 = f2.j;				nyf1 = nyd1;
		nzd0 = f1.k;				nzd1 = f0.k;				nzf0 = f2.k;				nzf1 = nzd1;
	}

	const double dyd = yd1 - yd0;
	const double dyf = yf1 - yf0;

	for (long y = std::round(f0.y); y < std::round(f2.y); ++y)
	{
		const double pd  = (y - yd0) / dyd;
		const double ppd = 1.0 - pd;
		const double xd  = (xd0  * ppd) + (xd1  * pd);
		const double zd  = (zd0  * ppd) + (zd1  * pd);
		const double ud  = (ud0  * ppd) + (ud1  * pd);
		const double vd  = (vd0  * ppd) + (vd1  * pd);
		const double rd  = (rd0  * ppd) + (rd1  * pd);
		const double gd  = (gd0  * ppd) + (gd1  * pd);
		const double bd  = (bd0  * ppd) + (bd1  * pd);
		const double ad  = (ad0  * ppd) + (ad1  * pd);
		const double nxd = (nxd0 * ppd) + (nxd1 * pd);
		const double nyd = (nyd0 * ppd) + (nyd1 * pd);
		const double nzd = (nzd0 * ppd) + (nzd1 * pd);

		const double pf  = (y - yf0) / dyf;
		const double ppf = 1.0 - pf;
		const double xf  = (xf0  * ppf) + (xf1  * pf);
		const double zf  = (zf0  * ppf) + (zf1  * pf);
		const double uf  = (uf0  * ppf) + (uf1  * pf);
		const double vf  = (vf0  * ppf) + (vf1  * pf);
		const double rf  = (rf0  * ppf) + (rf1  * pf);
		const double gf  = (gf0  * ppf) + (gf1  * pf);
		const double bf  = (bf0  * ppf) + (bf1  * pf);
		const double af  = (af0  * ppf) + (af1  * pf);
		const double nxf = (nxf0 * ppf) + (nxf1 * pf);
		const double nyf = (nyf0 * ppf) + (nyf1 * pf);
		const double nzf = (nzf0 * ppf) + (nzf1 * pf);

		const double dx = xf - xd;
		for (long x = std::round(std::min(xd, xf)); x <= std::max(xd, xf); ++x)
		{
			const double pp = (x - xd) / dx;
			const double p = 1.0 - pp;

			// Initialise the interpolated fragment.
			fi.x = x;
			fi.y = y;
			fi.z = (p * zd) + (pp * zf);
			fi.u = (p * ud) + (pp * uf);
			fi.v = (p * vd) + (pp * vf);
			fi.color.alpha = (p * ad) + (pp * af);
			fi.color.red = (p * rd) + (pp * rf);
			fi.color.green = (p * gd) + (pp * gf);
			fi.color.blue = (p * bd) + (pp * bf);

			fi.i = (p * nxd) + (pp * nxf);
			fi.j = (p * nyd) + (pp * nyf);
			fi.k = (p * nzd) + (pp * nzf);

			plot(fi, fragmentOP);
		}
	}
}
