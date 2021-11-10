#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    char filename[1024];
    scanf("%[^\n]", filename);

    FILE *fp;
    uint64_t filelength;
    fp = fopen(filename, "rb");
    fseek(fp, 0L, SEEK_END);
    filelength = ftell(fp);
    rewind(fp);
    char* filecontent = calloc(1, filelength + 1);
    fread(filecontent, filelength, 1, fp);
    fclose(fp);

    printf("#include <stdio.h>\n#include <stdint.h>\n#include <stdlib.h>\n#undef putchar\n\nint main() {\n    char *ptr = malloc(30000);\n");
    for (uint64_t i = 0; i < filelength; i++) {
        switch (filecontent[i]) {
        case '>':
            printf("    ++ptr;\n");
            break;
        case '<':
            printf("    --ptr;\n");
            break;
        case '+':
            printf("    ++*ptr;\n");
            break;
        case '-':
            printf("    --*ptr;\n");
            break;
        case '.':
            printf("    putchar(*ptr);\n");
            break;
        case ',':
            printf("    *ptr = getchar();\n");
            break;
        case '[':
            printf("    while (*ptr) {\n");
            break;
        case ']':
            printf("    }\n");
            break;
        }
    }
    printf("}\n");
}