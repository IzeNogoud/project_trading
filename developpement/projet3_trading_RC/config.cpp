#include "config.h"

#include <QCheckBox>
#include <QDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QVBoxLayout>

Config::Config(QWidget *parent = 0) : QDialog(parent)
{
    setWindowTitle("Configuration"); /** Titre de la fenetre */
    setFixedSize(600,300);

    closeButton = new QPushButton("Fermer"); /** Bouton pour fermer la fenetre d'aide */
    closeButton->setCursor(Qt::PointingHandCursor);
    connect(closeButton, SIGNAL(clicked()) ,this, SLOT(accept())); /** Slot de fermeture avec le bouton */

    validButton = new QPushButton("Enregistrer");
    validButton->setCursor(Qt::PointingHandCursor);

    QVBoxLayout *layout = new QVBoxLayout(); /** Affichage du texte et du bouton */

    adresseLine = new QLineEdit;
    baseNameLine = new QLineEdit;

    QFormLayout* formulaireConfig = new QFormLayout;
    formulaireConfig->addRow("Adresse URL de récupération des données : ", adresseLine);
    formulaireConfig->addRow("Entrez le nom de la base de données : ", baseNameLine);

    QGroupBox* groupBoxDl = new QGroupBox("Couples de devise à télécharger");

    QCheckBox* eurUsdDl = new QCheckBox("Euro / Dollar");
    QCheckBox* eurChfDl = new QCheckBox("Euro / Franc suisse");
    eurChfDl->setChecked(true);
    eurUsdDl->setChecked(true);

    QVBoxLayout* vBoxDl = new QVBoxLayout;
    vBoxDl->addWidget(eurUsdDl);
    vBoxDl->addWidget(eurChfDl);

    groupBoxDl->setLayout(vBoxDl);



    QGroupBox* groupBoxShow = new QGroupBox("Couples de devise à afficher");

    QCheckBox* eurUsdShow = new QCheckBox("Euro / Dollar");
    QCheckBox* eurChfShow = new QCheckBox("Euro / Franc suisse");
    eurChfShow->setChecked(true);
    eurUsdShow->setChecked(true);

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
}

Config::~Config()
{

}

