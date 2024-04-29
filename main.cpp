#include <QApplication>
#include <QMainWindow>
#include <QTableView>
#include <QPlainTextEdit>
#include <QPushButton>
#include "ui_fontkonfig.h"
#include "fontkonfig.moc"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FontKonfig window;
    window.show();
    return app.exec();
}
