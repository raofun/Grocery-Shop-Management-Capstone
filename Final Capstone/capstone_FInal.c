#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include <sys/stat.h>



typedef struct {
    char fullName[100];
    char email[100];
    char phoneNumber[15];
    char password[50];
} User;

User mainUser;


void wel_come();
int optional();
void registerUser();
int loginUser();
void menu();



int main() {
wel_come();
optional();
registerUser();
loginUser();
return 0;
}



void wel_come() {
    int i;
	time_t t;
	time(&t);
	printf("\n");
	printf("WELCOME TO\n");
	for(i=0; i<10; i++)
    {
        printf(".");
        Sleep(1);
    }
    printf("\n");
	printf("Bhotvoti Groceries\n");
	for(i=0; i<18; i++)
    {
        printf(".");
        Sleep(1);
    }
	printf("\n");
	printf("HERE YOU FIND BEST PRODUCT IN REASONABLE PRICE!!\n");
	for(i=0; i<48; i++)
    {
        printf(".");
        Sleep(1);
    }
		printf("\n");
		printf("\n");

		printf("Current Time : %s",ctime(&t));
		for(i=0; i<40; i++)
    {
        printf(".");
        Sleep(1);
    }
		printf("\n");
		printf("\n");
        

}

int optional() {
     int choice;
    printf("****** Welcome to Bhotvoti Groceries System ******\n");
    while (1) {
        printf("\nChoose an option:");
        printf("\n[1] Register");
        printf("\n[2] Login");
        printf("\n[3] Exit\n");
        printf("\nYour choice: ");
        scanf("%d", &choice);
        system("cls");
        
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                printf("Thank you for using our system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
                break;
        }
    }
    return 0;
}

void toLowerCase(char *lowChar) {
    for (int i = 0; lowChar[i]; i++) {
        lowChar[i] = tolower(lowChar[i]);
    }
}

void takeEmail(char *email){
    
	char filename[120];
	struct stat buffer;

	printf("\nEmail Address: ");
    scanf("%s", email);
	toLowerCase(email);
	
	sprintf(filename, "%s.txt", email); 
	int user_found = stat(filename, &buffer) == 0;

	while(!isValidEmail(email)) {
		printf("\nInvalid email address. Please enter a valid email address.\n");
		printf("\nEmail Address: ");
		scanf("%s", email);
		toLowerCase(email);
	}

	while(user_found) {
		printf("\nUser with email %s already exists.\n", email);
		printf("\nEmail Address: ");
		scanf("%s", email);
		toLowerCase(email);

		sprintf(filename, "%s.txt", email); 
		user_found = stat(filename, &buffer) == 0;
	}
}

int isValidEmail(char *email){

    int i = 0, at = 0, dot = 0, atIndx = -1, dotIndx = -1;
    while(email[i] != '\0'){
        if(email[i] == '@') {at++; atIndx = i;}
        if(email[i] == '.') {dot++; dotIndx = i;}
        i++;
    }

    if(at == 1 && dot>=1&&dot<=2 && dotIndx > atIndx && dotIndx<i-1 ){
        return 1;
    }
    else{
        return 0;
    }
}

void takePhoneNumber(char *phoneNumber) {

    printf("Enter Phone Number: ");
    scanf("%s", phoneNumber); 
    while (!isAllDigits(phoneNumber)) { 
        printf("Invalid input. Please enter a valid phone number with digits only: ");
        scanf("%s", phoneNumber);
    }
}

int isAllDigits(char *number) {

    for (int i = 0; number[i] != '\0'; i++) {
        if (!isdigit(number[i])) {
            return 0; 
        }
    }
    return 1; 
}

