#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "book.h"
#include "file.h"
#include <string.h>
#define CREATE_MSG_LINE 2

#define MAX_CHAR_BUFFER 100
extern BookInfo *bookInfoHead;
extern uint32_t nowTime;
const char *creatBookMsg[CREATE_MSG_LINE] = {"图书管理系统 V1.0.0",
                                             "正在进行：录入新的图书"};

BookInfo *displayInputISBN(char *outputMsg)
{
    BookInfo *bookInfoPointer = NULL;
    bool isFirst = true;
    do
    {
        if (!isFirst)
            system("cls");
        isFirst = false;
        puts(outputMsg);
        uint64_t ISBN;
        scanf("%llu", &ISBN);
        bookInfoPointer = findBookbyISBN(ISBN);
        if (bookInfoPointer == NULL)
        {
            puts("未找到对应ISBN的书籍！请重试。");
            system("pause");
        }

    } while (bookInfoPointer == NULL);
    puts("找到对应ISBN的书籍！");
    return bookInfoPointer;
}
void displayCreateBookMenu(void)
{
    system("cls");
    for (int i = 0; i < CREATE_MSG_LINE; i++)
        puts(creatBookMsg[i]);
    puts("请输入书的名称：");
    char bookName[MAX_CHAR_BUFFER];
    scanf("\n%[^\n]", bookName);

    puts("请输入书的ISBN编码：");
    uint64_t ISBN = 0;
    scanf("%llu", &ISBN);

    puts("请输入书的的作者：");
    char autherName[MAX_CHAR_BUFFER] = "";

    scanf("\n%[^\n]", autherName);
    BookInfo *bookInfoPointer = findBookbyISBN(ISBN);
    if (bookInfoPointer != NULL)
        puts("书本已存在。");
    else
    {
        puts("书本不存在。");
        bookInfoPointer = createBook(ISBN, bookName, autherName, nowTime);
    }
    puts("输入添加的数量：");
    uint32_t bookCount = 0;
    scanf("%d", &bookCount);
    addBook(bookInfoPointer, bookCount, nowTime);
    writeCreateBook(ISBN, bookName, autherName);
    writeAddBook(ISBN, bookCount);
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
        displayBookManageMenu();
        break;
    case 3:
        displayBorrowBookMenu();
        break;
    case 4:
        displayReturnBookMenu();
        break;
    case 5:
        displayEraseBorrowRecordMenu();
        break;
    case 6:
        exit(0);
        break;
    default:
        break;
    }
}

void displayBookInfo(BookInfo *bookInfoPointer)
{
    printf("书籍名称：%s;\n", bookInfoPointer->name);
    printf("书籍作者：%s;\n", bookInfoPointer->auther);
    printf("总共拥有的书籍数量：%d本;\n", bookInfoPointer->bookStatus->totCount);
    printf("未借出的书籍数量：%d本。\n", bookInfoPointer->bookStatus->restCount);
}
void displayUserInfo(User *user)
{
    printf("借阅人学号: %d\n", user->uid);
    printf("借阅人姓名: %s\n", user->name);
}
void displayBookListInfo(BookList *bookList)
{
    printf("借阅时间: %s\n", timeToString(getDatefromTime(bookList->loanTime)));
    printf("到期时间: %s\n", timeToString(getDatefromTime(bookList->expireTime)));
    printf("是否超期：%s\n", (bookList->expireTime < nowTime ? "是" : "否"));
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
    BookInfo *bookInfoPointer = displayInputISBN("请输入要查询的书本ISBN号码：");
    displayBookInfo(bookInfoPointer);
    puts("借阅信息详情：");
    BookList *p = bookInfoPointer->bookStatus->books;
    for (int cnt = 0; p != NULL; p = p->nextBook)
    {
        if (p->isLoan == false)
            continue;
        printf("#%d\n", ++cnt);
        displayUserInfo(p->loaner);
        displayBookListInfo(p);
        puts("");
    }
    system("pause");
}
void displayBookModifyMenu(void)
{
    system("cls");
    BookInfo *bookInfoPointer = displayInputISBN("请输入您要更改信息的书籍的ISBN编号：");
    displayBookInfo(bookInfoPointer);
    puts("请选择要更改的信息：");
    puts("1. ISBN");
    puts("2. 书籍名称");
    puts("3. 书籍作者");
    int opt;
    scanf("%d", &opt);
    switch (opt)
    {
    case 1:
        puts("请输入新的ISBN编码：");
        uint64_t ISBN, originISBN = bookInfoPointer->ISBN;
        scanf("%llu", &ISBN);
        bookInfoPointer->ISBN = ISBN;
        printf("成功更改！原ISBN编码为%llu，新ISBN编码为%llu。\n", originISBN, ISBN);
        writeUpdateBook(originISBN, ISBN, bookInfoPointer->name, bookInfoPointer->auther);
        system("pause");
        return;
        break;
    case 2:
        puts("请输入新的书籍名称：");
        char bookName[MAX_CHAR_BUFFER], originBookName[MAX_CHAR_BUFFER];
        strcpy(originBookName, bookInfoPointer->name);
        getchar();
        scanf("%[^\n]", bookName);
        strcpy(bookInfoPointer->name, bookName);
        printf("成功更改！原书名为%s，新作者名为%s。\n", originBookName, bookName);
        writeUpdateBook(bookInfoPointer->ISBN, bookInfoPointer->ISBN, bookName, bookInfoPointer->auther);
        system("pause");
        return;
        break;
    case 3:
        puts("请输入新的作者名称：");
        char autherName[MAX_CHAR_BUFFER], originAutherName[MAX_CHAR_BUFFER];
        strcpy(originAutherName, bookInfoPointer->auther);
        getchar();
        scanf("%[^\n]", autherName);
        strcpy(bookInfoPointer->auther, autherName);
        printf("成功更改！原作者名为%s，新作者名为%s。\n", originAutherName, autherName);
        writeUpdateBook(bookInfoPointer->ISBN, bookInfoPointer->ISBN, bookInfoPointer->name, autherName);
        system("pause");
        return;
        break;
    default:
        break;
    }
}
void displayBookDeleteMenu(void)
{
    system("cls");
    BookInfo *bookInfoPointer = displayInputISBN("请输入您要删除书本的ISBN编号。");
    displayBookInfo(bookInfoPointer);
    puts("确认删除这本书的信息？(y/n)");
    char ch;
    scanf("\n%c", &ch);
    if (ch == 'y')
    {
        EraseBook(bookInfoPointer);
        puts("已删除书籍！");
        writeEraseBook(bookInfoPointer->ISBN);
        system("pause");
        return;
    }
    else
    {
        puts("取消删除，正在返回...");
        system("pause");
        return;
    }
}

