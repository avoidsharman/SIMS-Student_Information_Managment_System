#include "common.h"
#include "auth.h"
#include "menu.h"
#include "student.h"
#include "enrollment.h"
#include "reporting.h"
#include "utils.h"

void admin_menu(void) {
    int choice;

    do {
        printf("\n===== ADMINISTRATOR MENU =====\n");
        printf("1. Student Management\n");
        printf("2. Course Enrollment Management\n");
        printf("3. Grade Management\n");
        printf("4. Reporting\n");
        printf("0. Logout\n");
        printf("Enter your choice: ");

        choice = get_int_input("", 0, 4);

        switch (choice) {
            case 1: student_management_menu(); break;
            case 2: enrollment_management_menu(); break;
            case 3: grade_management_menu(); break;
            case 4: reporting_menu(); break;
            case 0: logout(); printf("Logged out.\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}


void staff_menu(void) {
    int choice;

    do {
        printf("\n===== ACADEMIC STAFF MENU =====\n");
        printf("1. Grade Management (Enter/Update Grades)\n");
        printf("2. View Student Transcript\n");
        printf("3. View Course Roster\n");
        printf("4. View Top Performers\n");
        printf("0. Logout\n");
        printf("Enter your choice: ");

        choice = get_int_input("", 0, 4);

        switch (choice) {
            case 1: grade_management_menu(); break;
            case 2: {
                char student_id[MAX_ID];
                get_string_input(student_id, MAX_ID, "Enter Student ID: ");
                student_transcript(student_id);
                break;
            }
            case 3: {
                char course_code[MAX_CODE];
                get_string_input(course_code, MAX_CODE, "Enter Course Code: ");
                course_roster(course_code);
                break;
            }
            case 4: top_performers(); break;
            case 0: logout(); printf("Logged out.\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}


void student_menu(char *student_id) {
    int choice;

    do {
        printf("\n===== STUDENT MENU =====\n");
        printf("Welcome, Student (ID: %s)\n", student_id);
        printf("1. View My Transcript\n");
        printf("2. View My Course Enrollments\n");
        printf("0. Logout\n");
        printf("Enter your choice: ");

        choice = get_int_input("", 0, 2);

        switch (choice) {
            case 1: student_transcript(student_id); break;
            case 2: view_enrollments(student_id); break;
            case 0: logout(); printf("Logged out.\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}


void student_management_menu(void) {
    int choice;

    do {
        printf("\n===== STUDENT MANAGEMENT MENU =====\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("0. Back to Admin Menu\n");
        printf("Enter your choice: ");

        choice = get_int_input("", 0, 5);

        switch (choice) {
            case 1: add_student(); break;
            case 2: view_all_students(); break;
            case 3: search_student(); break;
            case 4: update_student(); break;
            case 5: delete_student(); break;
            case 0: printf("Returning to Admin Menu...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}


void enrollment_management_menu(void) {
    int choice;

    do {
        printf("\n===== ENROLLMENT MANAGEMENT MENU =====\n");
        printf("1. Enroll Student\n");
        printf("2. Drop Enrollment\n");
        printf("3. View Enrollments\n");
        printf("0. Back to Admin Menu\n");
        printf("Enter your choice: ");

        choice = get_int_input("", 0, 3);

        switch (choice) {
            case 1: enroll_student(); break;
            case 2: drop_enrollment(); break;
            case 3: {
                char student_id[MAX_ID];
                get_string_input(student_id, MAX_ID, "Enter Student ID (leave blank for all): ");
                if (strlen(student_id) == 0) {
                    view_enrollments(NULL);
                } else {
                    view_enrollments(student_id);
                }
                break;
            }
            case 0: printf("Returning to Admin Menu...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}


void grade_management_menu(void) {
    int choice;

    do {
        printf("\n===== GRADE MANAGEMENT MENU =====\n");
        printf("1. Update Grade\n");
        printf("0. Back to Admin Menu\n");
        printf("Enter your choice: ");

        choice = get_int_input("", 0, 1);

        switch (choice) {
            case 1: update_grade(); break;
            case 0: printf("Returning to Admin Menu...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}


void reporting_menu(void) {
    int choice;

    do {
        printf("\n===== REPORTING MENU =====\n");
        printf("1. Student Transcript\n");
        printf("2. Course Roster\n");
        printf("3. Top Performers\n");
        printf("0. Back to Admin Menu\n");
        printf("Enter your choice: ");

        choice = get_int_input("", 0, 3);

        switch (choice) {
            case 1: {
                char student_id[MAX_ID];
                get_string_input(student_id, MAX_ID, "Enter Student ID: ");
                student_transcript(student_id);
                break;
            }
            case 2: {
                char course_code[MAX_CODE];
                get_string_input(course_code, MAX_CODE, "Enter Course Code: ");
                course_roster(course_code);
                break;
            }
            case 3: top_performers(); break;
            case 0: printf("Returning to Admin Menu...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}
