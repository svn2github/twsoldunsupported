#ifndef IRCNET_H
#define IRCNET_H

#include <QObject>
#include<QTcpSocket>
#include<QStringList>
#include<QTimer>
#include"userstruct.h"
class ircnet : public QObject
{
    Q_OBJECT

public:
    ircnet(QString s, QObject *parent = 0);
    ~ircnet();

    void joinchannel(const QString&);
    void sendmessage(const QString&, const QString&);
    void sendnotice(const QString&, const QString&);
    void sendrawcommand(const QString&);
    void setip(const QString&);
    void refreshlist();
    void who();
    void partchannel(const QString&);
    void quit();
    QList<userstruct> wholist;
    QMap<QString,QStringList> joinlist;
    QString nick;
public slots:
	void start();
	void connected();
	void disconnected();
	void tcpread();
signals: //public signals:
    void sigmsg(const QString&,const QString&,const QString&);
    void signotice(const QString&,const QString&,const QString&);
    void siggetlist(QStringList);
		//private signals:
    void sigconnected();
    void sigdisconnected();
    void sigusergarbage(const QString&,const QString&);
    void sigusergarbagejoin(const QString&,const QString&);
    void sigusergarbagepart(const QString&,const QString&);
    void sigusergarbagequit(const QString&,const QString&);
    void siggotidletime(const QString&, int);
    void signosuchnick(const QString&);

private:
	bool justgetlist;

	QList<userstruct> templist;

	QStringList channellist;
	QStringList tempchannellist;
	QString ircreadstring;
	QString wnip;
	QString servernick;
	QString servermessageindicator;
	QTcpSocket *tcp;
	QTimer reconnecttimer;
	void readservermassege(QString);
	void readusermessage(QString &);
	void gotusergarbage(QString&,QString&);

	QMap<QString,int> mapusercommand;
	bool whoreceivedcompletely;
};

#endif // IRCNET_H
