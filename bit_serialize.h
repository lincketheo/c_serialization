#ifndef _BIT_SERIALIZE_H_
#define _BIT_SERIALIZE_H_

#include <stdint.h>
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define STARTING_CAPACITY_BYTES 10

typedef struct {
  uint8_t* data; // data is a list of bytes, but bits are packed tightly
  size_t data_len_bits;
  size_t byte_i; // Current byte index - for readability only - functionally dependent on data_len_bits
  size_t data_capacity_bytes;
} bits_data;

/**
 * @brief Initialize a bit field. Assumes bits_data was never initialized
 *
 * @param data The data to initialize.
 * @return 0 if successful, non zero otherwise
 */
int bits_data_init(bits_data* data);

/**
 * @brief Free's a bits_data struct buffer
 *
 * @param data The data to free
 */
void bits_data_free(bits_data* data);

/**
 * @brief Adds data to the end of the bits data struct
 *
 * @param data The data to append to
 * @param elem The element to push onto the end
 * @param nbits Number of bits that the element should occupy. More significant
 * 0's are filled in the left if [nbits] is greater than the needed bits for elem
 * @return 0 if successful non zero else
 */
int bits_data_push(bits_data* data, const uint64_t elem, const size_t nbits);

/**
 * @brief Returns the data stored at bit [start] that is of length [nbits]
 *
 * @param data The data to get from
 * @param start The starting bit index
 * @param nbits The number of bits to extract
 * @return A uint64_t with zeros to the left if nbits < 64
 */
uint64_t bits_data_get(const bits_data* data, const size_t start, const size_t nbits);

// Utility
/**
 * @brief Unpacks bits into a uint8_t array of 1's and 0's
 *
 * @param data The data to unpack
 * @param dest The output destination for the bits
 * @param len The length of dest (only for redundancy, only allowable lengths are
 * data.data_len_bits
 * @return 0 if successful, 1 else
 */
int bits_data_unpack(const bits_data* data, uint8_t* dest, const size_t len);

#if defined(__cplusplus)
}
#endif

#endif
