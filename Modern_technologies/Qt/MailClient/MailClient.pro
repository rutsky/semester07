# -------------------------------------------------
# Project created by QtCreator 2010-01-21T04:32:29
# -------------------------------------------------
TARGET = MailClient
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    aboutdialog.cpp \
    directoryproxymodel.cpp \
    letterproxymodel.cpp \
    directorytreeview.cpp \
    lettertableview.cpp \
    letterobject.cpp \
    letterheaderview.cpp
HEADERS += mainwindow.h \
    aboutdialog.h \
    directoryproxymodel.h \
    letterproxymodel.h \
    directorytreeview.h \
    lettertableview.h \
    letterobject.h \
    precompiledheader.h \
    letterheaderview.h
FORMS += mainwindow.ui \
    aboutdialog.ui
QMAKE_CXXFLAGS += -Winvalid-pch
PRECOMPILED_HEADER = precompiledheader.h
