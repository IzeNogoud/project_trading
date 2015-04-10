#include "mainwindow.h"
#include "connectiondb.h"
#include "help.h"
#include "faq.h"
#include "config.h"


#include <QWebElement>
#include <QWebFrame>
#include <QNetworkAccessManager>
#include <QSqlQuery>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // Fixe des dimensions à l'ouverture de la fenêtre principale, et indique le titre de la fenêtre.
    setFixedSize(780,330);
    move(200,200);
    setWindowTitle("Fluctu'Action");
    setWindowIcon(QIcon("fluctu_opt.png"));

    //Ajoute une barre de menu et l'implémente
    barMenu = menuBar() ;

    //fileMenu = barMenu->addMenu("&Fichier");
    aboutMenu = barMenu->addMenu("&Aide");

    //Ajoute des actions possible dans les options de la barre de menu
    configAct = aboutMenu->addAction( "Configuration", this, SLOT(configUrl()) ) ;
    helpAct = aboutMenu->addAction( "About", this, SLOT(About()) ) ;
    helpAct->setIcon(QIcon("fluctu_opt.png"));

    aideAct = aboutMenu->addAction( "FAQ", this, SLOT(Aide()) ) ;
    aideAct->setIcon(QIcon("interro.png"));

    toolBar = addToolBar("OutilsBarre");

    eurUsdAct = toolBar->addAction( "Euro / Dollar", this, SLOT(showEurUsd()));
    eurChfAct = toolBar->addAction( "Euro / Franc Suisse", this, SLOT(showEurChf()));


    QDateEdit* dateDebut = new QDateEdit(QDate::currentDate(),this);
    dateDebut->move(350,60);

    QDateEdit* dateFin = new QDateEdit(QDate::currentDate(),this);
    dateFin->move(460,60);

    QPushButton* filtrerAffichage = new QPushButton("Filtrer", this);
    filtrerAffichage->move(580,60);

    loadWebView();

    QTimer* timer = new QTimer;
    timer->setInterval(10000);
    timer->start();

    connect(timer, SIGNAL(timeout()), this, SLOT(loadWebView()));


}

MainWindow::~MainWindow()
{

}

void MainWindow::loadWebView()
{
    webView = new QWebView;
    webView->load(QUrl("http://fxrates.fr.forexprostools.com/index.php?force_lang=5&pairs_ids=1;10"));
    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(elementSearch()));
    webView->hide();

}

void MainWindow::elementSearch()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("forex.db");

    docElement = webView->page()->mainFrame()->documentElement();
    element = docElement.findAll("tr");


    for(int i (0); i<element.count() ; i++)
    {
        element2 = element.at(i).findAll("td");


        QSqlQuery requete;


            if(!db.open()) qDebug()<< "Ne peut pas ouvrir le fichier de la base de données pour l'insertion" ;
            else
            {

                requete.prepare("INSERT INTO deviseTable (Nom, Achat, Vente, Haut, Bas, Var, Date)"
                                "VALUES (:Nom, :Achat, :Vente, :Haut, :Bas, :Var, :Date)" );
                requete.bindValue(0, element2.at(0).toPlainText());
                requete.bindValue(1, element2.at(1).toPlainText());
                requete.bindValue(2, element2.at(2).toPlainText());
                requete.bindValue(3, element2.at(3).toPlainText());
                requete.bindValue(4, element2.at(4).toPlainText());
                requete.bindValue(5, element2.at(6).toPlainText());
                requete.bindValue(6, QDate::currentDate().toString("dd MMMM yyyy"));
                qDebug() << element2.at(0).toPlainText();
                qDebug() << element.at(i).toPlainText();
                requete.exec();

            }




    }

}

void MainWindow::About()
{
    Help* about = new Help(this);
    about->exec();
}

void MainWindow::Aide()
{
    Faq* faq = new Faq(this);
    faq->exec();
}


void MainWindow::showEurUsd()
{
    ConnectionDB(this, "EUR/USD");
}

void MainWindow::showEurChf()
{
    ConnectionDB(this, "EUR/CHF");
}

void MainWindow::configUrl()
{
    Config* config = new Config(this);
    config->exec();
}

