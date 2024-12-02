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
    char password[30];
} User;
User mainUser;

typedef struct{
 char name[100];
 char category[50];
 float buyPrice;
 float sellPrice;
 int stockQuantity;
 int quantitySold;
} Product;

Product products[100];
int productCount = 0;
float totalProfit = 0.0;
int previousProductCount = 0;
int totalSales = 0;
int cashPayments = 0;
int cardPayments = 0;
int mobilePayments = 0;
int totalSalesCount = 0;
int cashPaymentsCount = 0;
int cardPaymentsCount = 0;
int mobilePaymentsCount = 0;


void wel_come();
int optional();
void registerUser();
int loginUser();
void loadProductsFromFile();
void saveProductsToFile();
void menu();
void addProduct();
void searchProducts();
void displayProducts();
void sellProducts();
void updateStock();
void trackSales();
void deleteProduct();
void returnProducts();


int main(){
    loadProductsFromFile();
    loadTotal();
    wel_come();
    optional();
    registerUser();
    loginUser();
    menu();
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
		Sleep(2);
	}
	printf("\n");
	printf("Tushi Groceries\n");
	for(i=0; i<18; i++)
	{
		printf(".");
		Sleep(2);
	}
	printf("\n");
	printf("HERE YOU FIND BEST PRODUCT IN REASONABLE PRICE!!\n");
	for(i=0; i<48; i++)
	{
		printf(".");
		Sleep(2);
	}
		printf("\n");
		printf("\n");

		printf("Current Time : %s",ctime(&t));
		for(i=0; i<40; i++)
	{
		printf(".");
		Sleep(2);
	}
		printf("\n");
		printf("\n");
}

