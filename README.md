# Student Information Management System (SIMS)

A modular C version of the original Student Information Management System.

## Modules

- `main.c` — startup and role routing
- `auth.c` — login/logout and password hashing
- `md5.c` — MD5 implementation
- `data.c` — load/save student and enrollment records
- `student.c` — student CRUD operations
- `enrollment.c` — enrollment and grade operations
- `reporting.c` — transcripts, rosters, top performers
- `utils.c` — input, string, and grading helpers
- `menu.c` — menus and navigation
- `common.h` — shared constants, structures, and global declarations

## Build

```bash
gcc -std=c11 -Wall -Wextra -Iinclude src/*.c -o sims
```

Run `./sims` (or `sims.exe` on Windows).
