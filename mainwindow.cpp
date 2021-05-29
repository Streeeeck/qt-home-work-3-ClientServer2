#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mys = new myserver(ui->listWidget);
    mys->startServer();
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));


}

MainWindow::~MainWindow()
{
delete ui;
}

void MainWindow::on_pushButton_clicked()
{
socket->connectToHost("127.0.0.1",8888);
}

void MainWindow::sockDisc()
{
socket->deleteLater();
}

void MainWindow::sockReady()
{
if (socket->waitForConnected(500))
{
    socket->waitForReadyRead(500);
    Data = socket->readAll();
    qDebug()<<"client::"<<Data;
}
}


void MainWindow::on_pushButton_2_clicked()
{
    QDateTime dateTime(QDateTime::currentDateTime());
    QString s = dateTime.toString("yyyy.MM.dd hh:mm:ss");
    ui->listWidget->addItem((port +"(Вы): " + ui->lineEdit->text()+"  ||"+s).toUtf8());
    mys->mymessage(ui->lineEdit->text());
     socket->write((port +": " + ui->lineEdit->text()).toUtf8());
}
