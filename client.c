#include<stdio.h>
#include"LinkList.h"
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

#define PORT 2001

#define IP "127.0.0.1"

struct clientRequest
{
    int operate;
    ElemenType data;
};

void printMenu()
{
    printf ("1.add friend\n");
    printf ("2.list friend\n");
    printf("please iput function that you choose\n");
}
void performOperation(int clientFd,int choose)
{
    struct clientRequest ClientRequest;
    switch (choose)
    {
    case 1: 
    ClientRequest.operate = 1;
    printf("please input information\n");
    scanf("%s %s %s",ClientRequest.data.name,ClientRequest.data.number,ClientRequest.data.chatName);
    break;
    case 2: 
    ClientRequest.operate = 2;
    break;

    default:
    exit(1);
    break;
    }
    send(clientFd,&ClientRequest,sizeof(ClientRequest),0);
    char tag[100]="0";
    recv(clientFd,tag,sizeof(tag),0);
    printf("sever tag:%s\n",tag);
    if (choose == 2)
    {
       while (1)
       {
        memset(&tag,0,sizeof(tag));
        if(recv(clientFd,tag,sizeof(tag)-1,0)<=0)
        {
            break;
        }
        if (strcmp(tag,"END")==0)
        {
            break;
        }
        printf("%s\n",tag);
        
       }
       
    }
    else
    {
        memset(&tag,0,sizeof(tag));
        if(recv(clientFd,tag,sizeof(tag)-1,0)<=0)
        {
            return;
        }
        printf("server respomse:%s\n",tag);
    }
}

int main()
{
    int clientFd = socket(AF_INET,SOCK_STREAM,0);
    if (clientFd<0)
    {
        perror("create erorr\n");
        exit(1);/* code */
    }
    struct sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(PORT);
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

   if( connect(clientFd,(struct sockaddr *)&clientAddr,sizeof(clientAddr))<0)
   {
    perror("connect erorr");
    exit(1);
   }
   int choose;

   while (1)
   {
    printMenu();
    scanf("%d",&choose);
    performOperation(clientFd,choose);

    /* code */
   }
    close(clientFd);
    return 0;

}

