#include "cvec.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

CVec* cvec_new() {
    CVec* cvec = malloc(sizeof(CVec));

    cvec->arr = malloc(ARRAY_START_LEN * sizeof(int));
    cvec->len = ARRAY_START_LEN;
    cvec->curr_index = 0;

    return cvec;
}

void cvec_push(CVec* cvec, int val) {
    int target_index = cvec->curr_index;
    assert(target_index >= 0);
    cvec->arr[target_index] = val;
    cvec->curr_index++;
}

int cvec_pop(CVec* cvec) {
    int target_index = --cvec->curr_index;
    assert(target_index >= 0);
    int val = cvec->arr[target_index];
    cvec->arr[target_index] = 0;
    return val;
}

int cvec_at(CVec* cvec, int index) {
    int target_index = cvec->curr_index - 1;
    // return out-of-bounds error perhaps?
    assert(index <= target_index);
    return cvec->arr[target_index];
}

size_t cvec_len(const CVec* cvec) {
    return cvec->curr_index;
}
