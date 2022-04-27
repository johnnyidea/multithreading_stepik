
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if(fork()) {
        if(fork()) {
            if(fork()) {
                fork();
            }
        }
    }
    printf("Hello!\n");
}

//int main(int argc, char **argv) {
//    fork();
//    fork();
//    fork();
//    fork();
//    printf("Hello!\n");
//}