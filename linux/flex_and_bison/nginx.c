#include <stdio.h>
void yyerror(char const *s) { fprintf(stderr, "%s\n", s); }

int main(void)
{
  return yyparse();
}
