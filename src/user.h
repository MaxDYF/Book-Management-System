#include <stdint.h>
#include "book.h"
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
    User *nextUser;
} User;
/*
 *  创建新用户
 *  如果用户不存在则返回创建后的用户指针
 *  反之则不创建，返回指针
 *  如果创建的uid和原有的用户有冲突，则直接返回NULL，不创建新用户
 */
User *createUser(User *headUser, uint32_t uid, char *name);