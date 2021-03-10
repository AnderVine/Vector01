#include "bool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


size_t len_bits(BB* bb){
    return bb->n_byte_ * 8 + bb->n_bit_;
}

int reset_bb(BB *bb) {
    if (bb == NULL) {
        return ERR_NULL_ARG;
    }
    memset(bb->vector, 0, MAX_PARTS);
    bb->n_bit_ = 0;
    bb->n_byte_ = 0;
    return ERR_OK;
}

void info_bb(BB* BB) {
    printf("Num parts:\t%d\nNum bit:\t%d\n", BB->n_byte_, BB->n_bit_);
}

int print_bb(BB* bb) {
    info_bb(bb);
    size_t n_byte = bb->n_byte_;
    size_t n_bit = bb->n_bit_;

    for (size_t part = 0; part < n_byte; part++) {
        for (size_t bit = 0; bit < 8; bit++) {
            printf("%d", ((bb->vector[part]) >> (bit) & 1));
        }
    }

    for (size_t bit = 0; bit < n_bit; bit++) {
        printf("%d", ((bb->vector[n_byte]) >> (bit) & 1));
    }
    puts("");
    return ERR_OK;
}

int get_bit(BB* bb, int pos) {
    return (bb->vector[pos / 8] >> (pos % 8) & 1);
}

int reverse_bits(BB* bb, int begin_b, int end_b) {
    if (bb == NULL) {
        return ERR_NULL_ARG;
    }
    if (begin_b < 0 || end_b > MAX_PARTS * 8 || begin_b > end_b) {
        return ERR_BAD_ARG;
    }
    BB tmp;
    if (end_b / 8 > bb->n_byte_) {
        bb->n_byte_ = end_b / 8;
    }
    memcpy(&tmp, bb, MAX_PARTS);
    for(int pos = begin_b; pos < end_b; pos++) {
        tmp.vector[pos / 8] = tmp.vector[pos / 8] & ~(1 << (pos % 8));
        tmp.vector[pos / 8] |= get_bit(bb, (end_b - pos + begin_b - 1)) << (pos % 8);
    }
    memcpy(bb, &tmp, MAX_PARTS);
    return ERR_OK;
}

int str_to_bb(char* str, BB* res) {

    if (res == NULL) {
        return ERR_NULL_ARG;
    }

    size_t len = strlen(str);
    if(len == 0) {
        return ERR_EMPTY_VECTOR;
    }
    memset(res->vector, 0, MAX_PARTS);

    res->n_byte_ = len / 8;
    res->n_bit_ = len % 8;

    size_t index;

    for(size_t part = 0; part < res->n_byte_; part++) {
        for (size_t bit = 0; bit < 8; bit++) {
            index = len - 1 - (part * 8 + bit);
            if(str[index] != '0' && str[index] != '1') {
                return ERR_BAD_STRING;
            }
            res->vector[part] |= ((str[index] - '0') << bit);
        }
    }

    for(size_t bit = 0; bit < res->n_bit_; bit++) {
        index = len - 1 - (res->n_byte_ * 8 + bit);
        if (str[index] != '0' && str[index] != '1') {
            return ERR_BAD_STRING;
        }
        res->vector[res->n_byte_] |= ((str[index] - '0') << bit);

    }
    return ERR_OK;
}

size_t high_bit_pos_cycle(uint64_t num) {
    size_t bytes = 0;
    while ((num >> ((bytes + 1) * 8)) != 0) {
        bytes++;
    }
    size_t bits = 0;
    while ((num >> (bytes * 8 + bits)) != 0) {
        bits++;
    }

    return bytes * 8 + bits;
}

int uint64_to_bb(uint64_t num, BB* res){

    if (res == NULL){
        return ERR_NULL_ARG;
    }
    memset(res->vector, 0, MAX_PARTS);

    for (int i = 0; i < 8; i++) {
        res->vector[i] |= (num >> 8 * i);
    }

    int pos = high_bit_pos_cycle(num);
    res->n_byte_ = pos / 8;
    res->n_bit_ = pos % 8;

    return ERR_OK;
}

char* bb_to_str(BB* res){

    size_t len = len_bits(res);

    char* str = (char*)malloc(len * sizeof(char));
    if (str == NULL){
        return NULL;
    }

    for (int str_pos = 0; str_pos < len; ++str_pos){
        str[len - str_pos - 1] = '0' + get_bit(res, str_pos);
    }
    str[len] = '\0';

    return str;
}

int xor (BB* bb1, BB* bb2, BB* res){

    if (bb1 == NULL || res == NULL || bb2 == NULL) {
        return ERR_BAD_ARG;
    }
    if(len_bits(bb1) < len_bits(bb2)) {
        return xor(bb2, bb1, res);
    }

    res->n_byte_ = bb1->n_byte_;
    res->n_bit_ = bb1->n_bit_;

    for(size_t part = 0; part <= bb2->n_byte_; ++part) {
        res->vector[part] = bb1->vector[part] ^ bb2->vector[part];
    }
    for(size_t part = bb2->n_byte_ + 1; part <= bb1->n_byte_; ++part) {
        res->vector[part] = bb1->vector[part];
    }
    return ERR_OK;
}

