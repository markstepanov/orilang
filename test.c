#include "stdio.h"
#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"




typedef struct 
{
    int a;
    int b;
} test;

void print_test(test* t){
    printf("test: a - %d, b - %d\n", t->a, t->b);
}

int main(void){
    Arena* r = create_arena(8*1024*1024);
    test* t = (test*) arena_malloc(r,sizeof(test));
    t->a = 3;
    t->b = 4;
    print_test(t);

    test* t2 = (test*) arena_malloc(r,sizeof(test));
    t2->a = 5;
    t2->b = 6;
    print_test(t2);



    



}
