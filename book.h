#include <stdint.h>
typedef struct BookList;
typedef struct BookStatus;
typedef struct BookInfo;
/*
 *  创建新的书本
 *  如果没有这本书，创建并返回该书的指针
 *  否则返回NULL
 */
BookInfo *createBook(BookInfo *bookhead, uint32_t ISBN, char *name, char *auther);
/*
 *  按照给定的ISBN号码
 *  查找对应的书本
 *  如果找到了，就返回该书本的指针
 *  反之返回找到的书的指针
 */
BookInfo *findBookbyISBN(BookInfo *bookhead, uint32_t ISBN);
/*
 *  按照给定的书本名称
 *  查找对应的书本
 *  如果找到了，就返回该书本的指针
 *  反之返回NULL
 */
BookInfo *findBookbyName(BookInfo *bookhead, char *name);
/*
 *  增加书本的数量
 */

void addBook(BookInfo *book, uint32_t val);
/*
 *  减少书本数量
 *  如果数量不够或者尚有未归还的，返回成功删除的书本数量
 *  否则返回0
 */
uint32_t deleteBook(BookInfo *book, uint32_t val);
