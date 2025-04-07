#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100 // Maximum inventory size
#define MAX_EMPLOYEES 50 // Maximum number of employees
#define HOURLY_RATE 20.0  // Base hourly wage
#define OVERTIME_MULTIPLIER 1.5  // Overtime is 1.5x regular pay


// Creating a structure of an item, and defining it with Item
typedef struct {
    char name[50];
    float price;
    int quantity;
} Item;

Item inventory[MAX_ITEMS]; // Creating array to hold items
int itemCount = 0; // Variable to hold amount of items in inventory

void addItem() { // Function to create item and add to inventory
    if (itemCount < MAX_ITEMS) { // Making sure inventory is not full
            printf("\033[H\033[J"); // Clears screen
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
        printf("\033[H\033[J");
        printf("Item(s) added successfully!\n");
    } else {
        printf("Inventory full! Cannot add any more items!\n");
    }
}

void displayInventory() {
if (itemCount == 0) {
    printf("\033[H\033[J");
    printf("Inventory is empty! Nothing to display!\n");
    return;
    }
    printf("\033[H\033[J");
    printf("\n------Inventory------\n");

    for (int i = 0; i < itemCount; i++) {
        printf("Item %d: \n", i + 1);
        printf("  Name: %s", inventory[i].name);
        printf("  Price: %.2f\n", inventory[i].price);
        printf("  Quantity: %d\n", inventory[i].quantity);
        printf("--------------------\n");
    }
}

void processSale() {
    if (itemCount == 0) {
        printf("\033[H\033[J");
        printf("Inventory is empty! No items available for sale.\n");
        return;
    }

    int itemIndex, quantity;
    float total = 0;

    printf("\033[H\033[J");
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
        printf("\033[H\033[J");
        printf("Enter employee name: ");
        getchar();
        fgets(employees[employeeCount].name, sizeof(employees[employeeCount].name), stdin);
        employees[employeeCount].name[strcspn(employees[employeeCount].name, "\n")] = '\0';

        printf("\nEnter employee ID: ");
        while (scanf("%d", &employees[employeeCount].employeeID) != 1 || employees[employeeCount].employeeID <= 0) {
            printf("Invalid ID! Please enter a positive number: ");
            while (getchar() != '\n');
        }
        employees[employeeCount].employeeID = employees[employeeCount].employeeID;


        employees[employeeCount].salary = 0;

        employeeCount++;
        printf("\033[H\033[J");
        printf("Employee added successfully!\n");
    } else {
        printf("\033[H\033[J");
        printf("Employee list full!\n");
    }
}

void calculatePayroll() {
    if (employeeCount == 0) {
        printf("\033[H\033[J");
        printf("No employees on payroll! Cannot calculate payroll with no employees to pay!\n");
        return;
    }

    printf("\033[H\033[J");
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



int input;

void displayMenu() {
    do {
    puts("\n");
    printf("--------Main Menu--------\n");
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
            printf("\033[H\033[J");
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
    break;
default:
    printf("Invalid input. Please try again\n");
    puts("\n");
    }
} while (input !=6);
};


int main() {

    displayMenu();

return 0;
}
