// compiler includes
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// cunit includes
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

// Project includes
#include "bit_serialize.h"

void test_bits_serialize_edge_cases(void)
{
  bits_data bd = { 0 };
  bits_data_init(&bd);

  size_t big_num = 15514242423412143;
  bits_data_push(&bd, big_num, 54);
  bits_data_push(&bd, big_num, 54);

  size_t num_ones = 19;
  for (int i = 0; i < num_ones; ++i)
    bits_data_push(&bd, 1, 1);

  size_t num_twos = 19;
  for (int i = 0; i < num_twos; ++i)
    bits_data_push(&bd, 2, 2);

  uint64_t dat = bits_data_get(&bd, 0, 54);
  CU_ASSERT_EQUAL(dat, big_num);
  dat = bits_data_get(&bd, 54, 54);
  CU_ASSERT_EQUAL(dat, big_num);

  for (int i = 108; i < 108 + num_ones; ++i) {
    dat = bits_data_get(&bd, i, 1);
    CU_ASSERT_EQUAL(dat, 1);
  }
  for (int i = 108 + num_ones; i < 108 + num_ones + num_twos * 2; i += 2) {
    uint64_t dat = bits_data_get(&bd, i, 2);
    CU_ASSERT_EQUAL(dat, 2);
  }
  bits_data_free(&bd);
}

static uint64_t rand_u64()
{
  return (uint64_t)rand() << 32 | rand();
}

static uint64_t rand_u64_range(uint64_t low, uint64_t high)
{
  assert(low < high);
  return low + (rand_u64() % (high - low));
}

static size_t count_bits(uint64_t value)
{
  size_t bits = 0;
  while (value) {
    bits++;
    value >>= 1;
  }
  return bits;
}

void test_bits_serialize_random(void)
{
  size_t num = 10;
  size_t* bit_sizes = malloc(num * sizeof *bit_sizes);
  uint64_t* elems = malloc(num * sizeof *bit_sizes);

  bits_data bd = { 0 };
  bits_data_init(&bd);

  for (int i = 0; i < num; ++i) {
    elems[i] = rand_u64();
    // Random size in range [len(elems[i]), 64]
    bit_sizes[i] = count_bits(elems[i]) + rand_u64_range(0, 10);
    if (bit_sizes[i] > 64)
      bit_sizes[i] = 64;
    bits_data_push(&bd, elems[i], bit_sizes[i]);
  }

  size_t ind = 0;
  for (int i = 0; i < num; ++i) {
    uint64_t ret = bits_data_get(&bd, ind, bit_sizes[i]);
    CU_ASSERT_EQUAL(ret, elems[i]);
    ind += bit_sizes[i];
  }

  bits_data_free(&bd);
}

int main()
{
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("bits serialize test", 0, 0);
  CU_add_test(suite, "random", test_bits_serialize_random);
  CU_add_test(suite, "edge cases", test_bits_serialize_edge_cases);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
}
