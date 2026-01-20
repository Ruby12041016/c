#include<stdio.h>
#include<string.h>
int main(){
    char a[] = "Program";
    char b[] = "Fortran";
    char c[] = "Basic";
    char* p[4];
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = NULL;
    for (int i = 0; i < 3;i++){
        for (int j = 0; j < 2 - i;j++){
            if(strcmp(p[j],p[j+1])>0){
                char* q = p[j];
                p[j] = p[j + 1];
                p[j + 1] = q;
            }
        }
    }
    for (int i = 0; i < 4;i++){
        printf("%s ", p[i]);
    }
    printf("\n");
    return 0;
}