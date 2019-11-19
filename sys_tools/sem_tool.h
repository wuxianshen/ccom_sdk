//
// Created by tao on 19-9-15.
//

#ifndef SM_TEST_SEM_TOOL_H
#define SM_TEST_SEM_TOOL_H

#include <sys/sem.h>

int init_sem(int sem_id, int init_value);
int del_sem(int sem_id);
int sem_p(int sem_id);
int sem_v(int sem_id);

#endif //SM_TEST_SEM_TOOL_H
