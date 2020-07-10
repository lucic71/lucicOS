#ifndef BITMAP_H_
#define BITMAP_H_

#include <stdint.h>
#include <stddef.h>

/*
 * bitmap_set:
 *  Sets bit at index bit in bitmap
 *
 * @param bitmap - Bitmap
 * @param bit    - Index to set
 *
 */

void bitmap_set(uint32_t *bitmap, int bit);

/*
 * bitmap_unset:
 *  Unsets bit at index bit in bitmap
 *
 * @param bitmap - Bitmap
 * @param bit    - Index to unset
 *
 */

void bitmap_unset(uint32_t *bitmap, int bit);

/*
 * bitmap_test:
 *  Tests bit at index bit in bitmap
 *
 * @param bitmap - Bitmap
 * @param bit    - Index to test
 *
 * @return - State of the respective bit
 *
 */

int bitmap_test(uint32_t *bitmap, int bit);

/*
 * bitmap_first_unset:
 *  Finds the index of the first unset bit.
 *
 * @param bitmap - Bitmap
 * @param size   - Size of bitmap
 *
 * @return - Index of first unset bit
 *
 */

int bitmap_first_unset(uint32_t *bitmap, size_t size);

#endif
