#include<stdio.h>
#include <stdlib.h>

void function (){
    int a=0, i = 0, j=0;

    for (i = 0; i < 40; i ++) {
        // if ((rand() % 2) == 1){
        //     a++;
        // }
        // else {
        //     j++;
        // }
        printf("%d ", rand() % 2);
    }
        //printf ("\n%d %d\n", a, j);
}

int main (int argc, char *argv[]) {


    srand(1638302658);

    function();
    printf ("\n");


    return 0;
}