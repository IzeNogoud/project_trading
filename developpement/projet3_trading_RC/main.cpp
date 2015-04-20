

#include <QApplication>
#include "mainwindow.h"


#define q2c(string) string.toStdString()



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();


    return a.exec();
}
