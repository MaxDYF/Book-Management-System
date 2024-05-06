#ifndef _UI_H_
#define _UI_H_
extern const char *mainMsg[];
extern const char *creatBookMsg[];
void clearScreen(void);
void displayCreateBookMenu(void);
void displayBookQueryMenu(void);
void displayBookModifyMenu(void);
void displayBookDeleteMenu(void);
void displayBookManageMenu(void);
void displayBorrowBookMenu(void);
void displayReturnBookMenu(void);
void displayMainMenu(void);
void displayEraseBorrowRecordMenu(void);
#endif