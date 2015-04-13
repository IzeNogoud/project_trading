#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QPushButton>
#include <QWebElement>
#include <QSqlDatabase>
#include <QtWebKitWidgets/QWebView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void        About();
    void        Aide();
    void        showEurUsd();
    void        showEurChf();


    void        configUrl();
    void        elementSearch();
    void        loadWebView();




private:

    QSignalMapper*      signalMapper;

    QMenuBar*           barMenu ;
    QMenu*              aboutMenu ;
    QMenu*              fileMenu ;
    QAction*            helpAct ;
    QAction*            configAct ;
    QAction*            aideAct ;
    QAction*            eurUsdAct ;
    QAction*            eurChfAct ;
    QToolBar*           toolBar;

    QWebView*           webView ;
    QWebElement         docElement;
    QWebElementCollection element;
    QWebElementCollection element2;

    QSqlDatabase            db;


    QString nom, achat, vente, haut, bas, var, date;

    QString dateDebutString;
    QString dateFinString;
    QDateEdit* dateFin;
    QDateEdit* dateDebut;





};

#endif // MAINWINDOW_H
