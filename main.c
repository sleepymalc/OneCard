#include "function.h"

int main(int argc, char* argv[]) {
    int n = 4, r = 1, d = 2, c = 5, run = 1, demo = 0, islog = 0, opt, option_index = 0;
    unsigned long sizelog;
    char *optstring = "hn:c:d:r:a", *filename = NULL, *default_log_name = "onecard.txt";
    static struct option long_options[] = {
        {"log", required_argument, NULL, 'l'},
        {"help", no_argument, NULL, 'h'},
        {"player-number", required_argument, NULL, 'n'},
        {"initial-cards", required_argument, NULL, 'c'},
        {"decks", required_argument, NULL, 'd'},
        {"rounds", required_argument, NULL, 'r'},
        {0, 0, 0, 0}};

    while ((opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1) {
        switch (opt) {
            case 'h':
                printf(
                    "\
-h|--help                    print this help message\n\
--log filename               write the logs in filename (default: onecard.log)\n\
-n n|--player-number=n       n players, n must be larger than 2 (default: 4)\n\
-c c|--initial-cards=c       deal c cards per player, c must be at least 2 (default: 5)\n\
-d d|--decks=d               use d decks 52 cards each, d must be at least 2 (default: 2)\n\
-r r|--rounds=r              play r rounds, r must be at least 1 (default: 1)\n\
a|--auto                     run in demo mode\n");
                run = 0;
                break;
            case 'l':
                sizelog = strlen(optarg);
                filename = (char*)malloc(sizelog * sizeof(char));
                islog = 1;
                sprintf(filename, "%s", optarg);
                printf("/n/n%s/n/n", filename);
                break;
            case 'n':
                n = atoi(optarg);
                break;
            case 'c':
                c = atoi(optarg);
                break;
            case 'd':
                d = atoi(optarg);
                break;
            case 'r':
                r = atoi(optarg);
                break;
            case 'a':
                demo = 1;
                break;
        }
    }

    if (run == 1) {
        if (islog == 0) filename = default_log_name;

        OneCard(n, r, d, c, demo, filename);
        if (islog == 1) free(filename);
    }
    return 0;
}
