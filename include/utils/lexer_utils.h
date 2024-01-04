#pragma once

/*!
 * \brief Validating char value.
 *
 * Function validating if char value is alphanumeric or _
 * @param ch character to validate
 * @return returning 1/0 as true/false
 */
int is_valid_char_token(char ch);

/*!
 * \brief Helping with extracting text values.
 *
 * Helper function to extract value of string/char from user program.
 * Returns true when the ch is not " or ' and is valid text value - any letter/number and symbol
 * @param ch character to check
 * @return returning 1/0 as true/false
 */
int get_text_value(char ch);

/*!
 * \brief Checking if char is bracket.
 *
 * Check if the char value is any type of bracket
 * @param ch character to check
 * @return returning 1/0 as true/false
 */
int is_bracket(char ch);

/*!
 * \brief Checking if char is operator.
 *
 * Check if the char value is any type of operator
 * @param ch character to check
 * @return returning 1/0 as true/false
 */
int is_operator(char ch);

/*!
 * \brief Checks if target is in the list.
 *
 * Check if target string is inside list
 * @param target target of search
 * @param list list in which to look for target
 * @param list_size size of the list
 * @return returning 1/0 as true/false
 */
int is_string_in_list(const char *target, const char *list[], int list_size);
