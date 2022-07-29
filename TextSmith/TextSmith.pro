QT       += core gui printsupport multimedia texttospeech

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 embed_manifest_exe

INCLUDEPATH += "C:/Users/chris/Documents/QtSource/Lua/lua"
DEPENDPATH += . "C:/Users/chris/Documents/QtSource/Lua/build-lua-Desktop_Qt_6_2_0_MSVC2019_64bit-Debug/debug"
LIBS += -L"C:/Users/chris/Documents/QtSource/Lua/build-lua-Desktop_Qt_6_2_0_MSVC2019_64bit-Debug/debug" -llua
LIBS += -lAdvapi32
RC_ICONS = TextSmith.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TextEdit.cpp \
    aboutdialog.cpp \
    epub.cpp \
    finddialog.cpp \
    fullscreen.cpp \
    html.cpp \
    main.cpp \
    mainwindow.cpp \
    markdown.cpp \
    optionsdialog.cpp \
    pdf.cpp \
    replacedialog.cpp \
    rtf.cpp \
    scriptsdialog.cpp \
    tagsdialog.cpp \
    text.cpp

HEADERS += \
    TextEdit.h \
    Zippy/ZipArchive.hpp \
    Zippy/ZipEntry.hpp \
    Zippy/ZipException.hpp \
    Zippy/ZipUtilities.hpp \
    Zippy/Zippy.hpp \
    Zippy/miniz/miniz.h \
    aboutdialog.h \
    epub.h \
    errors.h \
    finddialog.h \
    fullscreen.h \
    globals.h \
    html.h \
    mainwindow.h \
    markdown.h \
    optionsdialog.h \
    pdf.h \
    replacedialog.h \
    rtf.h \
    scriptsdialog.h \
    structures.h \
    tagsdialog.h \
    text.h

FORMS += \
    aboutdialog.ui \
    finddialog.ui \
    fullscreen.ui \
    mainwindow.ui \
    optionsdialog.ui \
    replacedialog.ui \
    scriptsdialog.ui \
    tagsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    audio.qrc \
    icons.qrc \
    styles.qrc
