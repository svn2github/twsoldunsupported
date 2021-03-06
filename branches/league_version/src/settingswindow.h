#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QtGui/QWidget>
#include "ui_settingswindow.h"
#include "global_macros.h"
class settingswindow : public QWidget
{
    Q_OBJECT
    DECLARE_SINGLETON(settingswindow);
public:
    QStringList objectnames;
    void safe();
    const QVariant from_map(const QString&) const;
    void to_map(const QString&, const QVariant&);
private:
    Ui::settingswindowClass ui;
    void load();
    QMap<QString,QVariant> map;
private slots:
    void ok();
    void cancel();
    void soundoptionbuttonslot();

};

#endif // SETTINGSWINDOW_H
