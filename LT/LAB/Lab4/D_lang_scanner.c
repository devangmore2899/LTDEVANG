#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int Delimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return 1;
    return 0;
}
int Operator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=')
        return 1;
    return 0;
}
int validIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || Delimiter(str[0]) == 1)
        return 0;
    return 1;
}
int Keyword(char* str)
{
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") ||
         !strcmp(str, "continue") || !strcmp(str, "int")
        || !strcmp(str, "double") || !strcmp(str, "float")
        || !strcmp(str, "return") || !strcmp(str, "char")
        || !strcmp(str, "case") || !strcmp(str, "char")
        || !strcmp(str, "sizeof") || !strcmp(str, "long")
        || !strcmp(str, "short") || !strcmp(str, "typedef")
        || !strcmp(str, "switch") || !strcmp(str, "unsigned")
        || !strcmp(str, "void") || !strcmp(str, "static")
        || !strcmp(str, "struct") || !strcmp(str, "goto"))
        return 1;
    return 0;
}
int Integer(char* str)
{
    int i, len = strlen(str);

    if (len == 0)
        return 0;
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return 0;
    }
    return 1;
}
int RealNumber(char* str)
{
    int i, len = strlen(str);
    int hasDecimal = 0;

    if (len == 0)
        return 0;
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return 0;
        if (str[i] == '.')
            hasDecimal = 1;
    }
    return (hasDecimal);
}
char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));

    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}
void parse(char* str)
{
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len && left <= right) {
        if (Delimiter(str[right]) == 0)
            right++;

        if (Delimiter(str[right]) == 1 && left == right) {
            if (Operator(str[right]) == 1)
                printf("'%c' IS AN OPERATOR\n", str[right]);

            right++;
            left = right;
        } else if (Delimiter(str[right]) == 1 && left != right
                   || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);

            if (Keyword(subStr) == 1)
                printf("'%s' IS A KEYWORD\n", subStr);

            else if (Integer(subStr) == 1)
                printf("'%s' IS AN INTEGER\n", subStr);

            else if (RealNumber(subStr) == 1)
                printf("'%s' IS A REAL NUMBER\n", subStr);

            else if (validIdentifier(subStr) == 1
                     && Delimiter(str[right - 1]) == 0)
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);

            else if (validIdentifier(subStr) == 0
                     && Delimiter(str[right - 1]) == 0)
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
            left = right;
        }
    }
    return;
}
int main()
{
    char str[100] = "int a = b + 1c; if(a>b){ a=a+b} ";
    parse(str);
    return (0);
}
