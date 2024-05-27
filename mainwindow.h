#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


QT_BEGIN_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_MonitoringStart_clicked();

    void on_Monitor_Network_clicked();

    void on_Monitor_SSH_clicked();

    void on_Monitor_Applications_clicked();
    void remove_row();
     void del_files();
     void block_addres();
      void block_ssh();
    void reboot();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
