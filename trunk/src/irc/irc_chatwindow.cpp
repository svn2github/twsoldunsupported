//#include "irc_chatwindow.h"
//#include"irc_netcoupler.h"
//#include"src/wormnet/snpsettings.h"
//#include"src/wormnet/settingswindow.h"
//#include"src/wormnet/chathandlerprv.h"
//#include"src/wormnet/ctcphandler.h"
//#include"src/wormnet/sound_handler.h"
//#include"src/wormnet/global_functions.h"
//#include<QKeyEvent>
//#include<QDir>
//#include<QTime>
//#include<QFileDialog>
//#include<QStatusBar>
//#include<QMessageBox>
//#include<QDesktopWidget>
//extern QStringList querylist;
//extern QMap<QString, QStringList> usergarbagemap;
//irc_chatwindow::irc_chatwindow(irc_netcoupler *n, const QString &s, QWidget *parent) :
//	QWidget(parent), chatpartner(s), net(n) {
//    this->setAttribute(Qt::WA_DeleteOnClose);
//    this->setObjectName("irc_chatwindow");
//    ui.setupUi(this);
//    ui.pbbuddy->setObjectName("chatwindowbutton");
//    ui.pbctcp->setObjectName("chatwindowbutton");
//    ui.pbidle->setObjectName("chatwindowbutton");
//    ui.pblog->setObjectName("chatwindowbutton");
//    ui.pbmute->setObjectName("chatwindowbutton");
//    ui.pbfilter->setObjectName("chatwindowbutton");
//    ui.lineEdit->installEventFilter(this);
//    ui.chatwindowbuttonscrollArea->installEventFilter(this);
//    this->update();
//    chat = new chathandlerprv(this, ui.chat, chatpartner);
//    foreach(QString s,usergarbagemap[chatpartner.toLower()]) {
//        chat->appendgarbage(s);
//    }
//    this->setWindowTitle(tr("Chat with") + " " + s);

//    if (containsCI(singleton<snpsettings>().map["buddylist"].value<QStringList> (), chatpartner))
//        this->setWindowIcon(QIcon("snppictures/buddyicon.png"));
//    else if (containsCI(singleton<snpsettings>().map["ignorelist"].value<QStringList> (),
//			chatpartner))
//        this->setWindowIcon(QIcon("snppictures/ignoreicon.png"));
//    else
//        this->setWindowIcon(QIcon("snppictures/usericon.png"));

//    connect(ui.send, SIGNAL(clicked()),ui.lineEdit, SIGNAL(returnPressed()));
//    connect(ui.lineEdit, SIGNAL(returnPressed()),this, SLOT(sendmsg()));
//    connect(net, SIGNAL(sigusergarbage(const QString&,const QString&)),this, SLOT(garbagemapchanged(const QString&,const QString&)));
//    ui.lineEdit->setFocus(Qt::MouseFocusReason);

//    if (containsCI(querylist, chatpartner)) { //best place to clean the querylist
//        querylist.removeAll(chatpartner);
//    }
//    usesettingswindow();
//    connect(net, SIGNAL(sigsettingswindowchanged()),this, SLOT(usesettingswindow()));

//    singleton<sound_handler>().play_chatwindowopensound();
//    if (net->mutedusers.contains(this->chatpartner, Qt::CaseInsensitive))
//        ui.pbmute->setIcon(QIcon("snppictures/buttons/nomutebutton.png"));
//    else
//        ui.pbmute->setIcon(QIcon("snppictures/buttons/mutebutton.png"));
//    if (singleton<snpsettings>().map["buddylist"].value<QStringList> ().contains(
//            this->chatpartner, Qt::CaseInsensitive))
//        ui.pbbuddy->setIcon(QIcon("snppictures/buttons/normal.png"));
//    else
//        ui.pbbuddy->setIcon(QIcon("snppictures/buttons/buddy.png"));

