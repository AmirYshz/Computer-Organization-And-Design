#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////
#define MAX_BITS 32
short int multipicand, multiplier;  //16 bit inputs
int result = 0;                     //32 output

/////////////////////////////////////////////////////////////////////
int FindDigit (int n,int i){        //finding the n`th digit of a number in base 2
    return (n & (1<<i-1))>>(i-1);
}

void BitByBitPrinter(int n){        //printing a number bit by bit
    for (int i = MAX_BITS; i != 0; i--){
           printf("%d", FindDigit(n,i));
    }
    printf("\n");
}

int BitRangeAdder(int a, int b, int max, int min){   // adds b to a in the choosen bit range
    for (int i = max; i != min; i--){
        a = a | (FindDigit(b,i)<<(i-1));
    }
    return a;
}

void BitRangePrinter(int n, int max, int min){  // prints out bits of given number in the wanted range
    for (int i = max; i != min; i--){
        printf("%d", FindDigit(n,i));
    }
}

void StepPrinter(int step, int q1q0){   // prints out steps
    printf("%d\t", step);
    BitRangePrinter(result, MAX_BITS-1, MAX_BITS/2);
    printf("  ");
    BitRangePrinter(result, MAX_BITS/2, 0);
    printf("   ");
    BitRangePrinter(q1q0, 2, 0);
}

int TwosCompliment(int n){      // Two`s complimenting a number
    return ~n+1;
}

void booth(short multipicand, short multiplier){    // booth algorithm implimentation

    result = BitRangeAdder(result, multiplier, MAX_BITS/2, 0);
    short q1q0 = 0;
    q1q0 = ((multiplier & 1) << 1) | 0;

    printf("n\tA\t\t Q\t\t    q1q0\tAction\n");

    for (short i = MAX_BITS/2; i != 0; i--){

        StepPrinter(i, q1q0);

        switch (q1q0){
            case 1:
                result = result + (multipicand<<16) ;
                printf("\t\tA = A + M then ASR\n");
                break;
            case 2:
                result = result + (TwosCompliment(multipicand)<<16) ;
                printf("\t\tA = A - M then ASR\n");
                break;
            default:
                printf("\t\tArithmatic shift right\n");
                break;
        }
        q1q0 = q1q0 >>1;
        q1q0 = q1q0 | (result&2);
        result = result>>1;
    }
    StepPrinter(0, q1q0);
}

////////////////////////////////////////////////////////////////////
void main(){

    printf("\t<<\tBOOTH'S MULTIPLICATION ALGORITHM\t>>\n");

    int Q = 1;
    while (Q){

        do{  //getting two numbers in range of -32,767 to 32,767
            printf("\nEnter two numbers to multiply, which both must be in range of -32,767 to 32,767 ");
            printf("\n");
            printf("\nEnter multipicand: ");
            scanf("%d",&multipicand);
            printf("Enter multiplier: ");
            scanf("%d", &multiplier);
            printf("%d %d %d %d", multipicand, multiplier, abs(multipicand) >>15 | abs(multiplier) >>15, abs(multipicand) >>15);
        }while(abs(multipicand) >>15 | abs(multiplier) >>15);

        booth(multipicand, multiplier);
        printf("\n\nSo, The Product is: %d\n Which its binary equivalent is : ", result);
        BitByBitPrinter(result);
        printf("\nDo you want to continue?(1/0) ");
        //Q = getchar();
        scanf("%d",&Q);
    }
    getchar();
}
