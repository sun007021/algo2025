#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int a, b, n;
    char answer;
    scanf("%d %d %d", &a, &b, &n);
    getchar();
    int mid;
    for (int i = 0; i < n; i++) {
        scanf("%c", &answer);
        mid = (a+b)/2;
        if(answer =='N'){
            b = mid;
        }
        else{
            a=mid+1;
        }
    }
    printf("%d",a);
    return 0;
}