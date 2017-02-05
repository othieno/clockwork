/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2017 Jeremy Othieno.
 *
 * The MIT License (MIT)
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
#ifndef CLOCKWORK_TEST_LERP_HH
#define CLOCKWORK_TEST_LERP_HH

#include "Test.hh"


namespace clockwork {
namespace testsuite {
/**
 * Tests the lerp function.
 * @see src/math/lerp.hh.
 */
class TestLerp : public Test {
	Q_OBJECT
public:
	explicit TestLerp(QObject& parent);
private slots:
	void testQReal_data();
	void testQReal();
/*
	void testQPointF_data();
	void testQPointF();
	void testQVector3D_data();
	void testQVector3D();
	void testQVector4D_data();
	void testQVector4D();
	void testColor_data();
	void testColor();
*/
};
} // namespace testsuite
} // namespace clockwork

#endif // CLOCKWORK_TEST_LERP_HH
