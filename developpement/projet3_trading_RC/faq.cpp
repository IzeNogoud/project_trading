#include "faq.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QtWidgets>

Faq::Faq(QWidget *parent) : QDialog(parent)
{
    //Ajoute le titre de la fenetre
    setWindowTitle("FAQ");

    //Création d'un widget pour les onglets
    QTabWidget *Tab = new QTabWidget(this);
    Tab->setGeometry(30, 20, 770, 450); // fixe la position et la taille du widget

    //Création des labels ou le texte apparaitra
    QLabel *frenchText = new QLabel;
    QLabel *englishText = new QLabel;

    //Insertion du texte en français
    frenchText->setText("<b><i>Comment utiliser Flutu'Action ?</i></b><br /><br />"
                        "Fluctu'Action est une application permettant de suivre en temps réel"
                        " l'évolution des cotations, en recherchant dynamiquement<br /> les données sur"
                        "http://www.forexpro.com.<br /><br /><br />"
                        "<b><i>Pour qui est destiné Fluctu'Action ?</i></b><br /><br />"
                        "Fluctu'Action a été crée pour tout utilisateur désirant suivre le cours des monnaies internationnales.<br /><br /><br />"
                        "<b><i>Pourquoi Fluctu'Action ? </i></b><br /><br />"
                        "Permettre un accès rapide et intuitif afin de ne plus perdre de temps.<br /><br /><br />"
                        "<b><i>Comment utiliser Fluctu'Action ? </i></b><br /><br />"
                        "Fluctu'Action est très simple d'utilisation. Pour pouvoir afficher le tableau de devise voulu,"
                        " il suffit de cliquer sur le couple<br /> de devise dans la barre de menu afin d'afficher les"
                        " dernières données téléchargées.Pour pouvoir changer la source<br />  de récupération de données,"
                        " il vous faudra modifier l'adresse dans Aide->Configuration, indiquer l'adresse URL puis Valider. ");



    //Insertion du texte en anglais
    englishText->setText("<b><i>What is Fluctu'Action ? </i></b><br /><br />"
                         "Fluctu'Action is an application that follows up in real time"
                         " the evolution of quotations by dynamically seeking data<br /> on "
                         "http://www.forexpro.com.<br /><br /><br />"
                         "<b><i>Who is it for ? </i></b><br /><br />"
                         "It was created for any user wishing to follows up the internationnal market price.<br /><br /><br />"
                         "<b><i>Why use it ? </i></b><br /><br />"
                         "Allow quick and intuitive access saving time.<br /><br /><br />"
                         "<b><i>How use it ? </i></b><br /><br />"
                         "Fluctu'Action is very easy to use. To display the currency table,"
                         " Just click on the currency pair in the menu bar to display<br /> the last data downloaded."
                         "To change the source data recovery, you need to modify the address in Help-> Configuration,"
                         " specify the<br /> URL and then validate.");

    //Ajoute les textes dans le widget des onglets
    Tab->addTab(frenchText, "Français");
    Tab->addTab(englishText, "English");


}


Faq::~Faq()
{

}

