#include "common.h"
#include "reporting.h"
#include "utils.h"

void student_transcript(const char *student_id) {
    int student_index = -1;
    for (int i = 0; i < student_count; i++) {
        if (students[i].active && strcmp(students[i].student_id, student_id) == 0) {
            student_index = i;
            break;
        }
    }

    if (student_index == -1) {
        printf("Error: Student ID '%s' not found.\n", student_id);
        return;
    }

    Student *s = &students[student_index];
    printf("\n=== STUDENT TRANSCRIPT ===\n");
    printf("Student ID: %s\n", s->student_id);
    printf("Name: %s\n", s->name);
    printf("Email: %s\n", s->email);
    printf("Age: %d\n\n", s->age);

    printf("%-20s %-20s %-8s %-8s %-8s\n",
           "Course Code", "Course Name", "Grade", "Letter", "GPA");
    printf("%-20s %-20s %-8s %-8s %-8s\n",
           "----------", "----------", "-----", "------", "---");

    float total_gpa_points = 0.0;
    int graded_count = 0;

    for (int i = 0; i < enrollment_count; i++) {
        if (enrollments[i].active &&
            strcmp(enrollments[i].student_id, student_id) == 0 &&
            enrollments[i].grade >= 0) {
            printf("%-20s %-20s %-8.2f %-8s %-8.2f\n",
                   enrollments[i].course_code,
                   enrollments[i].course_name,
                   enrollments[i].grade,
                   get_letter_grade(enrollments[i].grade),
                   grade_to_gpa_points(enrollments[i].grade));
            total_gpa_points += grade_to_gpa_points(enrollments[i].grade);
            graded_count++;
        }
    }

    if (graded_count > 0) {
        printf("\nCumulative GPA: %.2f (based on %d graded courses)\n",
               total_gpa_points / graded_count, graded_count);
    } else {
        printf("\nNo graded courses found.\n");
    }
}


void course_roster(const char *course_code) {
    int found = 0;
    float total_marks = 0.0;
    int graded_count = 0;

    printf("\n=== COURSE ROSTER: %s ===\n", course_code);
    printf("%-12s %-30s %-8s %-8s %-8s\n",
           "Student ID", "Student Name", "Grade", "Letter", "GPA");
    printf("%-12s %-30s %-8s %-8s %-8s\n",
           "----------", "------------", "-----", "------", "---");

    for (int i = 0; i < enrollment_count; i++) {
        if (enrollments[i].active &&
            strcmp(enrollments[i].course_code, course_code) == 0 &&
            enrollments[i].grade >= 0) {
            char student_name[MAX_NAME] = "Unknown";
            for (int j = 0; j < student_count; j++) {
                if (students[j].active &&
                    strcmp(students[j].student_id, enrollments[i].student_id) == 0) {
                    strcpy(student_name, students[j].name);
                    break;
                }
            }

            printf("%-12s %-30s %-8.2f %-8s %-8.2f\n",
                   enrollments[i].student_id,
                   student_name,
                   enrollments[i].grade,
                   get_letter_grade(enrollments[i].grade),
                   grade_to_gpa_points(enrollments[i].grade));
            total_marks += enrollments[i].grade;
            graded_count++;
            found = 1;
        }
    }

    if (found) {
        printf("\nClass Average: %.2f (based on %d graded students)\n",
               total_marks / graded_count, graded_count);
    } else {
        printf("No graded enrollments found for this course.\n");
    }
}


void top_performers(void) {
    typedef struct {
        char student_id[MAX_ID];
        char name[MAX_NAME];
        float average_mark;
        float gpa;
    } StudentPerformance;

    StudentPerformance performances[MAX_STUDENTS];
    int count = 0;

    for (int i = 0; i < student_count; i++) {
        if (!students[i].active) continue;

        float total_marks = 0.0;
        int graded_count = 0;

        for (int j = 0; j < enrollment_count; j++) {
            if (enrollments[j].active &&
                strcmp(enrollments[j].student_id, students[i].student_id) == 0 &&
                enrollments[j].grade >= 0) {
                total_marks += enrollments[j].grade;
                graded_count++;
            }
        }

        if (graded_count > 0) {
            strcpy(performances[count].student_id, students[i].student_id);
            strcpy(performances[count].name, students[i].name);
            performances[count].average_mark = total_marks / graded_count;

            float total_gpa = 0.0;
            for (int j = 0; j < enrollment_count; j++) {
                if (enrollments[j].active &&
                    strcmp(enrollments[j].student_id, students[i].student_id) == 0 &&
                    enrollments[j].grade >= 0) {
                    total_gpa += grade_to_gpa_points(enrollments[j].grade);
                }
            }
            performances[count].gpa = total_gpa / graded_count;
            count++;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (performances[i].average_mark < performances[j].average_mark) {
                StudentPerformance temp = performances[i];
                performances[i] = performances[j];
                performances[j] = temp;
            }
        }
    }

    printf("\n=== TOP PERFORMERS ===\n");
    printf("%-12s %-30s %-12s %-8s\n",
           "Student ID", "Name", "Average Mark", "GPA");
    printf("%-12s %-30s %-12s %-8s\n",
           "----------", "----", "-----------", "---");

    int display_count = count < 10 ? count : 10;
    for (int i = 0; i < display_count; i++) {
        printf("%-12s %-30s %-12.2f %-8.2f\n",
               performances[i].student_id,
               performances[i].name,
               performances[i].average_mark,
               performances[i].gpa);
    }

    if (count == 0) {
        printf("No students with graded courses found.\n");
    }
}
