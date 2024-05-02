#include "ui.h"
#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
int main()
{
    SetConsoleOutputCP(65001);
    while (true)
        displayMainMenu();
    system("pause");
    return 0;
}