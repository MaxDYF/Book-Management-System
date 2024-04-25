#include "book.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
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
BookInfo *findBookbyISBN(BookInfo *bookhead, uint32_t ISBN)
{
    BookInfo *p = bookhead;
    for (; p != NULL; ++p)
        if (p->ISBN == ISBN)
            return p;
    return NULL;
}
BookInfo *findBookbyName(BookInfo *bookhead, char *name)
{
    BookInfo *p = bookhead;
    for (; p != NULL; p = p->nextBook)
        if (strcmp(p->name, name) == 0)
            return p;
    return NULL;
}
BookInfo *createBook(BookInfo *bookhead, uint32_t ISBN, char *name, char *auther)
{
    if (bookhead == NULL)
    {
        bookhead = (BookInfo *)malloc(sizeof(BookInfo));
        strcpy(bookhead->name, name);
        strcpy(bookhead->auther, auther);
        return bookhead;
    }
    BookInfo *tmp = bookhead;
    BookInfo *p = findBookbyISBN(tmp, ISBN);
    if (p == NULL)
    {
        p = bookhead;
        for (; p->nextBook != NULL; p = p->nextBook)
            continue;
        p->nextBook = (BookInfo *)malloc(sizeof(BookInfo));
        p = p->nextBook;
        strcpy(p->name, name);
        strcpy(p->auther, auther);
        p->ISBN = ISBN;
        return p;
    }
    else
        return NULL;
}
void addBook(BookInfo *book, uint32_t val)
{
    book->bookStatus->totCount += val;
    book->bookStatus->restCount += val;
    BookList *p = book->bookStatus->books;
    if (p == NULL)
    {
        book = (BookList *)malloc(sizeof(BookList));
        p = book;
        p->isLoan = false;
        p->bookinfo = book;
        p->nextBook = NULL;
        val--;
    }
    else
    {
        for (; p->nextBook != NULL; p = p->nextBook)
            continue;
    }
    while (val > 0)
    {
        p->nextBook = (BookList *)malloc(sizeof(BookList));
        p = p->nextBook;
        p->isLoan = false;
        p->bookinfo = book;
        p->nextBook = NULL;
        val--;
    }
}
uint32_t deleteBook(BookInfo *book, uint32_t val)
{
    if (book == NULL)
        return 0;
    if (book->bookStatus->restCount < val)
    {
        val = book->bookStatus->restCount;
        book->bookStatus->restCount -= val;
        book->bookStatus->totCount -= val;
    }
    BookList *p = book->bookStatus->books, *pre = NULL, *next = NULL;
    int ans = val;
    while (val > 0 && p != NULL)
    {
        next = p->nextBook;
        if (p->isLoan == false)
        {
            if (pre != NULL)
                pre->nextBook = next;
            else
                book->bookStatus->books = next;
            free(p);
        }
        else
            pre = p;
        p = next;
    }
    return ans;
}