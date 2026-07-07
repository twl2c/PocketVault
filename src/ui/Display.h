#pragma once


class Display
{

public:

    void init();


    void drawMenu(
        const char* title,
        const char* items[],
        int count,
        int selected
    );


    void showTitle(const char* title);

};