#include "common.h"
#include "data.h"

Student students[MAX_STUDENTS];
int student_count = 0;
Enrollment enrollments[MAX_ENROLLMENTS];
int enrollment_count = 0;

void load_data(void) {
    FILE *fp = fopen(FILE_STUDENTS, "rb");
    if (fp) {
        student_count = fread(students, sizeof(Student), MAX_STUDENTS, fp);
        fclose(fp);
    }

    fp = fopen(FILE_ENROLLMENTS, "rb");
    if (fp) {
        enrollment_count = fread(enrollments, sizeof(Enrollment), MAX_ENROLLMENTS, fp);
        fclose(fp);
    }
}


void save_students(void) {
    FILE *fp = fopen(FILE_STUDENTS, "wb");
    if (fp) {
        fwrite(students, sizeof(Student), student_count, fp);
        fclose(fp);
    }
}


void save_enrollments(void) {
    FILE *fp = fopen(FILE_ENROLLMENTS, "wb");
    if (fp) {
        fwrite(enrollments, sizeof(Enrollment), enrollment_count, fp);
        fclose(fp);
    }
}
