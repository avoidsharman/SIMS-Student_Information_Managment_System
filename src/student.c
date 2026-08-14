#include "common.h"
#include "student.h"
#include "data.h"
#include "enrollment.h"
#include "utils.h"

int is_duplicate_id(const char *id) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].active && strcmp(students[i].student_id, id) == 0)
            return 1;
    }
    return 0;
}


void add_student(void) {
    if (student_count >= MAX_STUDENTS) {
        printf("Error: Maximum student limit (%d) reached.\n", MAX_STUDENTS);
        return;
    }

    Student new_student = {0};
    new_student.active = 1;

    printf("\n=== Add New Student ===\n");

    while (1) {
        get_string_input(new_student.student_id, MAX_ID, "Enter Student ID (max 11 chars): ");
        if (strlen(new_student.student_id) == 0) {
            printf("Error: Student ID cannot be empty.\n");
            continue;
        }
        if (is_duplicate_id(new_student.student_id)) {
            printf("Error: Student ID '%s' already exists.\n", new_student.student_id);
            continue;
        }
        break;
    }

    get_string_input(new_student.name, MAX_NAME, "Enter Full Name: ");
    get_string_input(new_student.email, MAX_EMAIL, "Enter Email Address: ");
    new_student.age = get_int_input("Enter Age: ", 1, 120);

    students[student_count++] = new_student;
    save_students();
    printf("\nStudent added successfully!\n");
}


void view_all_students(void) {
    printf("\n=== All Students (%d active) ===\n", student_count);
    if (student_count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("%-12s %-30s %-30s %-5s\n", "Student ID", "Name", "Email", "Age");
    printf("%-12s %-30s %-30s %-5s\n", "----------", "----", "-----", "---");

    for (int i = 0; i < student_count; i++) {
        if (students[i].active) {
            printf("%-12s %-30s %-30s %-5d\n",
                   students[i].student_id,
                   students[i].name,
                   students[i].email,
                   students[i].age);
        }
    }
}


void search_student(void) {
    char search_term[MAX_NAME];
    get_string_input(search_term, MAX_NAME, "Enter search term (ID or name): ");

    int found = 0;
    printf("\n=== Search Results ===\n");
    printf("%-12s %-30s %-30s %-5s\n", "Student ID", "Name", "Email", "Age");
    printf("%-12s %-30s %-30s %-5s\n", "----------", "----", "-----", "---");

    for (int i = 0; i < student_count; i++) {
        if (!students[i].active) continue;
        if (compare_strings_ignore_case(students[i].student_id, search_term) == 0 ||
            compare_strings_ignore_case(students[i].name, search_term) == 0) {
            printf("%-12s %-30s %-30s %-5d\n",
                   students[i].student_id,
                   students[i].name,
                   students[i].email,
                   students[i].age);
            found = 1;
        }
    }

    if (!found) printf("No matching students found.\n");
}


void update_student(void) {
    char id[MAX_ID];
    get_string_input(id, MAX_ID, "Enter Student ID to update: ");

    int index = -1;
    for (int i = 0; i < student_count; i++) {
        if (students[i].active && strcmp(students[i].student_id, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Student ID '%s' not found.\n", id);
        return;
    }

    Student *s = &students[index];
    printf("\n=== Update Student (leave blank to keep current value) ===\n");
    printf("Current: %s | %s | %s | %d\n",
           s->student_id, s->name, s->email, s->age);

    char name[MAX_NAME];
    get_string_input(name, MAX_NAME, "Enter new Name (or leave blank): ");
    if (strlen(name) > 0) strncpy(s->name, name, MAX_NAME-1);

    char email[MAX_EMAIL];
    get_string_input(email, MAX_EMAIL, "Enter new Email (or leave blank): ");
    if (strlen(email) > 0) strncpy(s->email, email, MAX_EMAIL-1);

    int age = get_int_input("Enter new Age (0 to keep current): ", 0, 120);
    if (age > 0) s->age = age;

    save_students();
    printf("\nStudent updated successfully!\n");
}


void delete_student(void) {
    char id[MAX_ID];
    get_string_input(id, MAX_ID, "Enter Student ID to delete: ");

    int index = -1;
    for (int i = 0; i < student_count; i++) {
        if (students[i].active && strcmp(students[i].student_id, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Student ID '%s' not found.\n", id);
        return;
    }

    printf("Student found: %s (%s)\n", students[index].name, students[index].student_id);
    char confirm;
    printf("Are you sure you want to delete this student and all their enrollments? (y/N): ");
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (tolower(confirm) != 'y') {
        printf("Deletion cancelled.\n");
        return;
    }

    students[index].active = 0;

    for (int i = 0; i < enrollment_count; i++) {
        if (enrollments[i].active && strcmp(enrollments[i].student_id, id) == 0) {
            enrollments[i].active = 0;
        }
    }

    save_students();
    save_enrollments();
    printf("\nStudent and associated enrollments deleted successfully!\n");
}
