#include <stdio.h>

#include "cvec.h"

int main() {
    CVec* cvec = cvec_new();

    cvec_push(cvec, 7);
    cvec_push(cvec, 11);

    int popped_val = cvec_pop(cvec);

    printf("popped_val = %d\n", popped_val);

    int cvec_0 = cvec_at(cvec, 0);

    printf("\n");
    printf("cvec_0: %d\n", cvec_0);

    size_t len = cvec_len(cvec);

    printf("\n");
    printf("before len: %zu\n", len);

    cvec_pop(cvec);

    printf("\n");
    printf("after len: %zu\n", cvec_len(cvec));

    return 0;
}
