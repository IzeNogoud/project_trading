#include "mainwindow.h"
#include "connectiondb.h"
#include "help.h"
#include "faq.h"
#include "config.h"


#include <QWebElement>
#include <QWebFrame>
#include <QNetworkAccessManager>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QIODevice>
#include <QSettings>
#include <QXmlStreamReader>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    QSettings::setPath(XmlFormat, QSettings::UserScope, QDir::currentPath());
    QSettings settings(XmlFormat, QSettings::UserScope, ".config", "Project_Trading");

    /** Fixe des dimensions à l'ouverture de la fenêtre principale, et indique le titre de la fenêtre. */
    setFixedSize(875,330);
    move(200,200);
    setWindowTitle("Fluctu'Action");
    setWindowIcon(QIcon("fluctu_opt.png"));
    QLabel* image = new QLabel(this);
    image->setPixmap(QPixmap("fluctu2.png"));
    image->move(350,100);
    image->setFixedSize(200,200);

    /** Ajoute une barre de menu et l'implémente */
    barMenu = menuBar() ;

    fileMenu = barMenu->addMenu("&Fichier");
    aboutMenu = barMenu->addMenu("&Aide");

    /** Ajoute des actions possible dans les options de la barre de menu */
    configAct = fileMenu->addAction( "Configuration", this, SLOT(configUrl()) ) ;

    /** Le menu A propos */
    helpAct = aboutMenu->addAction( "About", this, SLOT(About()) ) ;
    helpAct->setIcon(QIcon("fluctu_opt.png"));

    /** Le menu FAQ */
    aideAct = aboutMenu->addAction( "FAQ", this, SLOT(Aide()) ) ;
    aideAct->setIcon(QIcon("interro.png"));

    toolBar = addToolBar("OutilsBarre");


    /** Créer la connection lors du clic, pour afficher le tableau des cotations pour les devise Euros / Franc suisse*/
    eurChfAct = toolBar->addAction( "Euro / Franc Suisse" );
    connect(eurChfAct, SIGNAL(triggered()), this, SLOT(showEurChf()));
    if(settings.value("filesConfig/cBoxEFS").toBool() == false) eurChfAct->setVisible(false);

    /** A la modification de la date de filtre, un signal est envoyé pour rafraichir et ré-afficher le tableau filtrer*/
    dateDebut = new QDateEdit(this);
    dateDebut->move(350,60);
    dateDebutString = dateDebut->date().toString("dd.MM.yyyy");
    connect(dateDebut, SIGNAL(dateChanged(QDate)), this, SLOT(showEurChf()));

    dateFin = new QDateEdit(QDate::currentDate(),this);
    dateFin->move(460,60);
    dateFinString = dateFin->date().toString("dd.MM.yyyy");
    connect(dateFin, SIGNAL(dateChanged(QDate)), this, SLOT(showEurChf()));

    /** Créer la connection lors du clic, pour afficher le tableau des cotations pour les devise Euros / Dollar*/
    eurUsdAct = toolBar->addAction( "Euro / Dollar");
    connect(eurUsdAct, SIGNAL(triggered()), this, SLOT(showEurUsd()));


    /** A la modification de la date de filtre, un signal est envoyé pour rafraichir et ré-afficher le tableau filtrer*/
    dateDebut = new QDateEdit(this);
    dateDebut->move(350,60);
    dateDebutString = dateDebut->date().toString("dd.MM.yyyy");
    connect(dateDebut, SIGNAL(dateChanged(QDate)), this, SLOT(showEurUsd()));

    dateFin = new QDateEdit(QDate::currentDate(),this);
    dateFin->move(460,60);
    dateFinString = dateFin->date().toString("dd.MM.yyyy");
    connect(dateFin, SIGNAL(dateChanged(QDate)), this, SLOT(showEurUsd()));

    /** Appel de la fonction loadWebView qui charge une page web, et récupère les données désirées */
    loadWebView();

    /** Timer permettant de réactualiser les données télécharger toutes les 10 secondes */
    QTimer* timer = new QTimer;
    timer->setInterval(10000);
    timer->start();

    connect(timer, SIGNAL(timeout()), this, SLOT(loadWebView()));
}

MainWindow::~MainWindow()
{

}

/** Charge la page entière de l'URL renseignée */
void MainWindow::loadWebView()
{
    QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    QSettings::setPath(XmlFormat, QSettings::UserScope, QDir::currentPath());
    QSettings settings(XmlFormat, QSettings::UserScope, ".config", "Project_Trading");


    webView = new QWebView;
    webView->load(QUrl(settings.value("filesConfig/Adresse").toString()));
    connect(webView, SIGNAL(loadFinished(bool)), this, SLOT(elementSearch())); /** Appel un slot à la fin du chargement */
    webView->hide(); /** cache le widget généré */


}

