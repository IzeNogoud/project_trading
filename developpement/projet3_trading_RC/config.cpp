#include "config.h"

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>

Config::Config(QWidget *parent = 0) : QDialog(parent)
{
    setWindowTitle("Configuration"); //Titre de la fenetre
    setFixedSize(600,150);

    closeButton = new QPushButton("Fermer"); //Bouton pour fermer la fenetre d'aide
    closeButton->setCursor(Qt::PointingHandCursor);
    connect(closeButton, SIGNAL(clicked()) ,this, SLOT(accept())); //Slot de fermeture avec le bouton

    validButton = new QPushButton("Valider");
    validButton->setCursor(Qt::PointingHandCursor);

    QVBoxLayout *layout = new QVBoxLayout(); //Affichage du texte et du bouton

    adresseLine = new QLineEdit;
    baseNameLine = new QLineEdit;

    QFormLayout* formulaireConfig = new QFormLayout;
    formulaireConfig->addRow("Adresse URL de récupération des données : ", adresseLine);
    formulaireConfig->addRow("Entrez le nom de la base de données : ", baseNameLine);

    layout->addLayout(formulaireConfig);
    layout->addWidget(validButton);
    layout->addWidget(closeButton);

    setLayout(layout);
}

Config::~Config()
{

}

