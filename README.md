# 计算机网络PBL----ARP攻击工具编写
## arp断网攻击
spoof -i eth0 -t 网关 targetIP
## arp流量转发
## arp群体攻击
## arp编程
###   1.raw socket
####     int socket(int domain,int type,int protocol);//返回sockfd描述符
         domain:协议域；常见参数：AF_INET(IPV4)|AF_INET6(IPV6);原始套接字：PF_PACKET
         type：套接字类型；常见参数：SOCK_STREAM(TCP)|SOCK_DGRAM(UDP);原始套接字：SOCK_RAW
         protocal：协议类型；常见参数：IPPROTO_TCP|IPPROTO_UDP;原始套接字:ETH_P_IP|ETH_P_ARP|ETH_P_ALL
###   2.网络字节序函数
         htonl()
         ntohl()
         htons()
         ntohs()
