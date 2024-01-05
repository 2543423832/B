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

struct clientRequest
{
    int operate;
    ElemenType data;
};
void handleClientCommand(struct LinkList * contactList,int clientFd,struct clientRequest * request)
{
    switch (request->operate)
    {
    case 1:
        insertTail(contactList,request->data) ;
        writeFile("contacts.txt",contactList);
        send(clientFd,"insert success",strlen("insert success"),0);/* code */
        break;
    case 2:
            struct Lnode *travel = contactList->head;
            while (travel!=NULL)
            {
               char buffer[256]="0";
               sprintf(buffer,"%s %s %s\n",(travel->data).name,(travel->data).number,(travel->data).chatName);
                /* code */
                send(clientFd,buffer,strlen(buffer),0);
                travel= travel->next;
            }
            send(clientFd,"END",strlen("END"),0);
            break;
    default:
            send(clientFd,"Invaild choose",sizeof("Invaild choose"),0);
        break;
    }
}
int main()
{
    struct LinkList contactList;
    initLinkList(&contactList);
    readFile("contacts",&contactList);
    int serverFd = socket(AF_INET,SOCK_STREAM,0);
    if (serverFd<0)
    {
        perror("create erorr\n");
        exit(1);/* code */
    }
    struct sockaddr_in severadder;
    severadder.sin_family = AF_INET;
    severadder.sin_port = htons(PORT);
    severadder.sin_addr.s_addr = INADDR_ANY;

    int opt =1;
    setsockopt(serverFd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    if (bind(serverFd,(struct sockaddr*)&severadder,sizeof(severadder))<0)
    {
        perror("bing error\n");
        exit(1);/* code */
    }

    if (listen(serverFd,10)<0)
    {
       perror("listen error\n"); 
       exit(1);
    }
    printf("sever listening:%d\n",PORT);

    while (1)
    {   
        int clientFd = accept(serverFd,NULL,NULL);
        if (clientFd<0)
        {
          perror("accpept error");
          exit(1);  /* code */
        }
        struct clientRequest ClientRequest;
        recv(clientFd,&ClientRequest,sizeof(ClientRequest),0);

        handleClientCommand(&contactList,clientFd,&ClientRequest);

        close(clientFd);
        
    }
    
    
    

}