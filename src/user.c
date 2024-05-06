#include "user.h"
#include <stdlib.h>
#include <string.h>
#include "book.h"
User *headUser;
User *createUser(uint32_t uid, char *name)
{
    if (headUser == NULL)
    {
        headUser = (User *)calloc(1, sizeof(User));
        headUser->name = (char *)calloc(strlen(name), sizeof(char));
        headUser->loanlist = NULL;
        headUser->nextUser = NULL;
        strcpy(headUser->name, name);
        headUser->uid = uid;
        return headUser;
    }
    User *tempP = findUserbyUID(uid);
    if (tempP != NULL)
        return tempP;
    User *newUser = (User *)calloc(1, sizeof(User));
    newUser->name = (char *)calloc(strlen(name), sizeof(char));
    strcpy(newUser->name, name);
    newUser->uid = uid;
    newUser->nextUser = headUser;
    headUser = newUser;
}
User *findUserbyUID(uint32_t uid)
{
    User *userPointer = headUser;
    for (; userPointer != NULL; userPointer = userPointer->nextUser)
        if (userPointer->uid == uid)
            return userPointer;
    return NULL;
}
LoanList *findLoan(User *user, uint64_t ISBN)
{
    LoanList *loanListPointer = user->loanlist;
    for (; loanListPointer != NULL; loanListPointer = loanListPointer->nextLoan)
    {
        if (loanListPointer->bookList->bookInfo->ISBN == ISBN)
            return loanListPointer;
    }
    return NULL;
}