void takePassword(char *password) {

	while(1){

    	int i = 0;
    	char ch;
		printf("\nThe password must contain at least 8 characters, including uppercase, lowercase, digit, and special character.\n");
		printf("Enter password: ");
		while(1) {
			ch = getch(); 

			if(ch == '\r' || ch == '\n') { 
				break;
			} 
			else if (ch == '\b') { 
				if (i > 0) {
					i--;
					printf("\b \b"); 
				}
			} 
			else if (i < 50 && isprint(ch)) { 
				password[i++] = ch;
				printf("*"); 
			}
		}

		password[i] = '\0'; 

		if(isStrongPassword(password)) {
			break;
		} 
		else {
			printf("\nPassword is not strong enough.\n");
		}
	}
}

int isStrongPassword(char *password) {

    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    if(strlen(password) < 8) {
        return 0; 
    }

    for(int i = 0; password[i] != '\0'; i++) {
        
		if(isupper(password[i])) hasUpper = 1;
        if(islower(password[i])) hasLower = 1;
        if(isdigit(password[i])) hasDigit = 1;
        if(ispunct(password[i])) hasSpecial = 1;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial; 
}

void inputPasswordforLogin(char *password) {
	char ch;
	int i = 0;
	printf("Enter password: ");
	while(1) {
		ch = getch(); 

		if(ch == '\r' || ch == '\n') { 
			break;
		} 
		else if (ch == '\b') { 
			if (i > 0) {
				i--;
				printf("\b \b"); 
			}
		} 
		else if (i < 255 && isprint(ch)) { 
			password[i++] = ch;
			printf("*"); 
		}
	}

	password[i] = '\0'; 
}



void registerUser() {
    User user;
    char filename[120];

    printf("\n**********  REGISTER  **********\n");
    printf("\nFull Name: ");
    scanf(" %[^\n]s", user.fullName);

    takeEmail(user.email);

    takePhoneNumber(user.phoneNumber);

	takePassword(user.password);

	sprintf(filename, "%s.txt", user.email); 
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		printf("\nError opening file for writing.\n");
		return;
	}
	fprintf(file, "%s\n%s\n%s\n%s\n", user.fullName, user.email, user.phoneNumber, user.password);
	fclose(file);
	printf("\nRegistration Successful!\n");
	
}

int loginUser() {
    char email[100];
    char password[50];
    char filename[120];
	int attmpt=0;

    printf("\n**********  LOG IN  **********\n");
    printf("\nEmail Address: ");
    scanf("%s", email);
	toLowerCase(email);

    

    sprintf(filename, "%s.txt", email); 
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nError opening file for reading or user not found.\n");
        return 0;
    }

    User user;
    fscanf(file, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n", user.fullName, user.email, user.phoneNumber, user.password);
	while(1){

		inputPasswordforLogin(password);

		if (strcmp(user.password, password) == 0) {
			printf("\nLogin Successful!\n");
			fclose(file);
			mainUser = user;
			menu();
			return 1;
		} 
		else {
			
			printf("\nInvalid Password!\n");
			attmpt++;
			if(attmpt==3){
				printf("\nYou have entered wrong password 3 times. Please try again later.\n");
				fclose(file);
				return 0;
			}
		}
	}
}

void menu()
{
    int i;
	int choice;
    system("cls");
    printf("\nUser: %s\nEmail: %s\nPhone: %s\n", mainUser.fullName, mainUser.email, mainUser.phoneNumber);
    printf("\n\n");
	printf("****** Welcome to Bhotvoti Groceries System ******\n");
	printf("                                                                                          ");
	printf("                                                                                          ");
	printf("\n\t\tEnter [1] ....|_____|....\n");
	printf("\n\t\tEnter [2] ......   ....\n");
	printf("\n\t\tEnter [3] ......   .....\n");
	printf("\n\t\tEnter [4] ......   ......\n");
	printf("\n\t\tEnter [5] To Exit!\n");

	printf("\n\n\t\tEnter your choice[1-20]:");
	for(i=0; i<4; i++)
    {
        printf("");
        Sleep(100);
    }
	scanf("%i", &choice);
    system("cls");

    switch(choice)
	{
        case 1:
        printf("Next Pages under development\n");
        exit(0);
        break;

        default:
        printf("Invalid Choise! System Exit\n");
        getch();
    }
}