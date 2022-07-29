#include "mainwindow.h"

#include <QApplication>

static QApplication* _app;

QApplication& getApp() { return *_app; }

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    _app = &a;
    QStringList args = a.arguments();
    MainWindow w(args.count() < 2 ? "" : args.at(1));
    w.show();
    return a.exec();
}