int disjunction(BB* bb1, BB* bb2, BB* res){

    if (bb1 == NULL || res == NULL || bb2 == NULL){
        return ERR_BAD_ARG;
    }
    if(len_bits(bb1) < len_bits(bb2)){
        return disjunction(bb2, bb1, res);
    }

    res->n_byte_ = bb1->n_byte_;
    res->n_bit_ = bb1->n_bit_;

    for(size_t part = 0; part <= bb2->n_byte_; ++part){
        res->vector[part] = bb1->vector[part] | bb2->vector[part];
    }
    for(size_t bit = bb2->n_byte_ + 1; bit <= bb1->n_byte_; ++bit) {
        res->vector[bit] = bb1->vector[bit];
    }

    return ERR_OK;
}

int conjunction (BB* bb1, BB* bb2, BB* res){

    if (bb1 == NULL || res == NULL || bb2 == NULL) {
        return ERR_BAD_ARG;
    }
    if(len_bits(bb1) < len_bits(bb2)) {
        return conjunction(bb2, bb1, res);
    }
    memset(res->vector, 0, MAX_PARTS);
    res->n_byte_ = bb1->n_byte_;
    res->n_bit_ = bb1->n_bit_;

    for (int pos = 0; pos < len_bits(bb2); ++pos) {
        res->vector[pos / 8] |= (get_bit(bb1, pos) & get_bit(bb2, pos)) << (pos % 8);
    }
    for (int pos = len_bits(bb2); pos < len_bits(bb1); ++pos) {
        res->vector[pos / 8] |= get_bit(bb1, pos) << (pos % 8);
    }
    return ERR_OK;
}

int inversion (BB* bb1, BB* res){

    if (bb1 == NULL || res == NULL) {
        return ERR_BAD_ARG;
    }
    res->n_bit_ = bb1->n_bit_;
    res->n_byte_ = bb1->n_byte_;

    for (int part = 0; part <= bb1->n_byte_; part++){
        res->vector[part] = ~bb1->vector[part];
    }

    return ERR_OK;
}

int left_shift(BB* bb, BB* res, int len_shift){
    if (bb == NULL || res == NULL || len_shift < 0) {
        return ERR_BAD_ARG;
    }
    if (len_shift >= MAX_PARTS * 8) {
        memset(res->vector, 0, MAX_PARTS);
        res->n_bit_ = 1;
        res->n_byte_ = 0;
    }
    else {
        size_t len_new_vec = len_bits(bb) + len_shift;

        res->n_byte_ = len_new_vec / 8;
        res->n_bit_ = len_new_vec % 8;

        size_t end_new_vec = res->n_byte_ + (res->n_bit_ > 0) - 1;

        for (size_t part = end_new_vec; part > len_shift / 8; --part){
            uint8_t first_byte = bb->vector[part - len_shift / 8 - 1] >> (8 - len_shift % 8);
            res->vector[part] = bb->vector[part - len_shift / 8];
            res->vector[part] <<= len_shift % 8;
            res->vector[part] |= first_byte;
        }

        res->vector[len_shift / 8] = bb->vector[0];
        res->vector[len_shift / 8] <<= len_shift % 8;

        for (size_t part = 0; part < len_shift / 8; ++part){
            res->vector[part] = 0;
        }
        res->vector[len_shift / 8] >>= len_shift % 8;
        res->vector[len_shift / 8] <<= len_shift % 8;
    }
    return ERR_OK;
}

int right_shift (BB* bb, BB* res, int len_shift){

    if (bb == NULL || res == NULL || len_shift < 0) {
        return ERR_BAD_ARG;
    }
    if (len_shift >= len_bits(bb)) {
        memset(res->vector, 0, MAX_PARTS);
        res->n_bit_ = 1;
        res->n_byte_ = 0;
    }
    else {
        size_t last_part = bb->n_byte_ + (bb->n_bit_ > 0) - 1;
        size_t  len_new_vec = len_bits(bb) - len_shift;

        res->n_byte_ = len_new_vec / 8;
        res->n_bit_ = len_new_vec % 8;

        size_t end_new_vec = last_part - len_shift / 8;

        for (size_t part = 0; part < end_new_vec; part++)
        {
            uint8_t first_byte = bb->vector[part + len_shift / 8 + 1] << (8 - len_shift % 8);
            res->vector[part] = bb->vector[part + len_shift / 8];
            res->vector[part] >>= len_shift % 8;
            res->vector[part] |= first_byte;
        }

        res->vector[end_new_vec] = bb->vector[end_new_vec + len_shift / 8];
        res->vector[end_new_vec] >>= len_shift % 8;
    }
    return ERR_OK;
}

int left_cycle_shift (BB* bb, BB* res, int len_shift) {
    if (bb == NULL || res == NULL) {
        return ERR_BAD_ARG;
    }
    if (len_shift < 0) {
        return right_cycle_shift(bb, res, -len_shift);
    }
    len_shift %= len_bits(bb);
    memcpy(res, bb, MAX_PARTS);
    res->n_bit_ = bb->n_bit_;
    res->n_byte_ = bb->n_byte_;
    reverse_bits(res, 0, len_shift);
    reverse_bits(res, len_shift, len_bits(res));
    reverse_bits(res, 0, len_bits(res));
    return ERR_OK;
}

int right_cycle_shift (BB* bb, BB* res, int len_shift){
    if (bb == NULL || res == NULL) {
        return ERR_BAD_ARG;
    }
    int n_shift;
    if (len_shift < 0) {
        n_shift = -len_shift;
    }
    else {
        n_shift = len_bits(bb) - len_shift;
    }
    return left_cycle_shift(bb, res, n_shift);
}
