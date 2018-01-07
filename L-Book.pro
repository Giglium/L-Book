#-------------------------------------------------
#
# Project created by QtCreator 2016-12-17T11:27:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = L-Book
TEMPLATE = app


SOURCES += main.cpp\
    Lib/username.cpp \
    Lib/userinfo.cpp \
    Lib/account.cpp \
    Lib/publication.cpp \
    Lib/periodic.cpp \
    Lib/book.cpp \
    Lib/account_permission.cpp \
    Lib/publication_permission.cpp \
    Lib/loan.cpp \
    Lib/loans.cpp \
    Lib/users.cpp \
    Lib/library.cpp \
    Lib/dataCollector.cpp \
    Streams/IOStream.cpp \
    Utility/utility.cpp \
    App/applicationmanager.cpp \
    Gui/setup.cpp \
    Gui/modifyuser.cpp \
    Gui/mainwindow.cpp \
    Gui/showuser.cpp \
    Gui/showloan.cpp \
    Gui/publicationlist.cpp \
    Gui/showpublication.cpp \
    Gui/adminmainwindow.cpp \
    Gui/modifypublication.cpp \
    Gui/loanlist.cpp \
    Gui/userlist.cpp \
    Gui/makeloan.cpp

HEADERS  += \
    Lib/username.h \
    Lib/userinfo.h \
    Lib/account.h \
    Lib/publication.h \
    Lib/periodic.h \
    Lib/book.h \
    Lib/account_permission.h \
    Lib/publication_permission.h \
    Lib/loan.h \
    Lib/loans.h \
    Lib/users.h \
    Lib/library.h \
    Lib/dataCollector.h \
    Streams/IOStream.h \
    Utility/utility.h \
    App/applicationmanager.h \
    Gui/setup.h \
    Gui/modifyuser.h \
    Gui/mainwindow.h \
    Gui/showuser.h \
    Gui/showloan.h \
    Gui/publicationlist.h \
    Gui/showpublication.h \
    Gui/adminmainwindow.h \
    Gui/modifypublication.h \
    Gui/loanlist.h \
    Gui/userlist.h \
    Gui/makeloan.h

FORMS    += \
    Gui/setup.ui \
    Gui/modifyuser.ui \
    Gui/mainwindow.ui \
    Gui/showuser.ui \
    Gui/showloan.ui \
    Gui/publicationlist.ui \
    Gui/showpublication.ui \
    Gui/adminmainwindow.ui \
    Gui/modifypublication.ui \
    Gui/loanlist.ui \
    Gui/userlist.ui \
    Gui/makeloan.ui

RESOURCES += \
    Res/res.qrc

TRANSLATIONS += \
    Translation/it.ts \
    Translation/en.ts
