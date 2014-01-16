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
#include "polygon.render.parameters.hh"
#include "numerical.hh"

using clockwork::graphics::PolygonRenderParameters;


PolygonRenderParameters::PolygonRenderParameters(const RenderParameters::Type& type) :
RenderParameters(type)
{}


void
PolygonRenderParameters::primitiveAssembly(const std::array<const Fragment*, 3>& triangle) const
{
	// Sort the fragments based on their positions.
	std::array<const Fragment*, 3> sortedFragments = {triangle[0], triangle[1], triangle[2]};
	std::sort
	(
		sortedFragments.begin(),
		sortedFragments.end(),
		[](const Fragment* const f0, const Fragment* const f1)
		{
			const double& y0 = f0->position.y;
			const double& y1 = f1->position.y;

			if (y0 > y1)
				return false;
			else if (clockwork::fequal(y0, y1))
			{
				const double& x0 = f0->position.x;
				const double& x1 = f1->position.x;

				if (x0 > x1)
					return false;
				else if (clockwork::fequal(x0, x1))
				{
					const double& z0 = f0->position.z;
					const double& z1 = f1->position.z;

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
	const auto& f0 = *sortedFragments[0];
	const auto& f1 = *sortedFragments[1];
	const auto& f2 = *sortedFragments[2];

	// If the triangle primitive is not correctly formed for this algorithm, tessellate two
	// new triangle primitives. If it is, proceed with the scan conversion.
	const double& y0 = f0.position.y;
	const double& y1 = f1.position.y;
	const double& y2 = f2.position.y;

	const auto shouldTessellate = !clockwork::fequal(y0, y1) && !clockwork::fequal(y1, y2);
	if (shouldTessellate)
	{
		// Interpolate the new fragment.
		auto fi = Fragment::interpolate(f0, f2, (y1 - y0) / (y2 - y0));
		fi.position.y = y1;

		// Tesselate! Create two new triangle primitives from the previous one.
		const std::array<const Fragment*, 3> t0 = {&f0, &f1, &fi};
		const std::array<const Fragment*, 3> t1 = {&f1, &fi, &f2};
		primitiveAssembly(t0);
		primitiveAssembly(t1);
	}
	else
		scanConversion(f0, f1, f2);
}


void
PolygonRenderParameters::scanConversion
(
	const clockwork::graphics::Fragment& f0,
	const clockwork::graphics::Fragment& f1,
	const clockwork::graphics::Fragment& f2
) const
{
	const clockwork::graphics::Fragment *A, *B, *C;

	if (clockwork::fequal(f0.position.y, f1.position.y))
	{
		// Triangle type A:
		A = &f0;
		B = &f2;
		C = &f1;
	}
	else
	{
		// Triangle type B:
		A = &f1;
		B = &f0;
		C = &f2;
	}

	const double &xss = A->position.x,	&xse = B->position.x,	&xes = C->position.x,	&xee = xse;
	const double &yss = A->position.y,	&yse = B->position.y,	&yes = C->position.y,	&yee = yse;
	const double &zss = A->position.z,	&zse = B->position.z,	&zes = C->position.z,	&zee = zse;
	const double &rss = A->color.red,	&rse = B->color.red,		&res = C->color.red,		&ree = rse;
	const double &gss = A->color.green,	&gse = B->color.green,	&ges = C->color.green,	&gee = gse;
	const double &bss = A->color.blue,	&bse = B->color.blue,	&bes = C->color.blue,	&bee = bse;
	const double &ass = A->color.alpha,	&ase = B->color.alpha,	&aes = C->color.alpha,	&aee = ase;
	const double &uss = A->u,				&use = B->u,				&ues = C->u,				&uee = use;
	const double &vss = A->v,				&vse = B->v,				&ves = C->v,				&vee = vse;
	const double &iss = A->normal.i,		&ise = B->normal.i,		&ies = C->normal.i,		&iee = ise;
	const double &jss = A->normal.j,		&jse = B->normal.j,		&jes = C->normal.j,		&jee = jse;
	const double &kss = A->normal.k,		&kse = B->normal.k,		&kes = C->normal.k,		&kee = kse;

	const double &dys = yse - yss;
	const double &dye = yee - yes;

	// No divisions-by-zero!
	if (clockwork::fequal(dys, 0.0) || clockwork::fequal(dye, 0.0))
		return;

	// The interpolated fragment.
	clockwork::graphics::Fragment fi;

	// Remember that the fragments are arranged in such a way that f0 has the smallest
	// y value and f2 has the largest.
	for (long y = std::round(f0.position.y); y <= std::round(f2.position.y); ++y)
	{
		const double ps = (y - yss) / dys;
		const auto  pps = 1.0 - ps;

		const double pe = (y - yes) / dye;
		const auto  ppe = 1.0 - pe;

		// The scan-line's starting (xs) and ending (xe) horizontal position.
		const double xs = (pps * xss) + (ps * xse);
		const double xe = (ppe * xes) + (pe * xee);
		const double dx = xe - xs;

		// Once again, no divisions-by-zero!
		if (clockwork::fequal(dx, 0.0))
			continue;

		const double zs = (pps * zss) + (ps * zse);
		const double us = (pps * uss) + (ps * use);
		const double vs = (pps * vss) + (ps * vse);
		const double rs = (pps * rss) + (ps * rse);
		const double gs = (pps * gss) + (ps * gse);
		const double bs = (pps * bss) + (ps * bse);
		const double as = (pps * ass) + (ps * ase);
		const double is = (pps * iss) + (ps * ise);
		const double js = (pps * jss) + (ps * jse);
		const double ks = (pps * kss) + (ps * kse);

		const double ze = (ppe * zes) + (pe * zee);
		const double ue = (ppe * ues) + (pe * uee);
		const double ve = (ppe * ves) + (pe * vee);
		const double re = (ppe * res) + (pe * ree);
		const double ge = (ppe * ges) + (pe * gee);
		const double be = (ppe * bes) + (pe * bee);
		const double ae = (ppe * aes) + (pe * aee);
		const double ie = (ppe * ies) + (pe * iee);
		const double je = (ppe * jes) + (pe * jee);
		const double ke = (ppe * kes) + (pe * kee);

		for (long x = std::round(std::min(xs, xe)) ; x <= std::round(std::max(xs, xe)); ++x)
		{
			const double p = (x - xs) / dx;
			const double pp = 1.0 - p;

			// Initialise the interpolated fragment.
			fi.position = clockwork::Point4
			(
				x,
				y,
				(pp * zs) + (p * ze)
			);
			fi.color = clockwork::graphics::ColorRGBA
			(
				(pp * rs) + (p * re),
				(pp * gs) + (p * ge),
				(pp * bs) + (p * be),
				(pp * as) + (p * ae)
			);
			fi.normal = clockwork::Vector3
			(
				(pp * is) + (p * ie),
				(pp * js) + (p * je),
				(pp * ks) + (p * ke)
			);
			fi.u = (pp * us) + (p * ue);
			fi.v = (pp * vs) + (p * ve);

			// Draw the interpolated fragment.
			plot(fi);
		}
	}
}
