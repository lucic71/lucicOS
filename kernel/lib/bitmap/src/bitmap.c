#include "lib/bitmap.h"

/*
 * bitmap_set:
 * -----------
 *
 */

void bitmap_set(uint32_t *bitmap, int bit) {
    bitmap[bit / 32] |= (1 << (bit % 32));
}

/*
 * bitmap_unset:
 * -------------
 *
 */

void bitmap_unset(uint32_t *bitmap, int bit) {
    bitmap[bit / 32] &= ~(1 << (bit % 32));
}

/*
 * bitmap_test:
 * ------------
 *
 */

int bitmap_test(uint32_t *bitmap, int bit) {
    return bitmap[bit / 32] & (1 << (bit % 32)); 
}

/*
 * bitmap_first_unset:
 * -------------------
 *
 *  Search in each double word for an unset bit. If a double
 *  word is fully set then skip testing it.
 *
 *  It may be the case that at the end of the bitmap there are
 *  some bits that do not fully fit a double word. Last if's job
 *  is to test these reamining bits.
 *
 */


int bitmap_first_unset(uint32_t *bitmap, size_t size) {

    uint32_t rem_bits = size % 32;

    for (uint32_t i = 0; i < size / 32; i++)
        if (bitmap[i] != 0XFFFFFFFF)
            for (int j = 0; j < 32; j++)
                if (!(bitmap[i] & (1 << j)))
                    return (i * 32) + j;

    if (rem_bits) {

        for (uint32_t j = 0; j < rem_bits; j++)
            if (!(bitmap[size / 32] & (1 << j)))
                    return ((size / 32) * 32) + j;

    }

    return -1;
}
