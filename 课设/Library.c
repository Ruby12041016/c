#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOOK_MAX 10000
#define ACCOUNT_MAX 10000
int book_num = 0;
int account_num = 0;

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

// 图书基本信息结构体
typedef struct Book {
    int id;            // 书籍编号
    char author[20];   // 作者
    char name[20];     // 书名
    char publish[30];  // 出版社
    int statut;        // 状态
} Book;

typedef struct Account {
    char username[20];
    int password;
} Account;

char* status[] = {"未被借阅", "已被借阅"};

Book book[BOOK_MAX];  // 学生基本信息结构体数组
Account account[ACCOUNT_MAX];

// 比较函数，用于排序
int compare_by_id(const void* a, const void* b) {
    Book* book1 = (Book*)a;
    Book* book2 = (Book*)b;
    return book1->id - book2->id;
}

int compare_by_name(const void* a, const void* b) {
    Book* book1 = (Book*)a;
    Book* book2 = (Book*)b;
    return strcmp(book1->name, book2->name);
}

int compare_by_author(const void* a, const void* b) {
    Book* book1 = (Book*)a;
    Book* book2 = (Book*)b;
    return strcmp(book1->author, book2->author);
}

void borrow() {
    printf("请输入要借的书的编号：");
    int id = 0;
    scanf("%d", &id);
    int idex = -1;
    for (int i = 0; i < book_num; i++) {
        if (book[i].id == id) {
            idex = i;
            break;
        }
    }
    if (idex == -1) {
        printf("请输入正确编号！\n");
        return;
    }
    if (book[idex].statut == 1) {
        printf("该书已被借走。\n");
        return;
    }
    book[idex].statut = 1;
    printf("借阅成功！\n");
    return;
}

int sign_in() {
    printf("请输入账户名：");
    char name[20];
    scanf("%19s", name);
    int found = -1;
    int chance = 3;
    for (int i = 0; i < account_num; i++) {
        if (strcmp(name, account[i].username) == 0) {
            found = i;
        }
    }
    if (found == -1) {
        printf("您还没有账户，是否注册？（Y/N）");
        char option;
        scanf(" %c", &option);
        if (option == 'Y' || option == 'y') {
            printf("请输入密码（数字）：");
            int new_pss = 0;
            scanf("%d", &new_pss);
            strcpy(account[account_num].username, name);
            account[account_num].password = new_pss;
            account_num++;
            return 1;
        } else {
            return 0;
        }
    } else {
        int pass = 0;
        while (chance > 0) {
            printf("请输入密码：");
            scanf("%d", &pass);
            if (account[found].password == pass) {
                return 1;
            } else {
                chance--;
                printf("密码错误！\n");
                printf("您还有%d次机会\n", chance);
            }
        }
        return 0;
    }
}

void search_book() {
    printf("========= 菜单 ========\n");
    printf("1. 按书名查询\n");
    printf("2. 按作者查询\n");
    int option;
    scanf("%d", &option);
    switch (option) {
        case 1:
            char name[20];
            printf("请输入书名：\n");
            scanf("%19s", name);
            int index = 0;
            for (int i = 0; i < book_num; i++) {
                if (strcmp(book[i].name, name) == 0) {
                    index = 1;
                    printf(
                        "编号: %d\n书籍: %s\n作者: %s\n出版社: %s\n状态:%s\n",
                        book[i].id, book[i].name, book[i].author,
                        book[i].publish, status[book[i].statut]);
                }
            }
            if (index == 0) {
                printf("未找到%s！\n", name);
                return;
            }
            break;
        case 2:
            char a_name[20];
            printf("请输入作者姓名：\n");
            scanf("%19s", a_name);
            int a_index = -1;
            for (int i = 0; i < book_num; i++) {
                if (strcmp(book[i].author, a_name) == 0) {
                    printf(
                        "编号: %d\n书籍: %s\n作者: %s\n出版社: %s\n状态: %s\n",
                        book[i].id, book[i].name, book[i].author,
                        book[i].publish, status[book[i].statut]);
                    a_index = 1;
                }
            }
            if (a_index == -1) {
                printf("未找到该作者！\n");
                return;
            }
            break;
        default:
            printf("请输入正确选项！\n");
            return;
    }
    printf("是否借阅该书(Y/N)：\n");
    char resp;
    scanf(" %c", &resp);
    if (resp == 'Y' || resp == 'y') {
        borrow();
    } else {
        return;
    }
}
void list_book() {
    if (book_num == 0) {
        printf("当前没有书籍！\n");
        return;
    }
    printf("========= 所有书籍 =========\n");
    printf("共 %d 本书\n\n", book_num);
    for (int i = 0; i < book_num; i++) {
        printf("编号: %d\n书籍: %s\n作者: %s\n出版社: %s\n状态: %s\n\n",
               book[i].id, book[i].name, book[i].author, book[i].publish,
               status[book[i].statut]);
    }
}

