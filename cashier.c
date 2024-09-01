#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h> //https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

#define BOLD "\x1B[1m"
#define MAX_CUSTOMERS 100
#define CUSTOMER_FILE "customers.txt"

// Structure to represent a product
struct Product {
    char code[20];
    char name[50];
    float price;
    int quantity;
};

struct customer {
    char username[50];
    char password[50];
    char phone_number[15];
    char payment_method[10];  // Either "GCash" or "PayMaya"
    float balance;  // Customer's account balance
};

//general data initialization
struct Product cart[99]; // Array to hold products added by the customer
struct customer customers[MAX_CUSTOMERS];

struct Product counter[99];

int customer_count = 0;
int total_items = 0;
float total_price = 0.0;
char filename[256];


//data for the products
struct Product beverages[] = {
        {"BEV000", "C2 Solo", 13},        //99 75 50 25 00
        {"BEV001", "Chuckie 110ml", 15.25},
        {"BEV002", "Chuckie 180ml", 22.50},
        {"BEV003", "Coke Sakto", 10.75},
        {"BEV004", "Coke 12 Oz.", 14.75},
        {"BEV005", "Coke 8 Oz.", 12},
        {"BEV006", "Coke Mismo", 18},
        {"BEV007", "Coke Kasalo", 27.50},
        {"BEV008", "Sprite 1 Liter", 35.75},
        {"BEV009", "Gatorade", 32.99},
        {"BEV010", "Minute Maid", 10.00},
        {"BEV011", "Nutri Boost", 14.25},
        {"BEV012", "Sparkle", 10.50},
        {"BEV013", "Zesto", 11.50},
        {"BEV014", "Natures Spring 1Liter", 27.75},
        {"BEV015", "Wilkins 1000 ml", 29.99},
        {"BEV016", "Wilkins 237ml", 20.25},
        {"BEV017", "Wilkins 500ml", 20.50},
};

struct Product snacks[] = {
        {"SNK000", "Bengbeng", 8.00},
        {"SNK001", "Biscuits except", 6.25},
        {"SNK002", "Cheese it", 7.50},
        {"SNK003", "Chippy", 8.75},
        {"SNK004", "Choco knots", 8.99},
        {"SNK005", "Cloud 9", 9.00},
        {"SNK006", "Crackling", 7.25},
        {"SNK007", "Fudgee Bars", 7.50},
        {"SNK008", "Funcky", 7.75},
        {"SNK009", "Mang Juan", 8.99},
        {"SNK010", "Martys", 7.00},
        {"SNK011", "Nagaraya", 20.25},
        {"SNK012", "Nova", 14.50},
        {"SNK013", "Oish", 7.75},
        {"SNK014", "Onion rings", 7.99},
        {"SNK015", "Peewee", 7.00},
        {"SNK016", "Piatos", 14.25},
        {"SNK017", "Pillows big", 8.50},
        {"SNK018", "Pillows small", 6.75},
        {"SNK019", "Pretzels", 8.99},
        {"SNK020", "Quakes", 7.00},
        {"SNK021", "Ri-Chee", 7.25},
        {"SNK022", "Rinbee", 7.50},
        {"SNK023", "Skyflakes", 7.75}
};

//canned goods page 1
struct Product canned_fish[] = {
        {"CAF000", "555 Sardines", 20.00},
        {"CAF001", "Atami", 18.25},
        {"CAF002", "Magasardines red", 18.50},
        {"CAF003", "Megasardines green", 21.75},
        {"CAF004", "Unipak", 20.99},
        {"CAF005", "Young'stown red/green", 20.00},
        {"CAF006", "555 Tuna 150g", 35.25},
        {"CAF007", "555 Tuna Junior", 27.50},
        {"CAF008", "Century", 27.75},
        {"CAF009", "Wow Ulam", 24.99},
        {"CAF010", "Young'stown", 32.00}
};

struct Product canned_meat[] = {
        {"CAM000", "Argentina 100g", 25.00},
        {"CAM001", "Argentina 150g", 36.25},
        {"CAM002", "Goldcup", 21.50},
        {"CAM003", "Holiday Corned beef 100g", 25.75},
        {"CAM004", "Holiday Corned beef 150g", 37.99},
        {"CAM005", "Argentina Beef Loaf 100g", 16.00},
        {"CAM006", "Argentina beef Loaf 150g", 21.25},
        {"CAM007", "Fiesta Beef Loaf big", 35.75},
        {"CAM008", "Fiesta Beef Loat 150g", 23.99},
        {"CAM009", "Holiday Beef Loaf 100g", 16.00},
        {"CAM010", "Holiday Beef Loaf 150g", 21.25},
        {"CAM011", "Lami Beef Loaf 100g", 18.50},
        {"CAM012", "Lami Beef Loaf 150g", 23.75},
        {"CAM013", "Lami Beef Loaf big", 35.99}
};

//CONDIMENTS//
struct Product condiments[12]= {
        {"CON000", "Datu Puti Soy Sauce 100ml", 6.00},
        {"CON001", "Datu Puti Soy Sauce 200ml", 10.25},
        {"CON002", "Datu Puti Vinegar 100ml", 6.50},
        {"CON003", "Datu Puti Vinegar 200ml", 10.75},
        {"CON004", "Mang Tomas 357ml", 33.99},
        {"CON005", "Mang Tomas 357ml Hot & Spicy", 35.00},
        {"CON006", "Papa Catsup 200ml", 12.25},
        {"CON007", "Papa Catsup 357ml", 23.50},
        {"CON008", "Silver Swan Soy Sauce 200ml", 10.75},
        {"CON009", "Silver Swan Vinegar 200ml", 10.99},
        {"CON010", "UFC Catsup 357ml", 25.00},
        {"CON011", "UFC Tomato Sauce 200ml", 23.25}
};

struct Product dairy[]= {
        {"DAR000", "Alaska Evap", 15},
        {"DAR001", "Alaska Evap Big", 24.25},
        {"DAR002", "Alpine Evap", 34.50},
        {"DAR003", "Buttercup Butter", 60.75},
        {"DAR004", "Cowbell", 35.99},
        {"DAR005", "Dairy Creme Butter", 65},
        {"DAR006", "Daisy", 35.25},
        {"DAR007", "Doreen", 35.50},
        {"DAR008", "Eden Cheddar Cheese", 37.75},
        {"DAR009", "Liberty Big", 48.99},
        {"DAR010", "Liberty Small", 32.},
        {"DAR011", "Nestle Cream", 65.25},
};

struct Product frozen_foods [10] = {
        {"FRZ000", "Chicken 1kilo", 160.00},
        {"FRZ001", "Chicken Nuggets 50pcs", 170.25},
        {"FRZ002", "Chorizo 500g", 150.50},
        {"FRZ003", "Hotdog 500g", 180.75},
        {"FRZ004", "Logganisa 500g", 210.99},
        {"FRZ005", "Lumpia Chicken 24pcs", 155.00},
        {"FRZ006", "Lumpia Pork 24pcs", 160.25},
        {"FRZ007", "Meatballs 50pcs", 165.75},
        {"FRZ008", "Pork 1kilo", 250.99},
        {"FRZ009", "Tocino 500g", 185.00},
};

//body care
struct Product body_care[] = {
        {"BOC000", "Dove Conditioner 150ml", 235.00},
        {"BOC001", "Heads and Shoulder 200ml", 300.25},
        {"BOC002", "Keratin 100ml", 180.50},
        {"BOC003", "Sunlilk 150ml", 250.75},
        {"BOC004", "Bioderm", 18.99},
        {"BOC005", "Camay", 18.00},
        {"BOC006", "Dove Soap", 27.25},
        {"BOC007", "Johnsons", 18.50},
        {"BOC008", "Olay", 18.75},
        {"BOC009", "Palmolive", 18.99},
        {"BOC010", "Safeguard 160grms", 20.00},
        {"BOC011", "Safeguard Box", 37.25}
};

//body care page 2
struct Product beauty_care[] = {
        {"BEC000", "Cotton", 6.00},
        {"BEC001", "Cotton buds", 13.25},
        {"BEC002", "Gatsby", 5.50},
        {"BEC003", "Gel", 3.75},
        {"BEC004", "Master", 5.99},
        {"BEC005", "Ponds Cream", 12.00},
        {"BEC006", "Ponds facial wash", 7.25},
        {"BEC007", "Rexona Deodorant", 9.50},
        {"BEC008", "Silka Deodorant sachet", 8.75},
        {"BEC309", "Silka Lotion Sachet", 8.99}
};

