#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TASKS 100
#define MAX_SIZE 250

typedef struct {
    int id;
    char description[MAX_SIZE];
    int completed;
} Task;

Task tasks[MAX_TASKS];
int num_tasks = 0;
int last_task_id = 0;

char *get_field(char *line, int num) {
    char *tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {
        if (!--num)
            return tok;
    }
    return NULL;
}

void remove_task_from_array(Task array[], int index, int size) {
    for (int i = index; i < size - 1; i++) {
        array[i] = array[i + 1];
    }
    
}

int find_index_of_element(Task array[], int id, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i].id == id) return i;
    }
    return -1;
}

int update_file() {
    FILE *fp;
    char line[MAX_SIZE];
    fp = fopen("to_do_list.csv", "w");

    fprintf(fp, "id,description,completed\n");
    fclose(fp);

    fp = fopen("to_do_list.csv", "a");
    for (int i = 0; i < num_tasks; i++) {
        // printf("%d. %s [%d]\n", tasks[i].id, tasks[i].description, tasks[i].completed);
        if (tasks[i].id && tasks[i].description) {
            fprintf(fp, "%d,%s,%d\n", tasks[i].id, tasks[i].description, tasks[i].completed);
        }
        
    }
    fclose(fp);
}

int read_file() {
    FILE *fp;
    char line[MAX_SIZE];
    fp = fopen("to_do_list.csv", "r");

    if (fp == NULL) {
        perror("File doesn't exist");
        return -1;
    }

    // Read and ignore the header line
    if (!fgets(line, sizeof(line), fp)) {
        fprintf(stderr, "Error reading the header line\n");
        fclose(fp);
        return -1;
    }

    printf("Current to-do list:\n\n");
    num_tasks = 0;
    while (fgets(line, MAX_SIZE, fp)) {
        line[strcspn(line, "\n")] = '\0';
        char *tmp = strdup(line); // Duplicate the line

        Task task = {0};

        // Use the tmp variable to get the fields
        char *field = get_field(tmp, 1);
        if (field) task.id = atoi(field);
        last_task_id = task.id;
        free(tmp);
        tmp = strdup(line);


        field = get_field(tmp, 2);
        if (field) strncpy(task.description, field, sizeof(task.description) - 1);
        free(tmp);
        tmp = strdup(line);

        field = get_field(tmp, 3);
        if (field) task.completed = atoi(field);
        free(tmp);

        tasks[num_tasks] = task;
        num_tasks++;

        // Ensure num_tasks doesn't exceed the array size
        if (num_tasks >= MAX_SIZE) break;
    }

    fclose(fp);

    for (int i = 0; i < num_tasks; i++) {
        printf("%d. %s [%d]\n", tasks[i].id, tasks[i].description, tasks[i].completed);
    }

    return 0;
}


int create_task(Task task) {
    FILE *fp;
    fp = fopen("to_do_list.csv", "a");
    if (fp == NULL) {
        perror("File does'nt exist");
        return -1;
    }

    fprintf(fp, "%d,%s,%d\n", task.id, task.description, task.completed);
    fclose(fp);
    return 0;
}

void clear_scanf() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {
    int index;
    read_file();

    printf("\nAdd a new task [1]  |  Complete a task [2]  |  Delete a task [3]  |  Delete all completed tasks [4]\n");
    int choice;
    scanf("%d", &choice);
    clear_scanf();

    switch (choice) {
    case 1:
        printf("Write here the new task:\n");
        char new_task[MAX_SIZE];
        fgets(new_task, sizeof(new_task), stdin);
        new_task[strcspn(new_task, "\n")] = 0;
        Task task = {0};
        last_task_id++;
        task.id = last_task_id;
        strncpy(task.description, new_task, 250);
        task.description[250 -1] = '\0';
        task.completed = 0;
        create_task(task);
        read_file();
        break;
    case 2:
        printf("Which task do you want to complete:\n");
        int task_number_to_complete;
        scanf("%d", &task_number_to_complete);
        index = find_index_of_element(tasks, task_number_to_complete, MAX_TASKS);
        tasks[index].completed = 1;
        update_file();
        read_file();
        break;
    case 3:
        printf("Which task do you want to remove:\n");
        int task_number_to_delete;
        scanf("%d", &task_number_to_delete);
        index = find_index_of_element(tasks, task_number_to_delete, MAX_TASKS);
        printf("task to remove: %d. %s [%d]\n", tasks[index].id, tasks[index].description, tasks[index].completed);
        if (index != -1) {
            remove_task_from_array(tasks, index, MAX_TASKS);
            update_file();
            read_file();
        }
        break;
    case 4:
        for (int i = 0; i < num_tasks; i++){
            if (tasks[i].completed) {
                remove_task_from_array(tasks, i, MAX_TASKS);
            }
        }
        update_file();
        read_file();
        break;
    default:
        break;
    }
    
    return 0;
}