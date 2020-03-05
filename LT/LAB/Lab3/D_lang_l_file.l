%{

%}
DIGIT    [0-9]

ID       [a-zA-Z][a-zA-Z0-9]*

%%

{DIGIT}+    {printf( "An integer: %s (%d)\n", yytext,atoi( yytext ) );}



int|String|new|main|length|char|return|static|toLower|concat|charAt|toString|replace|reverse|substring|comareTo|equals|equalsIgnoreCase|indexOf|show|if|for|while|do|exit|else|case|switch|until  {printf( "A keyword: %s\n", yytext );}

{ID}        printf( "An identifier: %s\n", yytext );

":="|"<>"|"=="|"!="|"<="|"="|"&&"|"||"|"^"|"?:"  printf( "Relational operator: %s\n", yytext );

"+"|"-"|"*"|"%"   printf( "Match operator: %s\n", yytext );

"["|"]"|"{"|"}"|"("|")"|"\""|","|";"|":"|"."  printf( "Punctuations: %s\n", yytext );

"'"[^']*"'"    printf( "string constant: %s\n", yytext );

"***"[^\n]*     /* eat up one-line comments */

[ \t\n]+          printf("Whitespace\n",yytext);

.           printf( "Unrecognized character: %s\n", yytext );

%%

int yywrap(){};
main( argc, argv )
int argc;
char **argv;
{
               ++argv, --argc;  /* skip over program name */
               if ( argc > 0 )
                       yyin = fopen( argv[0], "r" );
               else
                       yyin = stdin;

               yylex();
}

