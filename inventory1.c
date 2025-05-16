#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Product;

Product inventory[MAX_PRODUCTS];
int productCount = 0;


void addProduct();
void displayProducts();
void updateProduct();
void deleteProduct();
void saveToFile();
void loadFromFile();

int main() {
    int choice;
    loadFromFile();

    while (1) {
        printf("\n Inventory Management System\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Update Product Quantity\n");
        printf("4. Delete Product\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: updateProduct(); break;
            case 4: deleteProduct(); break;
            case 5: saveToFile(); exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
}


void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Inventory full! Cannot add more products.\n");
        return;
    }

    Product p;
    printf("Enter Product ID: ");
    scanf("%d", &p.id);
    getchar();

    printf("Enter Product Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0; 

    printf("Enter Quantity: ");
    scanf("%d", &p.quantity);
    getchar();

    printf("Enter Price: ");
    scanf("%f", &p.price);
    getchar();

    inventory[productCount++] = p;
    printf("✅ Product Added Successfully!\n");
}


void displayProducts() {
    if (productCount == 0) {
        printf("No products in inventory!\n");
        return;
    }
    printf("\n📋 Product List:\n");
    printf("---------------------------------------\n");
    printf("ID   Name                Quantity  Price\n");
    printf("---------------------------------------\n");

    for (int i = 0; i < productCount; i++) {
        printf("%-4d %-20s %-8d $%.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}


void updateProduct() {
    int id, newQty;
    printf("Enter Product ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == id) {
            printf("Enter new Quantity: ");
            scanf("%d", &newQty);
            inventory[i].quantity = newQty;
            printf("✅ Product Updated Successfully!\n");
            return;
        }
    }
    printf("❌ Product Not Found!\n");
}


void deleteProduct() {
    int id, found = 0;
    printf("Enter Product ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == id) {
            found = 1;
            for (int j = i; j < productCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            productCount--;
            printf("✅ Product Deleted Successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("❌ Product Not Found!\n");
    }
}

// Save inventory to fil
void saveToFile() {
    FILE *file = fopen("inventory.txt", "w");
    if (!file) {
        printf("❌ Error saving inventory!\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%d %s %d %.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
    fclose(file);
    printf("💾 Inventory saved successfully!\n");
}

// Load inventory from file
void loadFromFile() {
    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        return;
    }

    while (fscanf(file, "%d %49s %d %f", &inventory[productCount].id, inventory[productCount].name, &inventory[productCount].quantity, &inventory[productCount].price) == 4) {
        productCount++;
    }
    fclose(file);
}
