#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stddef.h>

#define MAX_STUDENTS 200
#define MAX_ENROLLMENTS 2000
#define MAX_NAME 50
#define MAX_EMAIL 50
#define MAX_ID 12
#define MAX_CODE 10
#define MAX_COURSE_NAME 50
#define MAX_PASSWORD 20
#define FILE_STUDENTS "students.dat"
#define FILE_ENROLLMENTS "enrollments.dat"
#define MD5_HEX_SIZE 33

typedef enum {
    ROLE_ADMIN = 0,
    ROLE_STAFF = 1,
    ROLE_STUDENT = 2
} UserRole;

typedef struct {
    char student_id[MAX_ID];
    char name[MAX_NAME];
    char email[MAX_EMAIL];
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

extern Student students[MAX_STUDENTS];
extern int student_count;
extern Enrollment enrollments[MAX_ENROLLMENTS];
extern int enrollment_count;

#endif
