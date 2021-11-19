#include "trie_generic.h"
#include "string.h"
#include "stdio.h"

const char *pattern[] = {
    "fuck",
    "shit",
    "damn",
    "sex",
    "dick",
    "suck",
    NULL
};

const char *check[] = {
    "normal",
    "shit",
    "1shit1",
    "1shitfuck",
    "1shit1fuck",
    "1shit1fuck1dick",
    "1shit1fuck1dick1",
    "123",
    "",
    NULL
};

int main() {
    
    TrieGeneric<char> trie;

    for(int i = 0; ; ++i) {
        const char *p = pattern[i];

        if(!p) {
            break;
        }

        trie.AddKeyword(p, strlen(p));
    }

    for(int i = 0; ; ++i) {
        const char *c = check[i];

        if(!c) {
            break;
        }

        char check_buffer[1024];

        snprintf(check_buffer, sizeof(check_buffer), "%s", c);

        size_t result = trie.CheckAndReplace(check_buffer, strlen(check_buffer), '*');

        printf("check %s result: %s (%zd)\n", c, check_buffer, result);
    }

    return 0;
}