//DETERGENT / SOAP / FABCON //
struct Product detergents [] = {
        {"DET000", "Ariel Liquid Twin", 14.00},
        {"DET001", "Ariel Powder Twin", 14.25},
        {"DET002", "Ariel Single", 8.50},
        {"DET003", "Bonux Powder", 6.75},
        {"DET004", "Breeze", 12.99},
        {"DET005", "Calla", 6.00},
        {"DET006", "Champion Blue", 5.25},
        {"DET007", "Champion Pink", 6.50},
        {"DET008", "Pride", 5.75},
        {"DET009", "Surf Powder", 6.99},
        {"DET010", "Tide Single", 7.00},
        {"DET011", "Tide Twin", 12.25},
        {"DET012", "Wings Green", 5.50},
        {"DET013", "Wings Blue", 5.75},
        {"DET014", "Wings Pink", 6.99}
};

struct Product bar_soap[] = {
        {"BAR000", "Champion", 7.00},
        {"BAR001", "Champion Jumbo", 11.25},
        {"BAR002", "Perla", 15.50},
        {"BAR003", "Pride", 7.75},
        {"BAR004", "Bloom", 14.99},
        {"BAR005", "Speed", 7.00},
        {"BAR006", "Surf", 7.25},
        {"BAR007", "Surf Jumbo", 11.50},
        {"BAR008", "Tide", 7.75},
        {"BAR009", "Tide Jumbo", 12.99},
        {"BAR010", "Wings Jumbo", 10.00}
};

struct Product liquid_soaps[] = {
        {"FAB001", "Downy Classic", 6.00},
        {"FAB002", "Downy Sunflower", 8.25},
        {"FAB003", "Surf Sunflower", 6.50},
        {"DSH001", "Joy Sachet", 10.00},
        {"DSH002", "Smart", 35.25},
        {"ZON001", "Zonrox 100ml", 45.00},
        {"ZON002", "Zonrox 250ml", 55.25},
        {"ZON003", "Zonrox 500ml", 105.50}
};

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END**/

void press_any_key();

void user_type_choice();

void user_customer();
void customer_login();
void guest_customer_item_category();
void customer_register();

//attempts para sa login
void increment_attempts(int *attempt_count);
void ask_to_go_back();
void reset_attempts(int *attempt_count);


void registered_user_customer_item_category(char* username, float *balance, const char *registered_payment_method);
void registered_user_menu_customer_process (struct Product cart[], int *total_items, float *total_price, char* username, float *balance,  const char *registered_payment_method);
void choose_payment_mode(const char *registered_payment_method);
void generate_receipt(struct Product cart[], int total_items, float total_price, char* username, float *balance, const char *registered_payment_method);
void add_funds(char* username);
void guest_process();

void view_cart(struct Product cart[], int total_items, float total_price);
void display_cart(struct Product cart[], int total_items, float total_price);

//functions to show products
void browse_beverages(int *queue_number);
void browse_snacks(int *queue_number);
void browse_canned_goods(int *queue_number);
void browse_condiments(int *queue_number);
void browse_dairy(int *queue_number);
void browse_frozen_foods(int *queue_number);
void browse_self_care_products(int *queue_number);
void browse_detergent_soaps(int *queue_number);

//function at modifying items
void remove_from_cart(struct Product cart[], int *total_items, float *total_price, const char *code);
void ask_remove(struct Product cart[], int *total_items, float *total_price);
void ask_deduct(struct Product cart[], int *total_items, float *total_price);
void deduct_from_cart(struct Product cart[], int *total_items, float *total_price, const char *code);

//functions at processing the orders
void product_display(struct Product products[], int num_products);
void process_customer_order(struct Product products[], int num_products, struct Product cart[], int *total_items, float *total_price, int queue_number);
int find_product_code(char product_code[], struct Product products[], int num_products);
void display_product_details(struct Product product);
void add_to_cart(struct Product product, int quantity, struct Product cart[], int *total_items, float *total_price);
void reset_cart(struct Product cart[], int *total_items, float *total_price);

void guest_menu_customer_process (struct Product cart[], int *total_items, float *total_price);

//functions with file saving
void save_cart_to_csv(struct Product cart[], int total_items, float total_price);
void save_customer_to_file(struct customer customer);
void load_customers_from_file();
void save_queue_number(const char *filename, int queue_number);
int read_queue_number(const char *filename);

//functions for cashier
void user_cashier();
void cashier_login();
int validate_cashier_login(char username[], char password[]);
void cashier_process_choice();
void selecting_queue_list_to_process();
void display_counter(struct Product counter[], int total_items, float total_price);
float calculate_total_price(struct Product counter[], int total_items);
void read_csv_to_counter(const char *filename);

void reset_counter(struct Product counter[], int *total_items, float *total_price);
void cashier_pay_option();
void cashier_pay_process(struct Product counter[], int total_items, float *total_price);
void print_receipt(struct Product counter[], int total_items, float total_price, float payment);
void apply_discount(char promo_code[], float *total_price);
int validate_manager_login(char username[], char password[]);
void cashier_discount_process(float *total_price);
void save_receipt_to_csv(struct Product cart[], int total_items, float total_price, float payment);

//modify counter function
void ask_modify_counter(struct Product counter[], int *total_items, float *total_price, const char *filename);
void modify_counter(struct Product counter[], int *total_items, float *total_price, const char *code, int quantity);
int get_confirmation(const char *message);
int find_product_index(struct Product array[], int total_items, const char *code);


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

int main()
{
    //system("color F0");
    user_type_choice();

    return 0;
}

