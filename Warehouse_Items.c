#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_WAREHOUSES 4
#define EXP_DATE "28-01-2025"

typedef struct Item {
    char name[20];
    char expirationDate[10]; // DD-MM-YYYY
    struct Warehouse* warehouseID;
    struct Item* next;
} Item;

typedef struct Warehouse {
    char name[10];
    int ID;
    struct Warehouse* next;
    Item* items;
} Warehouse;

Warehouse* createWarehouse(char name[], int ID) {
    Warehouse* newWarehouse = (Warehouse*)malloc(sizeof(Warehouse));
    strcpy(newWarehouse->name, name);
    newWarehouse->ID = ID;
    newWarehouse->next = NULL;
    newWarehouse->items = NULL;
    return newWarehouse;
}

Item* createItem(char name[], char expirationDate[], Warehouse* warehouseID) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    strcpy(newItem->name, name);
    strcpy(newItem->expirationDate, expirationDate);
    newItem->warehouseID = warehouseID;
    newItem->next = NULL;
    return newItem;
}

void addWarehouse(Warehouse* warehouses[], Warehouse* warehouse) {
    for (int i = 0; i < MAX_WAREHOUSES; i++) {
        if (warehouses[i] == NULL) {
            warehouses[i] = warehouse;
            return;
        }
    }
}

void addItem(Warehouse* warehouse, Item* item) {
    if (warehouse->items == NULL) {
        warehouse->items = item;
    } else {
        Item* temp = warehouse->items;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = item;
    }
}

void removeExpiredMeatItems(Warehouse* warehouse) {
    if (warehouse == NULL) return;

    Item* temp = warehouse->items;
    Item* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->expirationDate, EXP_DATE) <= 0 && strcmp(temp->name, "Meat") == 0) {
            if (prev == NULL) {
                warehouse->items = temp->next;
                free(temp);
                temp = warehouse->items;
            } else {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

void printWarehouses(Warehouse* warehouses[]) {
    for (int i = 0; i < MAX_WAREHOUSES; i++) {
        Warehouse* temp = warehouses[i];
        if (temp == NULL) continue;
        printf("Warehouse %s with ID %d\n", temp->name, temp->ID);
        Item* tempItem = temp->items;
        while (tempItem != NULL) {
            printf("  Item: %s, Expiration Date: %s\n", tempItem->name, tempItem->expirationDate);
            tempItem = tempItem->next;
        }
    }
    printf("\n");
}

int main() {
    Warehouse* warehouses[MAX_WAREHOUSES] = {NULL};

    Warehouse* warehouse1 = createWarehouse("WH1", 100);
    Warehouse* warehouse2 = createWarehouse("WH2", 200);
    Warehouse* warehouse3 = createWarehouse("WH3", 300);
    Warehouse* warehouse4 = createWarehouse("WH4", 400);

    addWarehouse(warehouses, warehouse1);
    addWarehouse(warehouses, warehouse2);
    addWarehouse(warehouses, warehouse3);
    addWarehouse(warehouses, warehouse4);

    addItem(warehouse1, createItem("Meat", "28-03-2025", warehouse1));
    addItem(warehouse1, createItem("Vegetables", "10-01-2025", warehouse1));
    addItem(warehouse1, createItem("Fruits", "15-07-2025", warehouse1));
    addItem(warehouse2, createItem("Sweets", "01-09-2025", warehouse2));
    addItem(warehouse2, createItem("Meat", "01-01-2025", warehouse2));
    addItem(warehouse2, createItem("Seafruits", "13-07-2025", warehouse2));
    addItem(warehouse3, createItem("Pannifications", "30-11-2024", warehouse3));
    addItem(warehouse3, createItem("Oil", "19-03-2027", warehouse3));
    addItem(warehouse3, createItem("Milkproducts", "20-03-2025", warehouse3));

    printf("Before removing expired meat items:\n");
    printWarehouses(warehouses);

    for (int i = 0; i < MAX_WAREHOUSES; i++) {
        removeExpiredMeatItems(warehouses[i]);
    }

    printf("After removing expired meat items:\n");
    printWarehouses(warehouses);

    return 0;
}
