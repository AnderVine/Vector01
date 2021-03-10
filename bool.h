#include <stdio.h>
#include <stdint.h>

#define MAX_PARTS 20

#pragma once

/* ------------------------------------------
 *  Error codes
 * ------------------------------------------
 */
#define ERR_OK 0
#define ERR_EMPTY_VECTOR 1
#define ERR_BAD_STRING 2
#define ERR_BAD_ARG 3
#define ERR_NULL_ARG 4

typedef struct BB{
    uint8_t vector[MAX_PARTS];
    size_t n_byte_;
    size_t n_bit_;
} BB;

/* -------------------------------------------------------------------------
 * Extra functions
 * -------------------------------------------------------------------------
 *
 * Function: int reset_bb(bb **bb)
 *
 * Description: reset structure.
 *
 * Return:
 * 1) ERR_OK if all work properly
 * 2) ERR_NULL_ARG if bb == NULL
 */
int reset_bb(BB *bb);
/*
 * Function: int reverse_bits(bb **bb, int begin_b, int end_b)
 *
 * Description: reverse vector.
 *
 * Return:
 * 1) ERR_OK if all work properly,
 * 2) ERR_NULL_ARG if bb == NULL,
 *
 */
int reverse_bits(BB *bb, int begin_b, int end_b);

/* -------------------------------------------------------------------------
 * Transformations
 * -------------------------------------------------------------------------
 *
 * Function: int str_to_bb(char* str , BB* res )
 *
 * Description: takes string containing only '1' and '0' and makes vector of it.
 *
 * Returns:
 * 1) ERR_OK if function work properly,
 * 2) ERR_NULL_ARG if BB == NULL,
 * 3) ERR_EMPTY_VECTOR if strlen(str) == 0,
 * 4) ERR_BAD_STRING if string is not only '1' or '0'.
 *
 */
int str_to_bb(char* str , BB* res);

/*
 * Function: int uint64_to_bb(uint64_t num , BB* res)
 *
 * Description:  takes 64 bit number and makes vector of it.
 *
 * Returns:
 * 1) ERR_OK if function work properly,
 * 2) ERR_NULL_ARG if res == NULL,
 *
 */

int uint64_to_bb(uint64_t num , BB* res);

/*
 * Function: char* bb_to_str(BB* res)
 *
 * Description: makes a string of 1 and 0 from a Boolean vector
 *
 * Returns:
 * 1) Pointer to string,
 * 2) NULL, if failed to allocate.
 *
 */
char* bb_to_str(BB* res);

/* -------------------------------------------------------------------------
 * Logical operations
 * -------------------------------------------------------------------------
 *
 * Function: int disjunction (BB* bb1, BB* bb2, BB* res)
 *
 * Description:  makes disjunction of two boolean vectors
 *
 * Returns:
 * 1) ERR_OK if function work properly,
 * 2) ERR_BAD_ARG if BB == NULL.
 *
 */
int disjunction (BB* bb1, BB* bb2, BB* res);

/*
 * Function: int conjunction (BB* bb1, BB* bb2, BB* res)
 *
 * Description:  makes conjunction of two boolean vectors
 *
 * Returns:
 * 1) ERR_OK if function work properly,
 * 2) ERR_BAD_ARG if BB == NULL.
 *
 */
int conjunction (BB* bb1, BB* bb2, BB* res);

/*
 * Function: int xor (BB* bb1, BB* bb2, BB* res)
 *
 * Description:  makes xor of two boolean vectors
 *
 * Returns:
 * 1) ERR_OK if function work properly,
 * 2) ERR_BAD_ARG if BB == NULL.
 *
 */
int xor (BB* bb1, BB* bb2, BB* res);

/*
 * Function: int inversion (BB* bb1, BB* res)
 *
 * Description:   makes inversion of bool vector
 *
 * Returns:
 * 1) ERR_OK if function work properly,
 * 2) ERR_BAD_ARG if BB == NULL.
 *
 */
int inversion (BB* bb1, BB* res);

/* -------------------------------------------------------------------------
 * Shifts
 * -------------------------------------------------------------------------
 *
 * Function: int left_shift (BB* BB, BB* res, int len_shift)
 *
 * Description:  do left shift of bool vector
 *
 * Returns:
 * 1) ERR_OK if function work properly,
 * 2) ERR_BAD_ARG if BB == NULL,
 * 3) ERR_BIG_SHIFT if len of shift is bigger then len of vector,
 * 4) ERR_SMALL_SHIFT if len of shift less then 0.
 */
int left_shift (BB* bb, BB* res, int len_shift);

/*
 * Function: int right_shift (bb* bb, bb* res, int len_shift)
 *
 * Description: do rigth shift of bool vector
 *
 * Returns:
 * 1) ERR_OK if function work properly,
 * 2) ERR_BAD_ARG if bb == NULL,
 * 3) ERR_BIG_SHIFT if len of shift is bigger then len of vector,
 * 4) ERR_SMALL_SHIFT if len of shift less then 0.
 *
 */
int right_shift (BB* bb, BB* res, int len_shift);

/*
 * Function: int left_cycle_shift (bb* bb, bb** res, int len_shift)
 *
 * Description: do cyclic left shift of bool vector
 *
 * Returns:
 * 1) ERR_OK if function work properly,
 * 2) ERR_BAD_ARG if bb == NULL,
 * 3) right_cycle_shift(bb, res, -len_shift) if len of shift less than 0,
 *
 */
int left_cycle_shift (BB* bb, BB* res, int len_shift);

/*
 * Function: int right_cycle_shift (bb*bb, bb** res, int len_shift)
 *
 * Description: do cyclic right shift of bool vector
 *
 * Returns:
 * 1) ERR_OK if function work properly,
 * 2) ERR_BAD_ARG if bb == NULL,
 * 3) left_cycle_shift(bb, res, -len_shift) if len of shift less than 0,
 *
 */
int right_cycle_shift (BB* bb, BB* res, int len_shift);
