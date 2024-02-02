#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    float salary;
};

int main() {
    struct Employee emp;
    int choice, id, size;
    char filename[] = "employees.dat";
    FILE *fp;

    fp = fopen(filename, "rb+");
    if (fp == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(1);
    }

    size = sizeof(struct Employee);

    do {
        printf("1. Add an employee\n");
        printf("2. Update an employee\n");
        printf("3. Delete an employee\n");
        printf("4. Display all employees\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter employee id, name and salary: ");
                scanf("%d %s %f", &emp.id, emp.name, &emp.salary);
                fseek(fp, 0, SEEK_END);
                fwrite(&emp, size, 1, fp);
                break;
            case 2:
                printf("Enter employee id to modify: ");
                scanf("%d", &id);
                fseek(fp, (id - 1) * size, SEEK_SET);
                fread(&emp, size, 1, fp);
                if (emp.id == 0) {
                    printf("Employee with id %d not found\n", id);
                } else {
                    printf("Enter new name and salary: ");
                    scanf("%s %f", emp.name, &emp.salary);
                    fseek(fp, (id - 1) * size, SEEK_SET);
                    fwrite(&emp, size, 1, fp);
                    printf("Employee with id %d updated\n", id);
                }
                break;
            case 3:
                printf("Enter employee id to delete: ");
                scanf("%d", &id);
                fseek(fp, (id - 1) * size, SEEK_SET);
                fread(&emp, size, 1, fp);
                if (emp.id == 0) {
                    printf("Employee with id %d not found\n", id);
                } else {
                    emp.id = 0;
                    strcpy(emp.name, "");
                    emp.salary = 0.0;
                    fseek(fp, (id - 1) * size, SEEK_SET);
                    fwrite(&emp, size, 1, fp);
                    printf("Employee with id %d deleted\n", id);
                }
                break;
            case 4:
                rewind(fp);
                printf("id\tname\tsalary\n");
                while (fread(&emp, size, 1, fp) == 1) {
                    if (emp.id != 0) {
                        printf("%d\t%s\t%.2f\n", emp.id, emp.name, emp.salary);
                    }
                }
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 5);

    fclose(fp);
    return 0;
}