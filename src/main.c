#include "common.h"
#include "auth.h"
#include "data.h"
#include "menu.h"
#include "utils.h"

int main(void) {
    printf("Loading Student Information Management System...\n");
    load_data();
    printf("System loaded successfully! (%d students, %d enrollments)\n",
           student_count, enrollment_count);

    int role;
    char student_id[MAX_ID] = {0};

    do {
        role = login();

        if (role == ROLE_ADMIN) {
            admin_menu();
        }
        else if (role == ROLE_STAFF) {
            staff_menu();
        }
        else if (role == ROLE_STUDENT) {
            do {
                get_string_input(student_id, MAX_ID, "Enter your Student ID: ");
                int valid = 0;
                for (int i = 0; i < student_count; i++) {
                    if (students[i].active && strcmp(students[i].student_id, student_id) == 0) {
                        valid = 1;
                        break;
                    }
                }
                if (valid) {
                    break;
                }
                printf("Invalid Student ID. Please try again.\n");
            } while (1);

            student_menu(student_id);
        }
    } while (role != -1);

    printf("Exiting SIMS. Goodbye!\n");
    return 0;
}
