/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : sem_tool.c
   Author : tao.jing
   Date   : 19-9-15
   Brief  : 
**************************************************************************/
#include <stdio.h>
#include "sem_tool.h"

//def semun union, some system may provide by <sys/sem.h>
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

//set sem (with sem_id) to init_value, =1 will be binary semaphore
int init_sem(int sem_id, int init_value)
{
    union semun sem_union;
    sem_union.val = init_value;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
    {
        //perror("Sem init failed");
        return -1;
    }
    return 0;
}

// del sem (with sem_id)
int del_sem(int sem_id)
{
    union semun sem_union;
    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
    {
        perror("Sem delete failed");
        return -1;
    }
    return 0;
}

// conduct p opreation on sem (with sem_id)
int sem_p(int sem_id)
{
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = -1;//P operation
    sem_buf.sem_flg = SEM_UNDO;//system release sem if program exit without release
    if (semop(sem_id, &sem_buf, 1) == -1)
    {
        perror("Sem P operation failed");
        return -1;
    }
    return 0;
}

// conduct v opreation on sem (with sem_id)
int sem_v(int sem_id)
{
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = 1;//V operation
    sem_buf.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_buf, 1) == -1)
    {
        perror("Sem V operation failed");
        return -1;
    }
    return 0;
}

