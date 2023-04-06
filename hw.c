/*
*
* Cafeteria Menu System Version 1.0
* Author: Burak Keçeci - 290201103 & Berkan Gönülsever 270201064
* 
*/

#include <stdio.h>
#include "file_reader.h"
#include "display.h"

#define MAX_FIELD_LENGTH 70

typedef struct
{
    char* date; //  The day and the month need to be held as strings
    char* soup; //  The name of the soup.
    char* main_dish; //  The name of the main dish.
    char* side_dish; //  The name of the side dish.
    char* extra; //  Name any extra contents in the menu such as “salad”, “fruit”, etc.
    int sale_count_array[3]; //  An array with three elements that looks like [‘student_count’, ‘academic_count’, ‘administrative_count’]. 
}NormalMenu, VeganMenu, VegetarianMenu;

/*
including three other types of struct and the name of the month for the given menu. 
Cafeteria: 
- Name of the month (initially unallocated and NULL)
- Pointer for the normal menu array (initially unallocated and NULL)
- Pointer for the vegan menu array (initially unallocated and NULL)
- Pointer for the vegetarian menu array (initially unallocated and NULL)
*/

typedef struct {

    char* month;
    NormalMenu* normal_menu;
    VeganMenu* vegan_menu;
    VegetarianMenu* vegetarian_menu;

}Cafeteria;

/*
* Initialize the global cafeteria struct, including the menu structs as well. 
*/

void init(){
    NormalMenu normal_menu = {NULL,NULL,NULL,NULL,NULL,0};
    VeganMenu vegan_menu = {NULL,NULL,NULL,NULL,NULL,0};
    VegetarianMenu vegeterian_menu = {NULL,NULL,NULL,NULL,NULL,0};
    Cafeteria cafeteria = {NULL,NULL,NULL,NULL};
    
}



int main() {

    //header();
    init();
    //systemInfo();
    
    // initialize data array
     char** data = (char**) malloc((MAX_FIELD_LENGTH) * sizeof(char*));
    // read files
    readCSV("cafeteria_march_menu.csv", data);
    printf("%s", data[2]);



    
    return 0;
}