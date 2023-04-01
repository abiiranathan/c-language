#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../defer/defer.h"

void free_ptr(void *ptr) {
    free(ptr);
    printf("Free ptr\n");
}

int defer_main() {
    Deferral;

    int *p = malloc(sizeof(int));

    Defer(free_ptr(p));
    printf("Ptr dereference\n");
    *p = 42;
    printf("End of fnction\n");
    Return 0;
}

int main() {
    char *source = "___ abc123def ___ ghi456 ___";
    char *regexString = "[a-z]*([0-9]+)([a-z]*)";
    size_t maxGroups = 3;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
        printf("Could not compile regular expression.\n");
        return 1;
    };

    if (regexec(&regexCompiled, source, maxGroups, groupArray, 0) == 0) {
        unsigned int g = 0;
        for (g = 0; g < maxGroups; g++) {
            if (groupArray[g].rm_so == (size_t)-1)
                break;  // No more groups

            char sourceCopy[strlen(source) + 1];
            strncpy(sourceCopy, source, strlen(source) + 1);

            sourceCopy[groupArray[g].rm_eo] = 0;
            printf("Group %u: [%2u-%2u]: %s\n",
                   g, groupArray[g].rm_so, groupArray[g].rm_eo,
                   sourceCopy + groupArray[g].rm_so);
        }
    }

    regfree(&regexCompiled);
    return 0;
}