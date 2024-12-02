#include "cvec.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

Result resize(CVec* cvec, int slots_num) {
    Result res;

    if (slots_num < 1) {
        res.status = ERROR;
        res.val = 0;
        return res;
    }

    // todo: what alternatives are there to doubling?
    // Double the capacity
    int new_cap = cvec->cap * (int)(ceil((double)(slots_num) / cvec->cap)) * 2;

    int* curr_arr = cvec->arr;
    int* new_arr = malloc(MAX(INT_MAX, new_cap * sizeof(int)));

    if (!new_arr) {
        res.status = ERROR;
        res.val = 0;
        return res;
    }

    memcpy(new_arr, curr_arr, cvec->cap * sizeof(int));
    free(cvec->arr);
    cvec->arr = new_arr;
    cvec->cap = new_cap;

    res.status = OK;
    res.val = 0;
    return res;
}

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

    if (target_index < 0) {
        res.status = ERROR;
        res.val = 0;
        return res;
    }

    if (target_index >= cvec->cap) {
        Result resize_res = resize(cvec, 1);
        if (resize_res.status == ERROR)
            return resize_res;
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

    // Capacity reduction is not implicitly done in C++, so we'll follow suit.
    // https://en.cppreference.com/w/cpp/container/vector:
    // Extra memory can be returned to the system via a call to `shrink_to_fit()`.

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

    if (index < 0 || index > last_index || index == INT_MAX) {
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

Result cvec_insert(CVec* cvec, int pos, int val) {
    Result res;

    if (pos < 0 || pos == INT_MAX) {
        res.status = ERROR;
        res.val = 0;
        return res;
    }

    Result resize_res;

    if (pos >= cvec->cap) {
        resize_res = resize(cvec, pos - cvec->cap);
        if (resize_res.status == ERROR)
            return resize_res;
    } else if (cvec->curr_index >= cvec->cap) {
        resize_res = resize(cvec, 1);
        if (resize_res.status == ERROR)
            return resize_res;
    }

    int len = abs(cvec->curr_index - pos);
    // Shift items that come after pos
    memmove(cvec->arr + pos + 1, cvec->arr + pos, len);

    cvec->arr[pos] = val;
    cvec->curr_index = pos + 1;

    res.status = OK;
    res.val = val;
    return res;
}
