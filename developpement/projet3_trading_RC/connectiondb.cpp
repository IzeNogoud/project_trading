#include "connectiondb.h"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlError>
#include <QtSql/QSqlDatabase>
#include <QTableView>
#include <QSqlQuery>
#include <QNetworkRequest>
#include <QWebFrame>


ConnectionDB::ConnectionDB(QWidget *parent, QString debut, QString fin, QString devise)
{
    // Connection database

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("forex.db");
    if(!db.open()) qDebug()<< "Ne peut pas ouvrir le fichier de la base de données" ;
    else
    {
        //qDebug() << "Connection OK" ;
        QString sqlRequete;

        sqlRequete = "create table if not exists deviseTable (" ;
        sqlRequete += "Nom varchar(50)," ;
        sqlRequete += "Achat real,";
        sqlRequete += "Vente real," ;
        sqlRequete += "Haut real," ;
        sqlRequete += "Bas real," ;
        sqlRequete += "Var real," ;
        sqlRequete += "Date datetime )" ;


        QSqlQuery resultRequet = db.exec(sqlRequete);
        //qDebug() << resultRequet.lastError();

        model = new QSqlTableModel( NULL, db ) ;
        model->setTable("deviseTable");
        model->setFilter("Nom like'%" + devise + "' AND Date >='" + debut + "'" + " AND date <='" + fin + "'" );
        model->setSort(1,Qt::DescendingOrder);
        model->select();

        QTableView* view = new QTableView(parent) ;
        view->setGeometry(20,100,739,200);
        view->setModel( model );

        view->show();

        //db.close();
    }

}

ConnectionDB::~ConnectionDB()
{

}



