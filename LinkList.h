#ifndef __LINKLIDT_H__
#define __LINKLIDT_H__
#define ElemenType struct information 

struct information 
{
    char name[20];
    char number[11];
    char chatName[20];

};
 struct Lnode
{
   struct information  data;
   struct Lnode *next;
};
 struct LinkList
{
    struct Lnode *head;
    int length; 
};

void initLinkList(struct LinkList * LL);
int insertTail(struct LinkList*LL,ElemenType data);
void travel(struct LinkList * LL);
void removeByKey(struct LinkList * LL,ElemenType  data);
void setValueByValue(struct LinkList * LL,ElemenType olddata,ElemenType  data);
int * findbyKey(struct LinkList * LL, ElemenType  data);
void printfLocal(struct LinkList *LL,int local[]);
struct Lnode *creatNode(char *name,char *number,char *chatname);
struct information  Fill(char *name,char *number,char *chatname);
void readFile(const char * fileName,struct LinkList *LL);
void writeFile(const char * fileName,struct LinkList *LL);
#endif