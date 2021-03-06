#include "window.h"
#include"chatwindow.h"
#include<QHBoxLayout>
#include<QHeaderView>
#include<QFileDialog>
#include<QProcess>
#include<QKeyEvent>
#include<QItemSelectionModel>
#include<QItemSelection>
#include "snpsettings.h"
#include"mainwindow.h"
#include"chathandler.h"
#include"hostbox.h"
#include"hostprvbox.h"
#include"settingswindow.h"
#include"buttonlayout.h"
#include "sound_handler.h"
#include"global_functions.h"
#include<QDate>
#include<QScrollBar>
#include<QDebug>
QList<chatwindow*> window::chatwindows;
QStringList window::chatwindowstringlist;
QList< ::window*> window::hiddenchannelwindowshelper;
extern QStringList querylist;
window::window(netcoupler *n, QString s, int i) :
	currentchannel(s), chaticon("snppictures/Chat_Icon.png") {
    buttons = new buttonlayout;
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setObjectName("channelwindow");
    net = n;
    if (i == 1)
        ui1.setupUi(this);
    if (i == 2)
        ui2.setupUi(this);
    if (i == 3)
        ui3.setupUi(this);
    whichuiison = i;
    if (!singleton<snpsettings>().map["showchannelwindowbuttons"].toBool())
        buttons->hidebuttons();
    connect(buttons, SIGNAL(pbhostclicked()),this, SLOT(openhbox()));
    connect(buttons, SIGNAL(pbminimizedclicked()),this, SLOT(minimize()));
    connect(buttons, SIGNAL(sigchangealpha(int)),this, SLOT(changealpha(int)));
    connect(buttons, SIGNAL(sigshowme()),this, SLOT(showbuttons()));
    connect(buttons, SIGNAL(sigposteractivated()),this, SLOT(poster_activated()));
    ui.getchilds(this);
    QWidget *tempwidgetusers=new QWidget;
    QWidget *tempwidgethosts=new QWidget;
    QWidget *tempwidgetchat=new QWidget;
    tempwidgethosts->setObjectName("scrollareacorner");
    tempwidgetusers->setObjectName("scrollareacorner");
    tempwidgetchat->setObjectName("scrollareacorner");
    ui.users->setCornerWidget(tempwidgetusers);
    ui.hosts->setCornerWidget(tempwidgethosts);
    ui.chat->setCornerWidget(tempwidgetchat);

    ui.users->setAlternatingRowColors(1);
    ui.hosts->setAlternatingRowColors(1);
    ui.buttonlayout->addWidget(buttons);
    ui.msg->installEventFilter(this);
    ui.users->installEventFilter(this);
    connect(&net->users, SIGNAL(sigselectitem(const QModelIndex&,const QWidget*)),this, SLOT(setselection(const QModelIndex&,const QWidget*)));
    chat = new chathandler(this, ui.chat, currentchannel);
    connect(chat, SIGNAL(sigopenchatwindow(const QString&)),this, SLOT(openchatwindow(const QString&)));
    connect(ui.send, SIGNAL(clicked()),ui.msg, SIGNAL(returnPressed()));
    ui.users->setModel(&net->users);
    connect(ui.users->selectionModel(), SIGNAL(selectionChanged ( const QItemSelection&,const QItemSelection&)),this, SLOT(userselectionchanged(const QItemSelection&,const QItemSelection&)));
    ui.users->setEnabled(1);
    //ui.users->setSelectionMode(QAbstractItemView::NoSelection);
    ui.users->header()->swapSections(0, 1);
    ui.users->header()->swapSections(1, 2);
    ui.users->setColumnWidth(0, 180);
    ui.users->setColumnWidth(1, 22);
    ui.users->setColumnWidth(2, 48);
    ui.users->setColumnWidth(3, 48);
    ui.users->setColumnWidth(4, 120);
    ui.users->header()->setResizeMode(1, QHeaderView::Fixed);
    ui.users->header()->setResizeMode(2, QHeaderView::Fixed);

    ui.users->setSortingEnabled(1);
    ui.users->header()->setSortIndicator(0, Qt::AscendingOrder);
    ui.users->header()->setSortIndicator(1, Qt::AscendingOrder);
    ui.users->header()->setSortIndicator(2, Qt::AscendingOrder);
    ui.users->header()->setSortIndicator(3, Qt::AscendingOrder);
    ui.users->header()->setSortIndicatorShown(1);
    connect(ui.users->header(), SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)),&net->users, SLOT(sortslot(int, Qt::SortOrder)));

    ui.hosts->setModel(&net->hosts);
    ui.hosts->setEnabled(1);
    //ui.hosts->setSelectionMode(QAbstractItemView::NoSelection);
    ui.hosts->setSortingEnabled(1);
    ui.hosts->header()->swapSections(1, 3);
    ui.hosts->header()->swapSections(0, 2);
    ui.hosts->header()->setResizeMode(2, QHeaderView::Fixed);
    ui.hosts->header()->setResizeMode(3, QHeaderView::Fixed);
    ui.hosts->setColumnWidth(3, 16);
    ui.hosts->setColumnWidth(2, 22);
    ui.hosts->setColumnWidth(0, 190);
    ui.hosts->setColumnWidth(1, 120);
    ui.hosts->header()->setSortIndicatorShown(0);

    joinmenu2.setTitle(tr("Join"));
    hostmenu.addAction(tr("Host a game in ") + currentchannel);
    hostmenu.addAction(tr("Host a private game"));
    joinmenu.addMenu(&joinmenu2);
    usermenu.addAction(tr("Add this user to Buddylist."));
    usermenu.addAction(tr("Add this user to Ignorelist."));
    usermenu.addSeparator();
    usermenu.addAction(tr("Show info about this user."))->setIcon(chaticon);
    costumlistmenu.addAction(tr("Remove this user from the list."));
    costumlistmenu.addAction(tr("Show info about this user."))->setIcon(
            chaticon);

    connect(ui.users, SIGNAL(doubleClicked ( const QModelIndex &)),this, SLOT(useritemdblclicked(const QModelIndex&)));
    connect(ui.users, SIGNAL(pressed(const QModelIndex&)),this, SLOT(useritempressed(const QModelIndex&)));
    connect(ui.hosts, SIGNAL(pressed(const QModelIndex&)),this, SLOT(hostitempressed(const QModelIndex&)));
    connect(ui.hosts, SIGNAL(doubleClicked ( const QModelIndex &)),this, SLOT(hostitemdblclicked(const QModelIndex&)));

    connect(ui.msg, SIGNAL(returnPressed()),this, SLOT(sendmsg()));
    connect(net, SIGNAL(siggotmsg(const QString&,const QString&,const QString&)),this, SLOT(gotmsg(const QString&,const QString&,const QString&)));
    connect(net, SIGNAL(siggotnotice(const QString&,const QString&,const QString&)),this, SLOT(gotnotice(const QString&,const QString&,const QString&)));
    connect(net, SIGNAL(sigsettingswindowchanged()),this, SLOT(usesettingswindow()));

    net->refreshwho();

    connect(net, SIGNAL(siggotchanellist(QStringList)),this, SLOT(expandchannels(QStringList)));
    connect(net, SIGNAL(siggotchanellist(QStringList)),this, SLOT(getuserscount(QStringList)));
    linedittextlistcounter = 0;
    ui.msg->setFocus(Qt::MouseFocusReason);

    QVariantList windowstates = singleton<snpsettings>().map[this->currentchannel + ":"
                                                             + QString::number(this->whichuiison)].toList();
    if (!windowstates.isEmpty()) {
        if (!windowstates.isEmpty())
            this->restoreGeometry(windowstates.takeFirst().toByteArray());
        if (!windowstates.isEmpty())
            ui.splitter1->restoreState(windowstates.takeFirst().toByteArray());
        if (!windowstates.isEmpty())
            ui.splitter2->restoreState(windowstates.takeFirst().toByteArray());
        if (!windowstates.isEmpty())
            ui.users->header()->restoreState(
                    windowstates.takeFirst().toByteArray());
        if (!windowstates.isEmpty())
            ui.hosts->header()->restoreState(
                    windowstates.takeFirst().toByteArray());
    }
    usesettingswindow();
    this->windowtitlechannel = this->currentchannel;

}
void window::expandchannels() { //expand on startup
    expandchannels(QStringList());
}
void window::expandchannels(QStringList) { //expand on startup
    ui.hosts->setExpanded(net->hosts.indexbychannelname(currentchannel), 1);
    ui.users->setExpanded(net->users.indexbychannelname(currentchannel), 1);
    ui.users->setExpanded(net->users.indexbychannelname(usermodel::tr("Querys")), 1);
    if (singleton<settingswindow>().from_map("cbopenbuddylistonstartup").value<bool> ())
        ui.users->setExpanded(net->users.indexbychannelname(usermodel::tr(
                "Buddylist")), 1);
    if (ui.users->isExpanded(net->users.index(net->users.classes.indexOf(
            this->currentchannel), 0)) && ui.hosts->isExpanded(
                    net->hosts.index(net->hosts.classes.indexOf(this->currentchannel),
                                     0))) {
        disconnect(net, SIGNAL(siggotchanellist(QStringList)),this, SLOT(expandchannels(QStringList)));
    } else
        QTimer::singleShot(500, this, SLOT(expandchannels()));
}
void window::setselection(const QModelIndex &index, const QWidget *w) {
    if (w == this) {
        if (!index.isValid())
            ui.users->clearSelection();
        else {
            ui.users->clearSelection();
            ui.users->selectionModel()->select(index, QItemSelectionModel::Rows
                                               | QItemSelectionModel::Select);
        }
    }
}
void window::userselectionchanged(const QItemSelection &selected,
                                  const QItemSelection&) {

    if (!selected.indexes().isEmpty())
        net->users.selectionchanged(selected.indexes().first(), this);
}
bool window::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui.msg) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*> (event);
            Q_ASSERT(keyEvent!=0);
            if (keyEvent->key() == Qt::Key_Up) {
                if (linedittextlistcounter > 0) {
                    if (linedittextlistcounter == linedittextlist.size()
                        && ui.msg->text() != "") {
                        linedittextlist << ui.msg->text();
                    }
                    ui.msg->setText(linedittextlist[--linedittextlistcounter]);
                }
                return true;
            } else if (keyEvent->key() == Qt::Key_Down) {
                if (linedittextlistcounter < linedittextlist.size() - 1)
                    ui.msg->setText(linedittextlist[++linedittextlistcounter]);
                else if (linedittextlistcounter == linedittextlist.size() - 1) {
                    ui.msg->setText("");
                    linedittextlistcounter = linedittextlist.size();
                }
                return true;
            }
        }
    }
    if (obj == ui.users) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*> (event);
            Q_ASSERT(keyEvent!=0);
            if (keyEvent->key() == Qt::Key_Return) {
                QString s = net->users.data(ui.users->currentIndex().sibling(
                        ui.users->currentIndex().row(), 0)).value<QString> ();
                if (s != "")
                    this->openchatwindow(s);
                return true;
            } else if (keyEvent->key() == Qt::Key_Space) {
                QString s = net->users.data(ui.users->currentIndex().sibling(
                        ui.users->currentIndex().row(), 0)).value<QString> ();
                ui.msg->insert(s + " ");
                ui.msg->setFocus(Qt::MouseFocusReason);
                return true;
            }

        }
    }
    return QObject::eventFilter(obj, event);
}
void window::gotmsg(const QString &user, const QString &receiver,
                    const QString &msg) {
    if (!acceptignorys) {
        if (!containsCI(singleton<snpsettings>().map["ignorelist"].value<QStringList> (), user)) {
            if (compareCI(receiver, currentchannel)) {
                chat->append(user, receiver, msg);
            }
        }
    } else {
        if (compareCI(receiver, currentchannel))
            chat->append(user, receiver, msg);
    }

}
void window::gotnotice(const QString &user, const QString &receiver,
                       const QString &msg) {

    if (!containsCI(singleton<snpsettings>().map["ignorelist"].value<QStringList> (), user)) {
        if (containsCI(net->channellist, receiver)) { //notice from user to a channel
            if (compareCI(receiver, currentchannel))
                chat->appendnotice(user, receiver, msg); //only one channel will get the notice
        } else { //notice from user to yourself
            chat->appendnotice(user, receiver, msg);
        }
        if (alertonnotice) {
            QApplication::alert(this);
            emit sigalert(this);
        }
    }
}
void window::gotprvmsg(const QString &user, const QString &receiver,
                       const QString &msg) {
    if (!containsCI(chatwindowstringlist, user)) {
        if (!net->users.usermap[usermodel::tr("Ignorelist")].count(
                userstruct::whoami(user)) && !net->users.usermap[usermodel::tr(
                        "Buddylist")].count(userstruct::whoami(user))) {
            if (!containsCI(querylist, user))
                querylist << user;
            chat->append(user, receiver, msg);
            if (alertonprivmsg) {
                QApplication::alert(this);
                emit sigalert(this);
            }
            singleton<sound_handler>().play_normalmsgsound(user);                                        ;
        }
    }
}
void window::gotdebugmsg(const QString &msg) {
    chat->appenddebug(msg.simplified());
}
void window::gotgarbagejoin(const QString &user, const QString &msg) {
    chat->appendjoingarbage(user + "> " + msg);
}
void window::gotgarbagepart(const QString &user, const QString &msg) {
    chat->appendpartgarbage(user + "> " + msg);
}
void window::gotgarbagequit(const QString &user, const QString &msg) {
    chat->appendquitgarbage(user + "> " + msg);
}
void window::sendmsg(QString msg){
    QString s;
    if(msg==QString())
        s = ui.msg->text();
    else
        s=msg;
    linedittextlist << s;
    linedittextlistcounter = linedittextlist.size();
    if (s != "") {
        if (s.startsWith(">!")) {
            net->sendrawcommand(QString("PRIVMSG ") + currentchannel + " :\001"
                                + s.remove(0, 2) + " \001");
            chat->append(net->nick, currentchannel, "\001" + s + "\001");
        } else if (s.startsWith("/")) {
            net->sendrawcommand(s.remove(0, 1));
            chat->append(net->nick, currentchannel, s);
        } else if (s.startsWith(">>>")) {
            sendnoticeaction();
            chat->append(net->nick, currentchannel, s);
        } else if (s.startsWith(">>")) {
            sendnotice();
            chat->append(net->nick, currentchannel, s);
        } else if (s.startsWith(">")) {
            net->sendrawcommand(QString("PRIVMSG ") + currentchannel
                                + " :\001ACTION " + s.remove(0, 1).remove("\n") + " \001");
            chat->append(net->nick, currentchannel, "\001ACTION " + s + " \001");
        } else {
            net->sendmessage(currentchannel, s);
            chat->append(net->nick, currentchannel, s);
        }
        ui.msg->clear();
    }
}
void window::sendnotice() {
    const QString s = ui.msg->text().remove(0, 2);
    if (s != "") {
        net->sendnotice(currentchannel, s);
        gotnotice(net->nick, this->currentchannel, s);
        ui.msg->clear();
    }
}
void window::sendnoticeaction() {
    const QString s = ui.msg->text().remove(0, 3).remove("\n");
    if (s != "") {
        net->sendrawcommand(QString("NOTICE ") + this->currentchannel
                            + " :\001ACTION " + s + " \001");
        gotnotice(net->nick, currentchannel, "<" + s + ">");
        ui.msg->clear();
    }
}
void window::closeEvent(QCloseEvent * /*event*/) {
}
void window::useritempressed(const QModelIndex &index) {
    if (!index.isValid())
        return;
    if (QApplication::mouseButtons() != Qt::RightButton)
        return;
    QAction *a;
    QMenu menu;
    QString user = net->users.data(index.sibling(index.row(), 0),
                                   Qt::DisplayRole).value<QString> ();
    if (index.internalId() == 999) {
        if(net->users.data(index.sibling(index.row(), 0)).value<QString> ()==usermodel::tr("Querys")){
            menu.addAction(tr("Remove Querys"));
            a = menu.exec(QCursor::pos());
            if(a)
                querylist.clear();
        }
    } else if (index.column() == 3) {
        QStringList sl = singleton<snpsettings>().map["dissallowedclannames"].value<
                         QStringList> ();
        if (sl.contains(
                net->users.getuserstructbyindex(index).nickfromclient))
            menu.addAction(tr("Allow this clanname."));
        else
            menu.addAction(tr("Dissallow this clanname."));
        a = menu.exec(QCursor::pos());
        if (a) {
            if (a->text() == tr("Allow this clanname.")) {
                sl.removeAll(
                        net->users.getuserstructbyindex(index).nickfromclient);
            } else {
                sl
                        << net->users.getuserstructbyindex(index).nickfromclient;
            }
            singleton<snpsettings>().map["dissallowedclannames"].setValue<QStringList> (
                    sl);
            singleton<snpsettings>().safe();
        }
    } else if (net->users.classes[index.internalId()] == usermodel::tr(
            "Querys")) {
        QAction *a;
        QMenu menu;
        menu.addAction(tr("Remove this Query."));
        menu.addSeparator();
        menu.addAction(tr("Show info about this user."))->setIcon(
                chaticon);
        a = menu.exec(QCursor::pos());
        if (a) {
            if (a->text() == tr("Remove this Query.")) {
                querylist.removeAll(user);
            } else if (a->text() == tr("Show info about this user.")) {
                getuserinfo(user);
            }
        }
    } else if (net->users.classes[index.internalId()] != usermodel::tr(
            "Buddylist") && net->users.classes[index.internalId()]
               != usermodel::tr("Ignorelist")) {
        QAction *a;
        QMenu menu;
        if (containsCI(singleton<snpsettings>().map["buddylist"].value<QStringList> (),
                       user)) {
            menu.addAction(tr("Remove this user from Buddylist."));
            menu.addSeparator();
            menu.addAction(tr("Show info about this user."))->setIcon(
                    chaticon);
            a = menu.exec(QCursor::pos());
        } else if (containsCI(singleton<snpsettings>().map["ignorelist"].value<
                              QStringList> (), user)) {
            menu.addAction(tr("Remove this user from Ignorelist."));
            menu.addSeparator();
            menu.addAction(tr("Show info about this user."))->setIcon(
                    chaticon);
            a = menu.exec(QCursor::pos());
        } else
            a = usermenu.exec(QCursor::pos());
        if (a) {
            if (a->text() == tr("Add this user to Buddylist.")) {
                net->users.addbuddy(user);
            } else if (a->text() == tr("Add this user to Ignorelist.")) {
                net->users.addignore(user);
            } else if (a->text() == tr("Show info about this user.")) {
                getuserinfo(user);
            } else if (a->text() == tr(
                    "Remove this user from Buddylist.")) {
                net->users.deletebuddy(user);
            } else if (a->text() == tr(
                    "Remove this user from Ignorelist.")) {
                net->users.deleteignore(user);
            }
        } else
            return;
    } else if (net->users.classes[index.internalId()] == usermodel::tr(
            "Buddylist")) {
        QAction *a = costumlistmenu.exec(QCursor::pos());
        if (a) {
            if (a->text() == tr("Remove this user from the list.")) {
                net->users.deletebuddy(user);
            } else if (a->text() == tr("Show info about this user.")) {
                getuserinfo(user);
            }
        }
    } else if (net->users.classes[index.internalId()] == usermodel::tr(
            "Ignorelist")) {
        QAction *a = costumlistmenu.exec(QCursor::pos());
        if (a) {
            if (a->text() == tr("Remove this user from the list.")) {
                net->users.deleteignore(user);
            } else if (a->text() == tr("Show info about this user.")) {
                getuserinfo(user);
            }
        }
    }
}
void window::useritemdblclicked(const QModelIndex &index) {

    if (index.internalId() != 999 && net->users.classes[index.internalId()]
        != usermodel::tr("Ignorelist")) {
        QString s = net->users.data(index.sibling(index.row(), 0),
                                    Qt::DisplayRole).value<QString> ();
        openchatwindow(s);
    } else if (index.internalId() == 999) {
        emit sigjoinchannel(
                net->users.data(index.sibling(index.row(), 0)).value<QString> ());
    }
}
void window::hostitemdblclicked(const QModelIndex &index) {
    if (index.internalId() != 999) {
        QString hostinfo = " \"" + net->hosts.joininfo(index) + "&scheme="
                           + net->schememap[currentchannel] + "\"";
        QString gamename = net->hosts.gamename(index);
        net->joingame(hostinfo, currentchannel, gamename);
    } else if (index.internalId() == 999) {
        hbox = new hostbox(currentchannel);
        hbox->show();
        connect(hbox, SIGNAL(sigok()),this, SLOT(hboxok()));
    }
}
void window::getuserinfo(const QString &s) {
    foreach(QString chat,chatwindowstringlist) {
        if (compareCI(chat, s)) {
            foreach(chatwindow *c,chatwindows) {
                if (compareCI(chat, c->chatpartner)) {
                    c->getgamerwho();
                    return;
                }
            }
        }
    }
    openchatwindow(s);
    chatwindows.last()->getgamerwho();
}
void window::openchatwindow(const QString &s) {
    Q_ASSERT(s!="");
    if (containsCI(chatwindowstringlist, s)){
        foreach(chatwindow *w,chatwindows){
            if(w->chatpartner==s && w->isHidden())
                w->show();
            if(w->chatpartner==s){
                w->raise();
                qApp->setActiveWindow(w);
            }
            mainwindow::hiddenchatwindowshelper.removeAll(w);
            querylist.removeAll(s);
        }
        return;
    }emit sigopenchatwindow(s);
QApplication::processEvents();
/*chatwindowstringlist << s;
	 chatwindows.push_back(new chatwindow(net, s));
	 connect(chatwindows.last(), SIGNAL(closed()),this, SLOT(chatwinowclosed()));
	 chatwindows.last()->show();*/
}
void window::hostitempressed(const QModelIndex &index) {
    if (QApplication::mouseButtons() == Qt::RightButton) {
        QString hostinfo = " \"" + net->hosts.joininfo(index) + "&scheme="
                           + net->schememap[currentchannel] + "\"";
        QString gamename = net->hosts.gamename(index);
        if (index.internalId() == 999) {
            QAction *a = hostmenu.exec((QCursor::pos()));
            if (a != 0) {
                if (a->text() == tr("Host a private game")) {
                    hprvbox = new hostprvbox;
                    hprvbox->show();
                    connect(hprvbox, SIGNAL(sigok(const QString&)),this, SLOT(hboxprvok(const QString&)));
                } else {
                    openhbox();
                }
            }
        } else {
            getjoinmenu();
            QAction *a = joinmenu.exec(QCursor::pos());
            if (a != 0) {
                if (a->text() == tr("Choose a Program to join this game.")) {
                    QStringList sl = singleton<snpsettings>().map.value("joinstrings").value<
                                     QStringList> ();
#ifdef Q_WS_WIN
                    QString file = QFileDialog::getOpenFileName(this, tr("Choose a Program."), "c:/", "*.exe *.com");
#endif
#ifdef Q_WS_X11
                    QString file = QFileDialog::getOpenFileName(this, tr(
                            "Choose a Desktopicon."), "/home", "*.desktop");
#endif
                    if (!sl.contains(file) && file != "") {
                        sl.insert(0, file);
                        singleton<snpsettings>().map["joinstrings"] = sl;
                        joinmenu2.clear();
                        foreach(QString s,singleton<snpsettings>().map.value("joinstrings").value<QStringList>()) {
                            joinmenu2.addAction(s);
                        }
                        joinmenu2.addAction(tr(
                                "Choose a Program to join this game."));
                        singleton<snpsettings>().safe();
                    } else if (sl.contains(file) && file != "") {
                        sl.move(sl.indexOf(file), 0);
                        singleton<snpsettings>().map["joinstrings"] = sl;
                        singleton<snpsettings>().safe();
                    }
                    QFile f(file);
                    if (f.open(QFile::ReadOnly)) {
                        QTextStream ts(&f);
                        QString s = ts.readLine();
                        while (!s.startsWith("Exec=") && !ts.atEnd())
                            QString s = ts.readLine();
                        qDebug() << s;
                    }
                } else {
                    QStringList sl = singleton<snpsettings>().map["joinstrings"].value<
                                     QStringList> ();
                    sl.move(sl.indexOf(a->text()), 0);
                    singleton<snpsettings>().map["joinstrings"] = sl;
                    net->joingame(hostinfo, currentchannel, gamename);
                }
            }
        }
    }
}
void window::hboxok() {
    QString flag;
    foreach(userstruct u,net->users.users) {
        if (u.nick == net->nick) {
            flag = QString::number(u.flag);
        }
    }
    net->createhost(hbox->gamename, hbox->pwd, currentchannel, flag);
}
void window::hboxprvok(const QString &scheme) {
    net->createprvhost(currentchannel, scheme);
}
void window::usesettingswindow(const QString &s) {
    if (s == "cbalertmeonnotice" || s == "")
        alertonnotice = singleton<settingswindow>().from_map("cbalertmeonnotice").value<bool> ();
    if (s == "cbalertfromnormal" || s == "")
        alertonprivmsg
                = singleton<settingswindow>().from_map("cbalertfromnormal").value<bool> ();
    if (s == "cbignorysappearinchannel" || s == "")
        acceptignorys = singleton<settingswindow>().from_map("cbignorysappearinchannel").value<
                        bool> ();
    disconnect(net, SIGNAL(sigusergarbagejoin(const QString&,const QString&)),this, SLOT(gotgarbagejoin(const QString&,const QString&)));
    disconnect(net, SIGNAL(sigusergarbagepart(const QString&,const QString&)),this, SLOT(gotgarbagepart(const QString&,const QString&)));
    disconnect(net, SIGNAL(sigusergarbagequit(const QString&,const QString&)),this, SLOT(gotgarbagequit(const QString&,const QString&)));
    if (s == "chbjoininfo" || s == "") {
        if (singleton<settingswindow>().from_map("chbjoininfo").value<bool> ())
            connect(net, SIGNAL(sigusergarbagejoin(const QString&,const QString&)),this, SLOT(gotgarbagejoin(const QString&,const QString&)));
    }
    if (s == "chbpartinfo" || s == "") {
        if (singleton<settingswindow>().from_map("chbpartinfo").value<bool> ())
            connect(net, SIGNAL(sigusergarbagepart(const QString&,const QString&)),this, SLOT(gotgarbagepart(const QString&,const QString&)));
    }
    if (s == "chbquitinfo" || s == "") {
        if (singleton<settingswindow>().from_map("chbquitinfo").value<bool> ())
            connect(net, SIGNAL(sigusergarbagequit(const QString&,const QString&)),this, SLOT(gotgarbagequit(const QString&,const QString&)));
    }

}
void window::getjoinmenu() {
    joinmenu2.clear();
    if (!singleton<snpsettings>().map.value("joinstrings").value<QStringList> ().isEmpty()) {
        foreach(QString s,singleton<snpsettings>().map.value("joinstrings").value<QStringList>()) {
            joinmenu2.addAction(s);
        }
    }
    joinmenu2.addAction(tr("Choose a Program to join this game."));
}
void window::openhbox() {
    hbox = new hostbox(currentchannel);
    hbox->show();
    connect(hbox, SIGNAL(sigok()),this, SLOT(hboxok()));
}
void window::minimize() {
    if (!hiddenchannelwindowshelper.contains(this))
        this->hiddenchannelwindowshelper.push_back(this);
    this->hide();
}
void window::changealpha(int i) {
    singleton<snpsettings>().map["channeltransparency"] = i;
    if (i == 100)
        this->setWindowOpacity(1);
    else
        this->setWindowOpacity((double) i / 100);
    singleton<snpsettings>().safe();
}
void window::showbuttons() {
    ui.buttonlayout->addWidget(buttons);
}
void window::mysetwindowtitle() {
    this->setWindowTitle(windowtitlechannel + " " + windowtitletime + " " + tr(
            "Users online") + windowtitleaway.simplified());
}
void window::getuserscount(QStringList sl) {
    QString s;
    foreach(QString str,sl) {
        if (str.contains(this->currentchannel))
            s = str;
    }
    sl = s.split(" ", QString::SkipEmptyParts);
    if (sl.size() > 1) {
        this->windowtitletime = sl[1];
    }
    this->mysetwindowtitle();
}
void window::poster_activated(){
    sendmsg(singleton<snpsettings>().map["automatic_posts"].toString());
}
window::~window() {
    ui.buttonlayout->removeWidget(buttons);
    buttons->setParent(0);
    singleton<snpsettings>().map[this->currentchannel + ":" + QString::number(this->whichuiison)];
    QVariantList windowstates;
    windowstates << this->saveGeometry();
    windowstates << ui.splitter1->saveState();
    windowstates << ui.splitter2->saveState();
    windowstates << ui.users->header()->saveState();
    windowstates << ui.hosts->header()->saveState();

    singleton<snpsettings>().map[this->currentchannel + ":" + QString::number(this->whichuiison)]
            = windowstates;
    if(net!=0)
        net->partchannel(currentchannel);
    QString s = currentchannel;
    bool b = containsCI(net->hosts.hostmap.keys(), s);
    if(net!=0)
        net->hosts.sethoststruct(QList<hoststruct> (), s);emit
                sigwindowclosed(currentchannel);
    disconnect();
    hiddenchannelwindowshelper.removeAll(this);
}
