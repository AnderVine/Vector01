#include"bool.c"

#include<stdio.h>

int Test_First() {
    int temp = 0;

    BB res;

    if (str_to_bb("0001225a", &res) != ERR_BAD_STRING) {
        printf ("Don't set ERR_BAD_STRING\n");
        temp++;
    }

    return temp;
}

int Test_Second() {
    int temp = 0;

    BB result;
    BB *res = NULL;
    str_to_bb("1010010100", &result);

    if (left_shift(&result, res, -3) != ERR_BAD_ARG) {
        printf("Don't set ERR_BAD_ARG\n");
        temp++;
    }

    free(res);
    return temp;
}

int Test_Third() {

    int temp = 0;

    BB res, result;
    str_to_bb("1010010100", &result);

    if (left_shift(&result, &res, 3) == ERR_BAD_ARG) {
        printf("Don't set ERR_BAD_ARG\n");
        temp++;
    }

    if (right_shift(&result, &res, 2) == ERR_BAD_ARG) {
        printf("Don't set ERR_BAD_ARG\n");
        temp++;
    }

    if (right_cycle_shift(&result, &res, 2) == ERR_BAD_ARG) {
        printf("Don't set ERR_BAD_ARG\n");
        temp++;
    }

    if (left_cycle_shift(&result, &res, 2) == ERR_BAD_ARG){
        printf("Don't set ERR_BAD_ARG\n");
        temp++;
    }

    return temp;
}

int main (){
    int response = 0;
// Test errors in all functions
    response += Test_First();

// Test errors in Shift
    response += Test_Second();
    response += Test_Third();

    if(response != 0){
        printf("Amount of failed test = %d\n", response);
        return 0;
    }

    puts("This test of errors work properly");
    return 0;
}