#include "widget.h"
#include "ui_widget.h"
#include "arp.cpp"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Send_pushButton_clicked()
{
    //dingyisige huanchongqu baocun src_mac he dst_mac
    char eth_src_mac[6];
    char eth_dst_mac[6];
    char arp_src_mac[6];
    char arp_dst_mac[6];

    //QT zifuchuan zhuanhuawei 6zijie mac addr dehanshu
    QTSTRtoMAC(ui->eth_src_mac_Edit->text(),eth_src_mac);
    QTSTRtoMAC(ui->eth_dst_mac_Edit->text(),eth_dst_mac);
    QTSTRtoMAC(ui->arp_src_mac_Edit->text(),arp_src_mac);
    QTSTRtoMAC(ui->arp_dst_mac_Edit->text(),arp_dst_mac);

    //IPdizhileixing zhuanhuan wei char leixing
    QByteArray srcipstr = ui->src_ip_Edit->text().toLatin1();
    QByteArray dstipstr = ui->dst_ip_Edit->text().toLatin1();
    QByteArray ifnamestr = ui->ifname_Edit->text().toLatin1();

    char *srcip = srcipstr.data();
    char *dstip = dstipstr.data();
    char *ifname = ifnamestr.data();

    int op = ui->op_comboBox->currentText()=="request"?1:2;

    //Sendarp
    sendarp(eth_src_mac,eth_dst_mac,arp_src_mac,arp_dst_mac,srcip,dstip,ifname,op);
}

//QT zifuchuan zhuanhuawei 6zijie mac addr dehanshu
void Widget::QTSTRtoMAC(QString str, char *mac)
{
    QStringList list = str.split(":");
    bool ok;
    for(int i = 0;i<6;i++)
    {
        QString temp = list.at(i);
        *(mac+i)=temp.toInt(&ok,16);//yi 16jinzhi zhuanhuan
    }
}