int optional() {
     int choice;
    printf("****** Welcome to Tushi Groceries System ******\n");
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
			else if (i < 255 && isprint(ch)) { 
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
    char password[30];
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

void menu(){

    void loadProductsFromFile();
    int choice;
    system("cls");
    main:
    printf("\nUser: %s\nEmail: %s\nPhone: %s\n", mainUser.fullName, mainUser.email, mainUser.phoneNumber);
    printf("\n\n");
    printf("****** Welcome to Tushi Groceries System ******\n");
    printf("\n\t\tEnter [1] To Add Product\n");
    printf("\n\t\tEnter [2] To Search Product\n");
    printf("\n\t\tEnter [3] To Display Product\n");
    printf("\n\t\tEnter [4] To Sell Product\n");
    printf("\n\t\tEnter [5] To Update Stock\n");
    printf("\n\t\tEnter [6] To Track Sales\n");
    printf("\n\t\tEnter [7] To Delete Product\n");
    printf("\n\t\tEnter [8] To Return Product\n");
    printf("\n\t\tEnter [9] To Exit\n");

    printf("\n\n\t\tEnter your choice [1-9]: ");
    scanf("%d", &choice);
    system("cls");

    switch (choice)
    {
    case 1:
        addProduct();
        break;

    case 2:
        searchProducts();
        break;

    case 3:
        displayProducts();
        break;

    case 4:
        sellProducts();
        break;

    case 5:
        updateStock();
        break;

    case 6:
        trackSales();
        break;

    case 7:
        deleteProduct();
        break;

    case 8:
        returnProducts();
        break;

    case 9:
        printf("System Exit\n");
        printf("\nGood Bye\n");
        printf("\nThank You!!\n");
        exit(0);

    default:
        printf("Invalid Choice! Please select a valid option (1-9).\n");
        getch();
        menu();
        break;
    }

}

void loadProductsFromFile(){

    FILE *file = fopen("products.txt", "r");
    if (file == NULL)
    {
		printf("No existing data found. Starting fresh.\n");
		return;
    }
    
	int i;
    char line[100];

    while (fgets(line, sizeof(line), file)) {
		i = atoi(line);
        if (productCount < 100) {

            fgets(line, sizeof(line), file);
            sscanf(line, "Name:%[^\n]", products[i-1].name);

            fgets(line, sizeof(line), file);
            sscanf(line, "Category:%[^\n]", products[i-1].category);

            fgets(line, sizeof(line), file);
            sscanf(line, "Buy Price:%f", &products[i-1].buyPrice);

            fgets(line, sizeof(line), file);
            sscanf(line, "Sell prize:%f", &products[i-1].sellPrice);

            fgets(line, sizeof(line), file);
            sscanf(line, "Stock quantity:%d", &products[i-1].stockQuantity);

            fgets(line, sizeof(line), file);
            sscanf(line, "Sold quantity:%d", &products[i-1].quantitySold);
        }

		else {
			printf("Max product limit reached. Ignoring rest of the data.\n");
			break;
		}
		productCount++;
    }

    previousProductCount = productCount;
    fclose(file);
   
}


void saveProductsToFile(){

    FILE *file = fopen("products.txt", "w");
    if (file == NULL){
        perror("Error saving data to file");
        return;
    }

    
    for(int i = 0; i < productCount; i++){
        fprintf(file, "%d\n", i+1);
        fprintf(file, "Name:%s\n",products[i].name);
        fprintf(file, "Category:%s\n",products[i].category);
        fprintf(file, "Buy Price:%.2f\n",products[i].buyPrice);
        fprintf(file, "Sell prize:%.2f\n",products[i].sellPrice);
        fprintf(file, "Stock quantity:%d\n",products[i].stockQuantity);
        fprintf(file, "Sold quantity:%d\n",products[i].quantitySold);
    }
    
    fclose(file);
}


void addProduct(){
    while(1){

        if (productCount >= 100){
            printf("Product inventory is full!\n");
            return;
        }
        Product newProduct;
        printf("Enter product name: ");
        getchar();
        fgets(newProduct.name, sizeof(newProduct.name), stdin);
        newProduct.name[strcspn(newProduct.name, "\n")] = 0;

        printf("Enter category: ");
        fgets(newProduct.category, sizeof(newProduct.category), stdin);
        newProduct.category[strcspn(newProduct.category, "\n")] = 0;

        printf("Enter buy price: ");
        scanf("%f", &newProduct.buyPrice);

        printf("Enter sell price: ");
        scanf("%f", &newProduct.sellPrice);

        printf("Enter stock quantity: ");
        scanf("%d", &newProduct.stockQuantity);
        newProduct.quantitySold = 0;
        products[productCount++] = newProduct;

        printf("Product added successfully!\n");
        saveProductsToFile();

        printf("\nPress Enter to return to the main menu, or any other key to add another product...\n");

           
            char choice = getch(); 
            system("cls"); 
            if (choice == '\r') { 
                system("cls"); 
                menu();        
                return;
            }
    }
}


void searchProducts(){
    
    char query[100];
    printf("Enter product name or category to search: ");
    getchar();
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = 0;
    printf("Search Results:\n");
    for (int i = 0; i < productCount; i++){
        if (strstr(products[i].name, query) || strstr(products[i].category, query)){
        printf("Name: %s\n", products[i].name);
        printf("Category: %s\n", products[i].category);
        printf("Sell Price: %.2f\n", products[i].sellPrice);
        printf("Stock: %d\n", products[i].stockQuantity);
        }
    }
    printf("\nPress any key to return to the main menu...");
    getch(); 
    menu();
}

s
void displayProducts() {
    
        system("cls"); 
        printf("Product Inventory:\n");
        for (int i = 0; i < productCount; i++) {
            printf("%d. Name: %s\n", i + 1, products[i].name);
            printf("Category: %s\n", products[i].category);
            printf("Buy Price: %.2f\n", products[i].buyPrice);
            printf("Sell Price: %.2f\n", products[i].sellPrice);
            printf("Stock: %d\n", products[i].stockQuantity);
        }
        printf("\nPress any key to go back to the main menu...");
        
        getch(); 
        system("cls"); 
        menu(); 
    

}


void saveTotal(){
    FILE *file = fopen("total.txt", "w");
    if (file == NULL){
        perror("Error saving data to file");
        return;
    }
    fprintf(file, "Total Profit: %.2f\n", totalProfit);
    fprintf(file, "Total Sales: %d\n", totalSales);

    fprintf(file, "Cash Payments: %d\n", cashPayments);
    fprintf(file, "cash Payments Count: %d\n", cashPaymentsCount);

    fprintf(file, "Card Payments: %d\n", cardPayments);
    fprintf(file, "Card Payments Count: %d\n", cardPaymentsCount);

    fprintf(file, "Mobile Payments: %d\n", mobilePayments);
    fprintf(file, "Mobile Payments Count: %d\n", mobilePaymentsCount);

    fclose(file);
}


void loadTotal(){
    FILE *file = fopen("total.txt", "r");
    if (file == NULL){
        perror("Error loading data from file");
        return;
    }
    char line[100];
    fgets(line, sizeof(line), file);
    sscanf(line, "Total Profit: %f", &totalProfit);
    fgets(line, sizeof(line), file);
    sscanf(line, "Total Sales: %d", &totalSales);

    fgets(line, sizeof(line), file);
    sscanf(line, "Cash Payments: %d", &cashPayments);
    fgets(line, sizeof(line), file);
    sscanf(line, "Cash Payments: %d", &cashPaymentsCount);

    fgets(line, sizeof(line), file);
    sscanf(line, "Card Payments: %d", &cardPayments);
    fgets(line, sizeof(line), file);
    sscanf(line, "Card Payments: %d", &cardPaymentsCount);

    fgets(line, sizeof(line), file);
    sscanf(line, "Mobile Payments: %d", &mobilePayments);
    fgets(line, sizeof(line), file);
    sscanf(line, "Mobile Payments: %d", &mobilePaymentsCount);

    fclose(file);
}


void sellProducts() {
    char name[100];
    char phoneNumber[15];
    int quantity;

    printf("Enter product name to sell: ");
    getchar(); 
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; 

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, name) == 0) {
            printf("Enter quantity to sell: ");
            scanf("%d", &quantity);
            
            if (quantity > products[i].stockQuantity) {
                printf("Not enough stock available!\n");
                printf("Press any key to go back to the menu...");
                getchar(); 
                getch(); 
                menu();
                return;
            }

            getchar(); 
            printf("Enter customer phone number: ");
            fgets(phoneNumber, sizeof(phoneNumber), stdin);
            phoneNumber[strcspn(phoneNumber, "\n")] = 0; 

            float totalPrice = quantity * products[i].sellPrice;
            totalProfit += totalPrice - (quantity * products[i].buyPrice);

            
            printf("Select payment method:\n");
            printf("1. Cash\n");
            printf("2. Card\n");
            printf("3. Mobile Payment\n");
            printf("Enter your choice: ");
            int paymentChoice;
            char paymentMethod[20];
            scanf("%d", &paymentChoice);

            
            switch (paymentChoice) {
                case 1:
                    strcpy(paymentMethod, "Cash");
                    cashPayments += totalPrice;
                    cashPaymentsCount++;
                    break;
                case 2:
                    strcpy(paymentMethod, "Card");
                    cardPayments += totalPrice;
                    cardPaymentsCount++;
                    break;
                case 3:
                    strcpy(paymentMethod, "Mobile Payment");
                    mobilePayments += totalPrice;
                    mobilePaymentsCount++;
                    break;
                default:
                    printf("Invalid payment method! Sale canceled.\n");
                    printf("Press any key to go back to the menu...");
                    getchar(); 
                    getch(); 
                    menu();
                    return;
            }
 
            products[i].stockQuantity -= quantity;
            
            products[i].quantitySold += quantity;
            
            totalSales++;

            printf("\n------- RECEIPT -------\n");
            printf("Product Name     : %s\n", products[i].name);
            printf("Quantity Sold    : %d\n", quantity);
            printf("Price per Unit   : %.2f\n", products[i].sellPrice);
            printf("Total Price      : %.2f\n", totalPrice);
            printf("Payment Method   : %s\n", paymentMethod);
            printf("Customer Contact : %s\n", phoneNumber);
            printf("------------------------\n");

            saveProductsToFile();
            saveTotal();

            printf("Press any key to return to the menu...");
            getchar(); 
            getch(); 
            system("cls"); 
            menu();
            return;
        }
    }

    printf("Product not found!\n");
    printf("Press any key to go back to the menu...");
    getch(); 
    menu();
}


