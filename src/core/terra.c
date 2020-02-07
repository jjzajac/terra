#include "terra.h"

extern FILE *yyin;
int yylex();
int yyparse();

FILE *prepFile(char *inName)
{
    FILE *in = fopen(inName, "r");

    if (in == NULL)
        perror("Error");

    FILE *out = tmpfile();

    fprintf(out, "%s\n", START_PROGRAM);

    fseek(in, 0, SEEK_END);
    long size = ftell(in);
    fseek(in, 0, SEEK_SET);

    char *buffer = (char *)malloc(sizeof(char) * size);
    // TODO check if buffer is create
    size_t result = fread(buffer, sizeof(char), size, in);
    // TODO check result
    result = fwrite(buffer, sizeof(char), size, out);
    // TODO check result
    buffer = freeAndNullify(buffer);
    // TODO check if is delete

    fprintf(out, "\n%s", END_PROGRAM);

    rewind(out);

    return out;
}

int main()
{
    yyin = prepFile("test/easy");

    yyparse();

    fclose(yyin);

    return 0;
}
