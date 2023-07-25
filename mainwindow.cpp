#include "mainwindow.h"

#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //main widget
    setWindowIcon(QIcon(":/images/logo.png"));
}

MainWindow::~MainWindow()
{
}