//asking if what user are you
void user_type_choice()
{
    char user_type;

    do {
        //system("cls");
        printf("||======================================================||\n");
        printf("||\t\t\t\t\t\t\t||\n");
        printf("||\t\tWelcome to Fourgramming\t\t\t||\n");
        printf("||\t\t\t\t\t\t\t||\n");
        printf("||\t\tPlease chooser a user type\t\t||\n");
        printf("||\t\t\t\t\t\t\t||\n");
        printf("||\t\t\t\t\t\t\t||\n");
        printf("||\t[1] Customer\t\t\t\t\t||\n");
        printf("||\t[2] Cashier\t\t\t\t\t||\n");
        printf("||\t[3] Manager\t\t\t\t\t||\n");
        printf("||\t[0] Exit\t\t\t\t\t||\n");
        printf("||\t\t\t\t\t\t\t||\n");
        printf("||\t\t\t\t\t\t\t||\n");
        printf("||======================================================||\n");
        printf("\n\nType here: ");
        scanf(" %c", &user_type);

        switch (user_type)
        {
            case '0':
                return;
            case '1':
                user_customer();
                break;
            case '2':
                user_cashier();
                break;
            case '3':
                //user_manager();
                break;
            default:
                printf("\nInvalid input. Try again...\n");
                press_any_key();
        }

    } while (user_type != '0');
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void user_customer()
{
    char choice;

    //system("cls");
    printf("||======================================================||\n");
    printf("||\t\t\t\t\t\t\t||\n");
    printf("||\t[1] Login as Existing Customer\t\t\t||\n");
    printf("||\t[2] Continue as Guest\t\t\t\t||\n");
    printf("||\t[3] Register\t\t\t\t\t||\n");
    printf("||\t[0] Go Back\t\t\t\t\t||\n");
    printf("||\t\t\t\t\t\t\t||\n");
    printf("||======================================================||\n");

    printf("\nEnter Here: ");
    scanf(" %c", &choice);

    switch (choice)
    {
        case '1':
            customer_login();
            break;
        case '2':
            guest_customer_item_category();
            break;
        case '3':
            customer_register();
            break;
        case '0':
            user_type_choice();
        default:
            printf("\nInvalid input. Try again...\n");
            press_any_key();
    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

//dito mag display pag customer at dito lalabas mga category ng products
void guest_customer_item_category()
{
    char choice, item_category;
    int queue_number = 1; // Initialize queue_number to 1

    while (1)
    {
        //system("cls");
        printf("\nNOTE: THE PROMO CODES WILL APPLY ONLY TO THE CUSTOMER WHO SPEND ABOVE 200 PESOS\n");

        printf("Welcome to our store\n");
        printf("What do you what to browse?\n\n");

        printf("[1] Beverages\n");
        printf("[2] Snacks\n");
        printf("[3] Canned Goods\n");
        printf("[4] Condiments\n");
        printf("[5] Dairy\n");
        printf("[6] Frozen Foods\n");
        printf("[7] Body Care & Beauty Care\n");
        printf("[8] Detergents and Soaps\n\n");

        printf("[0] Go back\n");

        printf("\nEnter Here: ");
        scanf(" %c", &item_category);

        switch (item_category)
        {
            case '0':
                user_customer();
                reset_cart(cart, &total_items, &total_price);
                break;
            case '1':
                browse_beverages(&queue_number);
                guest_process();
                break;
            case '2':
                browse_snacks(&queue_number);
                guest_process();
                break;
            case '3':
                browse_canned_goods(&queue_number);
                guest_process();
                break;
            case '4':
                browse_condiments(&queue_number);
                guest_process();
                break;
            case '5':
                browse_dairy(&queue_number);
                guest_process();
                break;
            case '6':
                browse_frozen_foods(&queue_number);
                guest_process();
                break;
            case '7':
                browse_self_care_products(&queue_number);
                guest_process();
                break;
            case '8':
                browse_detergent_soaps(&queue_number);
                guest_process();
                break;

            default:
                printf("\nInvalid input. Try again...");
                press_any_key();
        }

    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void guest_process()
{
    //system("cls");
    char choice;

    guest_menu_customer_process(cart, &total_items, &total_price);

// Display cart before finalization
    display_cart(cart, total_items, total_price);

    printf("\nPress [E] to checkout or press any key to shop again.: ");
    scanf(" %c", &choice);

    if (choice == 'E' || choice == 'e')
    {
        save_cart_to_csv(cart, total_items, total_price);

        reset_cart(cart, &total_items, &total_price);

        printf("Exiting...\n");
        user_type_choice();
        return;
    }
    else {
        guest_customer_item_category();
    }

}


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void ask_to_go_back() {
    char ch;

    while (1) {
        printf("Do you want to go back yes[Y] or no[N]: ");
        ch = getch(); // Reads a single character without echoing it
        printf("\n");

        if (ch == 'Y' || ch == 'y') {
            return; // Return 1 if the user chooses yes
        } else if (ch == 'N' || ch == 'n') {
            printf("You chose to continue.\n");
            continue; // Return 0 if the user chooses no
        } else {
            printf("Invalid input. Please enter Y or N.\n");
        }
    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void press_any_key()
{
    char ch;

    printf("Press any key to continue: ");
    ch = getch(); // Reads a single character without echoing it
    printf("\nYou pressed: %c\n", ch);
    //system("cls");
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void browse_beverages(int *queue_number)
{
    //system("cls");
    printf("Beverages:\n");
    product_display(beverages, 18);
    process_customer_order(beverages, 18, cart, &total_items, &total_price, (*queue_number)++);
}

void browse_snacks(int *queue_number)
{
    //system("cls");
    printf("Snacks:\n");
    product_display(snacks, 24);
    process_customer_order(snacks, 24, cart, &total_items, &total_price, (*queue_number)++);
}

void browse_canned_goods(int *queue_number)
{
    //system("cls");
    char choice;
    printf("Canned Goods:\n");
    printf("[1] Canned Fish\n");
    printf("[2] Canned Meat\n");
    printf("[0] Go back\n");
    printf("\nEnter Here: ");
    scanf(" %c", &choice);

    switch (choice) {
        case '0':
            return;
        case '1':
            //system("cls");
            product_display(canned_fish, 11);
            process_customer_order(canned_fish, 11, cart, &total_items, &total_price, (*queue_number)++);
            break;
        case '2':
            //system("cls");
            product_display(canned_meat, 14);
            process_customer_order(canned_meat, 14, cart, &total_items, &total_price, (*queue_number)++);
            break;
        default:
            printf("\nInvalid input. Try again...\n");
            press_any_key();
    }
}

void browse_condiments(int *queue_number)
{
    //system("cls");
    printf("Condiments:\n");
    product_display(condiments, 12);
    process_customer_order(condiments, 12, cart, &total_items, &total_price, (*queue_number)++);
}

void browse_dairy(int *queue_number)
{
    //system("cls");
    printf("Dairy:\n");
    product_display(dairy, 12);
    process_customer_order(dairy, 12, cart, &total_items, &total_price, (*queue_number)++);
}

void browse_frozen_foods(int *queue_number)
{
    //system("cls");
    printf("Frozen Foods:\n");
    product_display(frozen_foods, 10);
    process_customer_order(frozen_foods, 10, cart, &total_items, &total_price, (*queue_number)++);
}

void browse_self_care_products(int *queue_number)
{
    char choice;

    //system("cls");
    printf("Select what body care or beauty care product you want to browse.\n[1] Body Care\n[2] Beauty Care\n[0] Go back\n\nEnter here:");
    scanf(" %c", &choice);

    switch (choice) {
        case '0':
            return;
        case '1':
            //system("cls");
            product_display(body_care, 12);
            process_customer_order(body_care, 12, cart, &total_items, &total_price, (*queue_number)++);
            break;
        case '2':
            //system("cls");
            product_display(beauty_care, 10);
            process_customer_order(beauty_care, 10, cart, &total_items, &total_price, (*queue_number)++);
            break;
        default:
            printf("\nInvalid input. Try again...\n");
            press_any_key();
    }
}

void browse_detergent_soaps(int *queue_number)
{
    char choice;

    //system("cls");
    printf("Select what body care or beauty care product you want to browse.\n[1] Body Care\n[2] Beauty Care\n[0] Go back\n\nEnter here:");
    scanf(" %c", &choice);

    switch (choice) {
        case '0':
            return;
        case '1':
            //system("cls");
            product_display(detergents, 15);
            process_customer_order(detergents, 15, cart, &total_items, &total_price, (*queue_number)++);
            break;
        case '2':
            //system("cls");
            product_display(bar_soap, 11);
            process_customer_order(bar_soap, 11, cart, &total_items, &total_price, (*queue_number)++);
            break;
        case '3':
            //system("cls");
            product_display(liquid_soaps, 8);
            process_customer_order(liquid_soaps, 8, cart, &total_items, &total_price, (*queue_number)++);
            break;
        default:
            printf("\nInvalid input. Try again...\n");
            press_any_key();
    }
}


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void view_cart(struct Product cart[], int total_items, float total_price)
{
    //system("cls");

    if (total_items == 0) {
        printf("Your cart is empty.\n");
        return;
    }

    printf("\nCurrent Cart:\n");
    printf("CODE:\t\tPRODUCT NAME:\t\t\tQUANTITY:\tPRICE:\n");

    // Iterate through the items in the cart
    for (int i = 0; i < total_items; i++) {
        printf("%-8s\t%-24s\tx%d\t\t%.2f\n", cart[i].code, cart[i].name, cart[i].quantity, cart[i].price * cart[i].quantity);
    }

    printf("\nTotal Price: %.2f\n", total_price);


}


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

/* Display available products, ung parameters dito ay hiram kesa isusulat ulit
    sa loob ng function ung initialization, edi hihiramin nalng kahit void sya*/
void product_display(struct Product products[], int num_products)
{
    printf("\nAvailable Products:\n");
    for (int i = 0; i < num_products; i++) {
        printf("Code: %-6s   Name: %-24s Price: %5.2f\n", products[i].code, products[i].name, products[i].price);
    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

/* dito na ung proseso ng pag order kaya pag may babaguhin sa pag order,
    dito makikita tsaka may pointer dito sa parameter kahit void, dahil need mabago ung value kahit nasaang parte ng code*/

void process_customer_order(struct Product products[], int num_products, struct Product cart[], int *total_items, float *total_price, int queue_number)
{
    char choice;
    char product_code[20];
    int quantity, check;

    do{
        // Prompt user to enter product code
        printf("\nEnter product code: ");
        scanf("%s", &product_code);

        // Find the index of the product with the entered code
        check = find_product_code(product_code, products, num_products);

        if(check == -1){
            printf("Invalid input.\n");
            char ch;

            printf("Press any key to continue: ");
            ch = getch(); // Reads a single character without echoing it
            printf("\nYou pressed: %c\n", ch);

        }
    } while (check == -1);

    // Get the selected product
    struct Product selected_product = products[check];

    // Display details of the selected product
    display_product_details(selected_product);
    int valid_input;
    do {
        valid_input = 1; // Assume input is valid

        printf("Enter quantity: ");
        if (scanf("%d", &quantity) != 1) {
            // If scanf returns anything other than 1, it means input was not a valid integer
            printf("Invalid input. Please enter a valid quantity.\n");
            // Clear input buffer
            while (getchar() != '\n');
            valid_input = 0; // Set flag to indicate invalid input
        }

    } while (!valid_input);

    printf("Price: %5.2f\n", selected_product.price * quantity);

    printf("Add to cart (A) or cancel (C)? ");
    scanf(" %c", &choice);

    // If user chooses to add to cart, call add_to_cart function
    if (choice == 'A' || choice == 'a') {
        add_to_cart(selected_product, quantity, cart, total_items, total_price);
        printf("Item added to cart.\n");
    }
        // If user chooses to cancel, display message and break out of loop
    else if (choice == 'C' || choice == 'c')
    {
        printf("Item not added to cart.\n");
    }

}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void reset_cart(struct Product cart[], int *total_items, float *total_price)
{
    // Reset the cart array
    memset(cart, 0, sizeof(struct Product) * 99);

    /*The memset function is used to set all elements in the cart array to zero,
                effectively clearing out any previous entries.*/

    // Reset total_items and total_price
    *total_items = 0;
    *total_price = 0.0;

    printf("Cart has been reset.\n");

    return;
}


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/


void guest_menu_customer_process (struct Product cart[], int *total_items, float *total_price)
{
    char choice;
    char confirm_choice;

    do {
        // Display cart after processing each order
        view_cart(cart, *total_items, *total_price);

        // Prompt user to add more items or proceed to checkout
        printf("\nAdd more items (A)\n");
        printf("Remove Items (R)\n");
        printf("Deduct Quantity(D)\n");
        printf("Clear Cart(C)\n");
        printf("Proceed to checkout (P)\n");
        printf("Go Back (B)\n");

        printf("\nEnter choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
            case 'A':
            case 'a':
                guest_customer_item_category();
                break;
            case 'R':
            case 'r':
                view_cart(cart, *total_items, *total_price);
                ask_remove(cart, total_items, total_price);
                break;
            case 'D':
            case 'd':
                view_cart(cart, *total_items, *total_price);
                ask_deduct(cart, total_items, total_price);
                break;
            case 'C':
            case 'c':
                do{
                    printf("\nAre you sure you want to clear cart? (Y/N): ");
                    scanf(" %c", &confirm_choice);

                    switch (confirm_choice) {
                        case 'y' :
                        case 'Y' :
                            break;
                        case 'n' :
                        case 'N' :
                            guest_menu_customer_process(cart, total_items, total_price);
                            break;
                        default:
                            printf("\nInvalid input. Try again...\n");
                            press_any_key();
                    }

                } while (confirm_choice != 'Y' && confirm_choice != 'y');
                reset_cart(cart, total_items, total_price);

                break;
            case 'B':
            case 'b':
                guest_customer_item_category();
                break;
            case 'P':
            case 'p':
                // Confirmation before checkout
                printf("\nAre you sure you want to proceed to checkout? (Y/N): ");
                scanf(" %c", &confirm_choice);

                if (confirm_choice == 'Y' || confirm_choice == 'y') {
                    // Proceed to checkout logic
                    // (replace this with your actual checkout process)
                    printf("\nProcessing checkout...\n");
                } else {
                    printf("\nCheckout cancelled.\n");
                    press_any_key();
                    guest_menu_customer_process(cart, total_items, total_price);
                }
                break;
            default:
                printf("\nInvalid input. Try again...\n");
                press_any_key();
        }

    } while (choice != 'p' && choice != 'P');
}


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function para mahanap ung item kung tama ba type ng user at babalik nya ung index (ung value kung tama ba pag type ng user)
int find_product_code(char product_code[], struct Product products[], int num_products)
{
    for (int i = 0; i < num_products; i++) {
        if (strcmp(products[i].code, product_code) == 0) {
            return i; // Return the index of the product if found
        }
    }
    return -1; // Return -1 if product not found
    //return negative 1 kasi pag nag 0 nag eerror lng kaya -1 nalang ginamit
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to display product details, reusable tong part na to
void display_product_details(struct Product products)
{
    printf("Name: %-24s   Price: %5.2f\n", products.name, products.price);
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to add product to cart, dito nag aadd add kung may bago bang nilagay na item sa cart/ void to pero madaming parameter dahil need nya ng info kaya
// may parameter kasi eto ung mga value na need ma check para mag function ang function
void add_to_cart(struct Product product, int quantity, struct Product cart[], int *total_items, float *total_price) {
    int found = 0;

    // Check if the product is already in the cart
    for (int i = 0; i < *total_items; i++) {
        if (strcmp(cart[i].code, product.code) == 0) {
            cart[i].quantity += quantity; // Update the quantity of existing product
            found = 1;
            break;
        }
    }

    // If the product is not found, add it as a new item
    if (!found) {
        product.quantity = quantity;
        cart[*total_items] = product;
        (*total_items)++;
    }

    // Update total price
    *total_price += product.price * quantity;
}


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// eto ung taga print ng laman sa cart kung may mga nadagdag ba or wala pero hindi pa to ung totoong resibo

void display_cart(struct Product cart[], int total_items, float total_price)
{
    if (total_items > 0)
    {
        //system("cls");
        printf("\nCart:\n");
        printf("CODE:\t\tPRODUCT NAME:\t\t\tQUANTITY:\tPRICE:\n");

        // Iterate through the cart items
        for (int i = 0; i < total_items; i++) {
            printf("%-8s\t%-24s\tx%d\t\t%5.2f\n", cart[i].code, cart[i].name, cart[i].quantity, cart[i].price * cart[i].quantity);
        }

        printf("\nTotal Price: %8.2f\n", total_price);

        printf("\nNOTE: THE PROMO CODES WILL APPLY ONLY TO THE CUSTOMER WHO SPEND ABOVE 200 PESOS\n");

    }
}


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void ask_remove(struct Product cart[], int *total_items, float *total_price)
{
    char choice[20];

    printf("Enter the Product Code you want to remove from the cart: ");
    scanf("%s", choice);

    remove_from_cart(cart, total_items, total_price, choice);
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void remove_from_cart(struct Product cart[], int *total_items, float *total_price, const char *code) {
    int removed_items = 0;            // Bilang ng mga item na tinanggal
    float price_to_deduct = 0;      // Kabuuang presyo ng mga item na dapat ibawas
    char confirmation;                // Variable para sa kumpirmasyon ng user

    // Hingin ang kumpirmasyon ng user para tanggalin ang item
    printf("Are you sure you want to remove this item? (Y/N): ");
    scanf(" %c", &confirmation);

    // Suriin kung ang user ay nagkumpirma na gusto niyang tanggalin
    if (confirmation == 'Y' || confirmation == 'y') {
        // Mag-iterate sa mga item sa cart
        for (int i = 0; i < *total_items;) {
            // Suriin kung ang code ng kasalukuyang item ay tugma sa code na tatanggalin
            if (strcmp(cart[i].code, code) == 0) {
                price_to_deduct += cart[i].price * cart[i].quantity; // Calculate total price for removed items
                removed_items++;         // Dagdagan ang bilang ng tinanggal na item

                // I-shift ang mga natitirang item sa cart pakaliwa para punan ang puwang
                for (int j = i; j < *total_items - 1; j++) {
                    cart[j] = cart[j + 1];
                }
                (*total_items)--;        // Bawasan ang kabuuang bilang ng item sa cart
                // Huwag i-increment ang i, dahil kailangan suriin ang bagong item sa kasalukuyang index pagkatapos ng pag-lipat sa ibang item
            } else {
                i++; // Lumipat sa susunod na item sa cart kung ang code ng kasalukuyang item ay hindi tugma
            }
        }

        // Ibawas ang naipong presyo ng mga tinanggal na item sa kabuuang presyo
        *total_price -= price_to_deduct;

        // Magbigay ng feedback sa user tungkol sa proseso ng pagtanggal
        if (removed_items > 0) {
            printf("%d item(s) with product code %s removed from cart.\n", removed_items, code);
        } else {
            printf("Product with code %s not found in the cart.\n", code);
        }
    } else {
        // Kung kinansela ng user ang pagtanggal, magpakita ng mensahe ng pagkansela
        printf("Item removal canceled.\n");
    }
}




/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void ask_deduct(struct Product cart[], int *total_items, float *total_price)
{
    char choice[20];

    printf("Enter the Product Code you want to remove from the cart: ");
    scanf("%s", choice);

    deduct_from_cart(cart, total_items, total_price, choice);
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void deduct_from_cart(struct Product cart[], int *total_items, float *total_price, const char *code) {
    int found = 0;
    char confirmation;
    int deduct_quantity = 0;

    // Search for the product in the cart
    for (int i = 0; i < *total_items; i++) {
        if (strcmp(cart[i].code, code) == 0) {
            // Product found in cart
            found = 1;

            // Confirm deduction with the user
            printf("Enter how many items you want to deduct for product with code %s: ", code);
            if (scanf("%d", &deduct_quantity) != 1 || deduct_quantity <= 0) {
                printf("Invalid input. Please enter a valid number greater than zero.\n");
                return; // Exit function if invalid input
            }

            printf("Are you sure you want to deduct %d item(s) of product with code %s from the cart? (Y/N): ", deduct_quantity, code);
            scanf(" %c", &confirmation);

            if (confirmation == 'Y' || confirmation == 'y') {
                // Check if deduct_quantity exceeds available quantity
                if (deduct_quantity > cart[i].quantity) {
                    printf("Cannot deduct more than what's in the cart. Deduction canceled.\n");
                } else {
                    // Deduct the specified quantity from the total items of the product in the cart
                    cart[i].quantity -= deduct_quantity;

                    // Update total items and total price only if deduction happened
                    *total_price -= (cart[i].price * deduct_quantity);

                    printf("Deducted %d item(s) of product with code %s from the cart.\n", deduct_quantity, code);
                }
            } else if (confirmation == 'N' || confirmation == 'n') {
                printf("Deduction canceled.\n");
            } else {
                printf("Invalid input. Please enter Y or N.\n");
            }

            return; // Exit function after processing
        }
    }

    if (!found) {
        printf("Product with code %s not found in the cart.\n", code);
    }
}






/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to read the queue number from a file
int read_queue_number(const char *filename) {
    FILE *file = fopen(filename, "r");
    int queue_number = 1; // Default queue number

    if (file != NULL) {
        fscanf(file, "%d", &queue_number);
        fclose(file);
    }

    return queue_number;
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to save the queue number to a file
void save_queue_number(const char *filename, int queue_number) {
    FILE *file = fopen(filename, "w");

    if (file != NULL) {
        fprintf(file, "%d", queue_number);
        fclose(file);
    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to save cart items to a CSV file
void save_cart_to_csv(struct Product cart[], int total_items, float total_price)
{
    char any;

    // Get current time
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // Filename for storing the queue number
    const char *queue_filename = "queue_number.txt";

    // Read the current queue number
    int queue_number = read_queue_number(queue_filename);

    // Create a filename with timestamp and queue number
    char filename[50];
    sprintf(filename, "queue_number_%d_%02d_%02d_%d.csv", queue_number, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);

    // Open file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write header
    fprintf(file, "Code,Name,Quantity,Price\n");

    // Write cart items
    for (int i = 0; i < total_items; i++) {
        fprintf(file, "%s,%s,%d,%.2f\n", cart[i].code, cart[i].name, cart[i].quantity, cart[i].price);
    }


    // Close file
    fclose(file);

    printf("\nFile successfully saved\n");

    // Print the current queue number
    printf("\n||==============================================||\n");
    printf("||\t\t\t\t\t\t||\n");
    printf("||\tYour queue number is: %d\t\t\t||\n", queue_number);
    printf("||\t\t\t\t\t\t||\n");
    printf("||==============================================||\n\n");
    printf("Thank you for ordering! Please remember your queue number and proceed to the cashier.\n\n");


    // Increment the queue number and save it back to the file
    queue_number++;
    save_queue_number(queue_filename, queue_number);
    press_any_key();
    user_type_choice();
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void save_customer_to_file(struct customer customer)
{
    FILE *file = fopen(CUSTOMER_FILE, "a");  // Open file in append mode
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "%s %s %s %s %.2f\n", customer.username, customer.password, customer.phone_number, customer.payment_method, customer.balance);
    fclose(file);
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void load_customers_from_file() {
    FILE *file = fopen(CUSTOMER_FILE, "r");  // Open file in read mode
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    struct customer customer;

    while (fscanf(file, "%s %s %s %s %f", customer.username, customer.password, customer.phone_number, customer.payment_method, &customer.balance) != EOF) {
        customers[customer_count++] = customer;
    }
    fclose(file);
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void save_all_customers_to_file()
{
    FILE *file = fopen(CUSTOMER_FILE, "w");  // Open file in write mode to overwrite
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < customer_count; i++) {
        fprintf(file, "%s %s %s %s %.2f\n", customers[i].username, customers[i].password, customers[i].phone_number, customers[i].payment_method, customers[i].balance);
    }
    fclose(file);
}


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

//Registration Function
void customer_register()
{
    if (customer_count >= MAX_CUSTOMERS) {
        printf("\nCustomer limit reached. Cannot register new customers.\n");
        return;
    }

    struct customer new_customer;
    char confirm_password[50];
    float initial_funds;

    printf("\nEnter Username: ");
    scanf("%s", new_customer.username);

    // Check if the username already exists
    for (int i = 0; i < customer_count; i++) {
        if (strcmp(customers[i].username, new_customer.username) == 0)
        {
            printf("\nUsername already exists. Please choose a different username.\n");
            return;
        }
    }

    printf("Enter Password: ");
    scanf("%s", new_customer.password);

    printf("Confirm Password: ");
    scanf("%s", confirm_password);

    // Check if the passwords match
    if (strcmp(new_customer.password, confirm_password) != 0) {
        printf("\nPasswords do not match. Please try again.\n");
        return;
    }

    // Ask for phone number
    printf("Enter Phone Number: ");
    scanf("%s", new_customer.phone_number);

    // Ask for payment method
    char payment_choice;

    printf("Is the phone number for GCash (G) or PayMaya (P)? ");
    scanf(" %c", &payment_choice);

    if (payment_choice == 'G' || payment_choice == 'g') {
        strcpy(new_customer.payment_method, "GCash");
    } else if (payment_choice == 'P' || payment_choice == 'p') {
        strcpy(new_customer.payment_method, "PayMaya");
    } else {
        printf("\nInvalid choice. Please try again.\n");
        press_any_key();
        return;
    }

    // Prompt for initial funds
    printf("Enter initial amount to add to your account: ");
    scanf("%f", &initial_funds);

    // Initialize balance with the entered initial funds
    new_customer.balance = initial_funds;

    // Save the new customer to the array
    customers[customer_count++] = new_customer;

    // Save the new customer to the file
    save_customer_to_file(new_customer);

    printf("\nRegistration successful. You can now log in.\n");

    registered_user_customer_item_category(new_customer.username, &new_customer.balance, new_customer.payment_method);
}


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void add_funds(char* username)
{
    float amount;

    // Find the customer by username
    for (int i = 0; i < customer_count; i++) {
        if (strcmp(customers[i].username, username) == 0)
        {
            printf("Enter amount to add: ");
            scanf("%f", &amount);

            // Add the amount to the customer's balance
            customers[i].balance += amount;

            // Save the updated customers to the file
            save_all_customers_to_file();

            printf("\nFunds added successfully. New balance: %.2f\n", customers[i].balance);
            return;
        }
    }

    printf("\nUsername not found. Please try again.\n");
}


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/
void increment_attempts(int *attempt_count) {
    (*attempt_count)++;
    printf("\nInvalid username or password. Attempt %d\n", *attempt_count);
    if (*attempt_count == 5) {
        char choice;
        printf("You have reached the maximum number of attempts.\n");
        printf("Do you want to reset attempts (R) or change password (C)? (R/C): ");
        choice = getch(); // Use getch() to capture user input without displaying it
        if (choice == 'R' || choice == 'r') {
            reset_attempts(attempt_count);
        } else if (choice == 'C' || choice == 'c') {
            printf("Please proceed to manager to reset your password\n");
            printf("Press any key to return to the main menu...\n");
            getch(); // Wait for user input before returning to main menu
            return;
        } else {
            printf("Invalid choice. Please enter R or C.\n");
            increment_attempts(attempt_count); // Loop until a valid choice is made
        }
    }
}

void reset_attempts(int *attempt_count) {
    int manager_code;
    printf("Manager verification required to reset attempts.\n");
    do {
        printf("Enter manager code: ");
        scanf("%d", &manager_code);
        if (manager_code == 123) {
            *attempt_count = 0; // Reset attempts
            printf("Attempts reset successfully.\n");
            break; // Exit the loop if manager code is correct
        } else {
            printf("Incorrect manager code. Please try again.\n");
        }
    } while (1); // Loop until correct manager code is entered
}


void customer_login() {
    char username[50];
    char password[50];
    int attempt_count = 0;
    int max_attempts = 5;  // Set a maximum number of attempts to 5

    load_customers_from_file();

    while (attempt_count < max_attempts) {
        printf("\nEnter Username: ");
        scanf("%s", username);

        printf("Enter Password: ");
        scanf("%s", password);

        // Check if the username and password match any customer record
        int login_successful = 0;
        for (int i = 0; i < customer_count; i++) {
            if (strcmp(customers[i].username, username) == 0 && strcmp(customers[i].password, password) == 0) {
                printf("\nLogin successful.\n");
                registered_user_customer_item_category(customers[i].username, &customers[i].balance, customers[i].payment_method);
                login_successful = 1;
                break;
            }
        }

        if (login_successful) {
            break;
        } else {
            increment_attempts(&attempt_count);
            if (attempt_count >= max_attempts) {
                break;
            }
        }
    }
}



/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void registered_user_customer_item_category(char* username, float *balance, const char *registered_payment_method)
{
    char choice, item_category;
    int queue_number = 1; // Initialize queue_number to 1

    do {
        //system("cls");
        printf("\nWelcome to our store\n");
        printf("\nWelcome back, %s!\n", username);
        printf("Your balance: %.2f\n", *balance);
        printf("What do you want to browse?\n\n");

        printf("[1] Beverages\n");
        printf("[2] Snacks\n");
        printf("[3] Canned Goods\n");
        printf("[4] Condiments\n");
        printf("[5] Dairy\n");
        printf("[6] Frozen Foods\n");
        printf("[7] Body Care & Beauty Care\n");
        printf("[8] Detergents and Soaps\n");
        printf("[9] Add Funds\n\n");

        printf("[0] Go back\n");

        printf("\nEnter Here: ");
        scanf("%s", &item_category);

        switch (item_category)
        {
            case '0':
                printf("\nDo you really want to go back? (Y/N): ");
                scanf(" %c", &choice);

                // Check if the choice is 'Y' or 'y' for confirmation to go back
                if (choice == 'Y' || choice == 'y') {
                    reset_cart(cart, &total_items, &total_price);
                    //save to csv
                    return;
                }
                break;
            case '1':
                browse_beverages(&queue_number);
                registered_user_menu_customer_process(cart, &total_items, &total_price, username, balance, registered_payment_method);

                //call out the choose payment here
                choose_payment_mode(registered_payment_method);
                break;
            case '2':
                browse_snacks(&queue_number);
                registered_user_menu_customer_process(cart, &total_items, &total_price, username, balance, registered_payment_method);
                choose_payment_mode(registered_payment_method);
                break;
            case '3':
                browse_canned_goods(&queue_number);
                registered_user_menu_customer_process(cart, &total_items, &total_price, username, balance, registered_payment_method);
                choose_payment_mode(registered_payment_method);
                break;
            case '4':
                browse_condiments(&queue_number);
                registered_user_menu_customer_process(cart, &total_items, &total_price, username, balance, registered_payment_method);
                choose_payment_mode(registered_payment_method);
                break;
            case '5':
                browse_dairy(&queue_number);
                registered_user_menu_customer_process(cart, &total_items, &total_price, username, balance, registered_payment_method);
                choose_payment_mode(registered_payment_method);
                break;
            case '6':
                browse_frozen_foods(&queue_number);
                registered_user_menu_customer_process(cart, &total_items, &total_price, username, balance, registered_payment_method);
                choose_payment_mode(registered_payment_method);
                break;
            case '7':
                browse_self_care_products(&queue_number);
                registered_user_menu_customer_process(cart, &total_items, &total_price, username, balance, registered_payment_method);
                choose_payment_mode(registered_payment_method);
                break;
            case '8':
                browse_detergent_soaps(&queue_number);
                registered_user_menu_customer_process(cart, &total_items, &total_price, username, balance, registered_payment_method);
                choose_payment_mode(registered_payment_method);
                break;
            case '9':
                add_funds(username);
                // Update balance display after adding funds
                for (int i = 0; i < customer_count; i++) {
                    if (strcmp(customers[i].username, username) == 0) {
                        *balance = customers[i].balance;
                        return;
                    }
                }
                printf("\nYour updated balance: %.2f\n", *balance);
                break;
            default:
                printf("\nInvalid input. Try again...\n");
                press_any_key();
        }



    } while (item_category != '0' || (item_category == '0' && (choice != 'Y' && choice != 'y')));

}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/


void registered_user_menu_customer_process (struct Product cart[], int *total_items, float *total_price, char* username, float *balance,  const char *registered_payment_method)
{
    char choice;
    char confirm_choice;

    do {
        // Display cart after processing each order
        view_cart(cart, *total_items, *total_price);

        // Prompt user to add more items or proceed to checkout
        printf("\nAdd more items (A)\n");
        printf("Remove Items (R)\n");
        printf("Deduct Quantity(D)\n");
        printf("Clear Cart(C)\n");
        printf("Proceed to checkout (P)\n");
        printf("Go Back (B)\n");

        printf("\nEnter choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
            case 'A':
            case 'a':
                registered_user_customer_item_category(username, balance,registered_payment_method);
                break;
            case 'R':
            case 'r':
                view_cart(cart, *total_items, *total_price);
                ask_remove(cart, total_items, total_price);
                break;
            case 'D':
            case 'd':
                view_cart(cart, *total_items, *total_price);
                ask_deduct(cart, total_items, total_price);
                break;
            case 'C':
            case 'c':
                do{
                    printf("\nAre you sure you want to clear cart? (Y/N): ");
                    scanf(" %c", &confirm_choice);

                    switch (confirm_choice) {
                        case 'y' :
                        case 'Y' :
                            break;
                        case 'n' :
                        case 'N' :
                            guest_menu_customer_process(cart, total_items, total_price);
                            break;
                        default:
                            printf("\nInvalid input. Try again...\n");
                            press_any_key();
                    }

                } while (confirm_choice != 'Y' && confirm_choice != 'y');
                reset_cart(cart, total_items, total_price);
                break;
            case 'B':
            case 'b':
                guest_customer_item_category();
                break;
            case 'P':
            case 'p':
                printf("\nAre you sure you want to proceed to checkout? (Y/N): ");
                scanf(" %c", &confirm_choice);

                if (confirm_choice == 'Y' || confirm_choice == 'y') {
                    // Proceed to checkout logic
                    // (e.g., payment processing, order confirmation)
                    printf("\nProceeding to Checkout...\n");
                    // ... your checkout code here ...
                } else {
                    printf("\nCheckout cancelled.\n");
                    press_any_key();
                    registered_user_menu_customer_process(cart, total_items, total_price, username, balance, registered_payment_method);
                }
                break;
        }

    } while (choice != 'p' && choice != 'P');
}


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void choose_payment_mode(const char *registered_payment_method)
{
    int choice;
    char password[50];
    char contact_number[50];

    do {
        printf("\nChoose your mode of payment:\n");
        printf("1. Cash\n");
        printf("2. Use E-wallet\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("You have chosen Cash as your mode of payment.\n");
                {
                    // Display the contents of the cart
                    display_cart(cart, total_items, total_price);

                    // Save the cart to a CSV file
                    save_cart_to_csv(cart, total_items, total_price);
                }
                break; // Add break statement here

            case 2:
                printf("You have chosen %s as your mode of payment.\n", registered_payment_method);
                do {
                    printf("Enter Password: ");
                    scanf("%s", password);

                    load_customers_from_file();

                    int login_success = 0; // Variable to track login success
                    for (int i = 0; i < customer_count; i++) {
                        if (strcmp(customers[i].password, password) == 0) {
                            printf("\nLogin successful.\n");

                            // Prompt user to enter their contact number
                            while (1) {
                                printf("Enter Contact Number: ");
                                scanf("%s", contact_number);

                                if (strcmp(customers[i].phone_number, contact_number) == 0) {
                                    // Contact number matches, proceed
                                    printf("Contact number verified.\n");
                                    generate_receipt(cart, total_items, total_price, customers[i].username, &(customers[i].balance), registered_payment_method);
                                    // Save the updated balance to file
                                    save_all_customers_to_file();
                                    login_success = 1;
                                    break;
                                } else {
                                    printf("Wrong contact number. Please try again.\n");
                                }
                            }
                            if (login_success) break; // Exit the outer loop if login is successful
                        }
                    }

                    if (login_success) break; // Exit the do-while loop if login is successful

                    printf("Invalid password. Please try again or enter '0' to cancel payment.\n");
                    printf("Enter choice: ");
                    scanf("%d", &choice);
                    if (choice == 0) {
                        printf("Payment canceled.\n");
                        return; // Exit the function if payment is canceled
                    }
                } while (1); // Loop until a correct password and contact number are entered or payment is canceled
                break; // Add break statement here

            default:
                printf("Invalid choice. Please try again.\n");
                press_any_key();
        }
    } while (1); // Loop until a valid payment choice is made
}


//Function para magprint ng receipt para sa auto-pay process//
void generate_receipt(struct Product cart[], int total_items, float total_price, char* username, float *balance, const char *registered_payment_method)
{
    char choice;

    if (total_items > 0) {
        //system("cls");

        printf("\n------------------***** Receipt *****----------------\n");
        printf("\tWelcome To Fourgramming Store\n");
        //dito lagyan nung realtime na code
        //nag crash kasi code ko pag nilalagay ko
        printf("---------------------------------------------------------------\n");
        printf("\tUsername: %s\n", username);
        printf("---------------------------------------------------------------\n");
        // Display items purchased
        printf("\nCart:\n");
        printf("CODE\t\tProduct Name\t   Quantity   Price\n");

        // Initialize quantity count for the first product
        int quantity_count = 1;

        // Iterate through the cart items
        for (int i = 0; i < total_items; i++) {
            // Check if the next item is the same as the current one
            if (i < total_items - 1 && strcmp(cart[i].code, cart[i+1].code) == 0) {
                // If yes, increment quantity count
                quantity_count++;
            } else {
                // If no, print the current item with its quantity and reset quantity count
                printf("%-8s \t%-24s \t  x%d  \t%5.2f\n", cart[i].code, cart[i].name, quantity_count, cart[i].price * quantity_count);
                quantity_count = 1; // Reset quantity count for the next product
            }
        }
        printf("---------------------------------------------------------------\n");
        printf("\n\nTotal Price: %8.2f\n", total_price);
        printf("---------------------------------------------------------------\n");
        // Display payment method
        printf("\nPayment Method: %s\n", registered_payment_method);

        printf("\nAmount Paid: P%.2f\n", total_price);

        // Update user's balance
        *balance -= total_price;

        printf("---------------------------------------------------------------\n");
        // Display updated balance
        printf("\nUpdated Balance: P%.2f\n", *balance);
        printf("---------------------------------------------------------------\n");
        // Save receipt to CSV
        save_receipt_to_csv(cart, total_items, total_price, total_price);

        printf("\nGo back and shop again (Any key) or Go back to the Menu (E) ");
        scanf(" %c", &choice);

        if (choice == 'E' || choice == 'e')
        {
            // dito na yung csv na bago

            reset_cart(cart, &total_items, &total_price);

            printf("Going back to Menu...\n");
            user_type_choice();
        }
        else {
            registered_user_customer_item_category(username, balance,registered_payment_method);
        }

    }
}


/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

//functions at cashier


void user_cashier()
{
    //system("cls");
    cashier_login();

}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void cashier_login()
{
    char username[50], password[50];
    int valid = 0; //indicate if login is valid

    while (!valid)
    { // Loop until valid login
        printf("\nCashier Login\n\n");
        printf("Enter Credentials\n\n");
        printf("Enter username: ");
        scanf("%s", username);

        printf("Enter password: ");
        scanf("%s", password);

        // Validate login
        if (validate_cashier_login(username, password))
        {
            //system("cls");
            printf("Login successful!\n");
            valid = 1; // Set flag to exit loop
            cashier_process_choice();
        } else {
            printf("Invalid username or password. Please try again.\n");
            press_any_key();
        }
    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

int validate_cashier_login(char username[], char password[])
{
    // Define correct username and password
    char correct_username[] = "admin";
    char correct_password[] = "admin";

    // Compare entered credentials with correct ones
    //kailangan magiging 0 dahil ibigsabihin nun tugma mga letra at pagkakasunod sunod ng character
    //kaya 1 need ang bumalik dahil ayun ung nilagay ko sa return
    //hanggat hindi nakaka 1point edi mali
    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1; // Credentials are correct
    } else {
        return 0; // Credentials are incorrect
    }

}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void cashier_process_choice()
{
    char choice;
    char confirm;

    // Loop hanggang sa pumili ang cashier na lumabas.
    while (1)
    {
        reset_counter(counter, &total_items, &total_price);
        selecting_queue_list_to_process();

        printf("[1] Proceed to pay\n");
        printf("[2] Modify Counter Items (under development)\n");
        printf("[0] Exit\n");

        printf("\n\nEnter Here: ");
        scanf(" %c", &choice);
        // system("cls");

        switch (choice)
        {
            case '1':
                /*
                 dto dapat pupunta to sa proceed to payment
                            at mag aask bayad at mag aask ng discount coupon

                 gawa nalang cupon code at nasa if else

                 #PANALONATO = 50PESOS OFF

                 #INPR_UNO = 100% KASI MAANGAS

                 MGA GANYAN
                 */
                cashier_pay_option();
                break;

            case '2':
                // Pumunta sa function para sa pag-lista ng item.
                // MAG AASK NG MANAGER CODE TAPOS pwede na baguhin laman ng counter
                // modify_cart(counter, &total_items, selected_file);
                ask_modify_counter(counter, &total_items, &total_price, filename);
                break;

            case '3':
                // Function to view and select receipt from list
                selecting_queue_list_to_process();
                break;

            case '0':
                // Lumabas sa loop kung ang cashier ay pumili ng '0'.
                printf("\nAre you sure you want to log out? (y/n): ");
                scanf(" %c", &confirm);

                if (confirm == 'y' || confirm == 'Y')
                {
                    return;
                }
                else
                {
                    printf("\nLog out cancelled. Returning to menu...\n");
                    press_any_key();
                }
                break;

            default:
                // Kung ang input ay hindi wasto, ipakita ang error message.
                printf("\nInvalid input. Try again...");
                press_any_key();
        }
    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to display and select a receipt file
void selecting_queue_list_to_process()
{
    DIR *directory;
    struct dirent *dir;
    char files[100][256]; // Array to hold filenames
    int count = 0; // Count of CSV files found
    int choice; // User's choice
    char selected_file[256];
    char confirm;

    // Open the current directory
    directory = opendir(".");

    if (directory) {
        printf("\n\n\tCSV Files to Open:\n");
        // Iterate over files in the directory
        while ((dir = readdir(directory)) != NULL) {
            // Check if the file has a .csv extension
            if (strstr(dir->d_name, ".csv") != NULL) {
                // Save the file name if it has a .csv extension
                strcpy(files[count], dir->d_name);
                printf("[%d] %s\n", count + 1, files[count]);
                count++;
            }
        }
        // Close the directory
        closedir(directory);

        if (count > 0) {
            printf("[0] Log Out\n");
            printf("Enter the number of the file to open: ");
            scanf("%d", &choice);

            if (choice > 0 && choice <= count) {
                strcpy(selected_file, files[choice - 1]);
                printf("You selected: %s\n", selected_file);
                // Read and process the selected CSV file
                read_csv_to_counter(selected_file);
            } else if (choice == 0) {
                printf("\nAre you sure you want to log out? (y/n): ");
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y')
                {
                    user_type_choice();
                }
            } else {
                printf("Invalid choice.\n");
                press_any_key();
            }
        } else {
            printf("No CSV files found.\n");
            printf("No Queue Order to process.\n");

            printf("Enter [0] to Log Out: ");
            scanf(" %c", &choice);

            if (choice == '0') { user_type_choice();
            }else {
                printf("Invalid choice.\n");
                press_any_key();
            }
        }
    } else {
        // Print an error message if the directory cannot be opened
        printf("Error opening directory.\n");
    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to read the selected CSV file into the counter array
void read_csv_to_counter(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s.\n", filename);
        return;
    }

    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        if (i == 0) { // Skip header line
            i++;
            continue;
        }
        sscanf(line, "%[^,],%[^,],%d,%f", counter[i-1].code, counter[i-1].name, &counter[i-1].quantity, &counter[i-1].price);
        i++;
    }

    fclose(file);
    // Display the counter array contents
    total_items = i - 1;
    total_price = calculate_total_price(counter, total_items);
    display_counter(counter, total_items, total_price);
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to calculate the total price of items in the cart
float calculate_total_price(struct Product counter[], int total_items)
{
    float total_price = 0.0;

    for (int i = 0; i < total_items; i++) {
        total_price += counter[i].price * counter[i].quantity;
    }
    return total_price;
}



// New function to display the counter contents
void display_counter(struct Product counter[], int total_items, float total_price)
{
    if (total_items > 0) {
        printf("\nCounter:\n");
        printf("CODE:\t\tPRODUCT NAME:\t\t\tQUANTITY:\tPRICE:\n");

        // Iterate through the counter items
        for (int i = 0; i < total_items; i++) {
            printf("%-8s \t%-24s \t  x%d  \t\t %5.2f\n", counter[i].code, counter[i].name, counter[i].quantity, counter[i].price * counter[i].quantity);
        }
        printf("\n\nTotal Price: %8.2f\n", total_price);
    } else {
        printf("\nCounter is empty.\n");
    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void reset_counter(struct Product counter[], int *total_items, float *total_price)
{
    // Reset the counter array
    memset(counter, 0, sizeof(struct Product) * 99);

    /*The memset function is used to set all elements in the counter array to zero,
                effectively clearing out any previous entries.*/

    // Reset total_items and total_price
    *total_items = 0;
    *total_price = 0.0;

    //printf("Counter has been reset.\n");

    return;
}

// mga function dati na need ng fix

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function para sa pagpili ng cashier kung paano bayaran ang mga items.
void cashier_pay_option()
{
    char cashier_option;

    // Loop until valid input is given
    while(1)
    {
        printf("\n[1] Pay\n");
        printf("[2] Discount\n");
        printf("[0] Go back\n");
        printf("\nEnter Here: ");
        // Accept input from the cashier.
        scanf(" %c", &cashier_option);
        switch (cashier_option) {
            case '1':
                cashier_pay_process(counter, total_items, &total_price);
                break;
            case '2':
                cashier_discount_process(&total_price);
                break;
            case '0':
                return;
            default:
                // If the input is invalid, show an error message.
                printf("\nInvalid input. Try again...\n");
                press_any_key();
        }
    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void cashier_pay_process(struct Product counter[], int total_items, float *total_price)
{
    float payment;
    int choice;

    display_counter(counter, total_items, *total_price);
    printf("\nTotal Amount to Pay: %.2f\n", *total_price); // Display total price of items

    // Confirmation before proceeding to payment
    printf("Do you want to proceed with the payment?\n");
    printf("[1] Yes\n[2] Cancel\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter rendered amount: ");
            scanf("%f", &payment);

            if (payment >= *total_price) {
                printf("Payment accepted.\n");
                if (payment > *total_price) {
                    printf("Change: %.2f\n", payment - *total_price);
                }
                // Print receipt after successful payment
                print_receipt(counter, total_items, *total_price, payment);
            } else {
                printf("Insufficient payment. Please try again.\n");
                cashier_pay_process(counter, total_items, total_price); // Recursively ask for payment until enough is provided.
            }
            break;
        case 2:
            // Reset the counter and go back to cashier_process_choice
            reset_counter(counter, &total_items, total_price);
            cashier_process_choice();
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            press_any_key();
            cashier_pay_process(counter, total_items, total_price); // Recursively ask for choice until valid input is provided.
            break;
    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to print the receipt
void print_receipt(struct Product counter[], int total_items, float total_price, float payment)
{
    char choice;
    printf("\n\n----- RECEIPT -----\n");
    printf("CODE\t\tProduct Name\t   Quantity   Price\n");

    for (int i = 0; i < total_items; i++) {
        printf("%-8s \t%-24s \t  x%d  \t%5.2f\n", counter[i].code, counter[i].name, counter[i].quantity, counter[i].price * counter[i].quantity);
    }

    printf("----------------------------------------\n");
    printf("\nTotal Price: %.2f\n", total_price);
    printf("Payment: %.2f\n", payment);

    if (payment > total_price) {
        printf("Change: %.2f\n", payment - total_price);
    }
    printf("------------------------------------------\n");
    printf("Do you want to go back to cashier menu (press any key) or Save & Exit (E): ");
    scanf("%s", &choice);

    if (choice == 'E' || choice == 'e')
    {
        // Save receipt to CSV
        save_receipt_to_csv(cart, total_items, total_price, total_price);

        //reset the cart
        reset_counter(counter, &total_items, &total_price);
        // cls
        cashier_process_choice();
        return;
    }
    else {
        printf("Exiting...\n");
        // cls
        user_type_choice();
    }

}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void apply_discount(char promo_code[], float *total_price)
{
    if (strcmp(promo_code, "#PANALONATO") == 0) {
        *total_price -= 50.0;
        if (*total_price < 0) *total_price = 0;
        printf("Promo code applied: 50 pesos off.\n");

    } else if (strcmp(promo_code, "#COUPON") == 0) {
        *total_price -= 85.0;
        if (*total_price < 0) *total_price = 0;
        printf("Promo code applied: 85 pesos off.\n");

    } else if (strcmp(promo_code, "#FOURGRAMMING") == 0) {
        *total_price -= 90.0;
        if (*total_price < 0) *total_price = 0;
        printf("Promo code applied: 90 pesos off.\n");

    } else if (strcmp(promo_code, "#MAAMSHEINNGANDA") == 0) {
        *total_price -= 100.0;
        if (*total_price < 0) *total_price = 0;
        printf("Promo code applied: 100 pesos off.\n");

    } else {
        printf("Invalid promo code.\n");
    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

int validate_manager_login(char username[], char password[])
{
    char correct_username[] = "manager";
    char correct_password[] = "manager";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

void cashier_discount_process(float *total_price)
{
    char promo_code[50];
    char manager_username[50];
    char manager_password[50];
    int promo_code_valid = 0; // Flag to track if the promo code is valid
    bool coupon_used = false; // Flag to track if a coupon has been used

    printf("\nAvailable Promo Codes (Each coupon can be used only once):\n");
    printf("#PANALONATO - 50 pesos off\n");
    printf("#COUPON - 85 pesos off\n");
    printf("#FOURGRAMMING - 90 pesos off\n");
    printf("#MAAMSHEINNGANDA - 100 pesos off\n");

    while (!promo_code_valid) {
        printf("\nEnter promo code: ");
        scanf("%s", promo_code);

        // Check if the promo code is valid
        if ((strcmp(promo_code, "#PANALONATO") == 0 ||
             strcmp(promo_code, "#COUPON") == 0 ||
             strcmp(promo_code, "#FOURGRAMMING") == 0 ||
             strcmp(promo_code, "#MAAMSHEINNGANDA") == 0) && !coupon_used) {
            promo_code_valid = 1;
            coupon_used = true; // Mark the coupon as used
        } else {
            if (coupon_used) {
                printf("Coupons can only be used once. Please try another promo code.\n");
            } else {
                printf("Invalid promo code. Please try again.\n");
            }
        }
    }
    //system("cls");
    printf("Checking if you spend above 200...\n");

    if (*total_price > 200.0) {
        printf("You spent over %.2f pesos. You can proceed.\n", *total_price);
    } else {
        printf("Sorry, you didn't meet the qualified minimum spend. Please proceed to pay.\n");
        cashier_pay_process(counter, total_items, total_price); // Call the payment process function
        return;
    }

    // Ask for manager approval
    printf("\nManager approval required.\n");

    printf("\nEnter manager username: ");
    scanf("%s", manager_username);

    printf("\nEnter manager password: ");
    scanf("%s", manager_password);

    if (validate_manager_login(manager_username, manager_password)) {
        apply_discount(promo_code, total_price);
        printf("New Total Amount to Pay: %.2f\n", *total_price);
    } else {
        printf("\nInvalid manager credentials. Discount not applied.\n");
        press_any_key();
    }

    // Offer to proceed to pay or cancel
    int choice;

    printf("\n[1] Pay now\n[2] Cancel\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Proceed to paying
        cashier_pay_process(counter, total_items, total_price);
    } else {
        printf("The Paying process has been cancelled...\n2");
        // Reset the counter and return to the cashier menu
        reset_counter(counter, &total_items, total_price);

        cashier_process_choice();
    }
}



/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to find a product in the cart or counter by code
int find_product_index(struct Product array[], int total_items, const char *code)
{
    for (int i = 0; i < total_items; i++) {
        if (strcmp(array[i].code, code) == 0) {
            return i;
        }
    }
    return -1; // Return -1 if the product is not found
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to confirm user action
int get_confirmation(const char *message)
{
    char confirmation;

    printf("%s (Y/N): ", message);
    scanf(" %c", &confirmation);

    return (confirmation == 'Y' || confirmation == 'y');
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to save products to a CSV file
void save_counter_to_csv(struct Product counter[], int total_items, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Could not open file %s for writing.\n", filename);
        return;
    }

    for (int i = 0; i < total_items; i++) {
        fprintf(file, "%s,%s,%.2f,%d\n", counter[i].code, counter[i].name, counter[i].price, counter[i].quantity);
    }

    fclose(file);
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to modify the counter array
void modify_counter(struct Product counter[], int *total_items, float *total_price, const char *code, int quantity)
{
    int product_index = find_product_index(counter, *total_items, code);

    if (product_index == -1) {
        printf("Product with code %s not found in the counter.\n", code);
        return;
    }

    if (quantity == -1) {
        // Remove the product from the counter
        if (get_confirmation("Are you sure you want to remove this item?")) {
            *total_price -= counter[product_index].price * counter[product_index].quantity;
            for (int i = product_index; i < *total_items - 1; i++) {
                counter[i] = counter[i + 1];
            }
            (*total_items)--;
            printf("Product with code %s removed from the counter.\n", code);
        } else {
            printf("Item removal canceled.\n");
        }
    } else {
        // Deduct the specified quantity from the product in the counter
        if (quantity > counter[product_index].quantity) {
            printf("Cannot deduct more than what's in the counter. Deduction canceled.\n");
        } else if (get_confirmation("Are you sure you want to deduct the specified quantity?")) {
            counter[product_index].quantity -= quantity;
            *total_price -= counter[product_index].price * quantity;
            printf("Deducted %d item(s) of product with code %s from the counter.\n", quantity, code);
        } else {
            printf("Deduction canceled.\n");
        }
    }

    // Save the updated counter to the CSV file
    save_counter_to_csv(counter, *total_items, filename);
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to ask the user for product code and quantity to modify in the counter array
void ask_modify_counter(struct Product counter[], int *total_items, float *total_price, const char *filename)
{
    char code[20];
    int quantity;

    display_counter(counter, *total_items, *total_price);

    printf("Enter the Product Code you want to modify in the counter: ");
    scanf("%s", code);

    printf("Enter the quantity to deduct or -1 to remove the product: ");
    if (scanf("%d", &quantity) != 1) {
        printf("Invalid input. Please enter a valid number.\n");
        press_any_key();
        return;
    }

    modify_counter(counter, total_items, total_price, code, quantity);
    save_counter_to_csv(counter, *total_items, filename);
}

/*****END*********************END***********END***********END************END************END************END************END************END************END************END************END*****/

// Function to save the receipt to CSV
void save_receipt_to_csv(struct Product cart[], int total_items, float total_price, float payment)
{
    char any;

    // Get current time
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // Filename for storing the receipt with timestamp
    char filename[50];
    sprintf(filename, "receipt_%d_%02d_%02d_%d.txt", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, tm->tm_hour);

    // Open file for writing
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write header
    fprintf(file, "Code,Name,Quantity,Price\n");

    // Write receipt items
    for (int i = 0; i < total_items; i++) {
        fprintf(file, "%s,%s,%d,%.2f\n", cart[i].code, cart[i].name, cart[i].quantity, cart[i].price);
    }

    // Write totals
    fprintf(file, "\nTotal Price: ,%.2f\n", total_price);
    fprintf(file, "Payment: ,%.2f\n", payment);
    if (payment > total_price) {
        fprintf(file, "Change: ,%.2f\n", payment - total_price);
    }

    // Close file
    fclose(file);

    printf("\nReceipt successfully saved\n");

    // Prompt user to continue
    printf("\nPress any key and Enter to continue: ");
    scanf(" %c", &any);
}