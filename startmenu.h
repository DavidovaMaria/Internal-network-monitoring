#ifndef STARTMENU_H
#define STARTMENU_H

#include <QObject>

namespace Ui {
class StartMenu;
}

class StartMenu : public QObject
{
    Q_OBJECT
public:
    explicit StartMenu(QObject *parent = nullptr);

signals:
    void firstWindow();

private:
    Ui::StartMenu *ui;
};

#endif // STARTMENU_H
