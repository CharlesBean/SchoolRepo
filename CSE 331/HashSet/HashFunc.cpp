/**
* Charles Bean
*/

#include "HashFunc.h"
#include <iostream>

using namespace std;


/**
 * Hash function from figure 5.2 of the book - Page 192. A simple hash function that just
 * calculates the hash by multiplying a total hash by 37, and then adding the ascii value
 * of the current character. Quick - but bad with large table sizes
 */
unsigned int HashA(const std::string& s)
{
    unsigned int hashVal = 0;

    for(char ch : s)
        hashVal = 37 * hashVal + ch;

    return hashVal;
}

/**
 * The Jenkins Hash function. Designed by Bob Jenkins, it is a non-cryptographic hash function, that
 * uses an "avalanche" behavior to drastically change the output even if an input is just slightly changed
 */
unsigned int HashB(const std::string& s)
{
    uint32_t hash, i;

    for(hash = i = 0; i < s.length(); ++i)
    {
        hash += s[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

/**
 * The Murmur 3 Hash function created by Austin Appleby. It is non-cryptographic and is represented below in
 * it's 32-bit version.
 */
unsigned int HashC(const std::string& s)
{
    uint32_t seed = 12345;
    const char * key = s.data();
    int len = (int)s.length();

    static const uint32_t c1 = 0xcc9e2d51;
    static const uint32_t c2 = 0x1b873593;
    static const uint32_t r1 = 15;
    static const uint32_t r2 = 13;
    static const uint32_t m = 5;
    static const uint32_t n = 0xe6546b64;

    uint32_t hash = seed;

    const int nblocks = len / 4;
    const uint32_t *blocks = (const uint32_t *) key;
    int i;
    for (i = 0; i < nblocks; i++) {
        uint32_t k = blocks[i];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        hash ^= k;
        hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
    }

    const uint8_t *tail = (const uint8_t *) (key + nblocks * 4);
    uint32_t k1 = 0;

    switch (len & 3) {
        case 3:
            k1 ^= tail[2] << 16;
        case 2:
            k1 ^= tail[1] << 8;
        case 1:
            k1 ^= tail[0];

            k1 *= c1;
            k1 = (k1 << r1) | (k1 >> (32 - r1));
            k1 *= c2;
            hash ^= k1;
    }

    hash ^= len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}