void displayBorrowBookMenu(void)
{
    system("cls");
    puts("请输入借阅人学号：");
    uint32_t uid;
    scanf("%u", &uid);
    User *userPointer = findUserbyUID(uid);
    if (userPointer == NULL)
    {
        puts("没有该同学的信息，请输入姓名：");
        char userName[MAX_CHAR_BUFFER];
        getchar();
        scanf("%[^\n]", userName);
        userPointer = createUser(uid, userName);
        writeCreateUser(uid, userName);
        puts("成功创建！");
    }
    BookInfo *bookInfoPointer = displayInputISBN("请输入您要借阅的书籍的ISBN号：");
    if (findLoan(userPointer, bookInfoPointer->ISBN) != NULL)
    {
        puts("您已借阅过这本书，请勿重复借阅！");
        system("pause");
        return;
    }
    displayBookInfo(bookInfoPointer);
    BookStatus *status = bookInfoPointer->bookStatus;
    puts("请输入要借阅的时间（单位：天）：");
    uint32_t times;
    scanf("%u", &times);
    LoanList *loanPointer = borrowBook(bookInfoPointer, userPointer, times, nowTime);
    if (loanPointer != NULL)
    {
        puts("借阅成功！");
        writeBorrowBook(bookInfoPointer->ISBN, uid, times);
        printf("借阅书籍：%s\n", loanPointer->bookList->bookInfo->name);
        printf("借阅时间：%s\n", timeToString(getDatefromTime(nowTime)));
        printf("到期时间：%s\n", timeToString(getDatefromTime(loanPointer->bookList->expireTime)));
        system("pause");
        return;
    }
    else
    {
        puts("借阅失败！书籍余量不足。");
        return;
    }
}
void displayReturnBookMenu(void)
{
    system("cls");
    puts("请输入借阅人学号：");
    uint32_t uid;
    scanf("%u", &uid);
    User *userPointer = findUserbyUID(uid);
    if (userPointer == NULL)
    {
        puts("没有该同学的信息！请检查后重试！");
        return;
    }
    BookInfo *bookInfoPointer = displayInputISBN("请输入您要归还的书籍的ISBN编号：");
    int returnCode = returnBook(bookInfoPointer, userPointer, nowTime);
    if (returnCode == -1)
    {
        puts("归还失败！没有对应的借阅信息！");
    }
    else if (returnCode == 0)
    {
        puts("归还成功！书籍按时归还！");
        writeReturnBook(bookInfoPointer->ISBN, uid, nowTime);
    }
    else
    {
        printf("归还成功！超期%u天归还书籍！\n", returnCode);
        writeReturnBook(bookInfoPointer->ISBN, uid, nowTime);
    }
    system("pause");
}
void displayEraseBorrowRecordMenu(void)
{
    system("cls");
    puts("请输入借阅人学号：");
    uint32_t uid;
    scanf("%u", &uid);
    User *userPointer = findUserbyUID(uid);
    if (userPointer == NULL)
    {
        puts("没有该同学的信息！请检查后重试！");
        return;
    }
    BookInfo *bookInfoPointer = displayInputISBN("请输入您要删除用户书籍的ISBN编号：");
    int returnCode = returnBook(bookInfoPointer, userPointer, nowTime);
    if (returnCode != -1)
    {
        puts("删除成功！");
        system("pause");
    }
    else
    {
        puts("删除失败！");
        system("pause");
    }
}