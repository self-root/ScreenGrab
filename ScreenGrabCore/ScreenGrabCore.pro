QT -= gui
QT += sql quick concurrent

TEMPLATE = lib
DEFINES += SCREENGRABCORE_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databaseaccess.cpp \
    image.cpp \
    imagedao.cpp \
    imageprocessing.cpp \
    imageprovider.cpp \
    langmodel.cpp \
    maincontroller.cpp \
    recentimagemodel.cpp \
    imagetotext.cpp \
    resulttextviewcontroller.cpp

HEADERS += \
    ScreenGrabCore_global.h \
    databaseaccess.h \
    image.h \
    imagedao.h \
    imageprocessing.h \
    imageprovider.h \
    langmodel.h \
    maincontroller.h \
    recentimagemodel.h \
    resulttextviewcontroller.h \
    utils.h \
    imagetotext.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/dependencies/tesseract_x64-windows/lib/ -ltesseract52
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/dependencies/tesseract_x64-windows/lib/ -ltesseract52d

INCLUDEPATH += $$PWD/dependencies/tesseract_x64-windows/include
DEPENDPATH += $$PWD/dependencies/tesseract_x64-windows/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/dependencies/leptonica_x64-windows/lib/ -lleptonica-1.82.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/dependencies/leptonica_x64-windows/lib/ -lleptonica-1.82.0d

INCLUDEPATH += $$PWD/dependencies/leptonica_x64-windows/include
DEPENDPATH += $$PWD/dependencies/leptonica_x64-windows/include
