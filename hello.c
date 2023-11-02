#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

struct Person
{
    char name[10];
    int age;
};



int main(){
    printf("Hello, World!\n");

    int var = 10;
    int *pointer_to_var = &var;

    printf("Value of var: %d\n", var);
    printf("Address of var: %p\n", (void *)&var);
    printf("Value of pointer_to_var: %p\n", (void *)pointer_to_var);
    printf("Value pointed to by pointer_to_var: %d\n", *pointer_to_var);

    int *arr = malloc(5 * sizeof(int));

    if(arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        arr[i] = i * i;
        printf("%d\n", arr[i]);
    }

    free(arr);

    struct Person annie = {
        "Annie",
        22
    };

    printf("Meet %s, she is %d\n", annie.name, annie.age);
    
    struct Person jean_claude = {
        "Jean-claude",
        22
    };
    printf("Meet %s, he is %d\n", jean_claude.name, jean_claude.age);

    return 0;
}