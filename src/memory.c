#include "_memory_.h"
#include <stdlib.h>

void free_and_reset(void *ptr) {
    if (ptr != NULL) {
        free(ptr);
        ptr = NULL;
    }
}
