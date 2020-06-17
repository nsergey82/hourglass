#include "id.h"


int Id_create(int *v1, int *v2) {
    *v1 = 0;
    *v2 = 1;
    return 0;
}

int Id_applyLogic(int *v1, int *v2) {
    if (*v2 > 1836311903) { // 46th Fibonacci fits in int
        return 1;
    }

    int temp = *v1 + *v2;
    *v1 = *v2;
    *v2 = temp;
    return 0;
}
