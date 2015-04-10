#ifndef CONNECTIONDB_H
#define CONNECTIONDB_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QVBoxLayout>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QWebPage>
#include <QWebView>
#include <QWebElement>


class ConnectionDB : public QObject
{

    Q_OBJECT

public:
    ConnectionDB(QWidget *parent, QString debut, QString fin, QString devise);
    ~ConnectionDB();



public slots:


private:

    QSqlDatabase            db;
    QSqlTableModel*         model;
    QString*                devise;



};

#endif // CONNECTIONDB_H
