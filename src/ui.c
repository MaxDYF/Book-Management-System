#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "book.h"

#define CREATE_MSG_LINE 2
const char *creatBookMsg[CREATE_MSG_LINE] = {"图书管理系统 V1.0.0",
                                             "正在进行：录入新的图书"};

#define MAX_CHAR_BUFFER 100
void displayCreateBookMenu(void)
{
    system("cls");
    for (int i = 0; i < CREATE_MSG_LINE; i++)
        puts(creatBookMsg[i]);
    puts("请输入书的名称：");
    char bookName[MAX_CHAR_BUFFER];
    getchar();
    fgets(bookName, MAX_CHAR_BUFFER, stdin);

    puts("请输入书的ISBN编码：");
    uint64_t ISBN = 0;
    scanf("%llu", &ISBN);

    puts("请输入书的的作者：");
    char autherName[MAX_CHAR_BUFFER];
    getchar();
    fgets(autherName, MAX_CHAR_BUFFER, stdin);

    BookInfo *bookInfoPointer = findBookbyISBN(bookInfoHead, ISBN);
    if (bookInfoHead != NULL)
        puts("书本已存在。");
    else
    {
        puts("书本不存在。");
        bookInfoPointer = createBook(bookInfoHead, ISBN, bookName, autherName);
    }
    puts("输入添加的数量：");
    uint32_t bookCount = 0;
    scanf("%d", &bookCount);
    addBook(bookInfoPointer, bookCount);
    puts("录入完毕，返回主菜单。");
    system("pause");
}

#define MAIN_MSG_LINE 8
const char *mainMsg[MAIN_MSG_LINE] = {"图书管理系统 V1.0.0",
                                      "请输入您要进行的操作：",
                                      "1. 录入新的图书。",
                                      "2. 图书信息的查询修改与删除。",
                                      "3. 办理借书手续。",
                                      "4. 办理还书手续。",
                                      "5. 删除借阅信息。",
                                      "6. 退出系统。"};

void displayMainMenu(void)
{
    system("cls");
    for (int i = 0; i < MAIN_MSG_LINE; i++)
        puts(mainMsg[i]);
    int inputInt = 0;
    scanf("%d", &inputInt);
    switch (inputInt)
    {
    case 1:
        displayCreateBookMenu();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        exit(0);
        break;
    default:
        break;
    }
}

#define BOOK_MNG_MSG_LINE 5
const char *bookManageMsg[BOOK_MNG_MSG_LINE] = {"图书管理系统 V1.0.0",
                                                "请输入您要进行的操作：",
                                                "1. 图书信息的查询。",
                                                "2. 图书信息的修改。",
                                                "3. 图书信息的删除。"};
void displayBookManageMenu(void)
{
    system("cls");
    for (int i = 0; i < BOOK_MNG_MSG_LINE; i++)
        puts(bookManageMsg[i]);
    int opt = 0;
    scanf("%d", &opt);
    switch (opt)
    {
    case 1:
        displayBookQueryMenu();
        break;
    case 2:
        displayBookModifyMenu();
        break;
    case 3:
        displayBookDeleteMenu();
        break;
    default:
        break;
    }
}
void displayBookQueryMenu(void)
{
    system("cls");
    puts("请输入要查询的书本ISBN号码：");
    uint32_t ISBN = 0;
    scanf("%llu", &ISBN);
    BookInfo *bookInfoPointer = findBookbyISBN(bookInfoHead, ISBN);
    if (bookInfoPointer == NULL)
    {
        puts("找不到这本书，返回主菜单。");
        return;
    }
    else
    {
    }
}