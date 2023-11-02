#include <stdio.h>
#include <string.h>

struct Task {
    int id;
    char description[250];
    int completed;
};

int read_file() {
    FILE *fp;
    char str[250];

    fp = fopen("to_do_list.txt", "r");

    if (fp == NULL) {
        perror("File doesn't exist");
        return -1;
    }
    printf("Current to-do list:\n");
    while (fgets(str, 250, fp) != NULL) {
        printf("%s", str);
    }
    fclose(fp);
    return 0;
}

int create_task(char *description) {
    FILE *fp;
    fp = fopen("to_do_list.txt", "a");
    if (fp == NULL) {
        perror("File does'nt exist");
        return -1;
    }

    fputs(description, fp);
    fclose(fp);
    return 0;
}

void clear_scanf() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int create_task2() {

}

int main() {
    create_task("Hello, World!\n");
    read_file();

    printf("Add a new task [1]   Complete a task [2]\n");
    int choice;
    scanf("%d", &choice);
    clear_scanf();

    if (choice == 1) {
        printf("Write here the new task:\n");
        char new_task[100];
        fgets(new_task, sizeof(new_task), stdin);
        create_task(new_task);
        read_file();
    }

    return 0;
}