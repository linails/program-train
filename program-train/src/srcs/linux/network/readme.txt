# readme.txt
# Created Time: 2016-09-24 09:58:10
# Last modified: 2016-10-06 19:42:50
#

##########################################################

01.字节序分为大端字节序(高位存储在内存的低地址位)和小端字节序(高位存储在内存的高位)
    a.小端为主机字节序(pc采用小端字节序)
    b.大端为网络字节序(java虚拟机也是大端字节序)
    #include <netinet/in.h>
    unsigned long int htonl(unsigned long int hostlong);     :htonl : host to network long
    unsigned short int htons(unsigned short int hostshort);  :4个函数中，长整型用来转换IP
    unsigned long int ntohl(unsigned long int netlong);      :，短整型用来转换端口
    unsignd short int ntohs(unsigned short int netshort);

02.通用socket地址:
    socket网络编程接口中表示socket地址的是结构体sockaddr，其定义如下
    #include <bits/socket.h>
    struct sockaddr{
        sa_family_t  sa_family;   :地址族类型，通常与协议类型对应 { PF_UNIX, PF_INET, PF_INET6 }
        cahr         sa_data[14]; :用于存放socket地址值
    };
    ----------------------------------------------
    PF_UNIX  : 文件的路径名，长度可以达到108字节
    PF_INET  : 16bit端口号和32bit IPv4地址，共6个字节
    PF_INET6 : 16bit端口号，32bit流标志，128bit IPv6地址，32bit范围ID，共26个字节
    ----------------------------------------------
    #include <bits/socket.h>
    struct sockaddr_storage{
        sa_family_t       sa_family;
        unsigned long int __ss_align;
        char              _-ss_padding[128-sizeof(__ss_align)];
    };

03.专用socket地址
    #include <sys/un.h>
    struct sockaddr_un{
        sa_family_t sin_family;     //地址族：AF_UNIX
        char        sun_path[108]   //文件名路径
    };
    
    TCP/IP协议地址族有两个专用socket地址结构体
    ----------------------------------------------
    struct in_addr{
        u_int32_t   s_addr;
    }
    struct sockaddr_in{
        sa_family_t     sin_family; //地址族 : AF_INET
        u_int16_t       sin_port;   //端口号，要用网络字节序表示
        struct in_addr  sin_addr;   //IPv4 地址结构体
    };
    ----------------------------------------------
    struct in6_addr{
        unsigned char sa_addr[16];
    };
    struct sockaddr_in6{
        sa_family_t     sin6_family;    //地址族 : AF_INET6
        u_int16_t       sin6_port;      //端口号，要用网络字节序
        u_int32_t       sin6_flowinfo;  //流信息，应设置为0
        struct in6_addr sin6_addr;      //IPv6地址结构体
        u_int32_t       sin6_scope_id;  //scope ID, 尚处于实验阶段
    };
    ----------------------------------------------

04. #include <arpa/inet.h>
    /* 用于将字符串表示的IP地址src，转为网络字节序表示的IP地址dst */
    int inet_pton(int af, const char *src, void* dst);
    /* 进行相反的转换： cnt用于指定存储单元的大小
     *  cnt :
     *      #include <netinet/in.h>
     *      #define INET_ADDRSTRLEN  16
     *      #define INET6_ADDRSTRLEN 46
     *  失败返回NULL
     */
    const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);

05. #include <sys/types.h>
    #include <sys/socket.h>
    int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);

06. 高级I/O函数
    a.用于创建文件描述符的函数: pipe、dup/dup2函数
    b.用于读写数据的函数：readv/writev、sendfile、mmap/munmap、splice、tee函数
    c.用于控制i/o行为和属性的函数，包括fcntl函数

07. 服务端 socket 初始化方法的两种方法
    struct sockaddr_in  addr;
    char *serv_ip       = "211.217.168.13";
    cahr *serv_port     = "9001";

    memset(&addr, 0, sizeof(addr));

    addr.sin_family         = AF_INET;
    addr.sin_addr.s_addr    = inet_addr(serv_ip);
    addr.sin_port           = htons(atoi(serv_port));
    ----------------------------------------------
    struct sockaddr_in  addr;
    cahr *serv_port     = "9001";

    memset(&addr, 0, sizeof(addr));

    addr.sin_family         = AF_INET;
    addr.sin_addr.s_addr    = htonl(INADDR_ANY);
    addr.sin_port           = htons(atoi(serv_port));

08. 域名 与 IP
    #include <netdb.h>
    /* 利用域名获取IP地址 | domain --> IP */
    struct hostent * gethostbyname(const char *hostname);
    /* 利用IP地址获取域名 | IP --> domain */
    struct hostent * gethostbyaddr(const char *addr, socklen_t len, int family);
    ----------------------------------------------
    struct hostent {
        char *h_name;       //official name
        char ** h_aliases;  //alias list
        int h_addrtype;     //host address type
        int h_length;       //address length
        char ** h_addr_list;//address list  # 域名转IP时，只需关注 h_addr_list
    }
09. 
10.
12.

##########################################################

01.
02.
03.
04.
05.



