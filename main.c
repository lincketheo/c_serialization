
#include "bit_serialize.h"
#include <stdio.h>

int
main ()
{
  bits_data bd = { 0 };
  if (bits_data_init (&bd))
    return 1;

  // Packing data is maximally memory efficient
  bits_data_push (&bd, 10, 30);
  bits_data_push (&bd, UINT64_MAX, 64);
  bits_data_push (&bd, 1, 1);
  bits_data_push (&bd, 2, 2);
  bits_data_push (&bd, UINT32_MAX, 64);
  bits_data_push (&bd, UINT32_MAX, 32);
  bits_data_push (&bd, 12093710247, 60);

  printf ("Bit data size in bytes: %zu\n", bd.byte_i + 1);
  printf ("Bit data capacity in bytes: %zu\n", bd.data_capacity_bytes);
  printf ("Bit data size in bits: %zu\n", bd.data_len_bits);

  // Unpacking data converts from memory efficient to memory inefficient
  uint8_t *dest = malloc (bd.data_len_bits * sizeof *dest);
  bits_data_unpack (&bd, dest, bd.data_len_bits);
  printf ("Bits:\n");
  for (int i = 0; i < bd.data_len_bits; ++i)
    {
      printf ("%d", dest[i]);
    }
  printf ("\n");
  free (dest);

  // Get data at each index - memory efficient
  printf ("Elements\n");
  size_t ind = 0;
  printf ("%zu\n", bits_data_get (&bd, ind, 30));
  ind += 30;
  printf ("%zu\n", bits_data_get (&bd, ind, 64));
  ind += 64;
  printf ("%zu\n", bits_data_get (&bd, ind, 1));
  ind += 1;
  printf ("%zu\n", bits_data_get (&bd, ind, 2));
  ind += 2;
  printf ("%zu\n", bits_data_get (&bd, ind, 64));
  ind += 64;
  printf ("%zu\n", bits_data_get (&bd, ind, 32));
  ind += 32;
  printf ("%zu\n", bits_data_get (&bd, ind, 60));

  // Don't forget to free
  bits_data_free (&bd);

  return 0;
}
