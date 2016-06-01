#ifndef TERMINAL_H
#define TERMINAL_H

#include <QMainWindow>
#include <QProcess>
#include <QString>
#include <QFileInfo>
#include <QTextCodec>
#include <QStringList>
#include <QDateTime>
#include <QDebug>
#include <QBuffer>
#include <QTextStream>
#include <QFile>
#include <QTimer>
#include <QThread>
#include <QAbstractSocket>
class QTcpSocket;

namespace Ui {
class terminal;
}

class terminal : public QMainWindow
{
    Q_OBJECT

public:
    explicit terminal(QWidget *parent = 0);
    ~terminal();

private slots:
    void msg_refresh();
/*    void busid_refresh();
    void gprs_refresh();
    void gps_refresh();
    void limit_refresh();
    void speed_refresh();
    void curstation_refresh();
    void nextstation_refresh();*/

private:
    Ui::terminal *ui;
    QTcpSocket *tcpSocket;
    QProcess myProcess;
};

#endif // TERMINAL_H
