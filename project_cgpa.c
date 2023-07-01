// CGPA CALCULATOR
// TODO
// 1. MAKE A ARRAY OF MARKS , SUBJECT , CREDIT , GRADE -->
// 2. INPUT THE MARKS OF EACH SUBJECT FROM USER AND STORE IN MARKS ARRAY -->
// 3. MAKE A GRADE CALCULATION FUNCTION -->
// 4. STORE THE GRADE ACCORDINGG TO CREDIT IN THE GRADE ARRAY -->
// 5. SUM OF ALL GRADE -->
// 6. FINAL CGPA CALCULATION -->

#include <stdio.h>

// function to calculate grade
int cal_grade(int a)
{

    if (a >= 90)
    {
        return 10;
    }
    else if (a >= 80)
    {
        return 9;
    }
    else if (a >= 70)
    {
        return 8;
    }
    else if (a >= 60)
    {
        return 7;
    }
    else if (a >= 50)
    {
        return 6;
    }
    else if (a >= 40)
    {
        return 5;
    }
    else if (a >= 30)
    {
        return 4;
    }
    else if (a >= 20)
    {
        return 3;
    }
    else if (a >= 10)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

int main()
{
    char subject[9][20] = {"MATH", "C-LAB", "PHYSICS", "EVS", "BIO", "ELECTIVE-1", "ELECTIVE-2", "PHYSICS LAB", "ED LAB"};
    int credit[9] = {4, 4, 3, 2, 2, 2, 2, 1, 1};
    int marks[9] = {0};
    int grade[9] = {0};

    //  marks input
    for (int i = 0; i < 9; i++)
    {
        printf("Enter the marks for %s : ", subject[i]);
        scanf("%d", &marks[i]);
    }

    // grade calculation according to the cradit
    for (int j = 0; j < 9; j++)
    {
        int temp = 0;
        temp = cal_grade(marks[j]);
        temp = temp * credit[j];
        grade[j] = temp;
    }

    // sum of all grade
    float sum = 0;
    for (int k = 0; k < 9; k++)
    {
        sum += grade[k];
    }

    // final calculation

    float cgpa, total_grade = 21;

    cgpa = sum / total_grade;

    printf("\nYour CGPA is : %.2f", cgpa);

    return 0;
}
