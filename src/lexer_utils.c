// Check if char is valid ID or VAL
int is_valid_char_token(char ch)
{
    return isalnum(ch) || ch == '_';
}

// A function to help distinguish between T_VAL and VAL
int get_text_value(char ch)
{
    return (ch > 31 && ch < 127 && ch != 34 && ch != 39) || ch == 92;
}

// A function to check if char is valid bracket (Any bracket)
int is_bracket(char ch)
{
    return ch == 123 || ch == 125 || ch == 91 || ch == 93 || ch == 40 || ch == 41;
}

// A function to check if char is valid operator (Logic and Relational operators)
int is_operator(char ch)
{
    return ch == 60 || ch == 61 || ch == 62 || ch == 33 || ch == 38 || ch == 124;
}

// A function to check if string exists in list
int is_string_in_list(const char *target, const char *list[], int listSize)
{
    for (int i = 0; i < listSize; ++i)
    {
        if (strcmp(target, list[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}