/** Recherche dans la page les lignes du tableau uis chaque colone afin de la rentré dans la base de données */
void MainWindow::elementSearch()
{
    QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    QSettings::setPath(XmlFormat, QSettings::UserScope, QDir::currentPath());
    QSettings settings(XmlFormat, QSettings::UserScope, ".config", "Project_Trading");

    /** connection a la base pour l'insertion */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(settings.value("NomBase").toString());

    /** récupère le corp de la page pour pouvoir le manipuler */
    docElement = webView->page()->mainFrame()->documentElement();
    element = docElement.findAll("tr"); /** Récupère toute les lignes (tr) */

    /** Boucle sur les lignes */
    for(int i (0); i<element.count() ; i++)
    {
        element2 = element.at(i).findAll("td"); /** Récupère toutes les colonnes (td) */


        QSqlQuery requete;

            /** Ajoute les données récupérer dans les bon champs de la base de données */
            if(!db.open()) qDebug()<< "Ne peut pas ouvrir le fichier de la base de données pour l'insertion" ;
            else
            {
                QSqlQueryModel* model = new QSqlQueryModel;
                model->setQuery(QString("SELECT Nom, Var FROM deviseTable WHERE Nom like '%" + element2.at(0).toPlainText() + "' ORDER BY Heure DESC limit 1"), db);


                if( ( model->record(0).value(0).toString() == element2.at(0).toPlainText() ) &&
                        ( model->record(0).value(1).toString() != element2.at(6).toPlainText() ) ||
                        ( ( model->record(0).value(0).toString() == "") && ( model->record(0).value(1).toString() == "")) )
                {

                requete.prepare("INSERT INTO deviseTable (Nom, Achat, Vente, Haut, Bas, Var, Date, Heure)"
                                "VALUES (:Nom, :Achat, :Vente, :Haut, :Bas, :Var, :Date, :Heure)" );
                requete.bindValue(0, element2.at(0).toPlainText());
                requete.bindValue(1, element2.at(1).toPlainText());
                requete.bindValue(2, element2.at(2).toPlainText());
                requete.bindValue(3, element2.at(3).toPlainText());
                requete.bindValue(4, element2.at(4).toPlainText());
                requete.bindValue(5, element2.at(6).toPlainText());
                requete.bindValue(6, QDate::currentDate().toString("dd.MM.yyyy"));
                requete.bindValue(7, QTime::currentTime().toString("hh:mm:ss"));

                requete.exec();
                }
            }
    }
}


/** Affiche le tableau de devise euro / dollar */
void MainWindow::showEurUsd()
{

    dateDebutString = dateDebut->date().toString("dd.MM.yyyy");
    dateFinString = dateFin->date().toString("dd.MM.yyyy");
    ConnectionDB(this, dateDebutString, dateFinString, "EUR/USD");
}

/** Affiche le tableau de devise euro / franc suisse */
void MainWindow::showEurChf()
{
        dateDebutString = dateDebut->date().toString("dd.MM.yyyy");
        dateFinString = dateFin->date().toString("dd.MM.yyyy");
        ConnectionDB(this, dateDebutString, dateFinString, "EUR/CHF");

}


/** Appel la page A propos de */
void MainWindow::About()
{
    Help* about = new Help(this);
    about->exec();
}

/** Appel la page FAQ */
void MainWindow::Aide()
{
    Faq* faq = new Faq(this);
    faq->exec();
}


/** Appel la page configuration */
void MainWindow::configUrl()
{
    Config* config = new Config(this);
    config->exec();
}

bool readXmlFile(QIODevice &device, QSettings::SettingsMap &map) {
  QXmlStreamReader xmlReader(&device);
  QStringList elements;

  // Solange Ende nicht erreicht und kein Fehler aufgetreten ist
  while (!xmlReader.atEnd() && !xmlReader.hasError()) {
    // Nächsten Token lesen
    xmlReader.readNext();

    // Wenn Token ein Startelement
    if (xmlReader.isStartElement() && xmlReader.name() != "Settings") {
      // Element zur Liste hinzufügen
      elements.append(xmlReader.name().toString());
    // Wenn Token ein Endelement
    } else if (xmlReader.isEndElement()) {
      // Letztes Element löschen
      if(!elements.isEmpty()) elements.removeLast();
    // Wenn Token einen Wert enthält
    } else if (xmlReader.isCharacters() && !xmlReader.isWhitespace()) {
      QString key;

      // Elemente zu String hinzufügen
      for(int i = 0; i < elements.size(); i++) {
        if(i != 0) key += "/";
        key += elements.at(i);
      }

      // Wert in Map eintragen
      map[key] = xmlReader.text().toString();
    }
  }

  // Bei Fehler Warnung ausgeben
  if (xmlReader.hasError()) {
    qDebug() << xmlReader.errorString();
    return false;
  }

  return true;
}



bool writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map) {
  QXmlStreamWriter xmlWriter(&device);

  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("Settings");

  QStringList prev_elements;
  QSettings::SettingsMap::ConstIterator map_i;

  // Alle Elemente der Map durchlaufen
  for (map_i = map.begin(); map_i != map.end(); map_i++) {

    QStringList elements = map_i.key().split("/");

    int x = 0;
    // Zu schließende Elemente ermitteln
    while(x < prev_elements.size() && elements.at(x) == prev_elements.at(x)) {
      x++;
    }

    // Elemente schließen
    for(int i = prev_elements.size() - 1; i >= x; i--) {
      xmlWriter.writeEndElement();
    }

    // Elemente öffnen
    for (int i = x; i < elements.size(); i++) {
      xmlWriter.writeStartElement(elements.at(i));
    }

    // Wert eintragen
    xmlWriter.writeCharacters(map_i.value().toString());

    prev_elements = elements;
  }

  // Noch offene Elemente schließen
  for(int i = 0; i < prev_elements.size(); i++) {
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();

  return true;
}


