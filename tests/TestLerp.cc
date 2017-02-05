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
#include "TestLerp.hh"
#include "lerp.hh"

using clockwork::testsuite::TestLerp;


TestLerp::TestLerp(QObject& parent) :
Test(parent)
{}


void
TestLerp::testQReal_data() {
	QTest::addColumn<qreal>("from");
	QTest::addColumn<qreal>("to");
	QTest::addColumn<qreal>("percentage");
	QTest::addColumn<qreal>("result");

	QTest::newRow("0% interpolation") << 0.0 << 1.0 << 0.0 << 0.0;
	QTest::newRow("25% interpolation") << -1.0 << 1.0 << 0.25 << -0.5;
	QTest::newRow("50% interpolation") << 0.0 << 1.0 << 0.5 << 0.5;
	QTest::newRow("75% interpolation") << -1.0 << 1.0 << 0.75 << 0.5;
	QTest::newRow("100% interpolation") << 0.0 << 1.0 << 1.0 << 1.0;
}


void
TestLerp::testQReal() {
	QFETCH(qreal, from);
	QFETCH(qreal, to);
	QFETCH(qreal, percentage);
	QFETCH(qreal, result);

	QCOMPARE(lerp(from, to, percentage), result);

	QBENCHMARK {
		lerp(from, to, percentage);
	}
}

/*
void
TestLerp::testQPointF_data() {
}


void
TestLerp::testQPointF() {
}


void
TestLerp::testQVector3D_data() {
}


void
TestLerp::testQVector3D() {
}


void
TestLerp::testQVector4D_data() {
}


void
TestLerp::testQVector4D() {
}


void
TestLerp::testColor_data() {
}


void
TestLerp::testColor() {
}
*/
