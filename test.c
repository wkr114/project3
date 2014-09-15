#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define CMD_MAX_LEN 128

int Help();

typedef struct DataNode
{
    char*  cmd;
    char*  desc;
    int    (*handler)();
    struct DataNode *next;
}tDataNode;

tDataNode *FindCmd(tDataNode *head, char *cmd)
{
    tDataNode *p = head;
    while(p != NULL)
    {
        if(!strcmp(cmd, p->cmd))
        {
            return p;                
            break;    
        }
        p = p->next;
    }
    if(p == NULL)
    {
        return NULL;
    }
}

static tDataNode head[] = 
{
    {"help", "this is help cmd!", Help, &head[1]},
    {"version", "menu program v1.0", NULL, &head[2]},
    {"modtime", "2014/9/15", NULL, &head[3]},
    {"system", "ubuntu", NULL, NULL}
};

void main()
{
    tDataNode *p;
    while(1)
    {
        char cmd[CMD_MAX_LEN];
        printf("Input a cmd number > ");
        scanf("%s", cmd);
        p = FindCmd( head, cmd);
        if(p == NULL)
        {
            printf("this is a wrong cmd!\n");
            continue;
        }
        printf("%s - %s\n", p->cmd, p->desc); 
        if( p->handler != NULL)
        {
            p->handler();
        }  
    } 
}

int Help()
{
    tDataNode *p = head;
    printf("Menu List :\n");
    while(p != NULL)
    {
        printf("%s - %s\n", p->cmd, p->desc);
        p = p->next;
    }
    return 0;
}
