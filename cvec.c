#include "cvec.h"
#include <stdlib.h>

CVec* cvec_new(void) {
    CVec* cvec = malloc(sizeof(CVec));
    cvec->arr = malloc(ARRAY_START_CAP * sizeof(int));
    cvec->cap = ARRAY_START_CAP;
    cvec->curr_index = 0;
    return cvec;
}

void cvec_free(CVec* cvec) {
    free(cvec->arr);
    cvec->cap = 0;
    cvec->curr_index = 0;
    free(cvec);
}

Result cvec_push(CVec* cvec, int val) {
    Result res;
    int target_index = cvec->curr_index;

    if (target_index < 0 || target_index >= cvec->cap) {
        res.status = ERROR;
        res.val = 0;
        return res;
    }

    cvec->arr[target_index] = val;
    cvec->curr_index++;

    res.status = OK;
    res.val = val;
    return res;
}

Result cvec_pop(CVec* cvec) {
    Result res;
    int target_index = cvec->curr_index - 1;

    if (target_index < 0) {
        res.status = ERROR;
        res.val = 0;
        return res;
    }

    int val = cvec->arr[target_index];
    cvec->arr[target_index] = 0;
    cvec->curr_index--;

    res.status = OK;
    res.val = val;
    return res;
}

Result cvec_at(const CVec* cvec, int index) {
    Result res;
    int last_index = cvec->curr_index - 1;

    if (index < 0 || index > last_index) {
        res.status = ERROR;
        res.val = 0;
        return res;
    }

    int val = cvec->arr[index];

    res.status = OK;
    res.val = val;
    return res;
}

size_t cvec_len(const CVec* cvec) {
    return cvec->curr_index;
}
