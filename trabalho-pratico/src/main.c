#include "batch.h"
#include "config.h"

int main(int argc, char **argv)
{
    if (argc == 3) {
        batch(argv[1], argv[2]);
    }

    return 0;
}
