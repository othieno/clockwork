/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Jeremy Othieno.
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
#include "viewport.hh"

using clockwork::graphics::Viewport;


Viewport::Viewport(const double& X, const double& Y, const double& W, const double& H, const double& N, const double& F) :
x(X < 0.0 ? 0.0 : X > 1.0 ? 1.0 : X),
y(Y < 0.0 ? 0.0 : Y > 1.0 ? 1.0 : Y),
width(W < 0.0 ? 0.0 : W > 1.0 ? 1.0 : W),
height(H < 0.0 ? 0.0 : H > 1.0 ? 1.0 : H),
near(N < 0.0 ? 0.0 : N > 1.0 ? 1.0 : N),
far(F < 0.0 ? 0.0 : F > 1.0 ? 1.0 : F)
{}
