#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    //must be 0-23
    int hour = atoi(argv[1]);
    
    printf("Good %s\n", "Morning\0Day\0Evening\0Night\0"+(("UUUUUUAAAAAAIIIIIIMMMMMU"[hour]))-'A');
    return 0;
}
