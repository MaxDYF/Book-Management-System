#include <stdint.h>
#include "book.h"
typedef struct LoanList;
typedef struct User;
/*
 *  创建新用户
 *  如果用户不存在则返回false
 *  反之则不创建，返回true
 */
bool createUser(uint32_t uid, char *name);