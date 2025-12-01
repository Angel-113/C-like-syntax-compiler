#include "base.h"

void Error ( const char* message ) {
    fprintf(stderr, "%s", message);
    exit(EXIT_FAILURE);
}