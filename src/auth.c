#include "common.h"
#include "auth.h"
#include "md5.h"
#include "utils.h"

static const char *ADMIN_PASSWORD   = "admin";
static const char *STAFF_PASSWORD   = "staff";
static const char *STUDENT_PASSWORD = "student";

int login(void) {
    char username[MAX_ID];
    char password[MAX_PASSWORD];
    char password_hash[MD5_HEX_SIZE];
    char expected_hash[MD5_HEX_SIZE];

    printf("\n===== LOGIN =====\n");
    get_string_input(username, MAX_ID, "Username: ");
    get_string_input(password, MAX_PASSWORD, "Password: ");

    md5_hash_string(password, password_hash);

    md5_hash_string(ADMIN_PASSWORD, expected_hash);
    if (strcmp(username, "admin") == 0 && strcmp(password_hash, expected_hash) == 0) {
        return ROLE_ADMIN;
    }

    md5_hash_string(STAFF_PASSWORD, expected_hash);
    if (strcmp(username, "staff") == 0 && strcmp(password_hash, expected_hash) == 0) {
        return ROLE_STAFF;
    }

    md5_hash_string(STUDENT_PASSWORD, expected_hash);
    if (strcmp(username, "student") == 0 && strcmp(password_hash, expected_hash) == 0) {
        return ROLE_STUDENT;
    }

    printf("Invalid username or password. Please try again.\n");
    return -1;
}

void logout(void) {
    /* nothing */
}
