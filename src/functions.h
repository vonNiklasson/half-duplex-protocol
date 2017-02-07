/*
 * Name: Johan Niklasson
 * Project: Half duplex protocol
 *
 * Source: functions.h
 */

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

char* get_arg_value(char *args[], const int args_len, const char *arg);
int arg_exists(char *args[], const int args_len, const char *arg);
int str_starts_with(const char *str, const char *pre);
int divide_round_up(const int n, const int d);

#endif