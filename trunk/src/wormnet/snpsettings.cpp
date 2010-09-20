/*
 * snpsettings.cpp
 *
 *  Created on: 24.10.2008
 *      Author: looki
 */

#include "snpsettings.h"
#include"settingswindow.h"
#include<QFile>
#include<QDir>
#include<QApplication>
#include<QMessageBox>
#include<QFileDialog>
extern QStringList defaultServerList;
snpsettings::snpsettings(){}
snpsettings::~snpsettings(){}
void snpsettings::load(){
    if(!QDir().exists("query"))
        QDir().mkdir("query");
    if(!QDir().exists("snpini"))
        QDir().mkdir("snpini");
    QFile f(QApplication::applicationDirPath()+"/snpini/snpini");
    if(!f.open(QFile::ReadOnly)){
        int button=QMessageBox::question(0,QApplication::tr("Question")
                                         ,QApplication::tr("If you like to keep the settings from an older Snooper installation click yes.\n"
                                                           "If you use The Wheat Snooper at the first time just click No.")
                                         ,QMessageBox::Yes | QMessageBox::No);
        if(button==QMessageBox::Yes){
            QString folder;
            while(true){
                folder=QFileDialog::getExistingDirectory(0,qApp->tr("Please choose the folder from the old Snooper.")
                                                         ,qApp->applicationDirPath());
                if(QFile::exists(folder+"/snpini/snpini")){
                    QFile::copy(folder+"/snpini/snpini",QApplication::applicationDirPath()+"/snpini/snpini");
                    break;
                } else{
                    int button=QMessageBox::warning(0,qApp->tr("Warning!"),qApp->tr("This folder doesnt seem to hold a valid installation of The Wheat Snooper. Do you want to keep searching?"),QMessageBox::Yes | QMessageBox::No);
                    if(button==QMessageBox::Yes)
                        continue;
                    else return;
                }
            }
            QFile::copy(folder+"/snpini/"+"settingswindowini",QApplication::applicationDirPath()+"/snpini/settingswindowini");
            QFile::copy(folder+"/snpini/"+"ctcp.ini",QApplication::applicationDirPath()+"/snpini/ctcp.ini");

            QFile::copy(folder+"/query/"+"log",QApplication::applicationDirPath()+"/query/log");
            QFile::copy(folder+"/query/"+"querylist",QApplication::applicationDirPath()+"/query/querylist");
            singleton<settingswindow>().load();
        } else{
            loadDefaults();
            return;
        }
    }
    f.open(QFile::ReadOnly);
    QDataStream ds(&f);
    ds.setVersion(QDataStream::Qt_4_3);
    ds>>map;
    if(ds.status()==2 ||ds.status()==1){
        map.clear();
        ds.resetStatus();
        f.setFileName(QApplication::applicationDirPath()+QDir::separator()+"snpini"+QDir::separator()+"snpinifromlastquit");
        f.open(QFile::ReadOnly);
        ds.setDevice(&f);
        ds>>map;
    }
}
void snpsettings::safe(){
    QFile f(QApplication::applicationDirPath()+QDir::separator()+"snpini"+QDir::separator()+"snpini");
    f.open(QFile::WriteOnly);
    QDataStream ds(&f);
    ds.setVersion(QDataStream::Qt_4_3);
    ds<<map;
}
void snpsettings::safeonquit(){
    QFile f(QApplication::applicationDirPath()+QDir::separator()+"snpini"+QDir::separator()+"snpinifromlastquit");
    f.open(QFile::WriteOnly);
    QDataStream ds(&f);
    ds.setVersion(QDataStream::Qt_4_3);
    ds<<map;
}
void snpsettings::loadDefaults(){
    singleton<snpsettings>().map["volumeslidervalue"].setValue<int>(5);
    singleton<snpsettings>().map["chbminimized"].setValue<bool>(0);
    singleton<snpsettings>().map["dissallowedclannames"].setValue<QStringList>(QStringList()<<"Username");
    singleton<snpsettings>().map["language file"].setValue<QString> ("The_Wheat_Snooper_untranslated");
    singleton<snpsettings>().map["charformatfile"].setValue<QString>("comic by lookias.textscheme");
    singleton<snpsettings>().map["chbsendhostinfotochan"].setValue<bool>(true);
    singleton<snpsettings>().map["wormnetserverlist"].setValue<QStringList>(defaultServerList);
}