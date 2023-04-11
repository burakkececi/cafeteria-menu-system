/*
 *
 * Cafeteria Menu System Version 1.0
 * Author: Burak Keçeci - 290201103 & Berkan Gönülsever 270201064
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024

#define student_fee 6
#define academic_fee 16
#define adminstrative_fee 12

typedef struct
{
    char *date;      //  The day and the month need to be held as strings
    char *soup;      //  The name of the soup.
    char *main_dish; //  The name of the main dish.
    char *side_dish; //  The name of the side dish.
    char *extra;     //  Name any extra contents in the menu such as “salad”, “fruit”, etc.
    struct Customer
    {
        int student_count;
        int academic_count;
        int adminstrative_count;
    } sale_count_array; //  An array with three elements that looks like [‘student_count’, ‘academic_count’, ‘administrative_count’].
} Menu;

typedef struct
{

    char *month;
    Menu **normal_menu_array;
    Menu **vegan_menu_array;
    Menu **vegetarian_menu_array;

} Cafeteria;

int count_normal = 0, count_vegan = 0, count_vegetarian = 0;
void initialize_menus(Cafeteria *cafeteria, char *csv_file_name)
{
    char month_string[32];

    sscanf(csv_file_name, "%*[^_]_%[^_]_%*[^_]",  month_string);
    cafeteria->month = strdup(month_string);

    FILE *fp = fopen(csv_file_name, "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(0);
    }

    char line[MAX_LINE_LENGTH];
    char *token;
    int index = 0;

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        token = strtok(line, ",");
        if (strcmp(token, "\"Normal\"") == 0)
        {
            count_normal++;
        }
        else if (strcmp(token, "\"Vegan\"") == 0)
        {
            count_vegan++;
        }
        else if (strcmp(token, "\"Vegetarian\"") == 0)
        {
            count_vegetarian++;
        }
        index++;
    }
    rewind(fp);

    cafeteria->normal_menu_array = malloc((count_normal + 1) * sizeof(Menu *)); 
    cafeteria->vegan_menu_array = malloc((count_vegan + 1) * sizeof(Menu *));
    cafeteria->vegetarian_menu_array = malloc((count_vegetarian + 1) * sizeof(Menu *)); 
    char menu_type[32];
    char date[32], soup[64], main_dish[64], side_dish[64], extra[64];
    int j = 0, k = 0, l = 0;
    index = 0;
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", menu_type, date, soup, main_dish, side_dish, extra);

        if (strcmp(menu_type, "\"Normal\"") == 0)
        {
            cafeteria->normal_menu_array[j] = (Menu *)calloc(1, sizeof(Menu));
            cafeteria->normal_menu_array[j]->date = strdup(date);
            cafeteria->normal_menu_array[j]->soup = strdup(soup);
            cafeteria->normal_menu_array[j]->main_dish = strdup(main_dish);
            cafeteria->normal_menu_array[j]->side_dish = strdup(side_dish);
            cafeteria->normal_menu_array[j]->extra = strdup(extra);
            cafeteria->normal_menu_array[j]->sale_count_array.student_count = 0;
            cafeteria->normal_menu_array[j]->sale_count_array.academic_count = 0;
            cafeteria->normal_menu_array[j]->sale_count_array.adminstrative_count = 0;
            j++;
        }
        else if (strcmp(menu_type, "\"Vegan\"") == 0)
        {
            cafeteria->vegan_menu_array[k] = (Menu *)calloc(1, sizeof(Menu));
            cafeteria->vegan_menu_array[k]->date = strdup(date);
            cafeteria->vegan_menu_array[k]->soup = strdup(soup);
            cafeteria->vegan_menu_array[k]->main_dish = strdup(main_dish);
            cafeteria->vegan_menu_array[k]->side_dish = strdup(side_dish);
            cafeteria->vegan_menu_array[k]->extra = strdup(extra);
            cafeteria->vegan_menu_array[k]->sale_count_array.student_count = 0;
            cafeteria->vegan_menu_array[k]->sale_count_array.academic_count = 0;
            cafeteria->vegan_menu_array[k]->sale_count_array.adminstrative_count = 0;
            k++;
        }
        else if (strcmp(menu_type, "\"Vegetarian\"") == 0)
        {
            cafeteria->vegetarian_menu_array[l] = (Menu *)calloc(1, sizeof(Menu));
            cafeteria->vegetarian_menu_array[l]->date = strdup(date);
            cafeteria->vegetarian_menu_array[l]->soup = strdup(soup);
            cafeteria->vegetarian_menu_array[l]->main_dish = strdup(main_dish);
            cafeteria->vegetarian_menu_array[l]->side_dish = strdup(side_dish);
            cafeteria->vegetarian_menu_array[l]->extra = strdup(extra);
            cafeteria->vegetarian_menu_array[l]->sale_count_array.student_count = 0;
            cafeteria->vegetarian_menu_array[l]->sale_count_array.academic_count = 0;
            cafeteria->vegetarian_menu_array[l]->sale_count_array.adminstrative_count = 0;
            l++;
        }

        index++;
    }
    cafeteria->normal_menu_array[j] = NULL;
    cafeteria->vegan_menu_array[k] = NULL;
    cafeteria->vegetarian_menu_array[l] = NULL;
    fclose(fp);
}

int getRandomNumber(int min, int max)
{
    static int initialized = 0;
    if (!initialized)
    {
        srand(time(NULL));
        initialized = 1;
    }
    return min + rand() % (max - min + 1);
}
void record_customer_counts(Cafeteria *cafeteria)
{
    int j = 0, k = 0, l = 0;
    while (cafeteria->normal_menu_array[j] != NULL)
    {
        cafeteria->normal_menu_array[j]->sale_count_array.student_count = getRandomNumber(0, 50);
        cafeteria->normal_menu_array[j]->sale_count_array.academic_count = getRandomNumber(0, 50);
        cafeteria->normal_menu_array[j]->sale_count_array.adminstrative_count = getRandomNumber(0, 50);
        j++;
    }
    while (cafeteria->vegan_menu_array[k] != NULL)
    {
        cafeteria->vegan_menu_array[k]->sale_count_array.student_count = getRandomNumber(0, 50);
        cafeteria->vegan_menu_array[k]->sale_count_array.academic_count = getRandomNumber(0, 50);
        cafeteria->vegan_menu_array[k]->sale_count_array.adminstrative_count = getRandomNumber(0, 50);
        k++;
    }
    while (cafeteria->vegetarian_menu_array[l] != NULL)
    {
        cafeteria->vegetarian_menu_array[l]->sale_count_array.student_count = getRandomNumber(0, 50);
        cafeteria->vegetarian_menu_array[l]->sale_count_array.academic_count = getRandomNumber(0, 50);
        cafeteria->vegetarian_menu_array[l]->sale_count_array.adminstrative_count = getRandomNumber(0, 50);
        l++;
    }
}

void calc_and_show_income(Cafeteria *cafeteria)
{
    int subtotal = 0;
    int totalNormalMenuSales = 0, totalVeganMenuSales = 0, totalVegetarianMenuSales = 0;
    int totalStudentSales = 0, totalAcademicSales = 0, totalAdminstrativeSales = 0;

    int totalNormalStudent = 0, totalNormalAcademic = 0, totalNormalAdminstrative = 0;
    int totalVeganStudent = 0, totalVeganAcademic = 0, totalVeganAdminstrative = 0;
    int totalVegetarianStudent = 0, totalVegetarianAcademic = 0, totalVegetarianAdminstrative = 0;

    int j = 0, k = 0, l = 0;
    while (cafeteria->normal_menu_array[j] != NULL)
    {
        totalNormalStudent += student_fee * cafeteria->normal_menu_array[j]->sale_count_array.student_count;
        totalNormalAcademic += academic_fee * cafeteria->normal_menu_array[j]->sale_count_array.academic_count;
        totalNormalAdminstrative += adminstrative_fee * cafeteria->normal_menu_array[j]->sale_count_array.adminstrative_count;
        j++;
    }
    while (cafeteria->vegan_menu_array[k] != NULL)
    {
        totalVeganStudent += student_fee * cafeteria->vegan_menu_array[k]->sale_count_array.student_count;
        totalVeganAcademic += academic_fee * cafeteria->vegan_menu_array[k]->sale_count_array.academic_count;
        totalVeganAdminstrative += adminstrative_fee * cafeteria->vegan_menu_array[k]->sale_count_array.adminstrative_count;
        k++;
    }
    while (cafeteria->vegetarian_menu_array[l] != NULL)
    {
        totalVegetarianStudent += student_fee * cafeteria->vegetarian_menu_array[l]->sale_count_array.student_count;
        totalVegetarianAcademic += academic_fee * cafeteria->vegetarian_menu_array[l]->sale_count_array.academic_count;
        totalVegetarianAdminstrative += adminstrative_fee * cafeteria->vegetarian_menu_array[l]->sale_count_array.adminstrative_count;
        l++;
    }

    // total menu sales
    totalNormalMenuSales = totalNormalStudent + totalNormalAcademic + totalNormalAdminstrative;
    totalVeganMenuSales = totalVeganStudent + totalVeganAcademic + totalVeganAdminstrative;
    totalVegetarianMenuSales = totalVegetarianStudent + totalVegetarianAcademic + totalVegetarianAdminstrative;

    // customer sales
    totalStudentSales = totalNormalStudent + totalVeganStudent + totalVegetarianStudent;
    totalAcademicSales = totalNormalAcademic + totalVeganAcademic + totalVegetarianAcademic;
    totalAdminstrativeSales = totalNormalAdminstrative + totalVeganAdminstrative + totalVegetarianAdminstrative;

    subtotal = totalNormalMenuSales + totalVeganMenuSales + totalVegetarianMenuSales;

    printf("~ ~ ~ ~ Normal menu for the first and last days of the month:\n");
    printf("date--> %s\nsoup--> %s\nmain_dish--> %s\nside_dish--> %s\nextra--> %s\n\n",
           cafeteria->normal_menu_array[0]->date,
           cafeteria->normal_menu_array[0]->soup,
           cafeteria->normal_menu_array[0]->main_dish,
           cafeteria->normal_menu_array[0]->side_dish,
           cafeteria->normal_menu_array[0]->extra);

    printf("~ ~ ~ ~ Normal menu for the first and last days of the month:\n");
    printf("date--> %s\nsoup--> %s\nmain_dish--> %s\nside_dish--> %s\nextra--> %s\n\n",
           cafeteria->normal_menu_array[j - 1]->date,
           cafeteria->normal_menu_array[j - 1]->soup,
           cafeteria->normal_menu_array[j - 1]->main_dish,
           cafeteria->normal_menu_array[j - 1]->side_dish,
           cafeteria->normal_menu_array[j - 1]->extra);

    printf("~ ~ ~ ~ Vegan menu for the first and last days of the month:\n");
    printf("date--> %s\nsoup--> %s\nmain_dish--> %s\nside_dish--> %s\nextra--> %s\n\n",
           cafeteria->vegan_menu_array[0]->date,
           cafeteria->vegan_menu_array[0]->soup,
           cafeteria->vegan_menu_array[0]->main_dish,
           cafeteria->vegan_menu_array[0]->side_dish,
           cafeteria->vegan_menu_array[0]->extra);

    printf("~ ~ ~ ~ Vegan menu for the first and last days of the month:\n");
    printf("date--> %s\nsoup--> %s\nmain_dish--> %s\nside_dish--> %s\nextra--> %s\n\n",
           cafeteria->vegan_menu_array[k - 1]->date,
           cafeteria->vegan_menu_array[k - 1]->soup,
           cafeteria->vegan_menu_array[k - 1]->main_dish,
           cafeteria->vegan_menu_array[k - 1]->side_dish,
           cafeteria->vegan_menu_array[k - 1]->extra);

    printf("~ ~ ~ ~ Vegetarian menu for the first and last days of the month:\n");
    printf("date--> %s\nsoup--> %s\nmain_dish--> %s\nside_dish--> %s\nextra--> %s\n\n",
           cafeteria->vegetarian_menu_array[0]->date,
           cafeteria->vegetarian_menu_array[0]->soup,
           cafeteria->vegetarian_menu_array[0]->main_dish,
           cafeteria->vegetarian_menu_array[0]->side_dish,
           cafeteria->vegetarian_menu_array[0]->extra);

    printf("~ ~ ~ ~ Vegetarian menu for the first and last days of the month:\n");
    printf("date--> %s\nsoup--> %s\nmain_dish--> %s\nside_dish--> %s\nextra--> %s\n\n",
           cafeteria->vegetarian_menu_array[l - 1]->date,
           cafeteria->vegetarian_menu_array[l - 1]->soup,
           cafeteria->vegetarian_menu_array[l - 1]->main_dish,
           cafeteria->vegetarian_menu_array[l - 1]->side_dish,
           cafeteria->vegetarian_menu_array[l - 1]->extra);

    printf("Example output for normal menu ====> %s | %s | %s | %s | %s\n\n",
           cafeteria->normal_menu_array[2]->date,
           cafeteria->normal_menu_array[2]->soup,
           cafeteria->normal_menu_array[2]->main_dish,
           cafeteria->normal_menu_array[2]->side_dish,
           cafeteria->normal_menu_array[2]->extra);

    printf("Example output for vegan menu ====> %s | %s | %s | %s | %s\n\n",
           cafeteria->vegan_menu_array[7]->date,
           cafeteria->vegan_menu_array[7]->soup,
           cafeteria->vegan_menu_array[7]->main_dish,
           cafeteria->vegan_menu_array[7]->side_dish,
           cafeteria->vegan_menu_array[7]->extra);

    printf("Example output for vegetarian menu ====> %s | %s | %s | %s | %s\n\n",
           cafeteria->vegetarian_menu_array[13]->date,
           cafeteria->vegetarian_menu_array[13]->soup,
           cafeteria->vegetarian_menu_array[13]->main_dish,
           cafeteria->vegetarian_menu_array[13]->side_dish,
           cafeteria->vegetarian_menu_array[13]->extra);

    printf("Counts for the example normal menu output of March 3rd ====> Student:%d, Academic:%d, Administrative:%d\n\n",
           cafeteria->normal_menu_array[2]->sale_count_array.student_count,
           cafeteria->normal_menu_array[2]->sale_count_array.academic_count,
           cafeteria->normal_menu_array[2]->sale_count_array.adminstrative_count);

    printf("Counts for the example vegan menu output of March 10th ====> Student:%d, Academic:%d, Administrative:%d\n\n",
           cafeteria->vegan_menu_array[7]->sale_count_array.student_count,
           cafeteria->vegan_menu_array[7]->sale_count_array.academic_count,
           cafeteria->vegan_menu_array[7]->sale_count_array.adminstrative_count);

    printf("Counts for the example vegetarian menu output of March 20th ====> Student:%d, Academic:%d, Administrative:%d\n\n",
           cafeteria->vegetarian_menu_array[13]->sale_count_array.student_count,
           cafeteria->vegetarian_menu_array[13]->sale_count_array.academic_count,
           cafeteria->vegetarian_menu_array[13]->sale_count_array.adminstrative_count);

    printf("*************** The Sales Results ***************\n\n");
    printf("Normal Menu Sales: %d, Vegan Menu Sales: %d, Vegetarian Menu Sales: %d\n",
           totalNormalMenuSales, totalVeganMenuSales, totalVegetarianMenuSales);
    printf("Student Sales: %d, Academic Sales: %d, Adminstrative Sales: %d\n",
           totalStudentSales, totalAcademicSales, totalAdminstrativeSales);
    printf("Total Sales: %d\n", subtotal);
}

int main()
{

    Cafeteria cafeteria = {NULL, NULL, NULL, NULL};
    initialize_menus(&cafeteria, "cafeteria_march_menu.csv");
    record_customer_counts(&cafeteria);
    calc_and_show_income(&cafeteria);

    return 0;
}
