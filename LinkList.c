#include<stdio.h>
#include"LinkList.h"
#include"stdlib.h"
#include<stddef.h>
#include<string.h>

void initLinkList(struct LinkList *LL)
{
   LL->length=0;
   LL->head=NULL;
}
struct Lnode *creatNode(char *name,char *number,char *chatname)
{
    struct Lnode * P=(struct Lnode*)malloc(sizeof(struct Lnode));
    P->next=NULL;
    memset(P,0,sizeof(struct Lnode));
    strcpy((P->data).name,name);
    strcpy((P->data).number,number);
    strcpy((P->data).chatName,chatname);
    return P;
}
struct  information Fill(char *name, char *number, char *chatname)
{
    struct information tamp;
    strcpy(tamp.name,name);
    strcpy(tamp.number,number);
    strcpy(tamp.chatName,chatname);
    return tamp;
}
int insertTail(struct LinkList *LL, ElemenType data)
{
    struct Lnode *P=creatNode(data.name,data.number,data.chatName);
    if(P==NULL)
    {
        printf("p malloc error\n");
        exit(1);
    }
    P->data=data;
    struct Lnode *travePoint = LL->head;
    if (travePoint==NULL)
    {
       LL->head=P; /* code */
    }
    else
    {
        while (travePoint->next != NULL)
        {
             travePoint = travePoint->next; /* code */
        }
          travePoint->next = P;    
    } 
    (LL->length)++;
    
    return 0;
}
    void travel(struct LinkList *LL)
    {
        printf("LENGTH OF LINKLIST IS %d\n",LL->length);
        struct Lnode *travePoint = LL->head;
        while (travePoint!=NULL)
        {
            printf("name:%s\n",(travePoint->data).name);
            printf("number:%s\n",(travePoint->data).number);
            printf("chatName:%s\n",(travePoint->data).chatName);
            travePoint  = travePoint->next;
        }
        printf("\n");
    }

    void removeByKey(struct LinkList *LL, struct information data)
    {
        if (LL->length==0)
        {
            printf("list is null\n");
            return ;/* code */
        }
        struct Lnode * travelPoint = LL->head;
        while (travelPoint->next !=NULL)
        {
            if (strcmp((travelPoint->next->data).chatName,data.chatName)==0)
            {  
                struct Lnode *FreeNode = travelPoint->next;
            //    travelPoint->next=travelPoint->next->next;
                travelPoint->next=travelPoint->next->next;
                free(FreeNode);
                (LL->length)--;
            }
            else
            {
                travelPoint = travelPoint->next;
            }
            /* code */
        }
        if (strcmp((LL->head->data).chatName, data.chatName)==0)
        {
           struct Lnode *FreeNode = LL->head;
           LL->head = LL->head->next;
           free(FreeNode);
           LL->length--; /* code */
        }   
    }

    void setValueByValue(struct LinkList *LL, struct information  olddata, struct information  data)
    {
        struct Lnode *travelPoint = LL->head;
        while (travelPoint != NULL)
        {
            if (strcmp((travelPoint->data).chatName, olddata.chatName)==0)
            {
               travelPoint->data=data; /* code */
            }
            travelPoint = travelPoint->next;/* code */
        }
        
    }
    int  * findbyKey(struct LinkList * LL, struct information  data)
    {
        int* findKey = (int*)malloc(sizeof(LL->length));
        if (findKey==NULL)
        {
            printf("error");
            return NULL;/* code */
        }
        int locallist = 1;
        int local = 1;;
        struct Lnode* travelPoint  = LL->head;
        while (travelPoint!= NULL)
        {
           if (strcmp((travelPoint->data).chatName,data.chatName)==0)
           {
                findKey[local]=locallist;
                local++;/* code */
           }
           travelPoint = travelPoint->next;
           locallist++;
            /* code */
        }
        findKey[local] = 0;
        return findKey;
    }
    void printfLocal(struct LinkList *LL, int local[])
    {
        if (local==NULL||local[0]==0)
        {
            printf("have no result\n");
            return;/* code */
        }
        printf("Corresponding data...\n");
        for (int i = 0; local[i]!=0; i++)
        {
           int position = local[i];
           struct Lnode* travelPoint = LL->head;
           for (int i = 1; i < position; i++)
           {
            travelPoint=travelPoint->next;
           }
            printf("name:%s\n",(travelPoint->data).name);
            printf("number:%s\n",(travelPoint->data).number);
            printf("chatName:%s\n",(travelPoint->data).chatName);
        }
        
        printf("\n");
        
    }
   void readFile(const char * fileName,struct LinkList *LL)
    {
        FILE * file =fopen(fileName,"r"); 
        if (file == NULL)
        {
          perror("file open error");  /* code */
        }
        struct information tamp;
        memset(&tamp,0,sizeof(tamp));
        while (fscanf(file,"%s %s %s",tamp.name,tamp.number,tamp.chatName)==3)
        {
            insertTail(LL,tamp);/* code */
            memset(&tamp,0,sizeof(tamp));
        }
        fclose(file);
    }
    void writeFile(const char *fileName,struct LinkList *LL)
    {
        FILE * file =fopen(fileName,"w");
        if (file ==NULL)
        {
            perror("file open error");/* code */
        }
        struct Lnode *travlePoint = LL->head;
        while (travlePoint!= NULL)
        {
            fprintf(file,"%s %s %s",(travlePoint->data).name,
            (travlePoint->data).number,
            (travlePoint->data).chatName);
            travlePoint =travlePoint->next;/* code */
        }
        fclose(file);
        
    }
