#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char description[250];
    int completed;
} Task;

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

int create_task(Task task) {
    FILE *fp;
    fp = fopen("to_do_list.txt", "a");
    if (fp == NULL) {
        perror("File does'nt exist");
        return -1;
    }

    fprintf(fp, "%d. %s [ %d ]\n", task.id, task.description, task.completed);
    fclose(fp);
    return 0;
}

void clear_scanf() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {
    int id = 0;
    // create_task("Hello, World!\n");
    read_file();

    printf("Add a new task [1]   Complete a task [2]\n");
    int choice;
    scanf("%d", &choice);
    clear_scanf();

    if (choice == 1) {
        printf("Write here the new task:\n");
        char new_task[250];
        fgets(new_task, sizeof(new_task), stdin);
        new_task[strcspn(new_task, "\n")] = 0;
        Task task;
        task.id = id;
        strncpy(task.description, new_task, 250);
        task.description[250 -1] = '\0';
        task.completed = 0;
        create_task(task);
        read_file();
    }
    id++;

    return 0;
}