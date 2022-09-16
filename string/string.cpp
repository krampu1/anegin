#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <assert.h>

int KR_puts(const char *s) {
    assert(s != nullptr);

    int i = 0;
    for (;       s[i]; i++) {
        if (putc(s[i], stdout) == EOF) return EOF;
    }

    if (putc('\n', stdout) == EOF) return EOF;
    return i;
}

const char * KR_strchr(const char *s, int ch) {
    assert(s != nullptr);

    do {
        if  (*s == ch) return s;
    } while (*s++);
    
    return nullptr;
}

char * KR_strchr(char *s, int ch) {
    assert(s != nullptr);

    do {
        if  (*s == ch) return s;
    } while (*s++);

    return nullptr;
}

unsigned int KR_strlen (char *s) {
    assert(s != nullptr);

    char   *p = s;
    while (*p) p++;

    return (unsigned int)(p - s);
}

unsigned int KR_strlen (const char *s) {
    assert(s != nullptr);

    const char *p = s;
    while (    *p) p++;

    return (unsigned int)(p - s);
}

void KR_strcpy(char *s, char *ct) {
    assert(s  != nullptr);
    assert(ct != nullptr);

    while ((*s = *ct)) {
        s++;
        ct++;
    }
}

void KR_strcpy(char *s, const char *ct) {
    assert(s  != nullptr);
    assert(ct != nullptr);

    while ((*s = *ct)) {
        s++;
        ct++;
    }
}

void KR_strncpy(char *s, char *ct, int n) {
    assert(s  != nullptr);
    assert(ct != nullptr);

    for (int i = 0; i < n && (*s = *ct); i++) {
        s++;
        ct++;
    }
    *s = 0;
}

void KR_strncpy(char *s, const char *ct, int n) {
    assert(s  != nullptr);
    assert(ct != nullptr);

    for (int i = 0; i < n && (*s = *ct); i++) {
        s++;
        ct++;
    }
    *s = 0;
}

void KR_strcat(char *s, char *ct) {
    assert(s  != nullptr);
    assert(ct != nullptr);

    KR_strcpy(KR_strchr(s, '\0'), ct);
}

void KR_strcat(char *s, const char *ct) {
    assert(s  != nullptr);
    assert(ct != nullptr);

    KR_strcpy(KR_strchr(s, '\0'), ct);
}

void KR_strncat(char    *s, char  *ct, int n) {
    assert(s  != nullptr);
    assert(ct != nullptr);

    KR_strncpy(KR_strchr(s, '\0'), ct, n);
}

void KR_strncat(char *s, const char *ct, int n) {
    assert(s  != nullptr);
    assert(ct != nullptr);

    KR_strncpy(KR_strchr(s, '\0'), ct, n);
}

char * KR_fgets(char *s, int n, FILE *stream) {
    assert(s      != nullptr);
    assert(stream != nullptr);

    int c    = 0;
    char *cs = nullptr;

    cs = s;
    while (--n > 0 && (c = getc(stream)) != EOF)
        if ((*cs++ = (char)c) == '\n' ) break;

    if (cs != s && *(cs-1) == '\n') {
        *(--cs) = '\0';
    }
    else {
        *cs = '\0';
    }

    return (c == EOF && cs == s) ? nullptr : s;
}

char * KR_strdup(char *s) {
    assert(s != nullptr);

    char *p = nullptr;
    p = (char *) malloc(KR_strlen(s) + 1);

    KR_strcpy(p, s);

    return p;
}

char * KR_strdup(const char *s) {
    assert(s != nullptr);

    char *p = nullptr;
    p = (char *) malloc(KR_strlen(s) + 1);

    KR_strcpy(p, s);

    return p;
}

bool KR_strcmp(char *s1, char *s2) {
    assert(s1 != nullptr);
    assert(s2 != nullptr);

    int i = -1; // (-1)++ = 0 -> first element
    do {
        i++;
        if (s1[i] < s2[i]) {
            return true;
        }
        else if (s1[i] > s2[i]) {
            return false;
        }
    } while (s1[i] != 0 && s2[i] != 0);
    return true;
}

bool is_letter(char ch) {
    return (('a' <= ch && ch <= 'z')
             || ('A' <= ch && ch <= 'Z')
             || ch == 0); 
}

bool KR_strcmp_letonly(char *s1, char *s2) {
    assert(s1 != nullptr);
    assert(s2 != nullptr);
    
    do {
        while (!is_letter(*s1)) s1++;
        while (!is_letter(*s2)) s2++;

        if (*s1 < *s2) {
            return true;
        }
        else if (*s1 > *s2) {
            return false;
        }
    } while (*s1++ != 0 && *s2++ != 0);
    return true;
}

bool KR_strcmp_letonly_r(char *s1, char *s2) {
    assert(s1 != nullptr);
    assert(s2 != nullptr);

    char *p1 = s1;
    char *p2 = s2;

    assert(p1 != nullptr);
    assert(p2 != nullptr);

    while (*p1 != 0) {
        p1++;
    }
    while (*p2 != 0) {
        p2++;
    }

    do {
        p1--;p2--;
        while (p1 >= s1 && !is_letter(*p1)) p1--;
        while (p2 >= s2 && !is_letter(*p2)) p2--;

        if (p1 < s1) {
            return true;
        }
        if (p2 < s2) {
            return false;
        }
        
        if (*p1 < *p2) {
            return true;
        }
        else if (*p1 > *p2) {
            return false;
        }
    } while (true);

    return true;
}

void KR_strswap(char **s1, char **s2) {
    assert(s1 != nullptr);
    assert(s1 != nullptr);

    char *b = *s1;
    *s1 = *s2;
    *s2 = b;
}