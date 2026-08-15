#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 200
#define MAX_ENROLLMENTS 2000
#define MAX_NAME 50
#define MAX_ID 12
#define MAX_CODE 10
#define MAX_COURSE_NAME 50
#define FILE_ENROLLMENTS "enrollments.dat"


typedef struct {
    char student_id[MAX_ID];
    char name[MAX_NAME];
    char email[50];
    int age;
    int active;
} Student;

typedef struct {
    char student_id[MAX_ID];
    char course_code[MAX_CODE];
    char course_name[MAX_COURSE_NAME];
    float grade;
    int active;
} Enrollment;

static Student students[MAX_STUDENTS];
static int student_count = 0;

static Enrollment enrollments[MAX_ENROLLMENTS];
static int enrollment_count = 0;


void save_enrollments(void);
void enroll_student(void);
void drop_enrollment(void);
void view_enrollments(const char *student_id);
void update_grade(void);

float grade_to_gpa_points(float grade);
const char* get_letter_grade(float grade);

void clear_input_buffer(void);
float get_float_input(const char *prompt, float min, float max);
void get_string_input(char *buffer, size_t size, const char *prompt);


void save_enrollments(void) {
    FILE *fp = fopen(FILE_ENROLLMENTS, "wb");

    if (fp) {
        fwrite(enrollments, sizeof(Enrollment), enrollment_count, fp);
        fclose(fp);
    }
}



void enroll_student(void) {
    char student_id[MAX_ID];
    get_string_input(student_id, MAX_ID, "Enter Student ID: ");

    int student_index = -1;

    for (int i = 0; i < student_count; i++) {
        if (students[i].active &&
            strcmp(students[i].student_id, student_id) == 0) {
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
        if (enrollments[i].active &&
            strcmp(enrollments[i].student_id, student_id) == 0) {
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

    get_string_input(
        new_enrollment.course_code,
        MAX_CODE,
        "Enter Course Code: "
    );

    get_string_input(
        new_enrollment.course_name,
        MAX_COURSE_NAME,
        "Enter Course Name: "
    );

    for (int i = 0; i < enrollment_count; i++) {
        if (enrollments[i].active &&
            strcmp(enrollments[i].student_id, student_id) == 0 &&
            strcmp(enrollments[i].course_code,
                   new_enrollment.course_code) == 0) {

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
        printf(
            "Error: Enrollment not found for Student ID '%s' "
            "and Course Code '%s'.\n",
            student_id,
            course_code
        );
        return;
    }

    printf(
        "Enrollment found: %s (%s) - Grade: %.2f\n",
        enrollments[index].course_name,
        enrollments[index].course_code,
        enrollments[index].grade
    );

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

    printf(
        "\n=== Enrollments%s ===\n",
        student_id ? " for Student ID: " : " (All)"
    );

    if (student_id)
        printf("%s\n", student_id);

    printf(
        "%-12s %-20s %-20s %-30s %-8s %-12s\n",
        "Student ID",
        "Course Code",
        "Course Name",
        "Grade",
        "Letter",
        "GPA"
    );

    printf(
        "%-12s %-20s %-20s %-30s %-8s %-12s\n",
        "----------",
        "----------",
        "----------",
        "------",
        "------",
        "--------"
    );

    for (int i = 0; i < enrollment_count; i++) {
        if (!enrollments[i].active)
            continue;

        if (student_id &&
            strcmp(enrollments[i].student_id, student_id) != 0)
            continue;

        char letter[3];

        strcpy(
            letter,
            get_letter_grade(enrollments[i].grade)
        );

        float gpa = grade_to_gpa_points(enrollments[i].grade);

        printf(
            "%-12s %-20s %-20s %-30.2f %-8s %-12.2f\n",
            enrollments[i].student_id,
            enrollments[i].course_code,
            enrollments[i].course_name,
            enrollments[i].grade >= 0
                ? enrollments[i].grade
                : -1.0,
            letter,
            gpa
        );

        found = 1;
    }

    if (!found) {
        if (student_id)
            printf(
                "No enrollments found for Student ID '%s'.\n",
                student_id
            );
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
        printf(
            "Error: Enrollment not found for Student ID '%s' "
            "and Course Code '%s'.\n",
            student_id,
            course_code
        );
        return;
    }

    printf(
        "Current grade: %.2f (%s, GPA: %.2f)\n",
        enrollments[index].grade >= 0
            ? enrollments[index].grade
            : -1.0,
        get_letter_grade(enrollments[index].grade),
        grade_to_gpa_points(enrollments[index].grade)
    );

    float new_grade = get_float_input(
        "Enter new grade (0.0-100.0): ",
        0.0,
        100.0
    );

    enrollments[index].grade = new_grade;

    save_enrollments();

    printf("\nGrade updated successfully!\n");

    printf(
        "New grade: %.2f (%s, GPA: %.2f)\n",
        enrollments[index].grade,
        get_letter_grade(enrollments[index].grade),
        grade_to_gpa_points(enrollments[index].grade)
    );
}



float grade_to_gpa_points(float grade) {
    if (grade < 0) return 0.0;
    if (grade >= 90) return 4.00;
    if (grade >= 85) return 3.70;
    if (grade >= 80) return 3.30;
    if (grade >= 75) return 3.00;
    if (grade >= 70) return 2.70;
    if (grade >= 65) return 2.30;
    if (grade >= 60) return 2.00;
    if (grade >= 55) return 1.70;
    if (grade >= 50) return 1.30;
    if (grade >= 45) return 1.00;

    return 0.00;
}


const char* get_letter_grade(float grade) {
    static char letter[3];

    if (grade < 0) strcpy(letter, "NG");
    else if (grade >= 90) strcpy(letter, "A+");
    else if (grade >= 85) strcpy(letter, "A");
    else if (grade >= 80) strcpy(letter, "A-");
    else if (grade >= 75) strcpy(letter, "B+");
    else if (grade >= 70) strcpy(letter, "B");
    else if (grade >= 65) strcpy(letter, "B-");
    else if (grade >= 60) strcpy(letter, "C+");
    else if (grade >= 55) strcpy(letter, "C");
    else if (grade >= 50) strcpy(letter, "C-");
    else if (grade >= 45) strcpy(letter, "D");
    else strcpy(letter, "F");

    return letter;
}


void clear_input_buffer(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}


float get_float_input(const char *prompt, float min, float max) {
    float value;
    char input[100];

    while (1) {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%f", &value) == 1 &&
                value >= min &&
                value <= max) {

                return value;
            }

            printf(
                "Invalid input. Please enter a number "
                "between %.2f and %.2f.\n",
                min,
                max
            );
        }
    }
}


void get_string_input(
    char *buffer,
    size_t size,
    const char *prompt
) {
    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, size, stdin) != NULL) {
            size_t len = strlen(buffer);

            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            } else {
                int c;

                while ((c = getchar()) != '\n' && c != EOF);
            }

            return;
        }

        printf("Input error. Please try again.\n");
    }
}
