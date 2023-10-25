QT += sql
QT -= gui

TEMPLATE = lib
DEFINES += GALLERYCORE_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AlbumDao.cpp \
    AlbumModel.cpp \
    DatabaseManager.cpp \
    Picture.cpp \
    PictureDao.cpp \
    album.cpp

HEADERS += \
    AlbumDao.h \
    AlbumModel.h \
    DatabaseManager.h \
    Picture.h \
    PictureDao.h \
    gallery-core_global.h \
    album.h

# Default rules for deployment.
target.path = /usr/lib

!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore
