#!/bin/bash
#
# This file is part of Clockwork.
#
# Copyright (c) 2013-2016 Jeremy Othieno.
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
#
set -o pipefail

MAKE=$(type -P make)
if [ ! -x "$MAKE" ]
then
	echo "Error! Could not find 'make'. Check to make sure it's installed, in the PATH, and executable."
	exit 1
fi

QMAKE=$(type -P qmake)
if [ ! -x "$QMAKE" ]
then
	echo "Error! Could not find 'qmake'. Check to make sure it's installed, in the PATH, and executable."
	exit 1
fi

# If any of the following commands fails, exit the script immediately.
set -e

# The absolute path to the Clockwork project's directory.
ROOT_DIR="$(dirname $0 | xargs dirname | xargs realpath)"
BUILD_DIRS=(
	"$ROOT_DIR/resources/theme/material/"
	"$ROOT_DIR"
)
for directory in ${BUILD_DIRS[*]}; do cd "$directory"; $QMAKE; $MAKE; done


exit 0
