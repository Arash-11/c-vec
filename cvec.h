#ifndef _C_VEC_H_
#define _C_VEC_H_

#include <stddef.h>

// todo: optimal initial allocation size for a new array?
#define ARRAY_START_LEN 4

typedef struct CVec {
    int* arr;
    int len;
    int curr_index;
} CVec;

CVec* cvec_new();
void cvec_push(CVec* cvec, int val);
int cvec_pop(CVec* cvec);
int cvec_at(CVec* cvec, int index);
size_t cvec_len(const CVec* cvec);

#endif
