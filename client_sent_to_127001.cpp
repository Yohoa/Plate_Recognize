#include <stdio.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <string.h>  
#include <sys/types.h>  
#include <netinet/in.h>  
#include <sys/socket.h>  
#include <sys/wait.h>  
#include <arpa/inet.h>  
#include <unistd.h>  
#define SERVPORT 3333  //服務器端口
#define MAXDATASIZE 100  
#define SERVER_IP "127.0.0.1"  //服務器IP地址
//#define DATA  "this is a 555client message"  
/* 
 *自定义信息 
 */  
// typedef struct MyMessage{  20170328
    // int ID;  
    // char info[256];  
// }MyMessage,*pMyMessage;  

int main(int argc, char* argv[]) {  
   
    char hello[]="蓝牌:K62933";//一個14位的數組
	char m1[]="2017.04.26 20:45:16 E11847.5315 N3156.4055\n";
	char m2[]="蓝牌:苏AL8D01";
    char sockfd, recvbytes;  
    //char buf[MAXDATASIZE]='111';  //?????
    // MyMessage recvData; 
    
    struct sockaddr_in serv_addr;  
  for(char i = 0; i<2; i++)
  {
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  //開啟 Socket介面，通信類型AF_INET, 連接方式TCP
        perror("socket error!");  //拋出錯誤信息
        exit(1);  
    }  
    bzero(&serv_addr, sizeof(serv_addr));  //初始化變數serv_addr，它是用來存貯IP地址和通信方式的

	
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(SERVPORT);  
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);  
  
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr))== -1) {  
        perror("connect error!");  
        exit(1);  
    }  
    //write(sockfd, buf, sizeof(DATA)); 
    write(sockfd, m1,strlen(m1));  
    // memset((void *)&recvData,0,sizeof(MyMessage));  
    // if ((recvbytes = recv(sockfd, (void *)&recvData,sizeof(MyMessage), 0)) == -1) {  
        // perror("recv error!");  
        // exit(1);  
    // }  
    //buf[recvbytes] = '\0';  
    // printf("Received:ID=%d,Info= %s",recvData.ID,recvData.info);  
  close(sockfd);}  
	//REPEAT HERE
	
  for(char i = 0; i<2; i++)
  {
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  //開啟 Socket介面，通信類型AF_INET, 連接方式TCP
        perror("socket error!");  //拋出錯誤信息
        exit(1);  
    }  
    bzero(&serv_addr, sizeof(serv_addr));  //初始化變數serv_addr，它是用來存貯IP地址和通信方式的

	
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(SERVPORT);  
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);  
	
	
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr))== -1) {  
        perror("connect error!");  
        exit(1);  
    }  
    //write(sockfd, buf, sizeof(DATA)); 
    write(sockfd, m2,strlen(m2));  
    // memset((void *)&recvData,0,sizeof(MyMessage));  
    // if ((recvbytes = recv(sockfd, (void *)&recvData,sizeof(MyMessage), 0)) == -1) {  
        // perror("recv error!");  
        // exit(1);  
    // }  
    //buf[recvbytes] = '\0';  
    // printf("Received:ID=%d,Info= %s",recvData.ID,recvData.info);  
    close(sockfd); 
  }	
    return 0;  
}  
