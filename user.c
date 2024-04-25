#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include "book.h"
#include "user.h"
typedef struct LoanList
{
    struct BookList *book;
    LoanList *nextLoan;
} LoanList;
typedef struct User
{
    uint32_t uid;
    char *name;
    LoanList *loanlist;
} User;
/*
 *  创建新用户
 *  如果用户不存在则返回false
 *  反之则不创建，返回true
 */
bool createUser(uint32_t uid, char *name);