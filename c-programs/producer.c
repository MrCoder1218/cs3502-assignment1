#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    char *filename = NULL;
    int buffer_size = 4096;
    int opt;

    while ((opt = getopt(argc, argv, "f:b:")) != -1) {
        if (opt == 'f') filename = optarg;
        else if (opt == 'b') buffer_size = atoi(optarg);
    }

    FILE *in = stdin;
    if (filename) in = fopen(filename, "r");

    char buffer[buffer_size];
    size_t n;
    while ((n = fread(buffer, 1, buffer_size, in)) > 0)
        fwrite(buffer, 1, n, stdout);

    if (in != stdin) fclose(in);
    return 0;
}
