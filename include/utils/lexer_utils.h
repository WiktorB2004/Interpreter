#pragma once

int is_valid_char_token(char ch);
int get_text_value(char ch);
int is_bracket(char ch);
int is_operator(char ch);
int is_string_in_list(const char *target, const char *list[], int listSize);