void sort_book() {
    if (book_num == 0) {
        printf("暂无书籍数据！\n");
        return;
    }
    printf("========= 排序选项 =========\n");
    printf("1. 按编号排序\n");
    printf("2. 按书名排序\n");
    printf("3. 按作者排序\n");
    printf("请选择：");
    int option;
    scanf("%d", &option);
    switch (option) {
        case 1:
            qsort(book, book_num, sizeof(Book), compare_by_id);
            printf("已按编号排序！\n");
            break;
        case 2:
            qsort(book, book_num, sizeof(Book), compare_by_name);
            printf("已按书名排序！\n");
            break;
        case 3:
            qsort(book, book_num, sizeof(Book), compare_by_author);
            printf("已按作者排序！\n");
            break;
        default:
            printf("请输入正确选项！\n");
            return;
    }
    // 显示排序结果
    list_book();
}

void menu() {
    printf("=== 菜单 ===\n");
    printf("1. 添加书籍\n");
    printf("2. 删除书籍\n");
    printf("3. 查询书籍\n");
    printf("4. 显示所有书籍\n");
    printf("5. 排序\n");
    printf("6. 书籍统计\n");
    printf("7. 修改书籍信息\n");
    printf("0. 退出系统\n");
    printf("请选择操作：\n");
}

int main() {
    printf("欢迎使用图书管理系统！\n\n");
    int n;
    loaddata();
    printf("========登录========\n");
    if (!sign_in()) {
        return 0;
    }
    while (1) {
        menu();
        scanf("%d", &n);
        getchar();
        if (n == 0) {
            printf("感谢使用！\n");
            savedata();
            return 0;
        }
        switch (n) {
            case 1:
                add_book();
                savedata();
                break;
            case 2:
                delete_book();
                savedata();
                break;
            case 3:
                search_book();
                savedata();
                break;
            case 4:
                list_book();
                savedata();
                break;
            case 5:
                sort_book();
                savedata();
                break;
            case 6:
                count_book();
                savedata();
                break;
            case 7:
                revise();
                savedata();
                break;
            default:
                printf("请输入正确选项！\n");
                break;
        }
    }
    return 0;
}

void add_book() {
    if (book_num >= BOOK_MAX) {
        printf("书籍数量已达上限，无法添加！\n");
        return;
    }
    // getchar();

    // 检查书籍名称
    while (1) {
        printf("请输入书籍名称：");
        fgets(book[book_num].name, sizeof(book[book_num].name), stdin);
        book[book_num].name[strcspn(book[book_num].name, "\n")] = '\0';
        if (strlen(book[book_num].name) > 0) {
            break;
        }
        printf("书籍名称不能为空，请重新输入！\n");
    }

    // 检查作者
    while (1) {
        printf("请输入书籍作者：");
        fgets(book[book_num].author, sizeof(book[book_num].author), stdin);
        book[book_num].author[strcspn(book[book_num].author, "\n")] = '\0';
        if (strlen(book[book_num].author) > 0) {
            break;
        }
        printf("作者名称不能为空，请重新输入！\n");
    }

    // 检查出版社
    while (1) {
        printf("请输入出版社名称：");
        fgets(book[book_num].publish, sizeof(book[book_num].publish), stdin);
        book[book_num].publish[strcspn(book[book_num].publish, "\n")] = '\0';
        if (strlen(book[book_num].publish) > 0) {
            break;
        }
        printf("出版社名称不能为空，请重新输入！\n");
    }

    book[book_num].statut = 0;
    book[book_num].id = book_num + 1;
    book_num++;
    printf("书籍添加成功！当前总书籍数：%d\n", book_num);
}
void delete_book() {
    printf("======== 删除选项 =========\n");
    printf("1. 删除作者（连带其所有书籍）\n");
    printf("2. 删除某本书\n");
    printf("请选择：");
    int opt = 0;
    scanf("%d", &opt);
    getchar();
    if (book_num == 0) {
        printf("暂无书籍数据，无需删除！\n");
        return;
    }
    char name[20];
    int index = -1;
    int found = 0;
    if (opt == 1) {
        printf("请输入要删除的作者：");
        scanf("%19s", name);
        getchar();
        for (int i = 0; i < book_num; i++) {
            if (strcmp(book[i].author, name) == 0) {
                index = i;
                for (int j = index; j < book_num - 1; j++) {
                    book[j] = book[j + 1];
                }
                i--;
                book_num--;
                found = 1;
            }
        }
    } else if (opt == 2) {
        printf("请输入要删除的书籍：");
        scanf("%19s", name);
        getchar();
        // int index = -1;
        for (int i = 0; i < book_num; i++) {
            if (strcmp(book[i].name, name) == 0) {
                index = i;
                for (int j = index; j < book_num - 1; j++) {
                    book[j] = book[j + 1];
                }
                book_num--;
                i--;
                found = 1;
            }
        }
    } else {
        printf("输入选项错误！\n");
        return;
    }
    if (!found) {
        printf("未找到！\n");
        return;
    }
    /* 重建 id 序列 */
    for (int k = 0; k < book_num; k++) {
        book[k].id = k + 1;
    }
    printf("删除成功！\n");
}

