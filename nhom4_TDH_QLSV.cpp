#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

struct Information {
    string name, id, gioitinh, quequan, sdt;
    string birthday;
    int day, month, year;
    double gpa;
};

struct Student {
    Information info;
    Student *next;
};

struct ListStudents {
    Student *pHead;
    Student *pTail;
};

// Nhập thông tin sinh viên
Information getInform () {
    Information inform;
    cout << "Nhap thong tin sinh vien: " << endl;
    cout << "ID: " ;
    fflush(stdin);
    getline(cin, inform.id);
    bool trueName  = true;
    do {
        cout << "Ho ten: ";
        fflush(stdin);
        getline(cin, inform.name);
        for (int i = 0; i < inform.name.length(); i++) {
            if (inform.name[i] >= 'a' && inform.name[i] <= 'z' || inform.name[i] >= 'A' && inform.name[i] <= 'Z' || inform.name[i] == ' ') {
                trueName = true;
            } else {
                trueName = false;
                break;
            }
        }
    } while (! trueName);

    cout << "Gioi tinh: ";
    fflush(stdin);
    getline(cin, inform.gioitinh);

    do {
        cout << "GPA: ";
        cin >> inform.gpa;
    } while (inform.gpa < 0 || inform.gpa > 10);

    bool trueBirthday = true;

    do {
        // nhập ngày sinh
        do {
            cout << "Ngay sinh: ";
            cin >> inform.day;
        } while (inform.day < 1 || inform.day > 31);
        // nhập tháng sinh
        do {
            cout << "Thang sinh: ";
            cin >> inform.month;
        } while (inform.month < 1 || inform.month > 12);
        // nhập năm sinh
        do {
            cout << "Nam sinh: ";
            cin >> inform.year;
        } while (inform.year > 2006);
        // kiểm tra ngày sinh
        if (inform.month == 2) {
            if (inform.year % 4 == 0 && inform.year % 100 != 0 || inform.year % 400 == 0) {
                if (inform.day > 29) {
                    trueBirthday = false;
                } else {
                    trueBirthday = true;
                }
            } else {
                if (inform.day > 28) {
                    trueBirthday = false;
                } else {
                    trueBirthday = true;
                }
            }
        } else if (inform.month == 4 || inform.month == 6 || inform.month == 9 || inform.month == 11) {
            if (inform.day > 30) {
                trueBirthday = false;
            } else {
                trueBirthday = true;
            }
        } else {
            trueBirthday = true;
        }
    } while (! trueBirthday);

    // chuyển ngày sinh sang chuỗi dạng dd/mm/yyyy không dùng hàm to_string
    inform.birthday = "";
    if (inform.day < 10) {
        inform.birthday += "0";
        inform.birthday += inform.day + '0';
    } else {
        inform.birthday += inform.day / 10 + '0';
        inform.birthday += inform.day % 10 + '0';
    }
    inform.birthday += "/";
    if (inform.month < 10) {
        inform.birthday += "0";
        inform.birthday += inform.month + '0';
    } else {
        inform.birthday += inform.month / 10 + '0';
        inform.birthday += inform.month % 10 + '0';
    }
    inform.birthday += "/";
    inform.birthday += inform.year / 1000 + '0';
    inform.birthday += inform.year / 100 % 10 + '0';
    inform.birthday += inform.year / 10 % 10 + '0';
    inform.birthday += inform.year % 10 + '0';
    
    cout << "Que quan: ";
    fflush(stdin);
    getline(cin, inform.quequan);
     
    cout << "SDT: ";
    fflush(stdin);
    getline(cin, inform.sdt);
    
    return inform;
}

// Tạo node mới với thông tin sinh viên nhập từ bàn phím
Student *createStudent () {
    Student *student = new Student;
    student->info = getInform();
    student->next = NULL;
    return student;
}

// Kiêm tra rỗng
bool isEmpty (ListStudents *list) {
    if (list->pHead == NULL) {
        return true;
    }
    return false;
}

// Khởi tạo danh sách liên kết rỗng
ListStudents *createList () {
    ListStudents *list = new ListStudents();
    list->pHead = NULL;
    list->pTail = NULL;
    return list;
}

