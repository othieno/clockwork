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
include(../clockwork.pri)

TEMPLATE = app
TARGET = testsuite
QT += testlib

# Remove clockwork.cc since it will create an entry point conflict (two main functions).
SOURCES -= src/clockwork.cc

# Prefix the paths.
paths       = $$INCLUDEPATH
headers     = $$HEADERS
sources     = $$SOURCES
INCLUDEPATH =
HEADERS     =
SOURCES     =
for (path, paths):     INCLUDEPATH += ../$$path
for (header, headers): HEADERS += ../$$header
for (source, sources): SOURCES += ../$$source
INCLUDEPATH += .
DESTDIR = ../$${DESTDIR}
OBJECTS_DIR = ../$${OBJECTS_DIR}
MOC_DIR = ../$${MOC_DIR}
RCC_DIR = ../$${RCC_DIR}
UI_DIR = ../$${UI_DIR}

HEADERS += \
	Test.hh \
	TestFramebuffer.hh \
	TestLerp.hh \
	testsuite.hh
SOURCES += \
	TestFramebuffer.cc \
	TestLerp.cc \
	testsuite.cc
