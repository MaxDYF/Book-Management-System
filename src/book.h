#include <stdint.h>
#include <stdbool.h>
#include "time.h"
#include "user.h"
#ifndef _BOOK_H_
#define _BOOK_H_
typedef struct BookList
{
    bool isLoan;
    uint32_t loanTime;
    uint32_t expireTime;
    uint32_t loanUID;
    struct BookList *nextBook;
    struct BookInfo *bookinfo;
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
/*
 *  创建新的书本
 *  如果没有这本书，创建并返回该书的指针
 *  否则返回NULL
 */
BookInfo *createBook(BookInfo *bookhead, uint32_t ISBN, char *name, char *auther);
/*
 *  按照给定的ISBN号码
 *  查找对应的书本
 *  如果找到了，就返回该书本的指针
 *  反之返回找到的书的指针
 */
BookInfo *findBookbyISBN(BookInfo *bookhead, uint32_t ISBN);
/*
 *  按照给定的书本名称
 *  查找对应的书本
 *  如果找到了，就返回该书本的指针
 *  反之返回NULL
 */
BookInfo *findBookbyName(BookInfo *bookhead, char *name);
/*
 *  增加书本的数量
 */

void addBook(BookInfo *book, uint32_t val);
/*
 *  减少书本数量
 *  如果数量不够或者尚有未归还的，返回成功删除的书本数量
 *  否则返回0
 */
uint32_t deleteBook(BookInfo *book, uint32_t val);
/*
 *  借阅一本书
 *  如果借阅成功，则返回false，并修改借阅书本的借阅情况
 *  如果借阅失败，返回true
 */
bool borrowBook(BookInfo *book, Date time, User *user, uint32_t borrowTime);
/*
 *  归还一本书
 *  如果归还成功，返回还书的过期时间，未过期则返回0
 *  如果没有借阅信息，返回-1
 */
int returnBook(BookInfo *book, Date time, User *user);
#endif