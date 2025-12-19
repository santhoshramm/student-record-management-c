/*
File: student_management.c
Description: Console-based student record management system
Features:
- Add student
- Display all students
- Search student
- Delete student
Data stored using file handling
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
};

void addStudent() {
    struct Student s;
    FILE *fp = fopen("../data/students.txt", "a");

    if (!fp) {
        printf("File error\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);

    fprintf(fp, "%d %s %d\n", s.id, s.name, s.age);
    fclose(fp);

    printf("Student added successfully\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen("../data/students.txt", "r");

    if (!fp) {
        printf("No records found\n");
        return;
    }

    printf("\nID\tName\t\tAge\n");
    while (fscanf(fp, "%d %s %d", &s.id, s.name, &s.age) != EOF) {
        printf("%d\t%s\t\t%d\n", s.id, s.name, s.age);
    }

    fclose(fp);
}

void searchStudent() {
    int id, found = 0;
    struct Student s;
    FILE *fp = fopen("../data/students.txt", "r");

    if (!fp) return;

    printf("Enter ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d", &s.id, s.name, &s.age) != EOF) {
        if (s.id == id) {
            printf("Found: %d %s %d\n", s.id, s.name, s.age);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found\n");

    fclose(fp);
}

void deleteStudent() {
    int id;
    struct Student s;
    FILE *fp = fopen("../data/students.txt", "r");
    FILE *temp = fopen("../data/temp.txt", "w");

    if (!fp || !temp) return;

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %d", &s.id, s.name, &s.age) != EOF) {
        if (s.id != id)
            fprintf(temp, "%d %s %d\n", s.id, s.name, s.age);
    }

    fclose(fp);
    fclose(temp);

    remove("../data/students.txt");
    rename("../data/temp.txt", "../data/students.txt");

    printf("Student deleted if existed\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1.Add Student\n2.Display Students\n3.Search Student\n4.Delete Student\n5.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: exit(0);
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}
