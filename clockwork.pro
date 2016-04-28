include(resources/theme/material/material.pri)

TEMPLATE = app
TARGET = clockwork
CONFIG += c++14
RESOURCES += clockwork.qrc

QMAKE_CXXFLAGS += -Wextra

DESTDIR = build
OBJECTS_DIR = $${DESTDIR}/obj
MOC_DIR = $${DESTDIR}/moc
RCC_DIR = $${DESTDIR}/rcc
UI_DIR = $${DESTDIR}/ui

INCLUDEPATH += src \
               src/concurrency \
               src/graphics \
               src/graphics/renderer \
               src/io \
               src/math \
               src/scene \
               src/system \
               src/ui

HEADERS += \
           src/graphics/Framebuffer.hh \
           src/ui/FramebufferProvider.hh \
           src/ui/UserInterface.hh \
           src/system/Application.hh \
           src/system/Error.hh \
           src/system/Service.hh \
           src/clockwork.hh

SOURCES += \
           src/graphics/Framebuffer.cc \
           src/ui/FramebufferProvider.cc \
           src/ui/UserInterface.cc \
           src/system/Application.cc \
           src/system/Error.cc \
           src/system/Service.cc \
           src/clockwork.cc
