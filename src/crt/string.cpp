#include "string.hpp"

// CRAP
void *memmove(void *dest, const void *src, std::size_t n) {
    register char *_dst = (char *)dest;
    register char *_src = (char *)src;
    for (std::size_t i = 0; i < n; ++i)
        _dst[i] = _src[i];
    return dest;
}

void *memset(void *s, int c, std::size_t n) {
    long int dstp = (long int)s;

    if (n >= 8) {
        std::uint32_t cccc = (std::uint8_t)c;
        cccc |= cccc << 8;
        cccc |= cccc << 16;
        while (dstp % sizeof(std::uint32_t) != 0) {
            *(std::uint8_t*)dstp = c;
            ++dstp;
            --n;
        }

        std::size_t xlen = n / (sizeof(std::uint32_t) * 8);
        while (xlen > 0) {
            std::uint32_t *p = (std::uint32_t*)dstp;
            p[0] = cccc;
            p[1] = cccc;
            p[2] = cccc;
            p[3] = cccc;
            p[4] = cccc;
            p[5] = cccc;
            p[6] = cccc;
            p[7] = cccc;
            dstp += 8 * sizeof(std::uint32_t);
            --xlen;
        }
        n %= 8 * sizeof(std::uint32_t);
    }

    while (n-- > 0) {
        *(std::uint8_t*)dstp = c;
        ++dstp;
    }
    return s;
}

void *memcpy(void *dest, const char *src, std::size_t n) {
    return memmove(dest, src, n);
}

std::size_t strlen(const char *s) {
    register const char *p = s;

    if (*p && (std::uint32_t)p % 0x4)
        ++p;
    if (!*p)
        return p - s;

    if (*p && (std::uint32_t)p % 0x4)
        ++p;
    if (!*p)
        return p - s;

    if (*p && (std::uint32_t)p % 0x4)
        ++p;
    if (!*p)
        return p - s;

    std::uint32_t lomagic = 0x01010101, himagic = 0x80808080;
    for (std::uint32_t *longword = (std::uint32_t *)p;; ++longword) {
        std::uint32_t val = *longword;
        if (((val - lomagic) & himagic) != 0) {
            const char *cp = (const char *)longword;
            if (cp[0] == '\0')
                return cp - s;
            else if (cp[1] == '\0')
                return cp - s + 1;
            else if (cp[2] == '\0')
                return cp - s + 2;
            else
                return cp - s + 3;
        }
    }
    return 0;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        ++str1;
        ++str2;
    }
    return *str1 - *str2;
}

char *strcpy(char *dest, const char *src) {
    char *ret = dest;
    while ((*dest++ = *src++))
        ;
    return ret;
}

char *stpcpy(char *dest, const char *src) {
    do
        *dest++ = *src;
    while (*src++ != '\0');
    return dest - 1;
}

char *strcat(char *dest, const char *src) {
    char *t = dest;
    dest += strlen(dest);
    strcpy(dest, src);
    return t;
}

