#ifndef FAQ_H
#define FAQ_H

#include <QDialog>
#include <QPushButton>

class Faq : public QDialog
{
public:
    Faq(QWidget* parent);
    ~Faq();


private:
    QPushButton* closeButton;
};

#endif // FAQ_H
