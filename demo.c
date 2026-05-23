#include<stdio.h>
#include<stdlib.h>

int main(){
    char *intarr = malloc(100 * sizeof(int));
    for(int i=0; i <5; i++){
        intarr[i] = '1';
    }
    int val = atoi(intarr);
    printf("%d", val);
    return 0;
}
