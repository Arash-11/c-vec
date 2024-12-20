#include "cvec.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// https://en.wikipedia.org/wiki/Dynamic_array#Growth_factor
#define GROWTH_FACTOR 2

Result resize(CVec* cvec, int slots_num) {
    Result res;

    if (slots_num < 1) {
        res.status = ERROR;
        res.val = 0;
        return res;
    }

    int growth_multiplier = (int)ceil((double)(slots_num) / cvec->cap);
    if (growth_multiplier < 1) {
        res.status = ERROR;
        res.val = 0;
        return res;
    }

    long long new_cap_ll = (long long)cvec->cap * growth_multiplier * GROWTH_FACTOR;
    // Value is too large to fit in an int
    if (new_cap_ll > INT_MAX) {
        res.status = ERROR;
        res.val = 0;
        return res;
    }
    int new_cap = (int)new_cap_ll;

    int* new_arr = realloc(cvec->arr, new_cap * sizeof(int));
    if (!new_arr) {
        res.status = ERROR;
        res.val = 0;
        return res;
    }

    cvec->arr = new_arr;
    cvec->cap = new_cap;

    res.status = OK;
    res.val = 0;
    return res;
}

Result cvec_new(CVec** cvec) {
    Result res;

    *cvec = malloc(sizeof(CVec));
    if (!cvec) {
        res.status = ERROR;
        res.val = 0;
        return res;
    }

    (*cvec)->arr = malloc(ARRAY_START_CAP * sizeof(int));
    if (!(*cvec)->arr) {
        free((*cvec));
        res.status = ERROR;
        res.val = 0;
        return res;
    }

    (*cvec)->cap = ARRAY_START_CAP;
    (*cvec)->curr_index = 0;

    res.status = OK;
    res.val = 0;
    return res;
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
