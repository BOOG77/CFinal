#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100 // Maximum inventory size

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
        printf("Enter item name: ");
        getchar();  // Clear newline left in buffer
        fgets(inventory[itemCount].name, sizeof(inventory[itemCount].name), stdin); // Takes input from user allowing spaces be allowed

        printf("Enter item price: ");
        scanf("%f", &inventory[itemCount].price);

        printf("Enter item quantity: ");
        scanf("%d", &inventory[itemCount].quantity);

        itemCount++;
        printf("Item(s) added successfully!\n");
    } else {
        printf("Inventory full! Cannot add any more items!\n");
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
    scanf("%d", &input);
    puts("\n");

    switch (input) {
case 1:
    addItem();
    puts("\n");
    break;
case 2:
    printf("Displaying inventory\n");
    puts("\n");
    break;
case 3:
    printf("Processing sale\n");
    puts("\n");
    break;
case 4:
    printf("Adding employee\n");
    puts("\n");
    break;
case 5:
    printf("Calculating payroll\n");
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
