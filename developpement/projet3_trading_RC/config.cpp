/**
* \brief Cette classe permet l'affichage d'une fenêtre de configuration.
* Crée un fichier Xml afin d'enregistrer les données renseigner par l'utilisateur
* ------------
* ------------
* \author IzeNogoud
* ------------
* \date 24 Mars 2015
*
*/


#include "config.h"
#include "mainwindow.h"

#include <QCheckBox>
#include <QDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDir>

Config::Config(QWidget *parent = 0) : QDialog(parent)
{
    /** Initialise une variable pour l'écriture et la lecture du fichier Xml */
    QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    /** Indique le chemin du fichier Xml */
    QSettings::setPath(XmlFormat, QSettings::UserScope, QDir::currentPath());
    /** Initialise le nom du dossier et le nom du fichier  */
    QSettings settings(XmlFormat, QSettings::UserScope, ".config", "Project_Trading");


    /** Permet d'ouvrir le groupe du fichier Xml */
    settings.beginGroup("filesConfig");

    /** Recherche l'adresse url enregistré dans le fichier xml, une adresse par défault est renseigner si vide */
    adresseLine = new QLineEdit(settings.value("Adresse", "http://fxrates.fr.forexprostools.com/index.php?force_lang=5&pairs_ids=" ).toString());
    /** Recherche du nom de la base dans le fichier xml */
    baseNameLine = new QLineEdit(settings.value("NomBase", "forex.db").toString());

    setWindowTitle("Configuration"); /** Titre de la fenetre */
    setFixedSize(900,300);

    closeButton = new QPushButton("Fermer"); /** Bouton pour fermer la fenetre d'aide */
    closeButton->setCursor(Qt::PointingHandCursor);
    connect(closeButton, SIGNAL(clicked()) ,this, SLOT(accept())); /** Slot de fermeture avec le bouton */

    validButton = new QPushButton("Enregistrer");
    validButton->setCursor(Qt::PointingHandCursor);
    connect(validButton, SIGNAL(clicked()), this, SLOT(sauvegarder())); /** Slot de sauvergarde */

    QVBoxLayout *layout = new QVBoxLayout(); /** Affichage du texte et du bouton */


    QFormLayout* formulaireConfig = new QFormLayout;
    formulaireConfig->addRow("Adresse URL de récupération des données : ", adresseLine);
    formulaireConfig->addRow("Entrez le nom de la base de données : ", baseNameLine);

    QGroupBox* groupBoxDl = new QGroupBox("Couples de devise à télécharger");

    eurUsdDl = new QCheckBox("Euro / Dollar");
    eurChfDl = new QCheckBox("Euro / Franc suisse");

    /** Recherche dans le fichier Xml les dernières valeur pour les checkbox */
    eurUsdDl->setChecked(settings.value("cBoxEDdl").toBool());
    eurChfDl->setChecked(settings.value("cBoxEFSdl").toBool());

    QVBoxLayout* vBoxDl = new QVBoxLayout;
    vBoxDl->addWidget(eurUsdDl);
    vBoxDl->addWidget(eurChfDl);

    groupBoxDl->setLayout(vBoxDl);



    QGroupBox* groupBoxShow = new QGroupBox("Couples de devise à afficher");

    eurUsdShow = new QCheckBox("Euro / Dollar");
    eurChfShow = new QCheckBox("Euro / Franc suisse");
    eurUsdShow->setChecked(settings.value("cBoxED").toBool());
    eurChfShow->setChecked(settings.value("cBoxEFS").toBool());

    QVBoxLayout* vBoxShow = new QVBoxLayout;
    vBoxShow->addWidget(eurUsdShow);
    vBoxShow->addWidget(eurChfShow);

    groupBoxShow->setLayout(vBoxShow);


    layout->addLayout(formulaireConfig);
    layout->addWidget(groupBoxDl);
    layout->addWidget(groupBoxShow);
    layout->addWidget(validButton);
    layout->addWidget(closeButton);

    setLayout(layout);

    /** Ferme le groupe */
    settings.endGroup();
}

Config::~Config()
{

}

/** Permet la sauvegarde  */
void Config::sauvegarder()
{

    /** l'action de sauvegarder rinitialise l'application, on demande a l'utilisateur une confirmation */
    int reponse = QMessageBox::question(NULL, "Enregistrement et raifraichissement des paramètre", "L'enregistrement des nouveaux paramètres entrainera le rafraichissement de l'application !<br />Êtes vous sûr de vouloir continuer ?", QMessageBox::Yes | QMessageBox::No);

    if(reponse == QMessageBox::Yes)
    {
    QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    QSettings::setPath(XmlFormat, QSettings::UserScope, QDir::currentPath());
    QSettings settings(XmlFormat, QSettings::UserScope, ".config", "Project_Trading");


    settings.beginGroup("filesConfig");

    /** Ajout de l'adresse url renseigner par l'utilisateur dans le fichier Xml */
    settings.setValue("Adresse", adresseLine->text());
    /** Ajout du nom de la base renseigner par l'utilisateur dans le fichier Xml */
    settings.setValue("NomBase", baseNameLine->text());

    /** Ajoute au fichier Xml les valeurs des checkbox */
    settings.setValue("cBoxEDdl", eurUsdDl->isChecked());
    settings.setValue("cBoxEFSdl", eurChfDl->isChecked());

    settings.setValue("cBoxED", eurUsdShow->isChecked());
    settings.setValue("cBoxEFS", eurChfShow->isChecked());

    settings.endGroup();

    /** Ferme et relance l'application pour prendre les cahngement en compte */
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    qApp->quit();
    }

}

