#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    char usage[] = "sleep <time>";
    if (argc ==1) {
        printf("invalid argument. %s", usage);
        exit(1);
    }

    int iTimeToSleep = atoi(argv[1]);
    printf("sleeping for %d ticks", iTimeToSleep);
    sleep(iTimeToSleep);
    exit(0);
}
