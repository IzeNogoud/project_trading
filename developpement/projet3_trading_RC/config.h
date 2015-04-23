#ifndef CONFIG_H
#define CONFIG_H


#include <QDialog>
#include <QSettings>

class QPushButton;
class QCheckBox;
class QLineEdit;

class Config : public QDialog
{
    Q_OBJECT

public:
    Config(QWidget* parent);
    ~Config();

public slots:
    void            sauvegarder();

private:
    QPushButton*    closeButton;
    QPushButton*    validButton;
    QLineEdit*      adresseLine ;
    QLineEdit*      baseNameLine ;

    QCheckBox*      eurUsdDl;
    QCheckBox*      eurChfDl;
    QCheckBox*      eurUsdShow;
    QCheckBox*      eurChfShow;

};

#endif // CONFIG_H
