#include "terminal.h"
#include "ui_terminal.h"
#include <QtCore>
#include <QtNetwork>

terminal::terminal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::terminal)
{
    ui->setupUi(this);

    //先显示起点、终点站
    QFile file("/test/socket_show/source.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<file.errorString();
    QByteArray array;
    file.seek(13);
    array=file.read(12);
    ui->label_start->setText(tr(array));
    file.seek(139);
    array=file.read(12);
    ui->label_terminal->setText(tr(array));

    //连接服务器
    tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(QHostAddress("127.0.0.1"), 6666);
    if (!tcpSocket->waitForConnected(2000))
    {
        tcpSocket->disconnectFromHost();
        return;
    }
    else
        qDebug()<<"connected to host!"<<endl;

    //读取信息
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(msg_refresh()));
}

terminal::~terminal()
{
    delete ui;
}


//将读取的消息拆分显示在各个对应的label上
void terminal::msg_refresh()
 {
    //显示时间日期
    QDateTime time = QDateTime::currentDateTime();
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_time->setText(strTime);
    ui->label_time->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);


    //创建QString字符串用来存放从server读取的一条信息
    QString line;
    line += tcpSocket->readAll();

    //显示公交线路
    QString bus_id;
    bus_id = line.mid(0,3);
    ui->bus_number->setText(bus_id);
    ui->bus_number->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    //gprs状态
    QFont gprs_ft, gps_ft;
    QPalette gprs_pa, gps_pa;
    QString gprs_state;
    gprs_state = line.mid(3,3);
    ui->gprs_state->setText(gprs_state);
    ui->gprs_state->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    gprs_ft.setPointSize(16);
    gprs_pa.setColor(QPalette::WindowText,Qt::green);
    ui->gprs_state->setFont(gprs_ft);
    ui->gprs_state->setPalette(gprs_pa);

    //gps状态
    QString gps_state;
    gps_state = line.mid(6,3);
    ui->gps_state->setText(gps_state);
    ui->gps_state->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    gps_ft.setPointSize(16);
    gps_pa.setColor(QPalette::WindowText,Qt::green);
    ui->gps_state->setFont(gps_ft);
    ui->gps_state->setPalette(gps_pa);

    //路段限速
    QString limit;
    limit = line.mid(9,2);
    ui->limit->setText(limit);
    ui->limit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    //当前行驶速度
    QString speed;
    speed = line.mid(11,2);
    ui->speed->setText(speed);
    ui->speed->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    //当前站点
    QString cur_station;
    cur_station = line.mid(13,12);
    ui->cur_station->setText(cur_station);
    ui->cur_station->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    //下一站
    QString next_station;
    next_station = line.mid(25,12);
    ui->next_station->setText(next_station);
    ui->next_station->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
 }













