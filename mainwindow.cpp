#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include <QSettings>
#include <QMessageBox>
#include <QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
int row;
QStandardItem *item;
QStandardItemModel *model;
QSettings *setting;
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::reboot()
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->treeView->model());

    // Если модель данных существует, очистить её
    if (model) {
        model->clear(); // Этот метод очищает все данные из модели
    }
    return;
}

// Создаем слот для удаления строки из таблицы
void MainWindow::remove_row()
{
    QModelIndexList selectedRows = ui->treeView->selectionModel()->selectedRows();
    if (!selectedRows.empty()) {

        int row = selectedRows.first().row();
        ui->treeView->model()->removeRow(row);
    }
    return;
}

void MainWindow::del_files()
{
    QModelIndexList selectedRows = ui->treeView->selectionModel()->selectedRows();
        if (!selectedRows.empty()) {
        int row = selectedRows.first().row();
        // Открываем файл для записи
        QFile file("../Response_System/Del_Files.txt");
        // Открываем файл для чтения и записи
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QTextStream in(&file);
            // Сохраняем старые данные
            QString oldData = in.readAll();
            if (oldData.length()!=0){
                // Перемещаем указатель на конец файла
                file.seek(file.size());
                QTextStream out(&file);
                QString out_line =  model->index(row,1).data().toString().split(',')[0] + model->index(row,2).data().toString().split(',')[0] ;
                qDebug()<<out_line;
                out << out_line << "\n";
            }else
            {
                QTextStream out(&file);
                QString out_line =  model->index(row,1).data().toString().split(',')[0] + model->index(row,2).data().toString().split(',')[0] ;
                qDebug()<<out_line;
                out << out_line << "\n";
            }
            file.close();
        }
        else
        {
            qDebug() << "Не удалось открыть файл";
        }
        remove_row();
    }
}
void MainWindow::block_addres()
{
    QModelIndexList selectedRows = ui->treeView->selectionModel()->selectedRows();
     if (!selectedRows.empty()) {
        int row = selectedRows.first().row();
        // Открываем файл для записи
        QFile file("../Response_System/BlockedIP.txt");
        // Открываем файл для чтения и записи
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QTextStream in(&file);
            // Сохраняем старые данные
            QString oldData = in.readAll();
                if (oldData.length()!=0){
                // Перемещаем указатель на конец файла
                file.seek(file.size());
                QTextStream out(&file);
                QString out_line =  model->index(row,1).data().toString();
                out << out_line << "\n";

            }else
                {
                    QTextStream out(&file);
                    QString out_line =  model->index(row,1).data().toString();
                    out << out_line << "\n";
                }
            file.close();
        }
        else
        {
            qDebug() << "Не удалось открыть файл";
        }
            remove_row();
    }
}
void MainWindow::block_ssh()
{
    QModelIndexList selectedRows = ui->treeView->selectionModel()->selectedRows();
     if (!selectedRows.empty()) {
    int row = selectedRows.first().row();
    // Открываем файл для записи
    QFile file("../Response_System/SSH_PIDS.txt");
    // Открываем файл для чтения и записи
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream in(&file);
        // Сохраняем старые данные
        QString oldData = in.readAll();
        if (oldData.length()!=0){
            // Перемещаем указатель на конец файла
            file.seek(file.size());
            QTextStream out(&file);
            QString out_line =  model->index(row,5).data().toString();
            out << out_line << "\n";
        }else
        {
            QTextStream out(&file);
            QString out_line =  model->index(row,5).data().toString();
            out << out_line << "\n";
        }
        file.close();
    }
    else
    {
        qDebug() << "Не удалось открыть файл";
    }
    remove_row();
     }
}


