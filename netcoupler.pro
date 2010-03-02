# #####################################################################
# Automatically generated by qmake (2.01a) Mo. Aug 10 14:20:17 2009
# #####################################################################
TEMPLATE = app
TARGET = 
QT += gui \
    network \
    svg \
    phonon
DEPENDPATH += . \
    qfileupload \
    translations
INCLUDEPATH += . \
    qfileupload
MOC_DIR = ./moc
UI_DIR = ./UIC
OBJECTS_DIR = ./O
unix:TARGET = "./The Wheat Snooper/The Wheat Snooper"
win32:TARGET = "./The Wheat Snooper/The Wheat Snooper.exe"

# Input
HEADERS += about.h \
    awaybox.h \
    buddylist.h \
    buttonlayout.h \
    charformatsettings.h \
    chathandler.h \
    chathandlerprv.h \
    chatwindow.h \
    ctcphandler.h \
    ctcphandleratomic.h \
    ctctphandlerwidget.h \
    emoticonhandler.h \
    filehistorylister.h \
    hostbox.h \
    hostmodel.h \
    hostprvbox.h \
    hoststruct.h \
    inihandlerclass.h \
    initextbrowser.h \
    ircnet.h \
    joinprvgame.h \
    logbrowser.h \
    maintoolbox.h \
    mainwindow.h \
    mytabwidget.h \
    netcoupler.h \
    playername.h \
    settingswindow.h \
    snoppanet.h \
    snpsettings.h \
    textschemehandler.h \
    uihelper.h \
    uploadedfileatomic.h \
    usermodel.h \
    userstruct.h \
    volumeslider.h \
    window.h \
    qfileupload/config.h \
    qfileupload/dropwidget.h \
    qfileupload/qmainwindow.h \
    global_macros.h \
    singleton.h \
    sound_handler.h \
    global_functions.h \
    combobox_wrapper.h \
    balloon_handler.h
FORMS += about.ui \
    awaybox.ui \
    buddylist.ui \
    buttonlayout.ui \
    chatwindow.ui \
    ctcphandleratomic.ui \
    ctctphandlerwidget.ui \
    emoticonhandler.ui \
    filehistorylister.ui \
    hostbox.ui \
    hostprvbox.ui \
    initextbrowser.ui \
    joinprvgame.ui \
    logbrowser.ui \
    maintoolbox.ui \
    mainwindow.ui \
    playername.ui \
    settingswindow.ui \
    textschemehandler.ui \
    uploadedfileatomic.ui \
    volumeslider.ui \
    window.ui \
    window2.ui \
    window3.ui \
    qfileupload/config.ui \
    qfileupload/qmainwindow.ui \
    combobox_wrapper.ui
SOURCES += about.cpp \
    awaybox.cpp \
    buddylist.cpp \
    buttonlayout.cpp \
    charformatsettings.cpp \
    chathandler.cpp \
    chathandlerprv.cpp \
    chatwindow.cpp \
    ctcphandler.cpp \
    ctcphandleratomic.cpp \
    ctctphandlerwidget.cpp \
    emoticonhandler.cpp \
    filehistorylister.cpp \
    hostbox.cpp \
    hostmodel.cpp \
    hostprvbox.cpp \
    hoststruct.cpp \
    inihandlerclass.cpp \
    initextbrowser.cpp \
    ircnet.cpp \
    joinprvgame.cpp \
    logbrowser.cpp \
    main.cpp \
    maintoolbox.cpp \
    mainwindow.cpp \
    mytabwidget.cpp \
    netcoupler.cpp \
    playername.cpp \
    settingswindow.cpp \
    snoppanet.cpp \
    snpsettings.cpp \
    textschemehandler.cpp \
    uihelper.cpp \
    uploadedfileatomic.cpp \
    usermodel.cpp \
    userstruct.cpp \
    volumeslider.cpp \
    window.cpp \
    qfileupload/config.cpp \
    qfileupload/dropwidget.cpp \
    qfileupload/qmainwindow.cpp \
    sound_handler.cpp \
    combobox_wrapper.cpp \
    balloon_handler.cpp
RESOURCES += qfileupload/qfileupload.qrc
RC_FILE = myapp.rc
TRANSLATIONS += translations/Romanian_translation_The_Wheat_Snooper_by_MihaiS.ts \
    translations/The_Wheat_Snooper_danish.ts \
    translations/The_Wheat_Snooper_german_by_lookias.ts \
    translations/The_Wheat_Snooper_international_spanish.ts \
    translations/The_Wheat_Snooper_portugues.ts \
    translations/The_Wheat_Snooper_spanish-(of_spain)_by_kosmos.ts \
    translations/The_Wheat_Snooper_untranslated.ts \
    translations/The_Wheat_Snooper_spanish-(of_spain)_by_kosmos.ts