//    ui.pblog->setIcon(QIcon("snppictures/buttons/log.png"));
//    ui.pbidle->setIcon(QIcon("snppictures/buttons/idle.png"));
//    ui.pbctcp->setIcon(QIcon("snppictures/buttons/ctcp.png"));
//    ui.pbfilter->setIcon(QIcon("snppictures/buttons/filter.png"));
//    ui.pbsmileys->setIcon(QIcon("snppictures/buttons/smileys.png"));
//    ui.pbresize->setIcon(QIcon("snppictures/buttons/resize.png"));
//    ui.buttonlayout->setAlignment(Qt::AlignLeft);
//    connect(ui.pbmute, SIGNAL(clicked()),this, SLOT(pbmuteclicked()));
//    connect(ui.pbbuddy, SIGNAL(clicked()),this, SLOT(pbbuddyclicked()));
//    connect(ui.pblog, SIGNAL(clicked()),this, SLOT(pblogclicked()));
//    connect(ui.pbidle, SIGNAL(clicked()),this, SLOT(pbidleclicked()));
//    connect(ui.pbctcp, SIGNAL(clicked()),this, SLOT(pbctcpclicked()));
//    connect(ui.pbfilter, SIGNAL(clicked()),this, SLOT(filtergarbage()));
//    connect(ui.pbsmileys, SIGNAL(clicked()),chat->emot, SLOT(show()));

//    connect(net, SIGNAL(siggotidletime(const QString&, int)),this, SLOT(gotidletime(const QString&,int)));
//    connect(net, SIGNAL(signosuchnick(const QString&)),this, SLOT(gotnosuchnick(const QString&)));
//    this->statusbar = new QStatusBar(this);
//    ui.verticalLayout_2->addWidget(statusbar);
//    statusbar->setMaximumHeight(20);
//    if (net->joinListContains(chatpartner)){
//        statusbar->showMessage(tr("Online"));
//        userisoffline=0;
//    }
//    else{
//        statusbar->showMessage(tr("Was offline when this window opened."));
//        userisoffline=1;
//    }
//    connect(net, SIGNAL(siggotmsg(const QString&,const QString&,const QString&)),this, SLOT(channelmsg(const QString&,const QString&,const QString&)));
//}
//bool irc_chatwindow::eventFilter(QObject *obj, QEvent *event) {
//    if (obj == ui.lineEdit) {
//        if (event->type() == QEvent::KeyPress) {
//            QKeyEvent *keyEvent = static_cast<QKeyEvent*> (event);
//            if (keyEvent->key() == Qt::Key_Up)
//                qApp->postEvent(ui.lineEdit,new QKeyEvent(QEvent::KeyPress,Qt::Key_Z,Qt::ControlModifier));
//            else if (keyEvent->key() == Qt::Key_Down)
//                qApp->postEvent(ui.lineEdit,new QKeyEvent(QEvent::KeyPress,Qt::Key_Z,Qt::ShiftModifier | Qt::ControlModifier));
//        }
//        return false;
//    }
//    if (qobject_cast<QScrollArea*> (obj) != 0 && qobject_cast<QScrollArea*> (
//            obj)->objectName() == "chatwindowbuttonscrollArea") {
//        if (event->type() == QEvent::Enter) {
//            if(ui.chatwindowbuttonscrollArea->width()<305){
//                ui.chatwindowbuttonscrollArea->setMaximumHeight(70);
//                ui.chatwindowbuttonscrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//            }
//        } else if (event->type() == QEvent::Leave) {
//            ui.chatwindowbuttonscrollArea->setMaximumHeight(43);
//            ui.chatwindowbuttonscrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//        }
//    }
//    return QObject::eventFilter(obj, event);
//}
//void irc_chatwindow::garbagemapchanged(const QString &user, const QString &s) {

//    if (compareCI(user, chatpartner)) {
//        bool b = usergarbagemap.contains(user.toLower());
//        Q_UNUSED(b);
//        Q_ASSERT(b==1);
//        chat->appendgarbage(s);
//    }
//}
//void irc_chatwindow::gotmsg(const QString &user, const QString &receiver,
//                            const QString &msg) {
//    if (statusbar->currentMessage() == tr("Was offline when this window opened."))
//        statusbar->showMessage(tr("Online"));
//    if (compareCI(user, chatpartner)) {
//        chat->append(user, receiver, msg);
//        QApplication::alert(this);emit
//                sigalert(this);
//        if (net->countUsers(userstruct::whoami(user))) {
//            singleton<sound_handler>().play_buddymsgsound(user);

