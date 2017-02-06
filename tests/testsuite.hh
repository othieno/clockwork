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
#ifndef CLOCKWORK_TESTSUITE_HH
#define CLOCKWORK_TESTSUITE_HH

#include "Test.hh"


namespace clockwork {
namespace testsuite {
/**
 * Runs a set of tests.
 */
template<class... Tests>
int run(int argc, char** argv) {
	// The parent object is used to manage the memory dynamically allocated
	// for each test object, i.e. when it goes out of scope and is destroyed,
	// each test object attached to it will be destroyed too.
	QObject parent;
	const std::initializer_list<Test*> tests = {new Tests(parent)...};

	int exitStatus = 0;
	for (auto* const test : tests) {
		exitStatus |= QTest::qExec(test, argc, argv);
	}
	return exitStatus;
}
} // namespace testsuite
} // namespace clockwork

#endif // CLOCKWORK_TESTSUITE_HH
