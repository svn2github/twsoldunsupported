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
MOC_DIR = .moc
UI_DIR = .ui
OBJECTS_DIR = .lib
RCC_DIR = .rcc
unix:TARGET = "./TheWheatSnooper/TheWheatSnooper"
win32:TARGET = "../TheWheatSnooper/TheWheatSnooper"
unix:DEFINES += QT_WS_X11
        #DEFINES +=WITH_GAMESURGE_SUPPORT
CONFIG += debug_and_release

# Input
HEADERS += src/wormnet/about.h \
    src/wormnet/awaybox.h \
    src/wormnet/buddylist.h \
    src/wormnet/buttonlayout.h \
    src/wormnet/charformatsettings.h \
    src/wormnet/chathandler.h \
    src/wormnet/chathandlerprv.h \
    src/wormnet/chatwindow.h \
    src/wormnet/ctcphandler.h \
    src/wormnet/ctcphandleratomic.h \
    src/wormnet/ctctphandlerwidget.h \
    src/wormnet/emoticonhandler.h \
    src/wormnet/hostbox.h \
    src/wormnet/hostmodel.h \
    src/wormnet/hostprvbox.h \
    src/wormnet/hoststruct.h \
    src/wormnet/inihandlerclass.h \
    src/wormnet/ircnet.h \
    src/wormnet/joinprvgame.h \
    src/wormnet/logbrowser.h \
    src/wormnet/maintoolbox.h \
    src/wormnet/mainwindow.h \
    src/wormnet/mytabwidget.h \
    src/wormnet/netcoupler.h \
    src/wormnet/playername.h \
    src/wormnet/settingswindow.h \
    src/wormnet/snoppanet.h \
    src/wormnet/snpsettings.h \
    src/wormnet/textschemehandler.h \
    src/wormnet/uihelper.h \
    src/wormnet/uploadedfileatomic.h \
    src/wormnet/usermodel.h \
    src/wormnet/userstruct.h \
    src/wormnet/volumeslider.h \
    src/wormnet/window.h \
    src/wormnet/global_macros.h \
    src/wormnet/singleton.h \
    src/wormnet/sound_handler.h \
    src/wormnet/global_functions.h \
    src/wormnet/combobox_wrapper.h \
    src/wormnet/balloon_handler.h \
    \
    src/irc/irc_ircnet.h \
    src/irc/irc_netcoupler.h \
    src/irc/irc_window.h \
    src/irc/irc_usermodel.h \
    src/irc/ircjoindia.h \
    src/irc/irc_chatwindow.h \
    src/wormnet/codecselectdia.h

FORMS += src/wormnet/about.ui \
    src/wormnet/awaybox.ui \
    src/wormnet/buddylist.ui \
    src/wormnet/buttonlayout.ui \
    src/wormnet/chatwindow.ui \
    src/wormnet/ctcphandleratomic.ui \
    src/wormnet/ctctphandlerwidget.ui \
    src/wormnet/emoticonhandler.ui \
    src/wormnet/filehistorylister.ui \
    src/wormnet/hostbox.ui \
    src/wormnet/hostprvbox.ui \
    src/wormnet/joinprvgame.ui \
    src/wormnet/logbrowser.ui \
    src/wormnet/maintoolbox.ui \
    src/wormnet/mainwindow.ui \
    src/wormnet/playername.ui \
    src/wormnet/settingswindow.ui \
    src/wormnet/textschemehandler.ui \
    src/wormnet/uploadedfileatomic.ui \
    src/wormnet/volumeslider.ui \
    src/wormnet/window.ui \
    src/wormnet/window2.ui \
    src/wormnet/window3.ui \
    src/wormnet/combobox_wrapper.ui \
    \
    src/irc/irc_window.ui \
    src/irc/ircjoindia.ui \
    src/irc/irc_chatwindow.ui \
    src/wormnet/codecselectdia.ui

SOURCES +=  src/wormnet/about.cpp \
    src/wormnet/awaybox.cpp \
    src/wormnet/buddylist.cpp \
    src/wormnet/buttonlayout.cpp \
    src/wormnet/charformatsettings.cpp \
    src/wormnet/chathandler.cpp \
    src/wormnet/chathandlerprv.cpp \
    src/wormnet/chatwindow.cpp \
    src/wormnet/ctcphandler.cpp \
    src/wormnet/ctcphandleratomic.cpp \
    src/wormnet/ctctphandlerwidget.cpp \
    src/wormnet/emoticonhandler.cpp \
    src/wormnet/hostbox.cpp \
    src/wormnet/hostmodel.cpp \
    src/wormnet/hostprvbox.cpp \
    src/wormnet/hoststruct.cpp \
    src/wormnet/inihandlerclass.cpp \
    src/wormnet/ircnet.cpp \
    src/wormnet/joinprvgame.cpp \
    src/wormnet/logbrowser.cpp \
    src/wormnet/main.cpp \
    src/wormnet/maintoolbox.cpp \
    src/wormnet/mainwindow.cpp \
    src/wormnet/mytabwidget.cpp \
    src/wormnet/netcoupler.cpp \
    src/wormnet/playername.cpp \
    src/wormnet/settingswindow.cpp \
    src/wormnet/snoppanet.cpp \
    src/wormnet/snpsettings.cpp \
    src/wormnet/textschemehandler.cpp \
    src/wormnet/uihelper.cpp \
    src/wormnet/uploadedfileatomic.cpp \
    src/wormnet/usermodel.cpp \
    src/wormnet/userstruct.cpp \
    src/wormnet/volumeslider.cpp \
    src/wormnet/window.cpp \   
    src/wormnet/sound_handler.cpp \
    src/wormnet/combobox_wrapper.cpp \
    src/wormnet/balloon_handler.cpp \
    \
    src/irc/irc_ircnet.cpp \
    src/irc/irc_netcoupler.cpp \
    src/irc/irc_window.cpp \
    src/irc/irc_usermodel.cpp \
    src/irc/ircjoindia.cpp \
    src/irc/irc_chatwindow.cpp \
    src/wormnet/codecselectdia.cpp

RC_FILE = src/wormnet/myapp.rc
TRANSLATIONS += translations/The_Wheat_Snooper_Romanian_by_MihaiS \
    translations/The_Wheat_Snooper_danish.ts \
    translations/The_Wheat_Snooper_german_by_lookias.ts \
    translations/The_Wheat_Snooper_portugues.ts \
    translations/The_Wheat_Snooper_spanish-(of_spain)_by_kosmos.ts \
    translations/The_Wheat_Snooper_untranslated.ts \
    translations/The_Wheat_Snooper_spanish-(of_spain)_by_kosmos.ts \
    translations/The_Wheat_Snooper_Russian_translation_by_StepS.ts \
    translations/The_Wheat_Snooper_french_by_LeTotalKiller.ts \
    translations/The_Wheat_Snooper_Spanish_by_eViL.ts
