#include "batch.h"
#include <stdio.h>

#include <string.h>

int main(int argc, char **argv)
{
    if (argc == 3) {
        batch(argv[1], argv[2]);
    }

    return 0;
}
