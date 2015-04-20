#ifndef CONNECTIONDB_H
#define CONNECTIONDB_H

#include <QSqlDatabase>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QWebPage>
#include <QWebView>
#include <QWebElement>

class QSqlTableModel;
class QWidget;


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
    QWidget*                m_parent;
    QString                 m_debut;
    QString                 m_fin;
    QString                 m_devise;

};

#endif // CONNECTIONDB_H
