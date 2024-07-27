QT += core gui widgets

QT += sql
LIBS += -lUser32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dayimagelist.cpp \
    dbdaylisttablemanager.cpp \
    dbimagetablemanager.cpp \
    dbrandomlisttablemanager.cpp \
    dbtablescreator.cpp \
    dbweeklisttablemanager.cpp \
    dialogwindowlistofimage.cpp \
    imageloader.cpp \
    imageslist.cpp \
    interfaceaddition.cpp \
    main.cpp \
    mainwindow.cpp \
    randomimagelist.cpp \
    scrollareamanager.cpp \
    sqlitedbmanager.cpp \
    standarttab.cpp \
    style.cpp \
    timetab.cpp \
    timetabdaylistwidget.cpp \
    timetabrandomlistwidget.cpp \
    timetabweeklistwidget.cpp \
    uielementfactory.cpp \
    weekimagelist.cpp \
    wlapperimage.cpp \
    wlappersetter.cpp \
    wsexeptions.cpp

HEADERS += \
    dayimagelist.h \
    dbdaylisttablemanager.h \
    dbimagetablemanager.h \
    dbmanager.h \
    dbrandomlisttablemanager.h \
    dbtablescreator.h \
    dbweeklisttablemanager.h \
    dialogwindowlistofimage.h \
    imageloader.h \
    imageslist.h \
    interfaceaddition.h \
    mainwindow.h \
    randomimagelist.h \
    scrollareamanager.h \
    sqlitedbmanager.h \
    standarttab.h \
    style.h \
    timetab.h \
    timetabdaylistwidget.h \
    timetabrandomlistwidget.h \
    timetabweeklistwidget.h \
    uielementfactory.h \
    weekimagelist.h \
    wlapperimage.h \
    wlappersetter.h \
    wsexeptions.h

FORMS += \
    dialogwindowlistofimage.ui \
    mainwindow.ui \
    standarttab.ui \
    timetab.ui \
    timetabdaylistwidget.ui \
    timetabrandomlistwidget.ui \
    timetabweeklistwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
