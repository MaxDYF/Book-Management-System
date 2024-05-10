#include <stdint.h>
#include <stdio.h>
#include "date.h"
#include "book.h"
#include "user.h"
extern uint32_t nowTime;
const char *fileName = "data.txt";
void writeCreateUser(uint32_t uid, char *name)
{
    FILE *out = fopen(fileName, "a");
    fprintf(out, "%u N %u %s;\n", nowTime, uid, name);
    fclose(out);
}
// void writeRemoveUser(uint32_t uid, char *name);
void writeCreateBook(uint64_t ISBN, char *name, char *auther)
{
    FILE *out = fopen(fileName, "a");
    fprintf(out, "%u C %llu %s; %s;\n", nowTime, ISBN, name, auther);
    fclose(out);
}
void writeAddBook(uint64_t ISBN, uint32_t val)
{
    FILE *out = fopen(fileName, "a");
    fprintf(out, "%u A %llu %u\n", nowTime, ISBN, val);
    fclose(out);
}
void writeDelBook(uint64_t ISBN, uint32_t val)
{
    FILE *out = fopen(fileName, "a");
    fprintf(out, "%u D %llu %u\n", nowTime, ISBN, val);
    fclose(out);
}
void writeBorrowBook(uint64_t ISBN, uint32_t uid, uint32_t borrowTime)
{
    FILE *out = fopen(fileName, "a");
    fprintf(out, "%u B %llu %u %u\n", nowTime, ISBN, uid, borrowTime);
    fclose(out);
}
void writeReturnBook(uint64_t ISBN, uint32_t uid, uint32_t returnTime)
{
    FILE *out = fopen(fileName, "a");
    fprintf(out, "%u R %llu %u %u\n", nowTime, ISBN, uid, returnTime);
    fclose(out);
}
void writeUpdateBook(uint64_t ISBN, uint64_t newISBN, char *newName, char *newAuther)
{
    FILE *out = fopen(fileName, "a");
    fprintf(out, "%u U %llu %llu %s; %s;\n", nowTime, ISBN, newISBN, newName, newAuther);
    fclose(out);
}
void writeEraseBook(uint64_t ISBN)
{
    FILE *out = fopen(fileName, "a");
    fprintf(out, "%u E %llu\n", nowTime, ISBN);
    fclose(out);
}
void readInit()
{
    FILE *in = fopen(fileName, "r");
    if (in == NULL)
    {
        FILE *log = fopen("log.txt", "a");
        fprintf(log, "FILE ERROR!\n");
        return;
    }
    uint32_t time;
    char opt;
    char name[100], auther[100];
    uint32_t uid;
    uint64_t ISBN;
    uint32_t val;
    uint32_t borrowTime;
    uint32_t returnTime;
    while (fscanf(in, "%u %c", &time, &opt) != EOF)
    {
        switch (opt)
        {
        case 'N':
            fscanf(in, "%u %[^;];", &uid, name);
            createUser(uid, name);
            break;
        case 'C':
            fscanf(in, "%llu %[^;]; %[^;];", &ISBN, &name, auther);
            createBook(ISBN, name, auther, time);
            break;
        case 'A':
            fscanf(in, "%llu %u", &ISBN, &val);
            addBook(findBookbyISBN(ISBN), val, time);
            break;
        case 'D':
            fscanf(in, "%llu %u", &ISBN, &val);
            deleteBook(findBookbyISBN(ISBN), val, time);
            break;
        case 'B':
            fscanf(in, "%llu %u %u", &ISBN, &uid, &borrowTime);
            borrowBook(findBookbyISBN(ISBN), findUserbyUID(uid), borrowTime, time);
            break;
        case 'R':
            fscanf(in, "%llu %u %u", &ISBN, &uid, &returnTime);
            returnBook(findBookbyISBN(ISBN), findUserbyUID(uid), returnTime);
            break;
        case 'U':
            uint64_t ISBN, newISBN;
            char newName[100], newAuther[100];
            fscanf(in, "%llu %llu %[^;]; %[^;];", &ISBN, &newISBN, newName, newAuther);
            updateBook(findBookbyISBN(ISBN), newISBN, newName, newAuther);
            break;
        case 'E':
            fscanf(in, "%llu", &ISBN);
            EraseBook(findBookbyISBN(ISBN));
            break;
        default:
            break;
        }
    }
    fclose(in);
}