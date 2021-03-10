#include "bool.c"

#include <stdio.h>
#include <string.h>
#include <time.h>


int Test_First() {
    int temp = 0;

    BB res, result;

    uint64_t num = 4477799;
    uint64_to_bb(num, &res);

    str_to_bb("10001000101001101100111", &result);
    char* string = bb_to_str(&result);
    char* str = bb_to_str(&res);
    if (strcmp (string, str) != 0) {
        printf("Transformers don't work properly\n");
        temp++;
    }

    free((void*)string);
    free((void*)str);

    return temp;
}

int Test_Random_De_Morgan() {
    int temp = 0;

    srand (time (NULL));
    BB res1, res2, res3, not_res1, not_res2, first_part;

    uint64_to_bb(rand(), &res1);
    uint64_to_bb(rand(), &res2);

    // res1 or res2
    disjunction(&res1, &res2, &res3);
    // ~(res1 or res2)
    inversion(&res3, &not_res1);
    char* str_xor_vec = bb_to_str(&not_res1);
    reset_bb(&res3);
    reset_bb(&not_res1);

    // ~res1
    inversion(&res1, &not_res1);
    // ~res2
    inversion(&res2, &not_res2);

    // ~res1 & ~res2
    conjunction(&not_res1, &not_res2, &first_part);

    char* first_string = bb_to_str(&first_part);
    if(strcmp(str_xor_vec, first_string) != 0){
        printf("~(x or y) not equal ((~x) & (~y))");
        temp++;
    }

    free((void*)str_xor_vec);
    free((void*)first_string);

    return temp;
}

int Test_Random_Xor(){

    int temp = 0;

    srand(time (NULL));

    BB res1;
    BB res2;
    BB not_res1;
    BB not_res2;
    BB first_part;
    BB second_part;

    uint64_to_bb(rand(), &res1);
    uint64_to_bb(rand(), &res2);

    //xor res1 ^ res2
    xor(&res1, &res2, &not_res1);
    char* str_vec_xor = bb_to_str(&not_res1);
    reset_bb(&not_res1);

    // ~res1
    inversion(&res1, &not_res1);
    // ~res2
    inversion(&res2, &not_res2);
    //first part ~res1 & res2
    conjunction(&not_res1, &res2, &first_part);
    //second part res1 & ~res2
    conjunction(&res1, &not_res2, &second_part);
    reset_bb(&not_res1);
    disjunction(&first_part, &second_part, &not_res1);
    char* str_end_result = bb_to_str(&not_res1);

    if (strcmp(str_vec_xor,str_end_result) != 0) {
    printf("(x xor y) not equal ((~x & y) | (x & ~y))");
    temp++;
    }

    free((void*)str_vec_xor);
    free((void*)str_end_result);

    return temp;
}

int main () {
    int response = 0;

    // Test function transformation
    response += Test_First();
    response += Test_Random_De_Morgan();
    response += Test_Random_Xor();

    if(response != 0) {
        printf("Amount of failed test = %d\n", response);
        return 0;
    }
    puts("This test work properly");
    return 0;
}
