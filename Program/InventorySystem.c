#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100 // Maximum inventory size
#define MAX_EMPLOYEES 50 // Maximum number of employees
#define HOURLY_RATE 20.0  // Base hourly wage
#define OVERTIME_MULTIPLIER 1.5  // Overtime is 1.5x regular pay
#define credentials "credentials.txt"


/*
* Group: DJJJ
* Authors: Dawson Brown, Josh Leslie, Judah Csanyi, Jeremy Paruch
* Final Project
* LMD: April 8, 2025
*/

int choice;


void clearScreen(){
    printf("\033[H\033[J");
}
void pause(){
    printf("Press Enter to continue...\n");
    getchar();
}
// Creating a structure of an item, and defining it with Item
typedef struct {
    char name[50];
    float price;
    int quantity;
} Item;

Item inventory[MAX_ITEMS]; // Creating array to hold items
int itemCount = 0; // Variable to hold amount of items in inventory

void saveInventoryToFile() {
    FILE *file = fopen("inventory.txt", "w");  // Open file in write mode

    if (file == NULL) {
        printf("Error opening file for inventory save!\n");
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        fprintf(file, "%s|%.2f|%d\n", inventory[i].name, inventory[i].price, inventory[i].quantity);
    }

    fclose(file);  // Close the file
    printf("Inventory saved successfully!\n");
}


void addItem() { // Function to create item and add to inventory
    if (itemCount < MAX_ITEMS) { // Making sure inventory is not full
        clearScreen(); // Clears screen
        printf("Enter item name: ");
        getchar();  // Clear newline left in buffer
        fgets(inventory[itemCount].name, sizeof(inventory[itemCount].name), stdin); // Takes input from user allowing spaces be allowed

        printf("Enter item price: ");
        while (scanf("%f", &inventory[itemCount].price) != 1 || inventory[itemCount].price <= 0) { // Takes input but makes sure it is valid input
            printf("Invalid price! Please enter a positive number: ");
            while (getchar() != '\n'); // Clear buffer
        }


        printf("Enter item quantity: ");
        while (scanf("%d", &inventory[itemCount].quantity) != 1 || inventory[itemCount].quantity <= 0) {
            printf("Invalid quantity! Please enter a positive number: ");
            while (getchar() != '\n');
        }

        itemCount++;
        clearScreen();
        printf("Item(s) added successfully!\n");
    } else {
        printf("Inventory full! Cannot add any more items!\n");
    }
    saveInventoryToFile(); // Save inventory after item is added
}


void loadInventoryFromFile() {
    FILE *file = fopen("inventory.txt", "r");  // Open file in read mode

    if (file == NULL) {
        printf("No inventory file found! Starting fresh.\n");
        return;
    }

    itemCount = 0;
    while (fscanf(file, "%49[^|]|%f|%d\n", inventory[itemCount].name,
                  &inventory[itemCount].price, &inventory[itemCount].quantity) == 3) {
        itemCount++;
    }

    fclose(file);
    printf("Inventory loaded successfully!\n");
}

void displayInventory() {
    loadInventoryFromFile();
if (itemCount == 0) {
    clearScreen();
    printf("Inventory is empty! Nothing to display!\n");
    return;
    }
    clearScreen();
    printf("\n------Inventory------\n");

    for (int i = 0; i < itemCount; i++) {
        printf("Item %d: \n", i + 1);
        printf("  Name: %s", inventory[i].name);
        printf("  Price: %.2f\n", inventory[i].price);
        printf("  Quantity: %d\n", inventory[i].quantity);
        printf("--------------------\n");
    }
}

void saveTransaction(float total, int itemIndex, int quantity) {
    FILE *file = fopen("transactions.txt", "a");

    if (file == NULL) {
        printf("Error opening transactions file!\n");
        return;
    }

    fprintf(file, "Item: %s | Quantity: %d | Total Cost: $%.2f\n", inventory[itemIndex].name, quantity, total);
    fclose(file);
}

