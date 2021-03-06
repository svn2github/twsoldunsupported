#include"clantowebpagemapper.h"
#include"settingswindow.h"
#include"settings.h"
#include"leagueserverhandler.h"

#include<QFile>
#include<QDir>
#include<QApplication>
#include<QMessageBox>
#include<QUrl>
#include<QNetworkReply>

clantowebpagemapper::clantowebpagemapper()
{
}
clantowebpagemapper::~clantowebpagemapper()
{
}
bool clantowebpagemapper::contains(const QString &key){
    return map.contains(key.toLower());
}
QString clantowebpagemapper::value(const QString &key){
    return map[key.toLower()];
}
void clantowebpagemapper::refresh(){
    QUrl url("http://lookias.worms2d.info/wheat/clanlist.txt.php");
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(finished()),reply, SLOT(deleteLater()));
}
void clantowebpagemapper::httpFinished(){
    if(reply->error()!=QNetworkReply::NoError)
        return;
    QStringList sl=file.split("\n");
    foreach(QString s,sl){
        if(s.isEmpty())
            continue;
        QStringList temp=s.simplified().split(" ");
        if(temp.size()<2)
            continue;
        QString s=temp.takeFirst().toLower();
        map[s]=temp.takeFirst();
        InformationMap[s]=temp.join(" ");
    }
}
void clantowebpagemapper::httpReadyRead(){
    file.append(reply->readAll());
}
QString clantowebpagemapper::getInformation(const userstruct &u){
    QString clan=u.clan.toLower();
    if(S_S.spectateleagueserver){
        if(S_S.cbshowranksonlyfromsecureloggedusers)
            clan=singleton<leagueserverhandler>().map_at_toString(u.nick,leagueserverhandler::e_clan);        
    }
    if(!InformationMap.contains(clan))
        return QString();
    return InformationMap[clan];
}
