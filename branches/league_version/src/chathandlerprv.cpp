/*
 * chathandler.cpp
 *
 *  Created on: 19.11.2008
 *      Author: looki
 */

#include "chathandlerprv.h"
#include<QTextBrowser>
#include <QTextDocument>
#include<QTime>
#include<QDebug>
#include<QFontDialog>
#include<QColorDialog>
#include<QScrollBar>
#include<QMessageBox>
#include<QDesktopServices>
#include"settingswindow.h"
#include "snpsettings.h"
#include"netcoupler.h"
#include"joinprvgame.h"
#include "emoticonhandler.h"
#include"global_functions.h"
QPointer<emoticonhandler> chathandlerprv::emot;
extern QPointer<netcoupler> net;
chathandlerprv::chathandlerprv(QObject *parent, QTextBrowser *t, QString chan) :
	chathandler(parent, t, chan) {
	if (emot == 0)
		emot = new emoticonhandler;
	initialformatstarter();
	slideratmaximum = 1;
}
void chathandlerprv::append(const QString &user, const QString &/*receiver*/,
		const QString &msg) {
	QString msgtemp = msg.simplified();
	QString time = QTime::currentTime().toString("hh:mm");
        cursor->insertText(time + ":", timeformat);
        if (!containsCI(singleton<snpsettings>().map["buddylist"].value<QStringList> (), user)) {
		if (msg.startsWith("\001ACTION")) {
                        insertText("<" + user + " " + msgtemp + ">", actionformat,user);
		} else {
                        cursor->insertText(user + "> ", nickformat);
                        if (singleton<settingswindow>().from_map("chbsmileys").toBool() || containsCI(msg, "http://") || containsCI(msg, "wa://")) {
                                insertText(msgtemp, chatformat,user);
			} else {
				foreach(QVariant v,emot->preparemsg(msgtemp)) {
						if (v.canConvert(QVariant::Image))
							cursor->insertImage(qvariant_cast<QImage> (v));
                                                else{
                                                    if(user==net->nick)
                                                        insertText(v.toString(), myselfformat,user);
                                                    else
                                                        insertText(v.toString(), chatformat,user);
                                                    }
					}
			}
		}
	} else {
		if (msg.startsWith("\001ACTION")) {
                        insertText("<" + user + " " + msgtemp + ">", buddyformat,user);
		} else {
                        cursor->insertText(user + "> ", nickformat);
                        if (singleton<settingswindow>().from_map("chbsmileys").toBool() || containsCI(msg, "http://") || containsCI(msg, "wa://")) {
                                insertText(msgtemp, buddyformat,user);
			} else {
				foreach(QVariant v,emot->preparemsg(msgtemp)) {
						if (v.canConvert(QVariant::Image))
							cursor->insertImage(qvariant_cast<QImage> (v));
                                                else{
                                                        if(user==net->nick)
                                                            insertText(v.toString(), myselfformat,user);
                                                        else
                                                            insertText(v.toString(), buddyformat,user);
                                                    }
					}
			}
		}
	}
	cursor->insertText("\n");
	if (slideratmaximum)
		tb->verticalScrollBar()->setValue(tb->verticalScrollBar()->maximum());
}
void chathandlerprv::appendgarbage(const QString &msg) {
	cursor->insertText(msg + "\n", garbageformat);
	if (slideratmaximum)
		tb->verticalScrollBar()->setValue(tb->verticalScrollBar()->maximum());
}
chathandlerprv::~chathandlerprv() {
	// TODO Auto-generated destructor stub
}
