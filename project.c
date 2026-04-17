#include <stdio.h>
#include <string.h>

struct User {
    char username[50];
    char password[50];
};

struct Item {
    char name[50];
    int quantity;
};

int main() {
    int choice;

    struct User newUser, existingUser;

    // Inventory items
    struct Item inventory[3] = {
        {"Laptop", 10},
        {"Mouse", 25},
        {"Keyboard", 15}
    };

    FILE *fp;

    while (1) {
        printf("\n===== MENU =====\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("\n--- REGISTER ---\n");

                printf("Enter username: ");
                scanf("%s", newUser.username);

                printf("Enter password: ");
                scanf("%s", newUser.password);

                // Check if username already exists
                int exists = 0;

                fp = fopen("users.dat", "rb");

                if (fp != NULL) {
                    while (fread(&existingUser, sizeof(struct User), 1, fp)) {
                        if (strcmp(existingUser.username, newUser.username) == 0) {
                            exists = 1;
                            break;
                        }
                    }
                    fclose(fp);
                }

                if (exists) {
                    printf("Username already exists! Try another one.\n");
                } else {
                    fp = fopen("users.dat", "ab");

                    if (fp == NULL) {
                        printf("Error opening file!\n");
                    } else {
                        fwrite(&newUser, sizeof(struct User), 1, fp);
                        fclose(fp);
                        printf("Registration successful!\n");
                    }
                }
                break;

            case 2: {
                char username[50], password[50];
                int found = 0;

                printf("\n--- LOGIN ---\n");

                printf("Enter username: ");
                scanf("%s", username);

                printf("Enter password: ");
                scanf("%s", password);

                fp = fopen("users.dat", "rb");

                if (fp == NULL) {
                    printf("No registered users found!\n");
                    break;
                }

                while (fread(&existingUser, sizeof(struct User), 1, fp)) {
                    if (strcmp(existingUser.username, username) == 0 &&
                        strcmp(existingUser.password, password) == 0) {
                        found = 1;
                        break;
                    }
                }

                fclose(fp);

                if (found) {
                    printf("\nLogin Successful!\n");
                    printf("\n===== INVENTORY =====\n");
                    printf("%-15s %-10s\n", "Item Name", "Quantity");
                    printf("---------------------------\n");

                    for (int i = 0; i < 3; i++) {
                        printf("%-15s %-10d\n", inventory[i].name, inventory[i].quantity);
                    }
                } else {
                    printf("Invalid username or password!\n");
                }
                break;
            }

            case 3:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
}
