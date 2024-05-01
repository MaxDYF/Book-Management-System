#include "user.h"
User *createUser(User *headUser, uint32_t uid, char *name)
{
    if (headUser == NULL)
    {
        headUser = (User *)malloc(sizeof(User));
        headUser->loanlist = NULL;
        strcpy(headUser->name, name);
        headUser->uid = uid;
        return headUser;
    }
    User *p = headUser, *lst = NULL;
    for (; p != NULL; p = p->nextUser)
    {
        if (p->uid == uid)
        {
            if (strcmp(p->name, name) == 0)
                return p;
            else
                return NULL;
        }
        lst = p;
    }
    if (lst == NULL)
        p = headUser;
    else
        p = lst;
    p->nextUser = (User *)(malloc(sizeof(User)));
    p = p->nextUser;
    strcpy(p->name, name);
    p->uid = uid;
    return p;
}