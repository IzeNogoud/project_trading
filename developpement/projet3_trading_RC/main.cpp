

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "mainwindow.h"


#define q2c(string) string.toStdString()



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    w.show();


    return a.exec();
}
