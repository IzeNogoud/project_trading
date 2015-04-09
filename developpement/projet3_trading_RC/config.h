#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class Config : public QDialog
{
public:
    Config(QWidget* parent);
    ~Config();

private:
    QPushButton*    closeButton;
    QPushButton*    validButton;
    QLineEdit*      adresseLine ;
    QLineEdit*      baseNameLine ;
};

#endif // CONFIG_H
