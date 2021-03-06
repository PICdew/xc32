/* Test the `vreinterpretQf32_p8' ARM Neon intrinsic.  */
/* This file was autogenerated by neon-testgen.  */

/* { dg-do assemble } */
/* { dg-require-effective-target arm_neon_ok } */
/* { dg-options "-save-temps -O0" } */
/* { dg-add-options arm_neon } */

#include "arm_neon.h"

void test_vreinterpretQf32_p8 (void)
{
  float32x4_t out_float32x4_t;
  poly8x16_t arg0_poly8x16_t;

  out_float32x4_t = vreinterpretq_f32_p8 (arg0_poly8x16_t);
}

/* { dg-final { cleanup-saved-temps } } */
