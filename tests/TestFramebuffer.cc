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
#include "TestFramebuffer.hh"
#include "Framebuffer.hh"

using clockwork::testsuite::TestFramebuffer;


TestFramebuffer::TestFramebuffer(QObject& parent) :
Test(parent)
{}


void
TestFramebuffer::testClear_data() {
	using enum_traits = enum_traits<Framebuffer::Resolution>;
	QTest::addColumn<enum_traits::Ordinal>("resolution");

	QTest::newRow("ZERO") << enum_traits::ordinal(Framebuffer::Resolution::ZERO);
	QTest::newRow("VGA") << enum_traits::ordinal(Framebuffer::Resolution::VGA);
	QTest::newRow("SVGA") << enum_traits::ordinal(Framebuffer::Resolution::SVGA);
	QTest::newRow("XGA") << enum_traits::ordinal(Framebuffer::Resolution::XGA);
	QTest::newRow("SXGA") << enum_traits::ordinal(Framebuffer::Resolution::SXGA);
	QTest::newRow("FHD") << enum_traits::ordinal(Framebuffer::Resolution::FHD);
	QTest::newRow("QSXGA") << enum_traits::ordinal(Framebuffer::Resolution::QSXGA);
	QTest::newRow("UHD8K") << enum_traits::ordinal(Framebuffer::Resolution::UHD8K);
}


void
TestFramebuffer::testClear() {
	using enum_traits = enum_traits<Framebuffer::Resolution>;
	QFETCH(enum_traits::Ordinal, resolution);

	Framebuffer framebuffer(enum_traits::enumerator(resolution));

	QBENCHMARK {
		framebuffer.clear();
	}
}
