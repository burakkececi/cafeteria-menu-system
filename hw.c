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
    int student_count;
    int academic_count;
    int adminstrative_count;
} Customer;

typedef struct
{
    char *date;                  //  The day and the month need to be held as strings
    char *soup;                  //  The name of the soup.
    char *main_dish;             //  The name of the main dish.
    char *side_dish;             //  The name of the side dish.
    char *extra;                 //  Name any extra contents in the menu such as “salad”, “fruit”, etc.
    Customer sale_count_array; //  An array with three elements that looks like [‘student_count’, ‘academic_count’, ‘administrative_count’].
} Menu;

typedef struct
{

    char *month;
    Menu **normal_menu_array;
    Menu **vegan_menu_array;
    Menu **vegetarian_menu_array;

} Cafeteria;

void initialize_menus(Cafeteria *cafeteria, char *csv_file_name)
{
    FILE *fp = fopen(csv_file_name, "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(0);
    }

    char line[MAX_LINE_LENGTH];
    char *token;
    int index = 0, count_normal = 0, count_vegan = 0, count_vegetarian = 0;

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

    cafeteria->normal_menu_array = malloc(count_normal * sizeof(Menu));
    cafeteria->vegan_menu_array = malloc(count_vegan * sizeof(Menu));
    cafeteria->vegetarian_menu_array = malloc(count_vegetarian * sizeof(Menu));

    char menu_type[10];
    char date[32], soup[64], main_dish[64], side_dish[64], extra[64];
    int j = 0, k = 0, l = 0;
    index = 0;
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", menu_type, date, soup, main_dish, side_dish, extra);
        if (strcmp(menu_type, "\"Normal\"") == 0)
        {
            cafeteria->normal_menu_array[j] = (Menu *)malloc(sizeof(Menu));
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
            cafeteria->vegan_menu_array[k] = (Menu *)malloc(sizeof(Menu));
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
            cafeteria->vegetarian_menu_array[l] = (Menu *)malloc(sizeof(Menu));
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
    srand(time(NULL));
    return (rand() % max) + min;
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

}

int main()
{

    Cafeteria cafeteria = {NULL, NULL, NULL, NULL};
    initialize_menus(&cafeteria, "cafeteria_march_menu.csv");
    record_customer_counts(&cafeteria);
    
    return 0;
}