//        } else {
//            singleton<sound_handler>().play_normalmsgsound(user);
//        }
//    }
//}
//void irc_chatwindow::sendmsg(QString str) {
//    QString s;
//    if (str == "")
//        s = ui.lineEdit->text();
//    else
//        s = str;
//    if (s != "") {
//        if (s.startsWith(">!")) {
//            net->sendrawcommand(QString("PRIVMSG ") + chatpartner + " :\001"
//                                + s.remove(0, 2) + "\001");
//            chat->append(net->nick, chatpartner, "\001" + s + "\001");
//        } else if (s.startsWith("/")) {
//            chat->append(net->nick, chatpartner, s);
//            net->sendrawcommand(s.remove(0, 1));
//        } else if (s.startsWith(">>>")) {
//            sendnoticeaction();
//            chat->append(net->nick, chatpartner, s);
//        } else if (s.startsWith(">>")) {
//            sendnotice();
//            chat->append(net->nick, chatpartner, s);
//        } else if (s.startsWith(">")) {
//            net->sendrawcommand(QString("PRIVMSG ") + chatpartner
//                                + " :\001ACTION " + s.remove(0, 1).remove("") + " \001\n");
//            chat->append(net->nick, chatpartner, "\001ACTION " + s + " \001");
//        } else {
//            net->sendmessage(chatpartner, s);
//            chat->append(net->nick, chatpartner, s);
//        }
//        usergarbagemap[chatpartner.toLower()] << QDate::currentDate().toString(
//                "dd.MM") + " " + QTime::currentTime().toString("hh:mm") + " "
//                + net->nick + ">" + s;
//        ui.lineEdit->clear();
//        chat->moveSliderToMaximum();
//    }
//}
//void irc_chatwindow::sendnotice() {

//    const QString s = ui.lineEdit->text().remove(0, 2).remove("\n");
//    if (s != "") {
//        net->sendnotice(chatpartner, s);
//        chat->appendnotice(net->nick, chatpartner, s);
//        ui.lineEdit->clear();
//    }
//}
//void irc_chatwindow::sendnoticeaction() {