void updateStock() {

    char name[100];
    int addedQuantity;

    printf("Enter product name to update: ");
    getchar(); 
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; 

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, name) == 0) {
            printf("Enter quantity to add: ");
            scanf("%d", &addedQuantity);

            products[i].stockQuantity += addedQuantity;

            printf("\nUpdated stock quantity for %s = %d\n", products[i].name, products[i].stockQuantity);

            saveProductsToFile();

            printf("\nPress any key to return to the menu...");
            getch(); 
            menu(); 
            return;
        }
    }

    printf("Product not found!\n");
    menu();
}

void trackSales() { 

    printf("\n**********  SALES REPORT  **********\n");

    printf("Total Profit: %.2f\n", totalProfit);

    printf("\n------ Sales Breakdown ------\n");
    for (int i = 0; i < productCount; i++) {
        if (products[i].quantitySold >= 0) {

            float profit = (float)(products[i].quantitySold) * (products[i].sellPrice - products[i].buyPrice);
            printf("Product: %-15s | Sold: %-5d | Profit: %.2f\n", products[i].name, products[i].quantitySold, profit);
        }
    }

    printf("\n------ Payment Method Breakdown ------\n");
    printf("Cash Payments: %d\n", cashPayments);
    printf("Cash Payments Count: %d\n", cashPaymentsCount);

    printf("\nCard Payments: %d\n", cardPayments);
    printf("Card Payments Count: %d\n", cardPaymentsCount);

    printf("\nMobile Payments: %d\n", mobilePayments);
    printf("Mobile Payments Count: %d\n", mobilePaymentsCount);

    printf("\nTotal Sales Count: %d\n", totalSales);
    printf("Total Sales Transactions: %d\n", cashPayments + cardPayments + mobilePayments);

    printf("\nPress any key to go back to the main menu...");
    getch(); 
    system("cls"); 
    menu(); 
}

