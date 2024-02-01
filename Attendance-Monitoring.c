#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

struct Student
{
    int rollNum;
    int idNum;
    char fullName[50];
    char Course[10];
    char username[15];
    char password[15];
};

typedef struct{
    int idNum;
    char username[30];
    char password[30];
} Student;

int recordCount = 0;

void adminLogin();
void studentLogin();
void addStudent();
void studentRecord();
void searchStudent();
void deleteRecord();
void viewAttendance();
void timeIn(const char *username);
void timeOut(const char *username);


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void getCurrentTime(char timeStr[]) {
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    strftime(timeStr, 20, "%Y-%m-%d %H:%M:%S", localTime);
}

int nameExist(const char *filename, const char *fullName) {
    FILE *fp;
    struct Student info;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "\n\n\t\t\033[1;31mCan't open file..\033[0m\n");
        exit(EXIT_FAILURE);
    }

    while (fread(&info, sizeof(struct Student), 1, fp)) {
        if (strcmp(info.fullName, fullName) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


int main()
{
    char choice;
    do
    {
        system("cls");
        printf(" --------------------------------------------------------------\n");
        printf(" |||||||||||||||[\033[1;31mATTENDANCE MONITORING SYSTEM\033[0m]|||||||||||||||||\n");
        printf(" --------------------------------------------------------------\n\n\n");
        printf("              [1] \033[1;32m<<<Admin Login>>>\033[0m           \n");
        printf("                                                               \n");
        printf("              [2] \033[1;33m<<<Student Attendance>>>\033[0m         \n\n\n");
        printf(" --------------------------------------------------------------\n");
		printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
		printf(" --------------------------------------------------------------\n");
        
        printf("\n\n\t\tSelect User: ");
        scanf(" %c", &choice);
		
		int c;
        while ((c = getchar()) != '\n' && c != EOF);
		
        switch (choice)
        {
        case '1':
            adminLogin();
            break;
        case '2':
            studentLogin();
            break;
        default:
            printf("\n\n\tInvalid choice!! Press any key to try again...");
            getch();
        }
    } while (choice != '1' && choice != '2');
	
	do
    {
    	printf(" ---------------------------------------------------------------\n");
    	printf(" ||||||||||||||||||||\033[1;32m[WELCOME BACK, ADMIN]\033[0m||||||||||||||||||||||\n");
    	printf(" ---------------------------------------------------------------\n\n");
        printf("\t[1] Add Student Information\n\n");
        printf("\t[2] Show Records\n\n");
        printf("\t[3] Search Student\n\n");
        printf("\t[4] Delete Record\n\n");
        printf("\t[5] View Student Attendance\n\n");
        printf("\t[6] Logout\n\n");
        printf(" --------------------------------------------------------------\n");
		printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
		printf(" --------------------------------------------------------------\n");
        printf("\n\n\tEnter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
            addStudent();
            system("cls");
            break;
        case '2':
            studentRecord();
            printf("\n\n\t\t\033[1;32mTotal Records:\033[0m  %d", recordCount);
            printf("\n\n\t\tPress any key to exit..");
            getch();
            system("cls");
            break;
        case '3':
            searchStudent();
            printf("\n\n\t\tPress any key to exit..");
            getch();
            system("cls");
            break;
        case '4':
            deleteRecord();
            printf("\n\n\t\tPress any key to exit..");
            getch();
            system("cls");
            break;
        case '5':
            viewAttendance();
            printf("\n\n\t\tPress any key to exit..");
            getch();
            system("cls");
            break;
        case '6':
            system("cls");
            printf(" --------------------------------------------------------------\n");
			printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
			printf(" --------------------------------------------------------------\n");
			printf(" .                                                            .\n");
			printf(" .                     Account Logged out                     .\n");
			printf(" .                        Goodbye Admin!                      .\n");
			printf(" .                                                            .\n");
			printf(" --------------------------------------------------------------\n");
			printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
			printf(" --------------------------------------------------------------\n");
			exit(0);
        default:
            printf("\n\n\t\tInvalid choice. Please enter a number between 1 and 5!");
            getch();
            system("cls");
        }
    } while (choice != '6');

    return 0;
}

void adminLogin()
{
    int a = 0, i = 0;
    char username[10], c = ' ';
    char password[10], code[10];
    char user[10] = "admin";
    char pass[10] = "passw";

    do
    {
    	i = 0;
        system("cls");
        printf("--------------------------------------------------------------\n");
        printf("|||||||||||||||||||||||\033[1;32mADMIN LOGIN\033[0m||||||||||||||||||||||||||||\n");
        printf("--------------------------------------------------------------\n");
        printf("\n\n\tEnter username: ");
        scanf("%s", &username);
        printf("\n\n\tEnter password: ");

        while (i < 10)
        {
            password[i] = getch();
            c = password[i];
            if (c == 13)
                break;
            else
                printf("*");
            i++;
        }

        password[i] = '\0';
        
        if (strcmp(username, user) == 0 && strcmp(password, pass) == 0)
        {
            printf("\n\n\tLoading ");

            int dots;
            for (dots = 0; dots < 4; dots++)
            {
                Sleep(350);
                printf(".");
            }

            printf("\r                                    ");
            printf("\n\n\t\033[1;32mLogin successful! Welcome Admin!\033[0m");
            Sleep(1000);
            system("cls");
            break;
        }
        else
        {
            printf("\n\n\t\033[1;31mSorry. Login unsuccessful.\033[0m");
            a++;
            getch();
        }
    } while (a <= 2);

    if (a > 2)
    {
        printf("\n\n\n\tLogin limit has been reached.");
        printf("\n\n\tThe program will now be terminated.");
        Sleep(2000);
        exit(0);
    }

}

void studentLogin()
{
    int maxAttempts = 2;
    int found = 0;
    int rollNum;

    do
    {
        system("cls");
        printf("--------------------------------------------------------------\n");
        printf("||||||||||||||||||||||||\033[1;33mSTUDENT ATTENDANCE\033[0m|||||||||||||||||||||||||\n");
        printf("--------------------------------------------------------------\n");

        int attempts = 0;

        do
        {
            printf("\n\n\tEnter Roll Number: ");
            scanf("%d", &rollNum);
            clearBuffer();

            FILE *fp;
            struct Student info;
            fp = fopen("student_info.txt", "r");

            if (fp == NULL)
            {
                fprintf(stderr, "\n\n\t\033[1;31mCan't open file..\033[0m");
                exit(0);
            }

            found = 0;
            while (fread(&info, sizeof(struct Student), 1, fp))
            {
                if (info.rollNum == rollNum)
                {
                    found = 1;
                    printf("\n\n\t\033[1;32mLogin successful! Welcome, %s!\033[0m", info.fullName);
                    Sleep(1000);

                    int choice;
                    do
                    {
                        system("cls");
                        printf(" --------------------------------------------------------------\n");
                        printf(" ||||||||||||||||||||||||||\033[1;33mATTENDANCE\033[0m||||||||||||||||||||||||||\n");
                        printf(" --------------------------------------------------------------\n");
                        printf("\n\n\t[1] Time In");
                        printf("\n\n\t[2] Time Out");
                        printf("\n\n\t[3] Return");
                        printf("\n\n\t[4] Exit Program");
                        printf("\n\n --------------------------------------------------------------\n");
                        printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
                        printf(" --------------------------------------------------------------\n");
                        printf("\n\n\tEnter your choice: ");
                        scanf("%d", &choice);

                        switch (choice)
                        {
                        case 1:
                            timeIn(info.fullName);
                            break;
                        case 2:
                            timeOut(info.fullName);
                            break;
                        case 3:
                            break;
                        case 4:
                            system("cls");
                            printf(" --------------------------------------------------------------\n");
                            printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
                            printf(" --------------------------------------------------------------\n");
                            printf(" .                                                            .\n");
                            printf(" .                       Logged out                           .\n");
                            printf(" .                 Goodbye, %s!                   .\n", info.fullName);
                            printf(" .                                                            .\n");
                            printf(" --------------------------------------------------------------\n");
                            printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
                            printf(" --------------------------------------------------------------\n");
                            printf("\n\n\tPress 'Esc' to exit. ");
                            char exitChoice = getch();
                            if (exitChoice == 27)
                            {
                                exit(0);
                            }
                            else
                            {
                                break;
                            }
                        default:
                            printf("\n\n\tInvalid choice. Please enter a valid option.\n");
                        }
                    } while (choice != 3);

                    break;
                }
            }

            fclose(fp);

            if (found)
            {
                break;
            }
            else
            {
                attempts++;
                printf("\n\n\t\033[1;31mNo record found. Login unsuccessful.\033[0m");
                printf("\n\n\tRemaining attempts: %d\n\n", maxAttempts - attempts);
                getch();
            }

        } while (attempts < maxAttempts);

        if (!found)
        {
            printf("\n\n\n\tLogin limit has been reached.");
        	printf("\n\n\tThe program will now be terminated.");
            exit(0);
        }

    } while (1); 
}


void addStudent()
{
    char another;
    FILE *fp;
    struct Student info;

    do
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
		
		if (recordCount >= 50)
        {
            printf("\n\n\t\033[1;31mMaximum number of students reached (50).\033[0m\n");
            printf("\n\n\tPress any key to exit...");
            getch();
            system("cls");
            return;
        }
		
		system("cls");
        printf("--------------------------------------------------------------\n");
        printf("|||||||||||||||||\033[1;32mADD STUDENT INFORMATION\033[0m||||||||||||||||||||||\n");
        printf("--------------------------------------------------------------\n");
        fp = fopen("student_info.txt", "a");
        if (fp == NULL)
        {
            fprintf(stderr,"\n\t\t\033[1;31mCan't open file..\033[0m\n");
        }

        while (1) 
		{
    		printf("\n\n\tRoll Number: ");
    			if (scanf("%d", &info.rollNum) == 1) {
        		break;
    		} else {
        		printf("\n\n\t\033[1;31mInvalid input. Please enter a valid number for Roll Number.\033[0m\n");
        		clearBuffer();
    		}
		}

        printf("\n\n\tID number: ");
        scanf("%d", &info.idNum);
        
    	do {
            printf("\n\n\tFull name of the student: ");
            fflush(stdin);
            fgets(info.fullName, sizeof(info.fullName), stdin);
            info.fullName[strcspn(info.fullName, "\n")] = '\0';

            if (nameExist("student_info.txt", info.fullName)) {
                printf("\n\n\t\033[1;31mFull name already exists!\033[0m\n");
            }
        } while (nameExist("student_info.txt", info.fullName));
        
        printf("\n\n\tCourse: ");
        scanf("%s", info.Course);
        printf("\n\n\t\033[1;32mCreate Student Login Details\033[0m");
        printf("\n\n\tUsername: ");
        scanf("%s", info.username);
        printf("\n\n\tPassword: ");
        scanf("%15s", info.password);

        printf(" --------------------------------------------------------------\n");
		printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
		printf(" --------------------------------------------------------------\n");;
        printf("\n\n\t\033[1;32mRecord stored successfully!\033[0m\n");
        fwrite(&info, sizeof(struct Student), 1, fp);
        fclose(fp);

        printf("\n\n\tDo you want to add another record? (y/n)  ");
        scanf(" %c", &another);
		
        if (another == 'n' || another == 'N')
        {
            system("cls");
        }
    } while (another == 'y' || another == 'Y');
}

void studentRecord()
{
    FILE *fp;
    struct Student info;
    recordCount = 0;
    fp = fopen("student_info.txt", "r");

    system("cls");
    printf("--------------------------------------------------------------\n");
    printf("||||||||||||||||||||||||\033[1;32mSTUDENT RECORDS\033[0m|||||||||||||||||||||||\n");
    printf("--------------------------------------------------------------\n");

    if (fp == NULL)
    {
        fprintf(stderr, "\n\n\t\033[1;31mCan't open file'..\033[0m\n");
    }
    
	while (fread(&info, sizeof(struct Student), 1, fp))
    {
        recordCount++;
		printf("\n\n\t\tRoll Number : %d", info.rollNum);
        printf("\n\n\t\tID Number   : %d", info.idNum);
		printf("\n\n\t\tStudent name: %s", info.fullName);
        printf("\n\n\t\tClass/Course: %s", info.Course);
        printf("\n\n\t\tUsername    : %s", info.username);
        printf("\n\n\t\tPassword    : %s\n\n", info.password);
        printf("_______________________________________________________________\n");
    }
    printf(" \n\n --------------------------------------------------------------\n");
	printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	printf(" --------------------------------------------------------------\n");;
    fclose(fp);
}

void searchStudent()
{
    FILE *fp;
    struct Student info;
    int rollNum, found = 0;
    fp = fopen("student_info.txt", "r");

    system("cls");
    printf(" --------------------------------------------------------------\n");
    printf(" |||||||||||||||||||||\033[1;32mSEARCH STUDENT RECORD\033[0m||||||||||||||||||||\n");
    printf(" --------------------------------------------------------------\n");
    printf("\n\n\t\tRoll Number: ");
    scanf("%d", &rollNum);

    if (fp == NULL)
    {
        fprintf(stderr, "\n\n\t\t\033[1;31mCan't open file'..\033[0m\n");
    }

    while (fread(&info, sizeof(struct Student), 1, fp))
    {
        if (info.rollNum == rollNum)
        {
            found = 1;
        	printf("\n\n\t\tID Number   : %d", info.idNum);
			printf("\n\n\t\tStudent name: %s", info.fullName);
        	printf("\n\n\t\tClass/Course: %s", info.Course);
        	printf("\n\n\t\tUsername    : %s", info.username);
        	printf("\n\n\t\tPassword    : %s", info.password);
        	printf(" \n\n --------------------------------------------------------------\n");
		printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
		printf(" --------------------------------------------------------------\n");
        }
    }
    
	if (!found)
    {
		printf("\n\n\033[1;31mRecord not found. Kindly fill your record first. Thank you!\033[0m\n");
    }
    fclose(fp);
}

void deleteRecord()
{
    FILE *fp, *fp1;
    struct Student info;
    int rollNum, found = 0;
    char choice;
    char another;

    do
    {
        system("cls");
        printf("--------------------------------------------------------------\n");
        printf("||||||||||||||||||||||\033[1;32mDELETE STUDENT RECORD\033[0m|||||||||||||||||||\n");
        printf("--------------------------------------------------------------\n");
        printf("\n\n\t\tAre you sure if you want to delete the record?");
        printf("\n\n\t\tRoll Number: ");
        scanf("%d", &rollNum);

        fp = fopen("student_info.txt", "r");
        if (fp == NULL)
        {
            fprintf(stderr, "\n\n\t\t\033[1;36mCan't open file..\033[0m\n");
            exit(EXIT_FAILURE);
        }

        fp1 = fopen("temp.txt", "w");
        if (fp1 == NULL)
        {
            fprintf(stderr, "\n\n\t\t\033[1;36mCan't open file..\033[0m\n");
            fclose(fp);
        }

        while (fread(&info, sizeof(struct Student), 1, fp))
        {
            if (info.rollNum == rollNum)
            {
                found = 1;
            }
            else
            {
                fwrite(&info, sizeof(struct Student), 1, fp1);
            }
        }

        fclose(fp);
        fclose(fp1);

        if (found)
        {
            remove("student_info.txt");
            rename("temp.txt", "student_info.txt");
            printf("\n\t\t\033[1;32mRecord deleted..\033[0m");
            recordCount--;
        }

        if (!found)
        {
            printf("\n\t\t\033[1;31mRecord not found..\033[0m");
        }

        printf("\n\n\t\tDo you want to delete another record? (y/n): ");
        scanf(" %c", &choice);
        
        if (choice == 'n' || choice == 'N')
        {
            system("cls");
        }

    } while (choice == 'y' || choice == 'Y');
}

void timeIn(const char *username) {
    FILE *fp2;
    fp2 = fopen("student_attendance.txt", "a+");

    if (fp2 == NULL) {
        fprintf(stderr, "\n\n\t\t\033[1;31mCan't open attendance file..\033[0m\n");
    }

    system("cls");
    printf(" --------------------------------------------------------------\n");
    printf(" |||||||||||||||||||||||||||\033[1;33mTIME IN\033[0m||||||||||||||||||||||||||||\n");
    printf(" --------------------------------------------------------------\n");
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    char timeIn[64];
    strftime(timeIn, sizeof(timeIn), "%Y-%m-%d - %A, %I:%M:%S %p", localTime);
	printf("\n\t\033[1;32mSuccessfully Timed in!\033[0m\n");
    printf("\n\t\033[1;33mRecorded at\033[0m: %s\n", timeIn);

    fprintf(fp2, "%s - Time In: %s\n", username, timeIn);
	
	printf(" \n\n --------------------------------------------------------------\n");
	printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	printf(" --------------------------------------------------------------\n");
    fclose(fp2);
    printf("\n\n\tDon't forget to log your time out after class.");
    getch();
}


void timeOut(const char *username) {
    FILE *fp2;
    fp2 = fopen("student_attendance.txt", "a+");

    if (fp2 == NULL) {
        fprintf(stderr, "\n\n\t\t\033[1;31mCan't open attendance file..\033[0m\n");
    }

    system("cls");
    printf(" --------------------------------------------------------------\n");
    printf(" |||||||||||||||||||||||||||\033[1;33mTIME IN\033[0m||||||||||||||||||||||||||||\n");
    printf(" --------------------------------------------------------------\n");

    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    char timeIn[64];
    strftime(timeIn, sizeof(timeIn), "%Y-%m-%d - %A, %I:%M:%S %p", localTime);
	printf("\n\t\033[1;32mSuccessfully Timed Out!\033[0m\n");
    printf("\n\t\033[1;33mRecorded at\033[0m: %s\n", timeIn);

    fprintf(fp2, "%s - Time Out: %s\n", username, timeIn);
	
	printf(" \n\n --------------------------------------------------------------\n");
	printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	printf(" --------------------------------------------------------------\n");
    fclose(fp2);
    printf("\n\n\tYour attendance has been recorded!");
    getch();
}


void viewAttendance(const struct Student info) {
    FILE *fp2;
    fp2 = fopen("student_attendance.txt", "r");

    if (fp2 == NULL) {
        fprintf(stderr, "\n\n\t\t\033[1;31mCan't open attendance file..\033[0m\n");
        return;
    }

    system("cls");
    printf(" --------------------------------------------------------------\n");
    printf(" |||||||||||||||||||\033[1;33mATTENDANCE RECORD\033[0m|||||||||||||||||||||||||\n");
    printf(" --------------------------------------------------------------\n");

    char line[1024];
    int found = 0;
    int timeInCount = 0;
    int timeOutCount = 0;
    char timeInArray[50][1024];
    char timeOutArray[50][1024];

    while (fgets(line, sizeof(line), fp2)) 
	{ 
        if (strstr(line, "Time In")) {
            strcpy(timeInArray[timeInCount++], line);
        }
        else if (strstr(line, "Time Out")) {
            strcpy(timeOutArray[timeOutCount++], line);
        }
        found = 1;
        
    }
		
    if (!found) {
        printf("\n\n\033[1;31mNo attendance record yet.\033[0m\n");
    } else {
        
        for (int i = 0; i < timeInCount; i++) {
            printf("\n\n\t%s", timeInArray[i]);
        }

        printf("\n");
        for (int i = 0; i < 62; i++) {
            printf("-");
        }
        
		printf("\n");
        for (int i = 0; i < timeOutCount; i++) {
            printf("\n\n\t%s", timeOutArray[i]);
        }
    }

    fclose(fp2);
    printf(" \n\n --------------------------------------------------------------\n");
	printf(" ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	printf(" --------------------------------------------------------------\n");
    printf("\n\n\t\tPress any key to exit...");
    getch();
}

