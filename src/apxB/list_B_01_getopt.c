//
// Created by 曹子钰 on 2019/10/5.
//

#include <getopt.h>
#include <ctype.h>
#include <tlpi_hdr.h>

static char printable(int ch) {
    return isprint((unsigned char) ch) ? ch : '#';
}

/* Print "usage" message and exit */
static void usageError(char *progName, char *msg, int opt) {
    if (msg != NULL && opt != 0)
        fprintf(stderr, "%s (-%c)\n", msg, printable(opt));
    fprintf(stderr, "Usage: %s [-p arg] [-a arg] [-x]\n", progName);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int opt = 0;
    int xFnd = 0;
    char *pStr = NULL;
    char *pA = NULL;

    while ((opt = getopt(argc, argv, ":p:a:x")) != -1) {
        printf("opt = %3d (%c); option = %d", opt, printable(opt), optind);
        if (opt == '?' || opt == ':') {
            printf("; optopt = %3d (%c)", optopt, printable(optopt));
        }
        printf("\n");

        switch (opt) {
            case 'p':
                pStr = optarg;
                break;
            case 'x':
                ++xFnd;
                break;
            case 'a':
                pA = optarg;
                break;
            case ':':
                usageError(argv[0], "Missing argument", optopt);
                break;
            case '?':
                usageError(argv[0], "Unrecognized option", optopt);
                break;
            default:
                fatal("Unexpected case in switch()");
        }
    }

    if (xFnd != 0) {
        printf("-x was specified (count=%d)\n", xFnd);
    }
    if (pStr != NULL) {
        printf("-p was specified with the value \"%s\"\n", pStr);
    }
    if (pA != NULL) {
        printf("-a was specified with the value \"%s\"\n", pA);
    }
    if (optind < argc) {
        printf("First non-option argument is \"%s\" at argv[%d]\n", argv[optind], optind);
    }

    return 0;
}