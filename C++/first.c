#include<stdio.h>
#include<math.h>
#include <string.h>
int main(){
    char *a = NULL;
    char *b = NULL;
    scanf("%ms", &a);
    scanf("%ms", &b);
    int tong = 0;
    int soA = 0, soB = 0;
    for(int i = 0; i < strlen(a); i ++){
        soA = soA + (a[i] - 48) * pow(10, strlen(a) - i - 1);
    }
    for(int i = 0; i < strlen(b); i ++){
        soB = soB + (b[i] - 48) * pow(10, strlen(b) - i - 1);
    }
    printf("%d", soA + soB);
}