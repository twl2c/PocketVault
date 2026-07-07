#include "Display.h"
#include <M5Unified.h>


void Display::init()
{
    M5.Display.clear();

    M5.Display.setTextSize(2);
}



void Display::drawMenu(
    const char* title,
    const char* items[],
    int count,
    int selected
)
{
    M5.Display.clear();


    // Заголовок
    M5.Display.setTextSize(1);


    int screenWidth = M5.Display.width();

    int textWidth = M5.Display.textWidth(title);


    int x = (screenWidth - textWidth) / 2;


    M5.Display.setCursor(x, 5);

    M5.Display.println(title);



    // Меню
    M5.Display.setTextSize(2);

    int y = 35;


    for(int i = 0; i < count; i++)
    {
        M5.Display.setCursor(5,y);


        if(i == selected)
        {
            M5.Display.print("> ");
        }
        else
        {
            M5.Display.print("  ");
        }


        M5.Display.println(items[i]);


        y += 25;
    }
}

void Display::showTitle(const char* title)
{
    M5.Display.clear();


    M5.Display.setTextSize(2);


    M5.Display.setCursor(10, 30);


    M5.Display.println(title);
}