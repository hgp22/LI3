#include "controller/batch.h"
#include "controller/interactive.h"

int main(int argc, char **argv)
{
    if (argc == 3) {
        run_batch(argv[1], argv[2]);
    }
    else {
        run_interactive();
    }

    return 0;
}
