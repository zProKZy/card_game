#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ELEMENT_COUNT 3

int choice, money = 100, token = 1;
int card_count = 0;
int money_code, token_code, all_code = 0;
char money_choice[] = "money777";
char token_choice[] = "token888";
char all_choice[] = "all999";
char secret_ans[10];

void delay(int second);
void shop();
void shop_menu();

typedef struct {
    int level;
    int damage;
    int health;
    char element[6];
} card;

const char *elements[ELEMENT_COUNT] = {"Fire", "Wood", "Water"};

// Function to generate a random level based on specified probabilities
int generate_level() {
    int random_number = rand() % 100 + 1; // Generate a number between 1 and 100

    if (random_number <= 70) {
        return rand() % 3 + 1;  // Level 1-3 (70% chance)
    } else if (random_number <= 90) {
        return rand() % 3 + 4;  // Level 4-6 (20% chance)
    } else if (random_number <= 97) {
        return rand() % 2 + 7;  // Level 7-8 (7% chance)
    } else {
        return rand() % 2 + 9;  // Level 9-10 (3% chance)
    }
}

// Function to generate a random card
card generate_random_card() {
    card new_card;

    new_card.level = generate_level(); // Generate level with chances
    strcpy(new_card.element, elements[rand() % ELEMENT_COUNT]);  // Random element
    new_card.damage = (new_card.level * 10) + (rand() % 10);     // Damage based on level
    new_card.health = (new_card.level * 20) + (rand() % 20);     // Health based on level

    return new_card;
}

// Function to display card details
void display_card(const card *c) {
    printf("\n--- Card Details ---\n");
    printf("Element: %s\n", c->element);
    printf("Level: %d\n", c->level);
    printf("Damage: %d\n", c->damage);
    printf("Health: %d\n", c->health);
    printf("--------------------\n");
}

// Function to manage the inventory dynamically
void add_card_to_inventory(card **inventory, int *card_count, card new_card) {
    *inventory = realloc(*inventory, (*card_count + 1) * sizeof(card));  // Resize the inventory
    (*inventory)[*card_count] = new_card;  // Add new card to inventory
    (*card_count)++;
}

// Function to display all cards in the inventory
void display_inventory(card *inventory, int card_count) {
    if (card_count == 0) {
        printf("Inventory is empty.\n");
        return;
    }

    printf("\n--- Inventory ---\n");
    for (int i = 0; i < card_count; i++) {
        printf("Card %d\n  Element: %s \n  Level: %d \n  Damage: %d \n  Health: %d\n\n",
            i + 1,inventory[i].element, inventory[i].level, inventory[i].damage, inventory[i].health);
    }
}

int main() {
    srand(time(0));  // Seed the random number generator

    // start intro
    delay(1);
    printf("\n\n\t\t\t\t\t\t    zProKZy presents");
    delay(3);
    system("color 0b");
    printf("\n\n\t\t\t\t\t\t      -=Card Game=-\n");
    delay(2);
    printf("\n\t\t\t\t\t\t  Press any key to start\n");
    getch();

    system("color 0f");
    system("cls");

    int ch;
    card *inventory = NULL;  // Dynamic inventory to hold unlimited cards

    while (1) {
        printf("Money: %d\tToken: %d\n\n", money, token);
        printf("[1] Draw a card\n");
        printf("[2] Inventory\n");
        printf("[3] Shop\n");
        printf("[4] Battle\n");
        printf("[5] Quests\n");
        printf("[6] ???\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (token <= 0) {
                printf("\nYou don't have enough money to draw a card!\n");
                printf("Please go to the shop to earn more money.\n");
                getch();
                system("cls");
                continue;  // Stay in the menu without deducting money
            }

            system("cls");
            token -= 1;  // remove token when draw a card
            card new_card = generate_random_card(); // Generate a new random card
            add_card_to_inventory(&inventory, &card_count, new_card); // Add card to inventory
            display_card(&new_card);               // Display the new card
            getch();
            system("cls");
        }
        else if (choice == 2) {
            system("cls");
            display_inventory(inventory, card_count); // Display all cards in inventory
            getch();
            system("cls");
        }
        else if (choice == 3) {
            system("cls");
            shop_menu();
            getch(ch);
            system("cls");
        }
        else if (choice == 4) {
            system("cls");
            printf("Battle coming soon...\n");
        }
        else if (choice == 5) {
            system("cls");
            printf("Quests\n");
        }
        else if (choice == 6) {
            system("cls");
            printf("Hey! What are you doing?");
            delay(3);
            system("cls");
            printf("You gonna break something you know?");
            delay(3);
            system("cls");
            printf("So... What you want?\n");
            scanf("%s", &secret_ans);
            if (strcmp(money_choice, secret_ans) == 0) {
                if (money_code == 1) {
                    printf("You can't get this anymore!");
                    getch();
                    system("cls");
                    continue;
                }
                printf("You got 10000$ !");
                money_code += 1;
                money += 100000;
                getch();
                system("cls");
            }
            else if (strcmp(token_choice, secret_ans) == 0) {
                if (token_code == 1) {
                    printf("You can't get this anymore!");
                    getch();
                    system("cls");
                    continue;
                }
                printf("You got 100 Token!");
                token_code += 1;
                token += 100;
                getch();
                system("cls");
            }
            else if (strcmp(all_choice, secret_ans) == 0) {
                if (all_code == 1) {
                    printf("You can't get this anymore!");
                    getch();
                    system("cls");
                    continue;
                }
                printf("You got 10000$ and 100 Token!");
                all_code += 1;
                money += 10000;
                token += 100;
                getch();
                system("cls");
            }
        } else {
            system("cls");
            printf("\n\nLeft the game\n\n");
            break;
        }

    }

    // Free the allocated memory for inventory
    free(inventory);

    return 0;
}

// delay function
void delay(int second) {
    int milli_seconds = 1000 * second;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void shop_menu() {
    int shop_choice;
    printf("[1] 1 Token -------------------- 100$\n");
    printf("[2] 5 Token -------------------- 500$\n");
    delay(1);
    printf("Select your items: ");
    scanf("%d", &shop_choice);
    while(1) {
        if (shop_choice == 1 && money >= 100) {
            money -= 100;
            token += 1;
            printf("Purchase complete!\n");
            printf(" double any key\n");
            getch();
            break;
        }
        else if (shop_choice == 5 && money >= 500) {
            money -= 500;
            token += 5;
            printf("Purchase complete!\n");
            printf(" double any key\n");
            getch();
            break;
        } else {
            printf("Purchase cancel!");
            break;
        }
    }
}
