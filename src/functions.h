/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: functions.h
 */

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

char* get_arg_value();
int arg_exists();
int str_starts_with();
int divide_round_up();

unsigned char* convert_bits_to_binary(char* data_bits, int *ret_char_count);

int * convert_bits_to_array(char* data_bits);
int * convert_digits_to_array(char* data_digits);
int * convert_chars_to_array(char* data_chars);

#endif