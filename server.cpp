#include <stdio.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <string.h>  
#include <sys/types.h>  
#include <netinet/in.h>	//定義數據結構  
#include <sys/socket.h>  //提供socket函數及數據結構
#include <sys/wait.h>  //提供進程等待
#include <arpa/inet.h>  //提供IP地址轉換函數
#include <unistd.h> //提供通用的文件、目录、程序及进程操作的函数 
#define SERVPORT 3333  
#define BACKLOG 10  
#define MAXSIZE 1024  
/* 
 *自定义信息 
 */  
typedef struct MyMessage{  //定義結構體
    int ID;  //一個整型變量
    char info[256];  //一個字符串
}MyMessage,*pMyMessage;  //幫結構體命名，這是要發送的信息的結構


int main() {  
    int sockfd, client_fd;  
	
    struct sockaddr_in my_addr; //我的地址
    struct sockaddr_in remote_addr;  //cilent地址
    //创建套接字  
	
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  //判斷是否創建成功
        perror("socket create failed!");  //就是創建了一個互聯網範圍的TCP套接字
        exit(1);  
    } 


 
    //绑定端口地址  
    my_addr.sin_family = AF_INET;  
    my_addr.sin_port = htons(SERVPORT);  
    my_addr.sin_addr.s_addr = INADDR_ANY;  
    bzero(&(my_addr.sin_zero), 8);  //初始化
    if (bind(sockfd, (struct sockaddr*) &my_addr, sizeof(struct sockaddr))== -1) {  
        perror("bind error!");  
        exit(1);  
    }
	
	
    //监听端口  
    if (listen(sockfd, BACKLOG) == -1) {  
        perror("listen error");  
        exit(1);  
    }  
  
    while (1) {  
        //int sin_size = sizeof(struct sockaddr_in);  
        socklen_t sin_size = sizeof(struct sockaddr_in);  
        if ((client_fd = accept(sockfd,(struct sockaddr*) &remote_addr,&sin_size)) == -1){  
            perror("accept error!");  
            continue;  
        }  
        printf("Received a connection from %s\n", (char*)inet_ntoa(remote_addr.sin_addr)); 
       cout<< (char*)inet_ntoa(remote_addr.sin_addr)<<endl;
  
      
        //子进程段  
        if (!fork()){  
            //接受client发送的请示信息  
            int rval;  
            char buf[MAXSIZE];  
            if ((rval = read(client_fd, buf, MAXSIZE)) < 0) {  
                perror("reading stream error!");  
                continue;  
            }  
            printf("%s\n", buf);  
            //向client发送信息  
            char* msg = "Hello,Mr hqlong, you are connected!\n";  
            MyMessage data;  
            memset((void *)&data,0,sizeof(MyMessage));  
            data.ID=123;  
            strcpy(data.info,"This message come 6666from ServSocket!");  
            if(send(client_fd,(void*)&data,sizeof(MyMessage),0) == -1){  
                perror("send error!");  
            }  
            close(client_fd);  
            exit(0);  
        }  
        close(client_fd);  
    }  
    return 0;  
}  
