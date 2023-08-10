#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    //ui
    //main widget
    QWidget *mainWidget;




    //tcp socket
private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

    //tcp slots
public slots:
    void ConnectToSlave();
    void ReadInformation();

    void ConnectTo();


    // QWidget interface
protected:
    virtual void closeEvent(QCloseEvent *event);


};
#endif // MAINWINDOW_H
