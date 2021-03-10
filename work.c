#include "bool.c"

#include <stdio.h>
#include <string.h>

int main(){
    int response = 0;

    //BB* result = calloc(1, sizeof(BB));
    //BB* result1 = calloc(1, sizeof(BB));
    //BB* res = calloc(1, sizeof(BB));


    //int BB = str_to_bb("10011011101", result);  // normal work
    //print_bb(result);
    //int BB1 = str_to_bb( "100011101", result1); // normal work
    //response = left_shift(result, res, 3); // normal work
    //response = right_shift(result, res, 3);    // normal work
    //response = inversion(result,res);  // normal work
    //response = disjunction(result, result1, res);  // normal work
    //response = xor(result, result1, res);   // normal work
    //conjunction(result, result1, res); // normal work
    //uint64_t number = 44557799;
    //response = uint64_to_bb(number, result);    // normal work
    //response = left_cycle_shift(result, &res, 5);
    //BB_reverseBits(&result, 6, len_bits(result)); // normal work
    //puts("Shifts");
    //response = right_cycle_shift(result, res, 5);   // normal work
    //BB_reverseBits(&result, 6, len_bits(result));
    //print_bb(res);
   // response = right_shift(result, res, 5);
    //print_bb(res);
   /* if (response != ERR_OK){
        printf("ERROR: %d;\n", response);
        return response;
    }
    char* str = bb_to_str(result);
    printf("%s", str);*/

   BB temp;
   str_to_bb("10011", &temp);
   print_bb(&temp);

    return 0;
}
