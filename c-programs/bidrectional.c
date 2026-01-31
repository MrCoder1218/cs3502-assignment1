#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int p2c[2], c2p[2];
    char buffer[100];
    pipe(p2c);
    pipe(c2p);

    if (fork() == 0) {
        close(p2c[1]);
        close(c2p[0]);
        read(p2c[0], buffer, sizeof(buffer));
        write(c2p[1], "Hello from child!", 18);
    } else {
        close(p2c[0]);
        close(c2p[1]);
        write(p2c[1], "Hello from parent!", 19);
        read(c2p[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        wait(NULL);
    }
    return 0;
}
