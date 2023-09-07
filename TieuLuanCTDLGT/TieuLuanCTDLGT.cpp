#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_STUDENTS 100

struct Student {
    int id;
    char name[50];
    char gender[10];
};

void input_student(struct Student* s) {
    printf("Nhap ID cua hoc sinh: ");
    scanf("%d", &s->id);
    printf("Nhap ten cua hoc sinh: ");
    scanf(" %[^\n]", s->name);
    printf("Gioi tinh hoc sinh: ");
    scanf(" %[^\n]", s->gender);
}

struct Student find_student_by_id(struct Student* students, int num_students, int id) {
    for (int i = 0; i < num_students; i++) {
        if (students[i].id == id) {
            return students[i];
        }
    }
    // Nếu không tìm thấy học sinh có ID như vậy, trả về một học sinh không hợp lệ với ID là -1.
    struct Student invalid_student = { -1, "", "" };
    return invalid_student;
}

void filter_students(struct Student* students, int num_students, char* gender) {
    printf("Loc danh sach hoc sinh co gioi tinh %s:\n", gender);
    for (int i = 0; i < num_students; i++) {
        if (strcmp(students[i].gender, gender) == 0) {
            printf("ID: %d, Name: %s, Gender: %s\n", students[i].id, students[i].name, students[i].gender);
        }
    }
}


int main() {
    struct Student students[MAX_STUDENTS];
    int num_students;
    int choose;
    FILE* fp;
    // Đọc dữ liệu từ file
    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    fscanf(fp, "%d", &num_students);
    for (int i = 0; i < num_students; i++) {
        fscanf(fp, "%d,%[^,],%s", &students[i].id, students[i].name, students[i].gender);
    }
    fclose(fp);

    do {
        printf("\n\t\t\t   Hay chon cac chuc nang sau day");
        printf("\n\t\t\t1: Hien thi thong tin hoc  sinh");
        printf("\n\t\t\t2: Nhap them hoc sinh tu ban phim");
        printf("\n\t\t\t3: Ghi thong tin hoc sinh vao file");
        printf("\n\t\t\t4: Loc gioi tinh hoc sinh");
        printf("\n\t\t\t5: Tim hoc sinh theo ID");

        printf("\n\nNhap lua chon so: ");

        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            // Hiển thị thông tin học sinh đã đọc từ file
            printf("\nThong Tin Hoc Sinh:\n");
            for (int i = 0; i < num_students; i++) {
                printf("ID: %d, Ten: %s, GioiTinh: %s\n", students[i].id, students[i].name, students[i].gender);
            }
            break;
        case 2:
            // Nhập thêm học sinh từ bàn phím
            printf("\nNhap so luong hoc sinh ");
            int num_new_students;
            scanf("%d", &num_new_students);
            for (int i = 0; i < num_new_students; i++) {
                printf("Nhap chi tiet thong tin hoc sinh: \n", i + 1);
                input_student(&students[num_students + i]);
            }
            num_students += num_new_students;
            break;
        case 3:
            // Ghi thông tin học sinh vào file
            fp = fopen("students.txt", "w");
            if (fp == NULL) {
                printf("\nError opening file\n");
                return 1;
            }
            fprintf(fp, "%d\n", num_students);
            for (int i = 0; i < num_students; i++) {
                fprintf(fp, "%d,%s,%s\n", students[i].id, students[i].name, students[i].gender);
            }
            fclose(fp);
            break;
        case 4:
            char gender[10];
            printf("\nnhap vao gioi tinh can loc (nam/nu): ");
            scanf(" %[^\n]", gender);
            filter_students(students, num_students, gender);
            break;
        case 5:
            int id;
            printf("Nhap dia chi ID hoc sinh ban muon tim");
            scanf("%d", &id);
            struct Student found_student = find_student_by_id(students, num_students, id);
            // Kiểm tra xem học sinh có tồn tại hay không
            if (found_student.id == -1) {
                printf("Khong tim thay hoc sinh co ID la %d\n", id);
            }
            else {
                printf("Thong tin hoc sinh co ID la %d:\n", id);
                printf("Name: %s, Gender: %s\n", found_student.name, found_student.gender);
            }
            break;
        }

    } while (choose != 4);
    _getch();
    return 0;
}