// Thêm 1 phần tử vào đầu danh sách liên kết
void addHead (ListStudents *&list) {
    Student *student = createStudent();
    if (list->pHead == NULL) {
        list->pHead = student;
        list->pTail = student;
        return;
    }
    student->next = list->pHead;
    list->pHead = student;
}

// Thêm 1 phần tử vào cuối dslk
void addTail (ListStudents *&list) {
    Student *student = createStudent();
    if (list->pHead == NULL) {
        list->pHead = student;
        list->pTail = student;
        return;
    }
    list->pTail->next = student;
    list->pTail = student;
}

// Đếm số lượng sinh viên
int countStudent (ListStudents *&list) {
    int count = 0;
    Student *student = list->pHead;
    while (student != NULL) {
        count++;
        student = student->next;
    }
    return count;
   
}

// Xóa phần tử ở đầu
void deleteHead (ListStudents *&list) {
    if (isEmpty(list)) {
        cout << "Danh sach rong" << endl;
        return;
    }
    Student *student = list->pHead;
    list->pHead = list->pHead->next;
    delete student;
}

// Xóa phần tử ở cuối
void deleteTail (ListStudents *&list) {
    if (isEmpty(list)) {
        cout << "Danh sach rong" << endl;
        return;
    }
    Student *student = list->pHead;
    while (student->next != list->pTail) {
        student = student->next;
    }
    delete list->pTail;
    list->pTail = student;
    student->next = NULL;
}

// Chèn sinh viên vào vị trí pos
void insertPos (ListStudents *&list, int pos) {
    Student *student = createStudent();
    Student *temp = list->pHead;

    if (pos == 1) {
        addHead(list);
        return;
    }

    if (pos == countStudent(list) + 1) {
        addTail(list);
        return;
    }

    if (pos > countStudent(list) + 1) {
        cout << "Vi tri khong hop le" << endl;
        return;
    }

    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }
    student->next = temp->next;
    temp->next = student;
}

// Xóa sinh viên ở vị trí pos
void deletePos (ListStudents *&list, int pos) {
    Student *student = list->pHead;
    Student *temp = list->pHead;

    if (pos == 1) {
        deleteHead(list);
        return;
    }

    if (pos == countStudent(list)) {
        deleteTail(list);
        return;
    }

    if (pos > countStudent(list)) {
        cout << "Vi tri khong hop le" << endl;
        return;
    }

    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }
    student = temp->next;
    temp->next = student->next;
    delete student;
}

// In thông tin sinh viên
void printInform (Information inform) {
    cout << "ID: " << inform.id << endl;
    cout << "Ho ten: " << inform.name << endl;
    cout << "Gioi tinh: " << inform.gioitinh << endl;
    cout << "Ngay sinh: " << inform.birthday << endl;
    cout << "Que quan: " << inform.quequan << endl;
	cout << "SDT: " << inform.sdt << endl;    
    cout << "GPA: " << inform.gpa << endl;

}

// In danh sách sinh viên
void printList (ListStudents *list) {
    Student *student = list->pHead;
    cout << "Danh sach sinh vien: " << endl;
    while (student != NULL) {
        printInform(student->info);
        student = student->next;
    }
}

// Sắp xếp danh sách sinh viên theo ID
void sortList (ListStudents *&list) {
    Student *student = list->pHead;
    Student *temp = list->pHead;
    while (student != NULL) {
        temp = student->next;
        while (temp != NULL) {
            if (student->info.id > temp->info.id) {
                Information tempInfo = student->info;
                student->info = temp->info;
                temp->info = tempInfo;
            }
            temp = temp->next;
        }
        student = student->next;
    }
}

// Sắp xếp danh sách sinh viên theo GPA
void sortListGPA (ListStudents *&list) {
    Student *student = list->pHead;
    Student *temp = list->pHead;
    while (student != NULL) {
        temp = student->next;
        while (temp != NULL) {
            if (student->info.gpa < temp->info.gpa) {
                Information tempInfo = student->info;
                student->info = temp->info;
                temp->info = tempInfo;
            }
            temp = temp->next;
        }
        student = student->next;
    }
}

