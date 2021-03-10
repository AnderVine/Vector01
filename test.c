#include"bool.c"

#include<stdio.h>
#include<string.h>

int TestOrOperation1()
{
    int temp = 0;
    BB result, result1, res;

    str_to_bb("0001", &result);
    str_to_bb("1110", &result1);
    disjunction(&result, &result1, &res);

    char* string = bb_to_str(&res);

    if (strcmp (string, "1111") != 0){
        printf("0001 & 1111  != 1111\n");
        printf ("Error in  1 test\n");
        temp++;
    }

    free((void*)string);
    return temp;
}

int TestAndOperation2() {
    int temp = 0;
    BB result, result1, res;
    str_to_bb("1001", &result);
    str_to_bb("1001", &result1);
    conjunction(&result, &result1, &res);
    char* string = bb_to_str(&res);
    if (strcmp (string, "1001") != 0){
        printf("1001 & 1001  != 1001\n");
        printf ("Error in  2 test\n");
        temp++;
    }

    free((void*)string);

    return temp;
}

int TestXorOperation3() {
    int temp = 0;
    BB result, result1, res;
    str_to_bb("1010", &result);
    str_to_bb("1100", &result1);
    xor(&result, &result1, &res);

    char* string = bb_to_str(&res);

    if (strcmp (string, "0110") != 0){
        printf("1010 & 1100 != 1100\n");
        printf ("Error in 3 test\n");
        temp++;
    }

    free((void*)string);

    return temp;
}

int TestNotOperation4() {
    int temp = 0;
    BB result, res;

    str_to_bb("0000", &result);
    inversion(&result, &res);

    char* string = bb_to_str(&res);

    if (strcmp (string, "1111") != 0){
        printf("~0000  != 1111\n");
        printf ("Error in  4 test\n");
        temp++;
    }

    free((void*)string);

    return temp;
}

int Test_Right_Shift5() {

    int temp = 0;
    BB result, res;

    str_to_bb("1010", &result);
    right_shift(&result, &res, 2);

    char *string = bb_to_str(&res);

    if (strcmp(string, "10") != 0) {
        printf("(10101 >> 2)  != 10\n");
        printf ("Error in  5 test\n");
        temp++;
    }

    free((void *)string);

    return temp;
}

int Test_Left_Shift6() {

    int temp = 0;
    BB res, result;
    str_to_bb("1010", &result);
    left_shift(&result, &res, 2);

    char *string = bb_to_str(&res);

    if (strcmp(string, "101000") != 0) {
        printf("(1010 >> 2)  != 101000\n");
        printf ("Error in  6 test\n");
        temp++;
    }

    free((void *)string);

    return temp;
}

int Test_Cycle_Shifts7() {

    int temp = 0;

    BB result, res;

    str_to_bb("1010", &result);
    left_cycle_shift(&result, &res, 3);

    char *string = bb_to_str(&res);

    if (strcmp(string, "0101") != 0) {
        printf("(1010 << 3)   != 0101\n");
        printf ("Error in  7 test\n");
        temp++;
    }

    free((void *)string);

    return temp;
}

int Test_Right_Cycle_Shift8() {

    int temp = 0;

    BB result, res;

    str_to_bb("1001", &result);
    right_cycle_shift(&result, &res, 3);

    char *string = bb_to_str(&res);
    if (strcmp(string, "1100") != 0) {
        printf("(1001 >> 3)  != 1100\n");
        printf ("Error in  8 test\n");
        temp++;
    }

    free((void *)string);
    return temp;
}

int main () {
    int response = 0;
// Test basic operations, where len two vectors equal 4.
    response += TestOrOperation1();
    response += TestAndOperation2();
    response += TestXorOperation3();
    response += TestNotOperation4();
    response += Test_Right_Shift5();
    response += Test_Left_Shift6();
    response += Test_Cycle_Shifts7();
    response += Test_Right_Cycle_Shift8();

    if(response != 0) {
        printf("Amount of failed test = %d\n", response);
        return 0;
    }
    puts("This test with len_vector = 4 work properly");
    return 0;
}
