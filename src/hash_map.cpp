#include "hash_map.h"

#define ALPHABET_TOTALNUMBER 24

// a = 97, b = 98, ... z = 122 in ASCII
// letterA = int('a') = ASCII 97, letterZ = int('z') = ASCII 122
// even if OS uses different table, as long as the alphabet is sequentially stored, int('a') will
//  yield the first letter of the alphabet.

hash_map::hash_map()
{
    hashFuncTable = new int[ALPHABET_TOTALNUMBER];
    totalSize = 0;
    table = new dataHM[0];
    letterA = int('a');
}

void hash_table::

hash_map::~hash_map()
{
    //dtor
}
