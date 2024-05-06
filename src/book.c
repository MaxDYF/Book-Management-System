#include "book.h"
#include <stdlib.h>
#include <string.h>
BookInfo *bookInfoHead = NULL;
extern Date nowTime;
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
BookInfo *createBook(uint64_t ISBN, char *name, char *auther)
{
    if (bookInfoHead == NULL)
    {
        bookInfoHead = (BookInfo *)malloc(sizeof(BookInfo));
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
        p = (BookInfo *)malloc(sizeof(BookInfo));
        p->nextBook = bookInfoHead->nextBook;
        p->name = name;
        p->auther = auther;
        p->ISBN = ISBN;
        p->bookStatus = (BookStatus *)malloc(sizeof(BookStatus));
        memset(p->bookStatus, 0, sizeof(BookStatus));
        bookInfoHead->nextBook = p;
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
        book->bookStatus->books = (BookList *)malloc(sizeof(BookList));
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
        p->nextBook = (BookList *)malloc(sizeof(BookList));
        p = p->nextBook;
        p->isLoan = false;
        p->bookInfo = book;
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
LoanList *borrowBook(BookInfo *book, User *user, uint32_t borrowTime)
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
            uint32_t t = getTimefromDate(nowTime);
            bookListPointer->loanTime = t;
            bookListPointer->expireTime = t + borrowTime;
            bookListPointer->loaner = user;
            userBorrowPointer = (LoanList *)malloc(sizeof(LoanList));
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
int returnBook(BookInfo *book, User *user)
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
            uint32_t returnTime = getTimefromDate(nowTime);
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