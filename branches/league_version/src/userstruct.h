/*
 * userstruct.h
 *
 *  Created on: 16.10.2008
 *      Author: looki
 */

#ifndef USERSTRUCT_H_
#define USERSTRUCT_H_
#include<QStringList>
class userstruct {
public:
	userstruct();
	userstruct(QStringList);
	virtual ~userstruct();
	bool operator==(const userstruct&);
	QStringList returnwho();
	static userstruct whoami(const QString &,const QString &s="");
//private:
	QString chan;
	QString nickfromclient;
	QString address;
	QString server;
	QString nick;
	QString unknown;
	QString commandstart;
	int flag;
	int rank;
	QString country;
	QString client;
	bool wnvalid;		//this nick is to 80% a valid wn user
	static bool* boolhelper;
	static QMap<int,QString> temp;
	static bool addressischecked;
};
#endif /* USERSTRUCT_H_ */
