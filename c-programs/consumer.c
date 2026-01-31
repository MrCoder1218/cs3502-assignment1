#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>

volatile sig_atomic_t shutdown_flag = 0;
volatile sig_atomic_t print_stats_flag = 0;

long lines = 0;
long chars = 0;

void handle_sigint(int sig) {
    shutdown_flag = 1;
}

void handle_sigusr1(int sig) {
    print_stats_flag = 1;
}

int main(int argc, char *argv[]) {
    int verbose = 0;
    int opt;

    while ((opt = getopt(argc, argv, "v")) != -1) {
        if (opt == 'v') verbose = 1;
    }

    struct sigaction sa_int, sa_usr1;

    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    sa_usr1.sa_handler = handle_sigusr1;
    sigemptyset(&sa_usr1.sa_mask);
    sa_usr1.sa_flags = 0;
    sigaction(SIGUSR1, &sa_usr1, NULL);

    char buffer[4096];

    while (!shutdown_flag && fgets(buffer, sizeof(buffer), stdin)) {
        lines++;
        chars += strlen(buffer);

        if (verbose) {
            fputs(buffer, stdout);
        }

        if (print_stats_flag) {
            fprintf(stderr,
                    "[SIGUSR1] Lines: %ld, Characters: %ld\n",
                    lines, chars);
            print_stats_flag = 0;
        }
    }

    fprintf(stderr, "Final Lines: %ld\n", lines);
    fprintf(stderr, "Final Characters: %ld\n", chars);
    return 0;
}

