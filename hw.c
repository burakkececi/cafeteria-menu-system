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

/*
including three other types of struct and the name of the month for the given menu.
Cafeteria:
- Name of the month (initially unallocated and NULL)
- Pointer for the normal menu array (initially unallocated and NULL)
- Pointer for the vegan menu array (initially unallocated and NULL)
- Pointer for the vegetarian menu array (initially unallocated and NULL)
*/

typedef struct
{

    char *month;
    Menu *normal_menu;
    Menu *vegan_menu;
    Menu *vegetarian_menu;

} Cafeteria;

Cafeteria cafeteria = {NULL, NULL, NULL, NULL};


/*
* not ok!
*/
void setMenu(char **data, Menu **menu_list, char *type)
{

    Menu *menu_ptr;
    
    char menu_type[10];
    char date[32], soup[64], main_dish[64], side_dish[64], extra[64];

    int index = 0, j=0;
    while (index != MAX_FIELD_LENGTH)
    {
        sscanf(data[index], "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", menu_type, date, soup, main_dish, side_dish,extra);


        if (strcmp(menu_type, type) == 0)
        {
            menu_list[j] = malloc(sizeof(Menu));
            menu_ptr = &*menu_list[j];
            menu_ptr->date = date;
            menu_ptr->soup = soup;
            menu_ptr->main_dish = main_dish;
            menu_ptr->side_dish = side_dish;
            menu_ptr->extra = extra;         
            j++;
        }

        index++;
    }
}

int main()
{

    // header();
    // systemInfo();

    // initialize data array
    char **data = (char **)malloc((MAX_FIELD_LENGTH) * sizeof(char *));
    // read files
    readCSV("cafeteria_march_menu.csv", data);
    // printf("%s", data[2]);
    vegan_menu_list = malloc(MAX_FIELD_LENGTH * sizeof(Menu));
    setMenu(data, vegan_menu_list, "\"Vegan\"");

    return 0;
}