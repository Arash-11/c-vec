#ifndef _C_VEC_H_
#define _C_VEC_H_

#include <stddef.h>

#define ARRAY_START_CAP 4

typedef enum RetStatus {
    ERROR = -1,
    OK
} RetStatus;

typedef struct {
    RetStatus status;
    int val; // Only valid if status is OK
} Result;

typedef struct {
    int* arr;
    int cap;
    int curr_index;
} CVec;

// todo: all other functions take in a `CVec*`,
// should `cvec_new` do the same?
CVec* cvec_new(void);
void cvec_free(CVec* cvec);
Result cvec_push(CVec* cvec, int val);
Result cvec_pop(CVec* cvec);
Result cvec_at(const CVec* cvec, int index);
size_t cvec_len(const CVec* cvec);
// cvec_insert: using the term "pos" instead of "index" just
// because "index" may imply that we're replacing something at
// that index, whereas our intention is to insert something _before_
// that index.
Result cvec_insert(CVec* cvec, int pos, int val);

#endif
