#include "common.h"
#include "enrollment.h"
#include "data.h"
#include "utils.h"

void enroll_student(void) {
    char student_id[MAX_ID];
    get_string_input(student_id, MAX_ID, "Enter Student ID: ");

    int student_index = -1;
    for (int i = 0; i < student_count; i++) {
        if (students[i].active && strcmp(students[i].student_id, student_id) == 0) {
            student_index = i;
            break;
        }
    }

    if (student_index == -1) {
        printf("Error: Student ID '%s' not found or inactive.\n", student_id);
        return;
    }

    int current_enrollments = 0;
    for (int i = 0; i < enrollment_count; i++) {
        if (enrollments[i].active && strcmp(enrollments[i].student_id, student_id) == 0) {
            current_enrollments++;
        }
    }

    if (current_enrollments >= 10) {
        printf("Error: Student is already enrolled in maximum 10 courses.\n");
        return;
    }

    Enrollment new_enrollment = {0};
    strcpy(new_enrollment.student_id, student_id);
    new_enrollment.active = 1;
    new_enrollment.grade = -1.0;

    printf("\n=== Enroll in Course ===\n");
    get_string_input(new_enrollment.course_code, MAX_CODE, "Enter Course Code: ");
    get_string_input(new_enrollment.course_name, MAX_COURSE_NAME, "Enter Course Name: ");

    for (int i = 0; i < enrollment_count; i++) {
        if (enrollments[i].active &&
            strcmp(enrollments[i].student_id, student_id) == 0 &&
            strcmp(enrollments[i].course_code, new_enrollment.course_code) == 0) {
            printf("Error: Student is already enrolled in this course.\n");
            return;
        }
    }

    enrollments[enrollment_count++] = new_enrollment;
    save_enrollments();
    printf("\nEnrollment successful!\n");
}


void drop_enrollment(void) {
    char student_id[MAX_ID];
    char course_code[MAX_CODE];
    get_string_input(student_id, MAX_ID, "Enter Student ID: ");
    get_string_input(course_code, MAX_CODE, "Enter Course Code: ");

    int index = -1;
    for (int i = 0; i < enrollment_count; i++) {
        if (enrollments[i].active &&
            strcmp(enrollments[i].student_id, student_id) == 0 &&
            strcmp(enrollments[i].course_code, course_code) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Enrollment not found for Student ID '%s' and Course Code '%s'.\n",
               student_id, course_code);
        return;
    }

    printf("Enrollment found: %s (%s) - Grade: %.2f\n",
           enrollments[index].course_name,
           enrollments[index].course_code,
           enrollments[index].grade);
    char confirm;
    printf("Are you sure you want to drop this enrollment? (y/N): ");
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (tolower(confirm) != 'y') {
        printf("Drop cancelled.\n");
        return;
    }

    enrollments[index].active = 0;
    save_enrollments();
    printf("\nEnrollment dropped successfully!\n");
}


void view_enrollments(const char *student_id) {
    int found = 0;
    printf("\n=== Enrollments%s ===\n",
           student_id ? " for Student ID: " : " (All)");
    if (student_id) printf("%s\n", student_id);

    printf("%-12s %-20s %-20s %-30s %-8s %-12s\n",
           "Student ID", "Course Code", "Course Name", "Grade", "Letter", "GPA");
    printf("%-12s %-20s %-20s %-30s %-8s %-12s\n",
           "----------", "----------", "----------", "------", "------", "--------");

    for (int i = 0; i < enrollment_count; i++) {
        if (!enrollments[i].active) continue;
        if (student_id && strcmp(enrollments[i].student_id, student_id) != 0) continue;

        char letter[3];
        strcpy(letter, get_letter_grade(enrollments[i].grade));
        float gpa = grade_to_gpa_points(enrollments[i].grade);

        printf("%-12s %-20s %-20s %-30.2f %-8s %-12.2f\n",
               enrollments[i].student_id,
               enrollments[i].course_code,
               enrollments[i].course_name,
               enrollments[i].grade >= 0 ? enrollments[i].grade : -1.0,
               letter,
               gpa);
        found = 1;
    }

    if (!found) {
        if (student_id)
            printf("No enrollments found for Student ID '%s'.\n", student_id);
        else
            printf("No enrollments found.\n");
    }
}


void update_grade(void) {
    char student_id[MAX_ID];
    char course_code[MAX_CODE];
    get_string_input(student_id, MAX_ID, "Enter Student ID: ");
    get_string_input(course_code, MAX_CODE, "Enter Course Code: ");

    int index = -1;
    for (int i = 0; i < enrollment_count; i++) {
        if (enrollments[i].active &&
            strcmp(enrollments[i].student_id, student_id) == 0 &&
            strcmp(enrollments[i].course_code, course_code) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Enrollment not found for Student ID '%s' and Course Code '%s'.\n",
               student_id, course_code);
        return;
    }

    printf("Current grade: %.2f (%s, GPA: %.2f)\n",
           enrollments[index].grade >= 0 ? enrollments[index].grade : -1.0,
           get_letter_grade(enrollments[index].grade),
           grade_to_gpa_points(enrollments[index].grade));

    float new_grade = get_float_input("Enter new grade (0.0-100.0): ", 0.0, 100.0);
    enrollments[index].grade = new_grade;

    save_enrollments();
    printf("\nGrade updated successfully!\n");
    printf("New grade: %.2f (%s, GPA: %.2f)\n",
           enrollments[index].grade,
           get_letter_grade(enrollments[index].grade),
           grade_to_gpa_points(enrollments[index].grade));
}
