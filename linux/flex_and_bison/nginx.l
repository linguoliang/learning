%{
#include "nginx.tab.h"
%}

%option noyywrap

%%

"server" {return SERVER;}
"listern" {return LISTEN;}
"server_name" {return NAME;}
"access_log" {return ALOG;}
"error_log" {return ELOG;}
"location" {return LOCATION;}
"proxy_pass" {return PROXY_PASS;}
"include" {return INCLUDE;}

"{" {return OP;}
"}" {return CP;}
";" {return TERMINATOR;}
[\s\t\r\n] {}
[A-Za-z0-9\.\/:_]+ {printf("%s\n", yytext); return VALUE;}

%%