void processSale() {
    if (itemCount == 0) {
        clearScreen();
        printf("Inventory is empty! No items available for sale.\n");
        return;
    }

    int itemIndex, quantity;
    float total = 0;

    clearScreen();
    printf("\n------Inventory------\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d. %s - $%.2f (Stock: %d)\n", i + 1, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }

    while (1) { // Allow multiple items to be added to cart
        printf("\nEnter item number to purchase (0 to finish): ");
        if (scanf("%d", &itemIndex) != 1 || itemIndex < 0 || itemIndex > itemCount) {
            printf("Invalid input! Please enter a valid item number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (itemIndex == 0) break; // Finish transaction

        printf("Enter quantity: ");
        if (scanf("%d", &quantity) != 1 || quantity <= 0 || quantity > inventory[itemIndex - 1].quantity) {
            printf("Invalid quantity! Must be a positive number and within stock limit.\n");
            while (getchar() != '\n');
            continue;
        }

        total += inventory[itemIndex - 1].price * quantity;
        inventory[itemIndex - 1].quantity -= quantity;
        inventory[itemIndex - 1].quantity -= quantity;
        saveInventoryToFile();  // Save inventory changes after sale

        saveTransaction(total, itemIndex - 1, quantity);
    }

    // Apply Discount
    if (total > 100) {
        printf("\nDiscount Applied: 10%% OFF!\n");
        total *= 0.9;
    }

    printf("\nTotal Cost: $%.2f\n", total);
    printf("Transaction Complete!\n");
}

// Creating a structure of an employee, and defining it with Employee
typedef struct {
    char name[50];
    int employeeID;
    float hoursWorked;
    float overtime;
    float salary;
} Employee;

Employee employees[MAX_EMPLOYEES]; // Array for employees
int employeeCount = 0;

void addEmployee() {
    if(employeeCount < MAX_EMPLOYEES) {
        clearScreen();
        printf("Enter employee name: ");
        getchar();
        fgets(employees[employeeCount].name, sizeof(employees[employeeCount].name), stdin);
        employees[employeeCount].name[strcspn(employees[employeeCount].name, "\n")] = '\0';

        printf("\nEnter employee ID: ");
        while (scanf("%d", &employees[employeeCount].employeeID) != 1 || employees[employeeCount].employeeID <= 0) {
            printf("Invalid ID! Please enter a positive number: ");
            while (getchar() != '\n');
        }


        employees[employeeCount].salary = 0;

        employeeCount++;
        clearScreen();
        printf("Employee added successfully!\n");
    } else {
        clearScreen();
        printf("Employee list full!\n");
    }
}

void calculatePayroll() {
    if (employeeCount == 0) {
        clearScreen();
        printf("No employees on payroll! Cannot calculate payroll with no employees to pay!\n");
        return;
    }

    clearScreen();
    printf("\n------ Payroll Calculation ------\n");

    for (int i = 0; i < employeeCount; i++) {
        printf("\nEnter hours worked for %s (ID: %d): ", employees[i].name, employees[i].employeeID);
        while (scanf("%f", &employees[i].hoursWorked) != 1 || employees[i].hoursWorked < 0) {
            printf("Invalid input! Please enter a non-negative number: ");
            while (getchar() != '\n');
        }


        printf("Enter overtime hours for %s (ID: %d): ", employees[i].name, employees[i].employeeID);
        while (scanf("%f", &employees[i].overtime) != 1 || employees[i].overtime < 0) {
            printf("Invalid input! Please enter a non-negative number: ");
            while (getchar() != '\n');
        }


        float regularPay = employees[i].hoursWorked * HOURLY_RATE;
        float overtimePay = employees[i].overtime * (HOURLY_RATE * OVERTIME_MULTIPLIER);
        employees[i].salary = regularPay + overtimePay;

        printf("\nEmployee: %s (ID: %d)\n", employees[i].name, employees[i].employeeID);
        printf("  Hours Worked: %.2f | Overtime: %.2f\n", employees[i].hoursWorked, employees[i].overtime);
        printf("  Regular Pay: $%.2f | Overtime Pay: $%.2f\n", regularPay, overtimePay);
        printf("  Total Salary: $%.2f\n", employees[i].salary);
        printf("-----------------------------------\n");
    }
}


void loadTransactions() {
    FILE *file = fopen("transactions.txt", "r");  // Open file in read mode

    if (file == NULL) {
        printf("No transaction records found!\n");
        return;
    }

    char line[100];  // Buffer for each transaction entry
    printf("\n------ Transaction History ------\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);  // Print each transaction line from file
    }

    fclose(file);
}

int input;

void displayCustomerMenu() {
    clearScreen();
    do {
    puts("\n");
    printf("--------Customer Menu--------\n");
    puts("\n");
    printf("1. Display Inventory\n");
    printf("2. Process Sale\n");
    printf("3. View transaction history\n");
    printf("4. Exit\n");
    puts("\n");
    printf("Enter your choice: \n");
        if (scanf("%d", &input) != 1) {
            clearScreen();
            printf("\nInvalid input! Please enter a number between 1 and 3.\n");
            while (getchar() != '\n');  // Clear input buffer
            continue;  // Restart loop
        }

    puts("\n");

    switch (input) {
case 1:
    clearScreen();
    displayInventory();
    puts("\n");
    break;
case 2:
    clearScreen();
    processSale();
    puts("\n");
    break;
case 3:
    clearScreen();
    printf("Loading transaction history...\n");
    puts("\n");
    loadTransactions();
    break;
case 4:
    printf("Saving and exiting...\n");
    puts("\n");
    clearScreen();
    break;
default:
    clearScreen();
    printf("Invalid input. Please try again\n");
    puts("\n");
    }
} while (input !=4);
};


void displayEmployeeMenu() {
    clearScreen();
    do {
    puts("\n");
    printf("--------Employee Main Menu--------\n");
    puts("\n");
    printf("1. Add Item\n");
    printf("2. Display Inventory\n");
    printf("3. Process Sale\n");
    printf("4. Add Employee\n");
    printf("5. Calculate Payroll\n");
    printf("6. Save and Exit\n");
    puts("\n");
    printf("Enter your choice: \n");
        if (scanf("%d", &input) != 1) {
            clearScreen();
            printf("\nInvalid input! Please enter a number between 1 and 6.\n");
            while (getchar() != '\n');  // Clear input buffer
            continue;  // Restart loop
        }

    puts("\n");

    switch (input) {
case 1:
    addItem();
    puts("\n");
    break;
case 2:
    displayInventory();
    puts("\n");
    break;
case 3:
    processSale();
    puts("\n");
    break;
case 4:
    addEmployee();
    puts("\n");
    break;
case 5:
    calculatePayroll();
    puts("\n");
    break;
case 6:
    printf("Saving and exiting...\n");
    puts("\n");
    clearScreen();
    break;
default:
    printf("Invalid input. Please try again\n");
    puts("\n");
    }
} while (input !=6);
};

int userExists(const char *username) {//takes in the old username
    char fileUsername[50], filePassword[50], fileRole[50];//empty strings to hold data from file
    FILE *file = fopen(credentials, "r");//reads the file
    if (file == NULL) return 0;//empty file means there will be no duplicate username

    while (fscanf(file, "%s %s %s", fileUsername, filePassword, fileRole) != EOF) {//scans the file taking in 3 string from each line username, passord and role does this until the end of file (EOF)
        if (strcmp(username, fileUsername) == 0) {//with each line comparesthe username with the username in the file
            fclose(file);
            return 1;//if usernames are the same returns 1
        }
    }

    fclose(file);
    return 0;//returns 0 if the username did not match
}

void registerUser() {
    char username[50], password[50], role[50];

    clearScreen();
    printf("Register a new user\n");
    printf("Enter username: ");
    scanf("%s", username);//takes in user's username

    if (userExists(username)) {//checks the file if username is already there returns 0 if false and 1 if true
        clearScreen();
        printf("Username already exists!\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", password);//takes in user's password

    printf("Enter role (employee or customer): ");
    scanf("%s", role);//takes in the user's role in order to display the different menus
    if (strcmp(role, "employee") != 0 && strcmp(role, "customer") !=0){//if the role is not equal to employee or customer returns with error
        printf("Invalid role");
        return;
    }

    FILE *file = fopen(credentials, "a");//appends the credentials file
    if (file == NULL) {//if file didn't open properly
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s %s %s\n", username, password, role);//appends the username password and role as a single line like this [username password role] to the file
    fclose(file);
    clearScreen();
    printf("User registered successfully!\n");
}

void loginUser(){
    char username[50], password[50], fileUsername[50], filePassword[50], fileRole[50];
    clearScreen();
    printf("Enter username: ");
    scanf("%s",&username);
    printf("Enter password: ");
    scanf("%s", &password);

    int found = 0;
    FILE *file = fopen(credentials,"r");
    if (file == NULL) {
        printf("No registered users yet.\n");
        return;
    }

    while (fscanf(file, "%s %s %s", fileUsername, filePassword, fileRole) != EOF ){//scans each line of the file taking in 3 strings assigning them to fileUsername filePassword and fileRole
        if(strcmp(username, fileUsername)==0 && strcmp(password, filePassword)==0){
            found = 1;
            break;
        }
    }

    if(found){
        printf("Login successful\n");
        if(strcmp(fileRole, "customer")==0){
            //customerMenu();
            printf("display customer menu\n");
            displayCustomerMenu();
        } else if (strcmp(fileRole, "employee")==0){
            //employeeMenu();
            printf("display employee menu\n");
            displayEmployeeMenu();
        } else {
            printf("Error with role, -- returning to main menu");
            return;
        }
    }
}

   void mainMenu() {
   do {
        printf("\n--- Main Menu ---\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clearScreen();
                registerUser();
                break;
            case 2:
                clearScreen();
                loginUser();
                break;
            case 3:
                clearScreen();
                printf("Have a great day, thanks for using our program!\n");
                break;
            default:
                clearScreen();
                printf("Invalid option. Try again.\n");
        }
    } while (choice !=3);
}

int main() {
    mainMenu();
    saveInventoryToFile();

return 0;
}
