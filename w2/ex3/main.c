#include <stdio.h>

int main() {
    int end = 20;
    for(int i = 1; i <= end; i++) {
        int pow = i * i;
        
        if(pow %2 == 0) {
            printf("%d is even\n", pow);
        } else {
            printf("%d is odd\n", pow);
        }
    }

    return 0;
}