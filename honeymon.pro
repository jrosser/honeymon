CONFIG += serialport debug
QT += network

TARGET = honeymon
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    console.cpp \
    decoder.cpp \
    tempmodel.cpp \
    demandmodel.cpp \
    commandmodel.cpp \
    nodenames.cpp \
    logfile.cpp \
    setpointmodel.cpp \
    decodertab.cpp \
    prognownextmodel.cpp \
    unknown18model.cpp \
    unknowntab.cpp \
    unknown16model.cpp \
    temperaturestab.cpp \
    messagetab.cpp \
    messagemodel.cpp \
    parserbinary.cpp \
    parserfactory.cpp

HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    console.h \
    decoder.h \
    tempmodel.h \
    demandmodel.h \
    commandmodel.h \
    nodenames.h \
    logfile.h \
    setpointmodel.h \
    decodertab.h \
    prognownextmodel.h \
    unknown18model.h \
    unknowntab.h \
    unknown16model.h \
    temperaturestab.h \
    messagetab.h \
    messagemodel.h \
    parser.h \
    parserbinary.h \
    parserfactory.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    honeymon.qrc