//    const QString s = ui.lineEdit->text().remove(0, 3).remove("\n");
//    if (s != "") {
//        net->sendrawcommand(QString("NOTICE ") + chatpartner + " :\001ACTION "
//                            + s + " \001");
//        chat->appendnotice(net->nick, chatpartner, "<" + s + ">");
//        ui.lineEdit->clear();
//    }
//}
//void irc_chatwindow::closeEvent(QCloseEvent *) {
//}
//void irc_chatwindow::getgamerwho() {
//    userstruct u = net->getUser(chatpartner);
//    chat->append(chatpartner, net->nick, " GAMERWHO:\n"
//                 + u.returnwho().join(" | "));
//}
//void irc_chatwindow::usesettingswindow(const QString&) {
//}
//void irc_chatwindow::pbmuteclicked() {
//    if (net->mutedusers.contains(this->chatpartner, Qt::CaseInsensitive)) {
//        foreach(QString s,net->mutedusers) {
//            if (compareCI(s, this->chatpartner))
//                net->mutedusers.removeAt(net->mutedusers.indexOf(s));
//        }
//        ui.pbmute->setIcon(QIcon("snppictures/buttons/mutebutton.png"));
//    } else {
//        net->mutedusers << this->chatpartner;
//        ui.pbmute->setIcon(QIcon("snppictures/buttons/nomutebutton.png"));
//    }
//    singleton<snpsettings>().map["mutedusers"] = net->mutedusers;
//}
//void irc_chatwindow::pbbuddyclicked() {
//    if (singleton<snpsettings>().map["buddylist"].value<QStringList> ().contains(
//            this->chatpartner, Qt::CaseInsensitive)) {
//        ui.pbbuddy->setIcon(QIcon("snppictures/buttons/buddy.png"));
//        QStringList sl = singleton<snpsettings>().map["buddylist"].value<QStringList> ();
//        singleton<snpsettings>().map["buddylist"] = removeCI(sl, this->chatpartner);
//    } else if (singleton<snpsettings>().map["ignorelist"].value<QStringList> ().contains(
//            this->chatpartner)) {
//        QStringList sl = singleton<snpsettings>().map["ignorelist"].value<QStringList> ();
//        singleton<snpsettings>().map["ignorelist"] = removeCI(sl, this->chatpartner);
//        singleton<snpsettings>().map["buddylist"] = singleton<snpsettings>().map["buddylist"].value<QStringList> ()
//                                                    << this->chatpartner;
//        ui.pbbuddy->setIcon(QIcon("snppictures/buttons/normal.png"));
//    } else {
//        ui.pbbuddy->setIcon(QIcon("snppictures/buttons/normal.png"));
//        singleton<snpsettings>().map["buddylist"] = singleton<snpsettings>().map["buddylist"].value<QStringList> ()
//                                                    << this->chatpartner;
//    }
//}
//void irc_chatwindow::pblogclicked() {
//    QString s = ui.chat->toPlainText();
//    QString file = QFileDialog::getSaveFileName(this, tr("Choose a file."),
//                                                "*.log");
//    QFile f(file);
//    if (file != "" && f.open(QFile::WriteOnly)) {
//        QTextStream ts(&f);
//        ts << s;
//    }
//}
//void irc_chatwindow::pbidleclicked() {
//    net->sendrawcommand("whois " + this->chatpartner);
//}
//void irc_chatwindow::gotidletime(const QString &user, int i) {
//    QTime time(0, 0, 0);
//    time = time.addSecs(i);
//    if (compareCI(user, this->chatpartner)) {
//        chat->appenddebug(tr("<This users idle time: %1>").arg(time.toString(
//                "hh:mm:ss")));
//    }
//}
//void irc_chatwindow::gotnosuchnick(const QString &s){
//    if(compareCI(this->chatpartner,s)){
//        chat->appenddebug(tr("This user is currently offline"));
//        userisoffline=1;
//    }
//}
//void irc_chatwindow::pbctcpclicked() {
//    singleton<ctctphandlerwidget>().show();
//}
//void irc_chatwindow::setaway(bool b, const QString &msg) {
//    if (b) {
//        statusbar->showMessage(QString(msg).remove(0, 5).remove("\001"));
//    } else {
//        statusbar->showMessage(tr("Online"));
//    }
//}
//void irc_chatwindow::channelmsg(const QString &user, const QString &receiver,
//                                const QString &msg) {
//    if (user == this->chatpartner) {
//        usergarbagemap[user.toLower()]
//                << QDate::currentDate().toString("dd.MM") + " "
//                + QTime::currentTime().toString("hh:mm") + " " + user
//                + " to " + receiver + ">"
//                + QString(msg).remove("\n").remove("\r");
//        if (singleton<settingswindow>().from_map("chbshowchannelchatinchatwindows").toBool()) {
//            chat->appendgarbage(QDate::currentDate().toString("dd.MM") + " "
//                                + QTime::currentTime().toString("hh:mm") + " " + user
//                                + " to " + receiver + ">"
//                                + QString(msg).remove("\n").remove("\r"));
//        }
//    }
//}
//void irc_chatwindow::filtergarbage() {
//    ui.chat->clear();
//    foreach(QString s,usergarbagemap[chatpartner.toLower()]) {
//        if (!s.contains("JOIN") && !s.contains("PART") && !s.contains(
//                "QUIT"))
//            chat->appendgarbage(s);
//    }
//}
//irc_chatwindow::~irc_chatwindow() {
//    chat->disconnect();
//    chat->deleteLater();
//    emit
//            closed();
//}

//void irc_chatwindow::on_pbresize_clicked()
//{
//    static int clickCounter=0;
//    static int oldwidth;
//    static int screenCount=qApp->desktop()->screenCount();
//    static int desktopWidth=qApp->desktop()->size().width();

//    if(clickCounter==0)
//        oldwidth=size().width();

//    clickCounter=(clickCounter+1)%3;
//    switch(clickCounter){
//    case 0:
//        resize(oldwidth,height());
//        break;
//    case 1:
//        resize((desktopWidth/2)/screenCount,height());
//        break;
//    case 2:
//        resize((3*desktopWidth/4)/screenCount,height());
//        break;
//    }
//}
