#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"ui_mainwindow.h"
#include"maintoolbox.h"
#include"qobjectwrapper.h"

#include <QtGui/QWidget>
#include<QList>
#include<QSystemTrayIcon>

class window;
class netcoupler;
class chatwindow;
class QMenu;
class mainwindow : public QWidget
{
    Q_OBJECT

public:      
    void appenddebugmessage(const QString &);
    QString debugmsg;    
    QList< ::window * > windowlist;
    QList< ::chatwindow*> hiddenchatwindowshelper;
    void fillsnpsettings();
    void quit();

    static QString toString(){
        return "mainwindow";
    }

public slots:
    void returntologintab();

private:
    mainwindow();
    ~mainwindow();
    typedef ::window channelwindow;
    Ui::mainwindowClass ui;
    //QList<chatwindow* > chatwindows;
    QStringList currentchannellist;	//TODO: dont forget to clear this lists on ------void returntotabsettings(int);
    QStringList channellist;    

    QMenu *traymenu;
    QMenu *joinmenu;
    QMenu *layoutmenu;
    QMenu *stylemenu;
    QMenu *stuffmenu;
    QMenu *textschememenu;
    QMenu *languagemenu;
    QMenu *arrangementmenu;

    int whichuitype;
    bool joinonstartup;

    QRegExpValidator *validator;

    void setlanguage(const QString&);
    void init_menus();
    void get_baseStyleSheet();
    void handleAwayBox();
    QString baseStyleSheet;

    void joinGameSourge();    

    void connectToNetwork();
    void setleague();
    QStringList lastOpenedWindows;
    QStringList lastOpenedChatWindows;

private slots:    
    void on_cbleagueservers_activated(QString );
    void on_pbeditleagueprofile_clicked();
    void on_cbenabletus_toggled(bool checked);
    void on_pbjoin_clicked();
    void join(const QString channel);
    void openchatwindow(const QString &);
    void on_pbabout_clicked();
    void on_pbsettings_clicked();
    void getchannellist(const QStringList &);   
    void chooseclicked();        
    void trayactivation(QSystemTrayIcon::ActivationReason);
    void traymenutriggered(QAction *);
    void pbrememberjoinclicked();

    void snpsetcontains(const QString&);

    void windowremoved(const QString&);
    void usesettingswindow(const QString &s="");

    void chatwinowclosed();    

    void awayboxok();
    void awaymessagechanged();

    void gotctcpsignal(const QString&,const QString&);

    void settextscheme(const QString&);

    void openchatwindowhidden(const QString &);
    void gotprvmsg(const QString &user, const QString &receiver,const QString &msg);
    void connected();
    void disconnected();
    void reconnect();

    void reopenChatWindowsAndChannelWindows();

    void leagueserverconnectionfailed();
    void leagueserverconnectionsuccess();

    void currenttabchanged(int);

    void leagueserverprofilepage(QString);    

protected:
    void changeEvent (QEvent*);
    void closeEvent ( QCloseEvent * event );    
signals:
    void sigopenchatwindow(const QString&);

    friend class qobjectwrapper<mainwindow>;
};

#endif // MAINWINDOW_H
