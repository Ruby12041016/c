// #include<stdio.h>
// int main(){
//     int n;
//     scanf("%d", &n);
//     int arr[n][n];
//     for (int i = 0; i < n;i++){
//         for (int j = 0; j < n;j++){
//             arr[i][j] = 0;
//         }
//     }
//     arr[0][0] = 1;
//     for (int i = 1; i < n; i++) {
//         for (int j = 1; j <= i;j++){
//             arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
//         }
//     }
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j <= i; j++) {
//             printf("%3d", arr[i][j]);
//         }
//         printf("\n");
//     }
//     return 0;
// }
#include <stdio.h>

int main() {
    int n;
    printf("请输入杨辉三角的行数: ");
    scanf("%d", &n);

    int arr[n][n];

    // 初始化数组
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = 0;
        }
    }

    // 生成杨辉三角
    arr[0][0] = 1;

    for (int i = 1; i < n; i++) {
        arr[i][0] = 1;                  // 每行第一个元素为1
        for (int j = 1; j <= i; j++) {  // 修正：j <= i
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        }
    }

    // 打印杨辉三角
    printf("生成的杨辉三角:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {  // 修正：j <= i
            printf("%3d", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}