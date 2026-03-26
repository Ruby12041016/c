#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOK_MAX 10000
#define ACCOUNT_MAX 10000

extern int book_num;
extern int account_num;
extern char current_name[20];

// 图书基本信息结构体
typedef struct Book {
    int id;            // 书籍编号
    char author[20];   // 作者
    char name[20];     // 书名
    char publish[30];  // 出版社
    int statut;        // 状态
    char bow[20];      // 借阅人
} Book;

typedef struct Account {
    char username[20];
    int password;
} Account;

extern char* status[];
extern Book book[BOOK_MAX];
extern Account account[ACCOUNT_MAX];

// 函数声明
void add_book();
void delete_book();
void search_book();
void list_book();
void sort_book();
void count_book();
void revise();
void loaddata();
void savedata();
void menu();
void borrow();
void show_user();
int sign_in();
void return_book();

// 比较函数，用于排序
int compare_by_id(const void* a, const void* b);
int compare_by_name(const void* a, const void* b);
int compare_by_id_desc(const void* a, const void* b);
int compare_by_name_desc(const void* a, const void* b);
int compare_by_author_desc(const void* a, const void* b);
int compare_by_author(const void* a, const void* b);

#endif  // LIBRARY_H