void deleteProduct(){

    char name[100];
    printf("Enter product name to delete: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    for (int i = 0; i < productCount; i++){

        if (strcmp(products[i].name, name) == 0){
            for (int j = i; j < productCount - 1; j++){
                products[j] = products[j + 1];
            }
            productCount--;
            printf("Product '%s' deleted successfully!\n", name);
            saveProductsToFile();
            printf("\nPress any key to go back to the main menu...");
            getch(); 
            system("cls");
            menu(); 
            return;
        }
    }
    printf("Product not found!\n");
    printf("Press Enter to return to the menu...");
    getch(); 
    menu();
}

void returnProducts() {
    char name[100];
    int quantity;

    printf("Enter product name to return: ");
    getchar(); 
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; 

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, name) == 0) {
            printf("Enter quantity to return: ");
            scanf("%d", &quantity);

            if (quantity <= 0) {
                printf("Invalid quantity. Cannot return.\n");
                menu();
                return;
            }

            products[i].stockQuantity += quantity;
            printf("\nReturned %d units of '%s'.\nUpdated stock: %d\n", quantity, name, products[i].stockQuantity);
            saveProductsToFile(); 
            printf("\nPress any key to return to the menu...");
            getch();  
            menu();
            return;
        }
    }
    printf("Product '%s' not found!\n", name);
    
    printf("Press any key to return to the menu...");
    getch(); 
    menu();
}




