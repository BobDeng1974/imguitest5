#QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG += static

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+=/opt/sdl-st/include/SDL2

#LIBS+=-lgstreamer-1.0 \
LIBS+=-L"/opt/sdl-st/lib" -lSDL2

SOURCES += main.cpp \
    imgui/imgui.cpp \
    imgui/imgui_demo.cpp \
    imgui/imgui_draw.cpp \
    imgui_impl_sdl_gles2.cpp

HEADERS += \
    imgui/imconfig.h \
    imgui/imgui.h \
    imgui/imgui_internal.h \
    imgui/stb_rect_pack.h \
    imgui/stb_textedit.h \
    imgui/stb_truetype.h \
    imgui_impl_sdl_gles2.h
