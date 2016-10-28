#include <sys/socket.h>
#include <sys/ioctl.h>  /*io通道头文件*/
#include <netinet/if_ether.h>  //以太头头文件
#include <arpa/inet.h> //网络字节序头文件
#include <netpacket/packet.h> //网络地址头文件
#include <net/if.h> //网络接口头文件

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

//arp报文结构
struct arpbuf
{
    struct ether_header eth;
    struct ether_arp arp;
};

void sendarp(char *eth_src_mac,char *eth_dst_mac,char *arp_src_mac,char *arp_dst_mac,
             char *src_ip,char *dst_ip,char *ifname,int op)
{
    //定义arp包缓冲区
    int buflen=sizeof(arpbuf);
    char buf[buflen];
    struct arpbuf *abuf=(struct arpbuf *)buf;//定义指针指向缓冲区buf
    struct sockaddr_ll toaddr;//指明发送数据包的接口
    struct in_addr targetIP,srcIP;
    struct ifreq ifr;
    int skfd;//socket描述符

    if((skfd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ARP)))<0)//htons网络字节序
    {
        exit(1);
    }

    //初始化socket和接口信息函数
    bzero(&toaddr,sizeof(toaddr));
    bzero(&ifr,sizeof(ifr));

    //复制到接口函数
    memcpy(ifr.ifr_name,ifname,strlen(ifname));

    ioctl(skfd,SIOCGIFINDEX,&ifr);//SIOCGIFINDEX获取接口索引
    toaddr.sll_ifindex = ifr.ifr_ifindex;//获取接口索引

    //填充ARP包
    //--构造ethII头部
    memcpy(abuf->eth.ether_dhost,eth_dst_mac,ETH_ALEN);//填充目的地址
    memcpy(abuf->eth.ether_shost,eth_src_mac,ETH_ALEN);//填充源地址
    abuf->eth.ether_type = htons(ETHERTYPE_ARP);//设置包类型为arp包
    //--构造ARP报文
    abuf->arp.arp_hrd = htons(ARPHRD_ETHER);//类型定义为以太
    abuf->arp.arp_pro = htons(ETHERTYPE_IP);//定义协议类型为ip
    abuf->arp.arp_hln = ETH_ALEN;//硬件长度地址
    abuf->arp.arp_pln = 4;//协议长度地址
    abuf->arp.arp_op = htons(op==1?ARPOP_REQUEST:ARPOP_REPLY);//填充操作类型

    //填充发送端MAC地址和IP地址
    memcpy(abuf->arp.arp_sha,arp_src_mac,ETH_ALEN);
    inet_pton(AF_INET,src_ip,&srcIP);//填充源IP前的转换(从十进制转化为四字节)
    memcpy(abuf->arp.arp_spa,&srcIP,4);//存入缓冲区

    memcpy(abuf->arp.arp_tha,arp_dst_mac,ETH_ALEN);
    inet_pton(AF_INET,dst_ip,&targetIP);//填充目的IP前的转换
    memcpy(abuf->arp.arp_tpa,&targetIP,4);
    //更改协议域
    toaddr.sll_family = PF_PACKET;

    /*发送数据包*/
    sendto(skfd,buf,buflen,0,(struct sockaddr *)&toaddr,sizeof(toaddr));
    close(skfd);
}