void loaddata() {
    int count_book = 0;
    FILE* fp_book = fopen("Book.txt", "r");
    if (fp_book == NULL) {
        printf("文件不存在！\n");
        book_num = 0;
    } else {
        char line_book[100];
        fgets(line_book, sizeof(line_book), fp_book);
        for (int i = 0; i < BOOK_MAX; i++) {
            if (fscanf(fp_book, "%d %19s %19s %29s %d\n", &book[i].id,
                       book[i].name, book[i].author, book[i].publish,
                       &book[i].statut) == 5) {
                count_book++;
            } else {
                break;
            }
        }
        printf("已加载%d条书籍数据\n", count_book);
        fclose(fp_book);
    }
    book_num = count_book;

    int count_cnt = 0;
    FILE* fp_cnt = fopen("Account.txt", "r");
    if (fp_cnt == NULL) {
        printf("文件不存在！\n");
        count_cnt = 0;
    } else {
        for (int i = 0; i < ACCOUNT_MAX; i++) {
            if (fscanf(fp_cnt, "%19s%d", account[i].username,
                       &account[i].password) == 2) {
                count_cnt++;
            } else {
                break;
            }
        }
        fclose(fp_cnt);
    }
    account_num = count_cnt;
}
void savedata() {
    FILE* fp_book = fopen("Book.txt", "w");
    if (fp_book == NULL) {
        perror("文件打开错误！\n");
        return;
    }
    /* 输出对齐的列（空格分隔），与 loaddata 的 fscanf 格式兼容 */
    fprintf(fp_book,
            "编号    书名                 作者               出版社            "
            "             状态\n");
    for (int i = 0; i < book_num; i++) {
        fprintf(fp_book, "%-6d %-19s %-19s %-29s %-6d\n", book[i].id,
                book[i].name, book[i].author, book[i].publish, book[i].statut);
    }
    fclose(fp_book);

    FILE* fp_cnt = fopen("Account.txt", "w");
    if (fp_cnt == NULL) {
        perror("文件打开错误！\n");
        return;
    }
    for (int i = 0; i < account_num; i++) {
        fprintf(fp_cnt, "%s\n", account[i].username);
        fprintf(fp_cnt, "%d\n", account[i].password);
    }
    fclose(fp_cnt);
}

void count_book() {
    int i;
    int have = 0, none = 0;
    if (book_num == 0) {
        printf("暂无书籍信息！\n");
        return;
    }
    for (i = 0; i < book_num; i++) {
        switch (book[i].statut) {
            case 0:
                have++;
                break;
            case 1:
                none++;
                break;
        }
    }
    printf("总书籍数：%d\n", book_num);
    printf("未借阅：%d\n", have);
    printf("已被借阅：%d\n", none);
}

void revise() {
    int id, i, j;
    int found = 0;
    int record_index = -1;
    if (book_num == 0) {
        printf("暂无书籍，无法修改！\n");
        return;
    }
    list_book();
    printf("请输入要修改的书籍编号：");
    scanf("%d", &id);
    for (i = 0; i < book_num; i++) {
        if (book[i].id == id) {
            found = 1;
            record_index = i;
            break;
        }
    }
    if (!found) {
        printf("未找到书籍编号 %d！\n", id);
        return;
    }
    printf("========要修改内容========\n");
    printf("1.修改作者名\n");
    printf("2.修改书名\n");
    printf("3.修改状态\n");
    printf("请输入：");
    int option;
    scanf("%d", &option);
    switch (option) {
        case 1:
            char new_author[20];
            printf("请输入新的作者名：");
            scanf("%19s", new_author);
            strcpy(book[record_index].author, new_author);
            break;
        case 2:
            char new_name[20];
            printf("请输入新的书名：");
            scanf("%19s", new_name);
            strcpy(book[record_index].name, new_name);
            break;
        case 3:
            int new_statut;
            printf("请输入新的状态(0-未被借阅，1-已被借阅)：");
            scanf("%d", &new_statut);
            book[record_index].statut = new_statut;
            break;
        default:
            printf("请输入正确编号！");
            break;
    }
    count_book();
}