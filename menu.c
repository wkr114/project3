/**************************************************************************************************/
/* Copyright (C)  SSE@USTC, 2014-2015                                                             */
/*                                                                                                */
/*  FILE NAME             :  menu.c                                                               */
/*  PRINCIPAL AUTHOR      :  wangkairui                                                           */
/*  SUBSYSTEM NAME        :  menu                                                                 */
/*  MODULE NAME           :  menu                                                                 */
/*  LANGUAGE              :  C                                                                    */
/*  TARGET ENVIRONMENT    :  ANY                                                                  */
/*  DATE OF FIRST RELEASE :  2014/09/10                                                           */
/*  DESCRIPTION           :  This is a menu program                                               */
/**************************************************************************************************/

/*
 * Revision log:
 *
 * Created by wangkairui, 2014/09/15
 *
 */

/*head file*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define CMD_MAX_LEN 128

int Help();


/*structure and its functions*/
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

int ShowAllCmd(tDataNode *head)
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


/* menu programe */
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
        printf("Input a cmd > ");
        scanf("%s", cmd);
        p = FindCmd( head, cmd);   
        if(p == NULL)
        {
            printf("this is wrong cmd!\n");
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
    ShowAllCmd(head);
    return 0;
}
