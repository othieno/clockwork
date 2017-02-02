#!/bin/bash
#
# This file is part of Clockwork.
#
# Copyright (c) 2013-2017 Jeremy Othieno.
#
# The MIT License (MIT)
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
set -e
set -o pipefail

QMAKE=$(type -P qmake)
if [ ! -x "$QMAKE" ]
then
	echo "Error! Could not find the 'qmake' executable. Check to make sure it's installed, in your PATH, and executable."
	exit 1
fi

MAKE=$(type -P make)
if [ ! -x "$MAKE" ]
then
	echo "Error! Could not find the 'make' executable. Check to make sure it's installed, in your PATH, and executable."
	exit 1
fi

BASE_DIR="$(dirname $0 | xargs dirname | xargs realpath)"
WORK_DIR="$BASE_DIR/tests"

"$QMAKE" "$WORK_DIR" -o "$WORK_DIR/Makefile" && \
"$MAKE" --silent -C "$WORK_DIR" && \
"$BASE_DIR/build/testsuite"

exit 0
