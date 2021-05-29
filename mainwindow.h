#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <myserver.h>
#include <QDateTime>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpSocket* socket;
    QByteArray Data;
    myserver* mys;
    Ui::MainWindow *ui;
    QString port = "9999";

public slots:
    void sockReady();
    void sockDisc();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();


};
#endif // MAINWINDOW_H
