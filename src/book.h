#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "date.h"
#include "user.h"
#ifndef _BOOK_H_
#define _BOOK_H_
typedef struct BookList
{
    bool isLoan;
    uint32_t loanTime;
    uint32_t expireTime;
    User *loaner;
    struct BookList *nextBook;
    struct BookInfo *bookInfo;
} BookList;
typedef struct BookStatus
{
    uint32_t totCount;
    uint32_t restCount;
    struct BookList *books;
} BookStatus;
typedef struct BookInfo
{
    uint64_t ISBN;
    char *name;
    char *auther;
    struct BookInfo *nextBook;
    struct BookStatus *bookStatus;
} BookInfo;

extern BookInfo *bookInfoHead;
extern uint32_t nowTime;

/*
 *  创建新的书本
 *  如果没有这本书，创建并返回该书的指针
 *  否则返回NULL
 */
BookInfo *createBook(uint64_t ISBN, char *name, char *auther, uint32_t time);
/*
 *  删除指定的书本
 */
void EraseBook(BookInfo *bookInfoPointer);
/*
 *  按照给定的ISBN号码
 *  查找对应的书本
 *  如果找到了，就返回该书本的指针
 *  反之返回找到的书的指针
 */
BookInfo *findBookbyISBN(uint64_t ISBN);
/*
 *  按照给定的书本名称
 *  查找对应的书本
 *  如果找到了，就返回该书本的指针
 *  反之返回NULL
 */
BookInfo *findBookbyName(char *name);
/*
 *  增加书本的数量
 */

void updateBook(BookInfo *book, uint64_t newISBN, char *newName, char *newAuther);
void addBook(BookInfo *book, uint32_t val, uint32_t time);
/*
 *  减少书本数量
 *  如果数量不够或者尚有未归还的，返回成功删除的书本数量
 *  否则返回0
 */
uint32_t deleteBook(BookInfo *book, uint32_t val, uint32_t time);
/*
 *  借阅一本书
 *  如果借阅成功，则返回借阅信息的LoanList*，并修改借阅书本的借阅情况
 *  如果借阅失败，返回NULL
 */
LoanList *borrowBook(BookInfo *book, User *user, uint32_t borrowTime, uint32_t time);
/*
 *  归还一本书
 *  如果归还成功，返回还书的过期时间，未过期则返回0
 *  如果没有借阅信息，返回-1
 */
int returnBook(BookInfo *book, User *user, uint32_t time);
#endif