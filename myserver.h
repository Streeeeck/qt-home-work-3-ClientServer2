#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QListWidget>
#include <QDateTime>
#include <QSqlDatabase>
#include <QDir>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtSql>

class myserver: public QTcpServer
{
    Q_OBJECT
public:
    myserver(QListWidget* q);
    ~myserver();

    QTcpSocket* socket;
    QByteArray Data;
    QListWidget* qlistW;
    QSqlDatabase db;
    QString port = "9999";
    bool mymessage(QString mes);

public slots:
    void startServer();
    void incomingConnection(int socketDescriptor);
    void sockReady();
    void sockDisc();
};

#endif // MYSERVER_H
