#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Employee struct emp

void add(FILE *fp);
FILE *del(FILE *fp); 
void searchRecord(FILE *fp); 
void displayList(FILE *fp); 
void welcome(); 

struct emp {
    int id;
    char name[100];
    char desgn[10];
    float sal;
};

int main() {
    FILE *fp;
    int option;
    char another;

    welcome();

    if ((fp = fopen("employeeInfo.txt", "rb+")) == NULL) {
        if ((fp = fopen("employeeInfo.txt", "wb+")) == NULL) {
            printf("Can't open file");
            return 0;
        }
    }

    while (1) {
        system("cls");
        printf("\n\n\t\t\t\tMain Menu\n\n");

        printf("\n\t\t1. Add Employee");
        printf("\n\t\t2. Delete Employee");
        printf("\n\t\t3. Search Employee");
        printf("\n\t\t4. Display All Employees");
        printf("\n\t\t0. Exit");

        printf("\n\n\t\tEnter Your Option : ");
        scanf("%d", &option);

        switch (option) {
            case 0:
                return 0;
            case 1:
                add(fp);
                break;
            case 2:
                fp = del(fp);
                break;
            case 3:
                searchRecord(fp);
                break;
            case 4:
                displayList(fp);
                break;
            default:
                printf("\n\t\tYou Pressed wrong key");
                printf("\n\t\tProgram terminated\n");
                exit(0);
        }
    }

    return 1;
}

void welcome() {
    char username[10], password[10];
    int i;
    system("cls");
    printf("\n\n\n\n\n\t\t[ [ [ WELCOME TO OUR EMPLOYEE MANAGEMENT SYSTEM ] ] ]\n\n\n\n\n\n\n\t");
    system("pause");
    system("cls");
    printf("\n\n\t\t\t\t  Login Screen");
    printf("\n\t\t\t      Enter Your Credential");
    printf("\n\n\n\t\tUsername: ");
    scanf("%s", username);
    printf("\t\tPassword: ");

    i = 0;
    do {
        password[i] = getch();
        if (password[i] == 13) {
            break;
        } else if (password[i] == 8 && i > 0) {
            printf("\b \b");
            i--;
        } else {
            printf("*");
            i++;
        }
    } while (password[i] != 13);

    password[i] = '\0';

    if ((strcasecmp(username, "sujoy") == 0) && (strcasecmp(password, "sujoy") == 0)) {
        printf("\n\n\t\tLogin Successful\n\n");
    } else {
        printf("\n\n\t\tLogin Failed\n\n");
        exit(0);
    }
    system("pause");
}

void add(FILE *fp) {
    system("cls");
    printf("\n\n\t\tAdd Employee");

    Employee e;

    fseek(fp, 0, SEEK_END);

    printf("\n\n\t\tEnter ID number: ");
    scanf("%d", &e.id);

    printf("\n\t\tEnter Full Name of Employee: ");
    scanf("%s", e.name);

    printf("\n\t\tEnter Designation: ");
    scanf("%s", e.desgn);

    printf("\n\t\tEnter Salary: ");
    scanf("%f", &e.sal);

    fwrite(&e, sizeof(e), 1, fp);

    printf("\n\n\t\tEmployee added successfully!");
    system("pause");
}

FILE *del(FILE *fp) {
    system("cls");
    printf("\n\n\t\tDelete Employee");

    Employee e;
    int flag = 0, tempid, siz = sizeof(e);
    FILE *ft;

    if ((ft = fopen("temp.txt", "wb+")) == NULL) {
        printf("\n\n\t\tError creating temporary file\n");
        return fp;
    }

    printf("\n\n\t\tEnter ID number of Employee to Delete the Record: ");
    scanf("%d", &tempid);

    rewind(fp);

    while (fread(&e, siz, 1, fp) == 1) {
        if (e.id == tempid) {
            flag = 1;
            printf("\n\n\t\tRecord deleted for ID: %d\n", e.id);
            continue;
        }
        fwrite(&e, siz, 1, ft);
    }

    fclose(fp);
    fclose(ft);

    remove("employeeInfo.txt");
    rename("temp.txt", "employeeInfo.txt");

    if ((fp = fopen("employeeInfo.txt", "rb+")) == NULL) {
        printf("Error opening file");
        return NULL;
    }

    if (flag == 0)
        printf("\n\n\t\tRecord not found\n");

    system("pause");
    return fp;
}

void searchRecord(FILE *fp) {
    system("cls");
    printf("\n\n\t\tSearch Employee");

    int tempid, flag = 0;
    Employee e;

    printf("\n\n\t\tEnter ID Number of Employee to search the record: ");
    scanf("%d", &tempid);

    rewind(fp);

    while (fread(&e, sizeof(e), 1, fp) == 1) {
        if (e.id == tempid) {
            flag = 1;
            printf("\n\n\t\tID: %d", e.id);
            printf("\n\t\tName: %s", e.name);
            printf("\n\t\tDesignation: %s", e.desgn);
            printf("\n\t\tSalary: %.2f\n", e.sal);
            break;
        }
    }

    if (flag == 0)
        printf("\n\n\t\tRecord not found\n");

    system("pause");
}

void displayList(FILE *fp) {
    system("cls");
    printf("\n\n\t\tDisplay All Employees");

    Employee e;

    rewind(fp);

    while (fread(&e, sizeof(e), 1, fp) == 1) {
        printf("\n\n\t\tID: %d", e.id);
        printf("\n\t\tName: %s", e.name);
        printf("\n\t\tDesignation: %s", e.desgn);
        printf("\n\t\tSalary: %.2f\n", e.sal);
    }
    system("pause");
}
