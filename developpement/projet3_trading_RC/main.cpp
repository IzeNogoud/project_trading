#include "mainwindow.h"
#include "connectiondb.h"
#include <QApplication>
#include <QMessageBox>



#define q2c(string) string.toStdString()



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.show();


    return a.exec();
}
