#include"hostmodel.h"
#include"settings.h"
#include"settingswindow.h"
#include"sound_handler.h"
#include"balloon_handler.h"
#include"global_functions.h"
#include"myDebug.h"
#include"picturehandler.h"

#include<QTime>
#include<QPointer>
#include<QApplication>

hostmodel::hostmodel(QObject *parent) :
	QAbstractItemModel(parent) {

    stringnamelist << QObject::tr("Game") << QObject::tr("User") << "" << "" <<  QObject::tr("GameIp");
    if (!channelicon.load(QApplication::applicationDirPath()
        + "/snppictures/channelicon.png"))
        myDebug() << QObject::tr("Some Pictures are missing!");
    if (!hosticon.load(QApplication::applicationDirPath()
        + "/snppictures/hosticon.png"))
        myDebug() << QObject::tr("Some Pictures are missing!");
    if (!buddyhosticon.load(QApplication::applicationDirPath()
        + "/snppictures/buddyhosticon.png"))
        myDebug() << QObject::tr("Some Pictures are missing!");
    if (!ignorehosticon.load(QApplication::applicationDirPath()
        + "/snppictures/ignorehosticon.png"))
        myDebug() << QObject::tr("Some Pictures are missing!");
}
void hostmodel::sethoststruct(QList<hoststruct> l, QString chan) {
    emit layoutAboutToBeChanged();
    hostmap[chan].clear();
    classes = hostmap.keys();
    QList<hoststruct>::const_iterator i = l.end();
    QStringList sl;
    while (i != l.begin()) {
        i--;
        hostmap[chan].push_back(*i);
        if (!S_S.chbshowbaloonwhenbuddyhosts)
            continue;
        if (!S_S.buddylist.contains(i->nick()))
            continue;
        sl << i->nick();
        if (buddyhosts[chan].contains(i->nick()))   //if the host was allready alerted
            continue;

        singleton<sound_handler>().play_buddyhostedsound();
        singleton<balloon_handler>().got_game(i->nick(),i->name());

    }
    buddyhosts[chan] = sl;
    emit layoutChanged();
    emit dataChanged(createIndex(0, 0, classes.indexOf(chan)), createIndex(
            hostmap[chan].count() - 1, 4, classes.indexOf(chan)));
}
int hostmodel::columnCount(const QModelIndex & /*parent*/) const {
    if(!S_S.cbshowipofhosts)
        return 4;
    return 5;
}
int hostmodel::rowCount(const QModelIndex & parent) const {

    if (!parent.isValid())
        return classes.count();
    else if (parent.internalId() == 999)
        return hostmap[classes[parent.row()]].count();
    else
        return 0;
}
QVariant hostmodel::data(const QModelIndex & index, int role) const {

    if (!index.isValid())
        return QVariant();
    if (role == Qt::TextAlignmentRole)
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    if (role == Qt::DecorationRole) {
        if (index.internalId() == 999 && index.column() == 0) {
            return channelicon;
        } else if (index.column() == 0) {
            QString
                    s =
                    hostmap[classes[index.internalId()]][index.row()].nick();
            if (S_S.buddylist.contains(s))
                return buddyhosticon;
            else if (S_S.ignorelist.contains(s))
                return ignorehosticon;
            else
                return hosticon;
        } else
            return QVariant();
    } else if (role == Qt::DisplayRole || role == Qt::BackgroundRole) {
        if (index.internalId() == 999) {
            if (index.column() == 0) {
                return classes[index.row()];
            } else
                return "";
        }
        switch (index.column()) {
        case 0:
            if (role == Qt::DisplayRole) {
                return hostmap[classes[index.internalId()]][index.row()].name();
            }
            break;
		case 1:
            if (role == Qt::DisplayRole) {
                return hostmap[classes[index.internalId()]][index.row()].nick();
            }
            break;
		case 2:
            if (role == Qt::BackgroundRole) {
                return *singleton<picturehandler>().getflag(hostmap[classes[index.internalId()]][index.row()].country());
            }
            break;
		case 3:
            if (role == Qt::BackgroundRole) {
                if (hostmap[classes[index.internalId()]][index.row()].withkey())
                    return *singleton<picturehandler>().locked;
                else
                    return *singleton<picturehandler>().unlocked;
            }
            break;
		case 4:
            if (role == Qt::DisplayRole)
                return hostmap[classes[index.internalId()]][index.row()].ip();
            break;
        }
    }
    return QVariant();
}
QVariant hostmodel::headerData(int section, Qt::Orientation orientation,
                               int role) const {

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section < 5) {
        Q_ASSERT(section<stringnamelist.size() && section>=0);
        return stringnamelist[section];
    }
    if (role == Qt::TextAlignmentRole)
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    if (role == Qt::FontRole)
        return QFont("Times", 12, QFont::Bold);

    return QVariant();
}
QModelIndex hostmodel::index(int row, int column, const QModelIndex & parent) const {

    if (!parent.isValid())
        return createIndex(row, column, 999);
    if (parent.internalId() == 999) {
        return createIndex(row, column, parent.row());
    }
    return QModelIndex();
}
QModelIndex hostmodel::parent(const QModelIndex & index) const {

    if (!index.isValid())
        return QModelIndex();
    if (index.internalId() == 999)
        return QModelIndex();
    return createIndex(index.internalId(), 0, 999);
}
Qt::ItemFlags hostmodel::flags(const QModelIndex & index) const {

    Qt::ItemFlags f = QAbstractItemModel::flags(index);
    if (index.internalId() == 999)
        return f ^= Qt::ItemIsSelectable;
    else if (index.column() == 2 || index.column() == 3) {
        return f ^= Qt::ItemIsSelectable;
    } else
        return f;
}
QModelIndex hostmodel::indexbychannelname(QString s) {

    return createIndex(classes.indexOf(s), 0, 999);
}
QString hostmodel::joininfo(const QModelIndex &index) {

    if (index.internalId() != 999) {
        return hostmap[classes[index.internalId()]][index.row()].joinstring();
    }
    return "";
}
QString hostmodel::gamename(const QModelIndex &index) {

    if (index.internalId() != 999) {
        return hostmap[classes[index.internalId()]][index.row()].name();
    }
    return "";
}
hostmodel::~hostmodel() {

}
