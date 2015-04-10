#include "help.h"
#include <QLabel>
#include <QTabWidget>
#include <QVBoxLayout>


Help::Help(QWidget *parent = 0) : QDialog(parent)
{
    setWindowTitle("A propos de Fluctu'Action"); //Titre de la fenetre


    QTabWidget *Tab = new QTabWidget(this);
    Tab->setGeometry(15, 20, 470, 350);

    QLabel *frenchText = new QLabel;
    QLabel *englishText = new QLabel;

    //Insertion du texte
    frenchText->setText("<b>A propos</b><br /><br />"
                                  "<i>Nom</i> : Fluctu'Action<br /><br />"
                                  "<i>Version</i>  :  1.0<br /><br />"
                                  "<i>Basé sur</i> : Qt 5.4.1<br /><br />"
                                  "Compilé le <br /><br />"
                                  "<i>Copyright 2015 Tous droits réservés</i><br /><br />"
                                  "Ce program est sous licence GNU GPL version 3<br /><br />"
                                  "Le programme est fourni TEL QUEL sans GARANTIE D'AUCUNE SORTE,<br />"
                                  " Y COMPRIS DE GARANTIE DE LA CONCEPTION, DE QUALITÉ MARCHANDE ET<br />"
                                  " D'ADÉQUATION À UN USAGE PARTICULIER. <br /><br />"); //Insertion du texte

    englishText->setText("<b>About</b><br /><br />"
                                  "<i>Name</i> : Fluctu'Action<br /><br />"
                                  "<i>Version</i>  :  1.0<br /><br />"
                                  "<i>Based on</i> : Qt 5.4.1<br /><br />"
                                  "Release <br /><br />"
                                  "<i>Copyright 2015 All right reserved </i><br /><br />"
                                  "This program is licensed under the terms of the GNU General Public<br /> License version 3<br /><br />"
                                  "The program is provided AS IS without WARRANTY OF ANY KIND,<br />"
                                  " INCLUDING WARRANTIES OF DESIGN , MERCHANTABILITY AND<br />"
                                  " FITNESS FOR A PARTICULAR PURPOSE.<br /><br />"); //Insertion du texte




    Tab->addTab(frenchText, "Français");
    Tab->addTab(englishText, "English");
}

Help::~Help()
{

}

