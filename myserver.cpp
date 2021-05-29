#include "myserver.h"

myserver::myserver(QListWidget* q){
    qlistW = q;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath()+"/mes1.db");
    bool ok = db.open();
    qDebug()<<"connect to BD ="<<ok;
    QSqlQuery a_query;

    QString str = "CREATE TABLE Messages (id integer PRIMARY KEY AUTOINCREMENT, name varchar(30), message varchar(70), dat Datetime);";
    bool b = a_query.exec(str);
    if (!b) {
        qDebug() << "Не удается создать таблицу!";
    }



    if (!a_query.exec("SELECT * FROM Messages")) {
            qDebug() << "Даже селект не получается, я пас.";
            return;
        }
    QSqlRecord rec = a_query.record();
        int id = 0;
        QString name = 0;
        QString message = "";
        QString dat = "";

        while (a_query.next()) {
            id = a_query.value(rec.indexOf("id")).toInt();
            name = a_query.value(rec.indexOf("name")).toString();
            message = a_query.value(rec.indexOf("message")).toString();
            dat = a_query.value(rec.indexOf("dat")).toString();

           /* qDebug() << "id = " << id
                     << ". \nname = " << name
                     << ". \nmessage =" << message
                     << ". \ndat = " << dat;*/
            qlistW->addItem(name+":"+message+"  |"+dat);

        }

}

myserver::~myserver(){
    db.close();
}

bool myserver::mymessage(QString mes)
{
    QDateTime dateTime(QDateTime::currentDateTime());
    QString s = dateTime.toString("yyyy.MM.dd hh:mm:ss");
    QSqlQuery a_query;
    QString str = "INSERT into Messages(name, message,dat) VALUES (\""+port+"(Вы)\",\""+mes+"\",\""+s+"\");";
    bool b = a_query.exec(str);
    if (!b) {
        qDebug() << "Данные не вставляются!";
        return 0;
    }
    return 1;

}

void myserver::startServer()
{
    if (this->listen(QHostAddress::Any,9999))
    {
        qDebug()<<"Listening";
    }
    else
    {
        qDebug()<<"Not listening";
    }
}

void myserver::incomingConnection(int socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

        connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

    qDebug()<<socketDescriptor<<" Client connected";

    socket->write("You are connect");
    qDebug()<<"Send client connect status - YES";
}

void myserver::sockReady()
{
    if (socket->waitForConnected(500))
    {
        QDateTime dateTime(QDateTime::currentDateTime());
        QString s = dateTime.toString("yyyy.MM.dd hh:mm:ss");
        Data = socket->readAll();
        qDebug()<<"server::"<<Data;
        qlistW->addItem(Data + ("  |"+s).toUtf8());
        QByteArray sen = Data.split(':')[0];
        QByteArray mes = Data.split(':')[1];

        QSqlQuery a_query;
        QString str = "INSERT into Messages(name, message,dat) VALUES (\""+sen+"\",\""+mes+"\",\""+s+"\");";
        bool b = a_query.exec(str);
        if (!b) {
            qDebug() << "Данные не вставляются!";
        }

    }
}

void myserver::sockDisc()
{
    qDebug()<<"Disconnect";
    socket->deleteLater();
}
