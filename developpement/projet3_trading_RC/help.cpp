#include "help.h"
#include <QLabel>
#include <QVBoxLayout>


Help::Help(QWidget *parent = 0) : QDialog(parent)
{
    setWindowTitle("A propos de Fluctu'Action"); //Titre de la fenetre
    setFixedSize(500,400);

    closeButton = new QPushButton("Fermer"); //Bouton pour fermer la fenetre d'aide
    closeButton->setCursor(Qt::PointingHandCursor);
    connect(closeButton, SIGNAL(clicked()) ,this, SLOT(accept())); //Slot de fermeture avec le bouton

    //Insertion du texte
    QLabel *texte = new QLabel(tr("<b>A propos de Fluctu'Action</b><br />"
                                  "bla bla bla<br /"
                                  "><br /><b>About Fluctu'Action</b><br />"
                                  "bla bla bla")); //Insertion du texte

    QVBoxLayout *layout = new QVBoxLayout(); //Affichage du texte et du bouton
    layout->addWidget(texte);
    layout->addWidget(closeButton);

    setLayout(layout);

}

Help::~Help()
{

}

