#ifndef HELP_H
#define HELP_H

#include <QDialog>

class QPushButton;

class Help : public QDialog
{
public:
    Help(QWidget *parent);
    ~Help();

private:
    QPushButton* closeButton;
};

#endif // HELP_H

