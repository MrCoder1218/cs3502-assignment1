#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int verbose = 0;
    int opt;
    long lines = 0, chars = 0;
    char buffer[4096];

    while ((opt = getopt(argc, argv, "v")) != -1)
        if (opt == 'v') verbose = 1;

    while (fgets(buffer, sizeof(buffer), stdin)) {
        lines++;
        chars += strlen(buffer);
        if (verbose) printf("%s", buffer);
    }

    fprintf(stderr, "Lines: %ld\nCharacters: %ld\n", lines, chars);
    return 0;
}
