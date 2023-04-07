/*
 *
 * Cafeteria Menu System Version 1.0
 * Author: Burak Keçeci - 290201103 & Berkan Gönülsever 270201064
 *
 */

#include <stdio.h>
#include <regex.h>
#include "file_reader.h"
#include "display.h"

#define MAX_FIELD_LENGTH 69
#define MAX_WORD_LENGTH 64
typedef struct
{
    char *date;              //  The day and the month need to be held as strings
    char *soup;              //  The name of the soup.
    char *main_dish;         //  The name of the main dish.
    char *side_dish;         //  The name of the side dish.
    char *extra;             //  Name any extra contents in the menu such as “salad”, “fruit”, etc.
    int sale_count_array[3]; //  An array with three elements that looks like [‘student_count’, ‘academic_count’, ‘administrative_count’].
} Menu;

Menu **normal_menu_list = NULL;
Menu **vegan_menu_list = NULL;
Menu **vegetarian_menu_list = NULL;

typedef struct
{

    char *month;
    Menu *normal_menu;
    Menu *vegan_menu;
    Menu *vegetarian_menu;

} Cafeteria;

Cafeteria cafeteria = {NULL, NULL, NULL, NULL};


/*
* set data to related menu.
* @param **data contains lines of data that occurs on csv.
* @param **menu_list represents one of the menu list struct.
* @param *type that defines one of the menu list with regex [\"^\"]
*/
void setMenu(char **data, Menu **menu_list, char *type)
{

    Menu *menu_ptr;
    
    char menu_type[10];
    char date[32], soup[64], main_dish[64], side_dish[64], extra[64];

    int index = 0, j=0;
    while (index != MAX_FIELD_LENGTH && data[index] != NULL)
    {
        sscanf(data[index], "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", menu_type, date, soup, main_dish, side_dish,extra);


        if (strcmp(menu_type, type) == 0)
        {
            menu_list[j] = (Menu*) malloc(sizeof(Menu));
            if (menu_list[j] == NULL) {
                // malloc failed to allocate memory, handle error
                printf("Error: memory allocation failed\n");
                return;
            }

            menu_list[j]->date = strdup(date);
            menu_list[j]->soup = strdup(soup);
            menu_list[j]->main_dish = strdup(main_dish);
            menu_list[j]->side_dish = strdup(side_dish);
            menu_list[j]->extra = strdup(extra);     
            j++;
        }
        index++;
    }
}

void init(){

    char **data = (char **)malloc((MAX_FIELD_LENGTH) * sizeof(char *));
    readCSV("cafeteria_march_menu.csv", data);

    normal_menu_list = (Menu **)malloc((MAX_FIELD_LENGTH) * sizeof(Menu));
    vegan_menu_list = (Menu **)malloc((MAX_FIELD_LENGTH) * sizeof(Menu));
    vegetarian_menu_list = (Menu **)malloc((MAX_FIELD_LENGTH) * sizeof(Menu));
    setMenu(data, normal_menu_list, "\"Vegan\"");
    setMenu(data, vegan_menu_list, "\"Vegan\"");
    setMenu(data, vegetarian_menu_list, "\"Vegan\"");
}

int main()
{

    // header();
    // systemInfo();    
    
    init();
    printf("%s", vegetarian_menu_list[0]->date);
    return 0;
}