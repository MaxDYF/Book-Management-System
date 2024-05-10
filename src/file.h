#include <stdint.h>
#ifndef _FILE_H_
#define _FILE_H_
void writeCreateUser(uint32_t uid, char *name);
// void writeRemoveUser(uint32_t uid, char *name);
void writeCreateBook(uint64_t ISBN, char *name, char *auther);
void writeEraseBook(uint64_t ISBN);
void writeAddBook(uint64_t ISBN, uint32_t val);
void writeDelBook(uint64_t ISBN, uint32_t val);
void writeBorrowBook(uint64_t ISBN, uint32_t uid, uint32_t borrowTime);
void writeReturnBook(uint64_t ISBN, uint32_t uid, uint32_t returnTime);
void writeUpdateBook(uint64_t ISBN, uint64_t newISBN, char *newName, char *newAuther);
void readInit();
#endif