#include "faq.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QtWidgets>

Faq::Faq(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("FAQ");

    QTabWidget *Tab = new QTabWidget(this);
    Tab->setGeometry(30, 20, 800, 650);

    QLabel *frenchText = new QLabel;
    QLabel *englishText = new QLabel;

    frenchText->setText("Comment utiliser Flutu'Action ?");
    englishText->setText(tr("<b>How to use Flutu'Action ?</b><br />Blablabla"));


    Tab->addTab(frenchText, "Français");
    Tab->addTab(englishText, "English");


}


Faq::~Faq()
{

}

