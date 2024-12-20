#include "cvec.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

void test_cvec_new(void) {
    CVec* cvec;
    Result res = cvec_new(&cvec);

    assert(res.status == OK && res.val == 0);
    assert(cvec->arr != NULL);
    assert(cvec->cap == ARRAY_START_CAP);
    assert(cvec->curr_index == 0);

    cvec_free(cvec);

    printf("[OK] test_cvec_new\n");
}

void test_cvec_push(void) {
    int base[] = {7, 11, 10, 9};
    int got[ARRAY_START_CAP];

    CVec* cvec;
    cvec_new(&cvec);
    Result res_0 = cvec_push(cvec, base[0]);
    Result res_1 = cvec_push(cvec, base[1]);
    Result res_2 = cvec_push(cvec, base[2]);
    Result res_3 = cvec_push(cvec, base[3]);
    memcpy(&got, cvec->arr, ARRAY_START_CAP * sizeof(int));

    assert(res_0.status == OK && res_0.val == base[0]);
    assert(res_1.status == OK && res_1.val == base[1]);
    assert(res_2.status == OK && res_2.val == base[2]);
    assert(res_3.status == OK && res_3.val == base[3]);
    assert(got[0] == base[0]);
    assert(got[1] == base[1]);
    assert(got[2] == base[2]);
    assert(got[3] == base[3]);

    // resizing
    Result res_4 = cvec_push(cvec, 19);
    Result res_5 = cvec_push(cvec, 111);

    assert(res_4.status == OK && res_4.val == 19);
    assert(res_5.status == OK && res_5.val == 111);
    assert(cvec->cap == ARRAY_START_CAP * 2);

    cvec_free(cvec);

    printf("[OK] test_cvec_push\n");
}

void test_cvec_pop(void) {
    int base[] = {7, 11, 10, 9};
    int got[ARRAY_START_CAP];

    CVec* cvec;
    cvec_new(&cvec);
    cvec_push(cvec, base[0]);
    cvec_push(cvec, base[1]);
    cvec_push(cvec, base[2]);
    cvec_push(cvec, base[3]);
    Result res_0 = cvec_pop(cvec);
    Result res_1 = cvec_pop(cvec);
    memcpy(&got, cvec->arr, ARRAY_START_CAP * sizeof(int));

    assert(res_0.status == OK && res_0.val == base[3]);
    assert(res_1.status == OK && res_1.val == base[2]);
    assert(got[0] == base[0]);
    assert(got[1] == base[1]);
    assert(got[2] == 0);
    assert(got[3] == 0);

    Result res_2 = cvec_pop(cvec);
    Result res_3 = cvec_pop(cvec);
    Result res_4 = cvec_pop(cvec);
    Result res_5 = cvec_pop(cvec);

    assert(res_2.status == OK && res_2.val == base[1]);
    assert(res_3.status == OK && res_3.val == base[0]);
    assert(res_4.status == ERROR && res_4.val == 0);
    assert(res_5.status == ERROR && res_5.val == 0);

    // test pop after insert
    cvec_insert(cvec, 711, 19);
    Result res_6 = cvec_pop(cvec);
    size_t res_len = cvec_len(cvec);

    assert(res_6.status == OK && res_6.val == 19);
    assert(res_len == 711);

    cvec_free(cvec);

    printf("[OK] test_cvec_pop\n");
}

void test_cvec_at(void) {
    int base[] = {7, 11, 10, 9};

    CVec* cvec;
    cvec_new(&cvec);
    cvec_push(cvec, base[0]);
    cvec_push(cvec, base[1]);
    Result res_0 = cvec_at(cvec, 0);
    Result res_1 = cvec_at(cvec, 1);
    Result res_2 = cvec_at(cvec, 2);

    assert(res_0.status == OK && res_0.val == base[0]);
    assert(res_1.status == OK && res_1.val == base[1]);
    assert(res_2.status == ERROR && res_2.val == 0);

    cvec_free(cvec);

    printf("[OK] test_cvec_at\n");
}

void test_cvec_len(void) {
    int base[] = {7, 11, 10, 9};

    CVec* cvec;
    cvec_new(&cvec);
    cvec_push(cvec, base[0]);
    cvec_push(cvec, base[1]);
    cvec_push(cvec, base[2]);

    assert(cvec_len(cvec) == 3);

    cvec_pop(cvec);

    assert(cvec_len(cvec) == 2);

    cvec_free(cvec);

    printf("[OK] test_cvec_len\n");
}

void test_cvec_free(void) {
    CVec* cvec;
    cvec_new(&cvec);
    cvec_push(cvec, 7);
    cvec_push(cvec, 11);
    cvec_free(cvec);

    assert(cvec->arr == NULL);
    assert(cvec->cap == 0);
    assert(cvec->curr_index == 0);

    printf("[OK] test_cvec_free\n");
}

void test_cvec_insert(void) {
    int base[] = {7, 11, 10, 9};

    CVec* cvec;
    cvec_new(&cvec);
    cvec_push(cvec, base[0]);
    cvec_push(cvec, base[1]);
    Result res_0 = cvec_insert(cvec, 5, base[2]);
    Result res_1 = cvec_at(cvec, 5);

    assert(res_0.status == OK && res_0.val == base[2]);
    assert(res_1.status == OK && res_1.val == base[2]);

    Result res_2 = cvec_insert(cvec, 500, base[3]);
    Result res_3 = cvec_at(cvec, 500);

    assert(res_2.status == OK && res_2.val == base[3]);
    assert(res_3.status == OK && res_3.val == base[3]);

    Result res_4 = cvec_insert(cvec, 711, 19);
    Result res_5 = cvec_at(cvec, 711);

    assert(res_4.status == OK && res_4.val == 19);
    assert(res_5.status == OK && res_5.val == 19);

    Result res_6 = cvec_insert(cvec, INT_MAX - 1, 1);
    Result res_7 = cvec_at(cvec, INT_MAX - 1);

    assert(res_6.status == ERROR && res_6.val == 0);
    assert(res_7.status == ERROR && res_7.val == 0);

    Result res_8 = cvec_insert(cvec, INT_MAX, 6);
    Result res_9 = cvec_at(cvec, INT_MAX);

    assert(res_8.status == ERROR && res_8.val == 0);
    assert(res_9.status == ERROR && res_9.val == 0);

    cvec_free(cvec);

    printf("[OK] test_cvec_insert\n");
}

int main(void) {
    test_cvec_new();
    test_cvec_push();
    test_cvec_pop();
    test_cvec_at();
    test_cvec_len();
    test_cvec_free();
    test_cvec_insert();
    return 0;
}
