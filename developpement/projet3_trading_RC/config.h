#ifndef CONFIG_H
#define CONFIG_H

#include <QCheckBox>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>

class Config : public QDialog
{
    Q_OBJECT

public:
    Config(QWidget* parent);
    ~Config();

public slots:
    void sauvegarder();

private:
    QPushButton*    closeButton;
    QPushButton*    validButton;
    QLineEdit*      adresseLine ;
    QLineEdit*      baseNameLine ;

    QCheckBox* eurUsdDl;
    QCheckBox* eurChfDl;
    QCheckBox* eurUsdShow;
    QCheckBox* eurChfShow;


};

#endif // CONFIG_H
