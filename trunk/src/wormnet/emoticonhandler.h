#ifndef EMOTICONHANDLER_H
#define EMOTICONHANDLER_H

#include<QtGui/QWidget>
#include<QImage>

#include"ui_emoticonhandler.h"

class emoticonhandler : public QWidget
{
    Q_OBJECT

public:
    emoticonhandler(QWidget *parent = 0);
    ~emoticonhandler();
//    QVector<QVariant> preparemsg(QString);
    QVariant contains(QString s);        
    QMap<QString,QImage> map;
private:
//    QVector<QVariant> preparemsgrec(QString,int i);
    QStringList slhelper;
    Ui::emoticonhandlerClass ui;    
    QMap<QString,QMap<QString,QString> > filemap;
    QString scheme;    
private slots:
    void indexofcbchanged(const QString&);
    void myclose();
    void add();
    void remove();

    friend class emoticondialog;
};

#endif // EMOTICONHANDLER_H
