#include "common.h"
#include "utils.h"

void to_lower(char *str) {
    for (; *str; ++str) *str = tolower(*str);
}


int compare_strings_ignore_case(const char *s1, const char *s2) {
    char s1_copy[MAX_NAME], s2_copy[MAX_NAME];
    strncpy(s1_copy, s1, MAX_NAME-1);
    strncpy(s2_copy, s2, MAX_NAME-1);
    s1_copy[MAX_NAME-1] = s2_copy[MAX_NAME-1] = '\0';
    to_lower(s1_copy);
    to_lower(s2_copy);
    return strcmp(s1_copy, s2_copy);
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


int get_int_input(const char *prompt, int min, int max) {
    int value;
    char input[100];

    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &value) == 1 && value >= min && value <= max) {
                return value;
            }
            printf("Invalid input. Please enter an integer between %d and %d.\n", min, max);
        }
    }
}


float get_float_input(const char *prompt, float min, float max) {
    float value;
    char input[100];

    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%f", &value) == 1 && value >= min && value <= max) {
                return value;
            }
            printf("Invalid input. Please enter a number between %.2f and %.2f.\n", min, max);
        }
    }
}


void get_string_input(char *buffer, size_t size, const char *prompt) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) != NULL) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len-1] == '\n') {
                buffer[len-1] = '\0';
            } else {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
            return;
        }
        printf("Input error. Please try again.\n");
    }
}