void MainWindow::on_Monitor_Network_clicked()
 {
    reboot();
    model = new QStandardItemModel;
    model->setColumnCount(6);
    QStringList horizontalHeader;
    horizontalHeader.append("№");
    horizontalHeader.append("Ip источника");
    horizontalHeader.append("Ip приемника");
    horizontalHeader.append("Протокол");
    horizontalHeader.append("Время");
    horizontalHeader.append("Действие");
    model->setHorizontalHeaderLabels(horizontalHeader);
    ui->treeView->setModel(model);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Открываем файл для чтения
    QFile file("../Monitoring_System/Traffic_logs.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for reading";
        return;
    }
    // Читаем данные из файла построчно
    QTextStream in(&file);
    row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
        QStringList parts = line.split(" "); // Разбиваем строку на части по пробелам

        QRegularExpression re("[0-9]"); // Не цифры

        if(re.match(parts.at(1)[0]).hasMatch()){
            //Номер строки
            model->setItem(row,0,new QStandardItem(QString::number(row+1)));
            model->setItem(row,1,new QStandardItem(parts.at(1)));
            model->setItem(row,2,new QStandardItem(parts.at(3)));
            model->setItem(row,3,new QStandardItem(parts.at(4)));
            model->setItem(row,4,new QStandardItem(parts.at(0)));
            QStandardItemModel *model1 = model;
            // Создаем кнопку для удаления строки
            QPushButton *removeButton = new QPushButton("Удалить");
            connect(removeButton, &QPushButton::clicked, this, &MainWindow::block_addres);
            // Добавляем кнопку в 6-й столбец
            QHBoxLayout *layout = new QHBoxLayout();
            layout->addWidget(removeButton);
            QWidget *widget = new QWidget();
            widget->setLayout(layout);
            ui->treeView->setIndexWidget(model->index(row, 5), widget);

            row++;
        }

    }
    // Отображаем QTreeView
    ui->treeView->show();
    file.close();
    //return a.exec();
}
void MainWindow::on_Monitor_SSH_clicked()
{
    reboot();
    model = new QStandardItemModel;
    QStringList horizontalHeader;
    horizontalHeader.append("№");
    horizontalHeader.append("IP-Источника");
    horizontalHeader.append("IP-Приемника");
    horizontalHeader.append("Порт-Приемника");
    horizontalHeader.append("Протокол");
    horizontalHeader.append("PID процесса");
    horizontalHeader.append("Действие");
    model->setHorizontalHeaderLabels(horizontalHeader);
    ui->treeView->setModel(model);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Открываем файл для чтения
    QFile file("../Monitoring_System/SSH_Monitoring_Logs.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cann.atot open file for reading";
        return;
    }
    // Читаем данные из файла построчно
    QTextStream in(&file);
    qDebug() << "WE ARE HERE!!!";
    row = 0;
        while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" "); // Разбиваем строку на части по пробелам

        //Номер строки
        model->setItem(row,0,new QStandardItem(QString::number(row+1)));
        model->setItem(row,1,new QStandardItem(parts.at(32).split(":").at(0)));
        model->setItem(row,2,new QStandardItem(parts.at(15).split(":").at(0)));
        model->setItem(row,3,new QStandardItem(parts.at(15).split(":").at(1)));
        model->setItem(row,4,new QStandardItem(parts.at(0)));
        model->setItem(row,5,new QStandardItem(parts.at(48).split("/").at(0)));

        // Создаем кнопку для удаления строки

        QPushButton *removeButton = new QPushButton("Заблокировать");
        connect(removeButton, &QPushButton::clicked, this, &MainWindow::block_ssh);
        // Добавляем кнопку в 6-й столбец
        QHBoxLayout *layout = new QHBoxLayout();
        layout->addWidget(removeButton);
        QWidget *widget = new QWidget();
        widget->setLayout(layout);
        ui->treeView->setIndexWidget(model->index(row, 6), widget);
        row++;
    }
    ui->treeView->show();
    file.close();
}

void MainWindow::on_Monitor_Applications_clicked()
{
    reboot();
    model = new QStandardItemModel;
    model->setColumnCount(6);
    QStringList horizontalHeader;
    horizontalHeader.append("№");
    horizontalHeader.append("Путь");
    horizontalHeader.append("Файл");
    horizontalHeader.append("Дата");
    horizontalHeader.append("Время");
    horizontalHeader.append("Действие");
    model->setHorizontalHeaderLabels(horizontalHeader);
    ui->treeView->setModel(model);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Открываем файл для чтения
    QFile file("../Monitoring_System/FileMonitoringLogs.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for reading";
        return;
    }
    // Читаем данные из файла построчно
    QTextStream in(&file);
    row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
        QStringList parts = line.split(" "); // Разбиваем строку на части по пробелам

        for (int i =0;i <parts.length(); i++)
        {
            qDebug() << parts.at(i);
        }
        //Номер строки
        model->setItem(row,0,new QStandardItem(QString::number(row+1)));
        model->setItem(row,1,new QStandardItem(parts.at(1).split(",")[0]));
        model->setItem(row,2,new QStandardItem(parts.at(4).split(",")[0]));
        model->setItem(row,3,new QStandardItem(parts.at(7)));
        model->setItem(row,4,new QStandardItem(parts.at(8)));

        // Создаем кнопку для удаления строки
        QPushButton *removeButton = new QPushButton("Удалить");
        connect(removeButton, &QPushButton::clicked, this, &MainWindow::del_files);

        // Добавляем кнопку в 6-й столбец
        QHBoxLayout *layout = new QHBoxLayout();
        layout->addWidget(removeButton);
        QWidget *widget = new QWidget();
        widget->setLayout(layout);
        ui->treeView->setIndexWidget(model->index(row, 5), widget);
        row++;
    }
    // Отображаем QTreeView
    ui->treeView->show();
     file.close();

}

void MainWindow::on_MonitoringStart_clicked()
{
   // Мониторинг сети
}

