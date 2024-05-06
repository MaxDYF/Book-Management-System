#include "book.h"
#include <stdlib.h>
#include <string.h>
BookInfo *bookInfoHead = NULL;

extern uint32_t nowTime;
BookInfo *findBookbyISBN(uint64_t ISBN)
{
    BookInfo *p = bookInfoHead;
    for (; p != NULL; p = p->nextBook)
        if (p->ISBN == ISBN)
            return p;
    return NULL;
}
BookInfo *findBookbyName(char *name)
{
    BookInfo *p = bookInfoHead;
    for (; p != NULL; p = p->nextBook)
        if (strcmp(p->name, name) == 0)
            return p;
    return NULL;
}
void updateBook(BookInfo *book, uint64_t newISBN, char *newName, char *newAuther)
{
    book->ISBN = newISBN;
    strcpy(book->name, newName);
    strcpy(book->auther, newAuther);
}
BookInfo *createBook(uint64_t ISBN, char *name, char *auther, uint32_t time)
{
    if (bookInfoHead == NULL)
    {
        bookInfoHead = (BookInfo *)calloc(1, sizeof(BookInfo));
        bookInfoHead->name = (char *)malloc(sizeof(char) * strlen(name));
        strcpy(bookInfoHead->name, name);
        bookInfoHead->auther = (char *)malloc(sizeof(char) * strlen(auther));
        strcpy(bookInfoHead->auther, auther);
        bookInfoHead->ISBN = ISBN;
        bookInfoHead->bookStatus = (BookStatus *)malloc(sizeof(BookStatus));
        memset(bookInfoHead->bookStatus, 0, sizeof(BookStatus));
        bookInfoHead->nextBook = NULL;
        return bookInfoHead;
    }
    BookInfo *p = findBookbyISBN(ISBN);
    if (p == NULL)
    {
        p = (BookInfo *)calloc(1, sizeof(BookInfo));
        p->nextBook = bookInfoHead->nextBook;
        p->name = (char *)malloc(sizeof(char) * strlen(name));
        strcpy(p->name, name);
        p->auther = (char *)malloc(sizeof(char) * strlen(auther));
        strcpy(p->auther, auther);
        p->ISBN = ISBN;
        p->bookStatus = (BookStatus *)calloc(1, sizeof(BookStatus));
        memset(p->bookStatus, 0, sizeof(BookStatus));
        bookInfoHead->nextBook = p;
        return p;
    }
    else
        return NULL;
}
void EraseBook(BookInfo *bookInfoPointer)
{
    if (bookInfoPointer == bookInfoHead)
    {
        bookInfoHead = bookInfoHead->nextBook;
        free(bookInfoPointer);
    }
    else
    {
        BookInfo *p = bookInfoHead;
        for (; p->nextBook != bookInfoPointer; p = p->nextBook)
            continue;
        p->nextBook = bookInfoPointer->nextBook;
        free(bookInfoPointer);
    }
}
void addBook(BookInfo *book, uint32_t val, uint32_t time)
{
    book->bookStatus->totCount += val;
    book->bookStatus->restCount += val;
    BookList *p = book->bookStatus->books;
    if (p == NULL)
    {
        book->bookStatus->books = (BookList *)calloc(1, sizeof(BookList));
        p = book->bookStatus->books;
        p->isLoan = false;
        p->bookInfo = book;
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
        p->nextBook = (BookList *)calloc(1, sizeof(BookList));
        p = p->nextBook;
        p->isLoan = false;
        p->bookInfo = book;
        p->nextBook = NULL;
        val--;
    }
}
uint32_t deleteBook(BookInfo *book, uint32_t val, uint32_t time)
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
LoanList *borrowBook(BookInfo *book, User *user, uint32_t borrowTime, uint32_t time)
{
    if (book->bookStatus == NULL)
        return NULL;
    BookStatus *bookStatusPointer = book->bookStatus;
    if (bookStatusPointer->restCount <= 0) // 没有空余的书
        return NULL;
    BookList *bookListPointer = bookStatusPointer->books;
    if (bookListPointer == NULL)
        return NULL;
    LoanList *userBorrowPointer = NULL;
    for (; bookListPointer != NULL; bookListPointer = bookListPointer->nextBook)
    {
        if (bookListPointer->isLoan == false)
        {
            bookStatusPointer->restCount--;
            bookListPointer->isLoan = true;
            uint32_t t = time;
            bookListPointer->loanTime = t;
            bookListPointer->expireTime = t + borrowTime;
            bookListPointer->loaner = user;
            userBorrowPointer = (LoanList *)calloc(1, sizeof(LoanList));
            userBorrowPointer->bookList = bookListPointer;
            if (user->loanlist == NULL)
            {
                user->loanlist = userBorrowPointer;
                userBorrowPointer->nextLoan = NULL;
            }
            else
            {
                userBorrowPointer->nextLoan = user->loanlist;
                user->loanlist = userBorrowPointer;
            }
            return userBorrowPointer;
        }
    }
    return NULL;
}
int returnBook(BookInfo *book, User *user, uint32_t time)
{
    LoanList *loanListPointer = user->loanlist, *lstPointer = NULL;
    for (; loanListPointer != NULL; loanListPointer = loanListPointer->nextLoan)
    {
        if (loanListPointer->bookList->bookInfo == book)
        {
            BookList *p = loanListPointer->bookList;
            book->bookStatus->restCount++;
            p->isLoan = false;
            uint32_t endOfExpireTime = p->expireTime;
            uint32_t returnTime = time;
            if (lstPointer == NULL)
                user->loanlist = loanListPointer->nextLoan;
            else
                lstPointer->nextLoan = loanListPointer->nextLoan;
            free(loanListPointer);
            if (returnTime <= endOfExpireTime)
                return 0;
            else
                return returnTime - endOfExpireTime;
        }
        lstPointer = loanListPointer;
    }
    return -1;
}