// Tìm kiếm sinh viên theo ID
void searchStudent (ListStudents *list) {
    string id;
    cout << "Nhap ID sinh vien can tim: ";
    fflush(stdin);
    getline(cin, id);
    Student *student = list->pHead;
    while (student != NULL) {
        if (student->info.id == id) {
            printInform(student->info);
            return;
        }
        student = student->next;
    }
    cout << "Khong tim thay sinh vien" << endl;
}

// Tìm kiếm sinh viên theo tên
void searchStudentName (ListStudents *list) {
    string name;
    cout << "Nhap ten sinh vien can tim: ";
    fflush(stdin);
    getline(cin, name);
    Student *student = list->pHead;
    while (student != NULL) {
        if (strcmp(student->info.name.c_str(), name.c_str()) == 0) {
            printInform(student->info);
            return;
        }
        student = student->next;
    }
    cout << "Khong tim thay sinh vien" << endl;
}

// Tìm sinh viên có GPA thấp nhất
void searchStudentMinGPA (ListStudents *list) {
    Student *student = list->pHead;
    Student *temp = list->pHead;
    while (student != NULL) {
        if (student->info.gpa < temp->info.gpa) {
            temp = student;
        }
        student = student->next;
    }
    printInform(temp->info);
}

// Tìm sinh viên có GPA cao nhất 
void searchStudentMaxGPA (ListStudents *list) {
    Student *student = list->pHead;
    Student *temp = list->pHead;
    while (student != NULL) {
        if (student->info.gpa > temp->info.gpa) {
            temp = student;
        }
        student = student->next;
    }
    printInform(temp->info);
}

void set_color( int code ) {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}

int main() {

    ListStudents *list = createList();

    int choice;
    do { 
    	set_color( 10 );
    	cout << "===================MENU==================\n";
    	set_color( 0 | 15 );
        cout << "1. Them sinh vien vao dau danh sach" << endl;
        cout << "2. Them sinh vien vao cuoi danh sach" << endl;
        cout << "3. Them sinh vien vao vi tri bat ki" << endl;
        cout << "4. Xoa sinh vien o dau danh sach" << endl;
        cout << "5. Xoa sinh vien o cuoi danh sach" << endl;
        cout << "6. Xoa sinh vien o vi tri bat ki" << endl;
        cout << "7. Sap xep danh sach sinh vien theo ID" << endl;
        cout << "8. Sap xep danh sach sinh vien theo GPA" << endl;
        cout << "9. Tim kiem sinh vien theo ID" << endl;
        cout << "10. Tim kiem sinh vien theo ten" << endl;
        cout << "11. Tim sinh vien co GPA thap nhat" << endl;
        cout << "12. Tim sinh vien co GPA cao nhat" << endl;
        cout << "13. In danh sach sinh vien" << endl;
        cout << "0. Thoat" << endl;
        set_color( 10 );
        cout << "=========================================\n";
        set_color( 14 ); 
        cout << "Nhap lua chon: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addHead(list);
                break;
            case 2:
                addTail(list);
                break;
            case 3:
                int pos;
                cout << "Nhap vi tri can them: ";
                cin >> pos;
                insertPos(list, pos);
                break;
            case 4:
                deleteHead(list);
                break;
            case 5:
                deleteTail(list);
                break;
            case 6:
                cout << "Nhap vi tri can xoa: ";
                cin >> pos;
                deletePos(list, pos);
                break;
            case 7:
                sortList(list);
                break;
            case 8:
                sortListGPA(list);
                break;
            case 9:
                searchStudent(list);
                break;
            case 10:
                searchStudentName(list);
                break;
            case 11:
                searchStudentMinGPA(list);
                break;
            case 12:
                searchStudentMaxGPA(list);
                break;               
            case 13:
                printList(list);
                break;
            case 0:
                cout << "Thoat chuong trinh" << endl;
                break;
            default:
                cout << "Nhap sai, vui long nhap lai" << endl;
                break;
        }
    } while (choice != 0);       

}
