#include "ui.h"
#include "book.h"
#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define CODE_PAGE 65001
int main()
{
    // system("chcp 65001");
    timeInit();
    SetConsoleCP(CODE_PAGE);
    SetConsoleOutputCP(CODE_PAGE);
    while (true)
        displayMainMenu();
    system("pause");
    return 0;
}