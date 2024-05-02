#include "book.h"
#include <stdlib.h>
#include <string.h>
BookInfo *bookInfoHead = NULL;
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
        book->bookStatus->books = (BookList *)malloc(sizeof(BookList));
        p = book->bookStatus->books;
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
bool borrowBook(BookInfo *book, Date time, User *user, uint32_t borrowTime)
{
    if (book->bookStatus == NULL)
        return true;
    BookStatus *bookStatusPointer = book->bookStatus;
    if (bookStatusPointer->totCount <= bookStatusPointer->restCount) // 没有空余的书
        return true;
    BookList *bookListPointer = bookStatusPointer->books;
    if (bookListPointer == NULL)
        return true;
    LoanList *userBorrowPointer = user->loanlist;
    for (; userBorrowPointer->nextLoan != NULL; userBorrowPointer = userBorrowPointer->nextLoan)
        continue;
    for (; bookListPointer != NULL; bookListPointer = bookListPointer->nextBook)
    {
        if (bookListPointer->isLoan == false)
        {
            bookListPointer->isLoan = true;
            uint32_t t = getTimefromDate(time);
            bookListPointer->loanTime = t;
            bookListPointer->expireTime = t + borrowTime;
            userBorrowPointer->nextLoan = malloc(sizeof(LoanList));
            userBorrowPointer = userBorrowPointer->nextLoan;
            userBorrowPointer->book = bookListPointer;
            return false;
        }
    }
    return true;
}
int returnBook(BookInfo *book, Date time, User *user)
{
    LoanList *loanListPointer = user->loanlist, *lstPointer = NULL;
    for (; loanListPointer != NULL; loanListPointer = loanListPointer->nextLoan)
    {
        if (loanListPointer->book->bookinfo == book)
        {
            BookList *p = loanListPointer->book;
            p->isLoan = false;
            uint32_t endOfExpireTime = p->expireTime;
            uint32_t returnTime = getTimefromDate(time);
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