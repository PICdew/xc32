/* { dg-do run { target mips*-*-* } } */
/* { dg-options "-O2 -mips3d" } */
/* { dg-prune-output "require 64-bit h/w floating point" } */
/* { dg-prune-output "Assembler messages:\nError: -mfp32 used with -mips3d" } */
/* { dg-skip-if "-mips3d && -mips16 not supported" "mips*-sde-elf" "-mips16" "" } */
/* { dg-skip-if "-mips3d needs 64-bit floating point support" "mips*-sde-elf" "-mips32*" "-mfp64" } */

/* Test MIPS-3D absolute compare (doubles) builtin functions */

#if (((__mips == 32 && __mips_isa_rev == 2) || __mips == 64) \
	&& defined(__mips_hard_float) && __mips_fpr == 64)

int test0 (double a, double b);
int test1 (double a, double b);
int test2 (double a, double b);
int test3 (double a, double b);
int test4 (double a, double b);
int test5 (double a, double b);
int test6 (double a, double b);
int test7 (double a, double b);
int test8 (double a, double b);
int test9 (double a, double b);
int test10 (double a, double b);
int test11 (double a, double b);
int test12 (double a, double b);
int test13 (double a, double b);
int test14 (double a, double b);
int test15 (double a, double b);

int main ()
{
  double a, b;
  int i;

  /* cabs.eq.d */
  a = 12;
  b = -56;
  i = 0;
  if (__builtin_mips_cabs_eq_d(a, b) != i)
     abort ();

  /* cabs.eq.d */
  a = 12;
  b = -12;
  i = 1;
  if (__builtin_mips_cabs_eq_d(a, b) != i)
     abort ();

  /* Test all operators */
  a = 1984.0;
  b = 1984.0;

  i = test0 (a, b);
  if (i != 0)
    abort ();
  i = test1 (a, b);
  if (i != 0)
    abort ();
  i = test2 (a, b);
  if (i != 1)
    abort ();
  i = test3 (a, b);
  if (i != 1)
    abort ();
  i = test4 (a, b);
  if (i != 0)
    abort ();
  i = test5 (a, b);
  if (i != 0)
    abort ();
  i = test6 (a, b);
  if (i != 1)
    abort ();
  i = test7 (a, b);
  if (i != 1)
    abort ();
  i = test8 (a, b);
  if (i != 0)
    abort ();
  i = test9 (a, b);
  if (i != 0)
    abort ();
  i = test10 (a, b);
  if (i != 1)
    abort ();
  i = test11 (a, b);
  if (i != 1)
    abort ();
  i = test12 (a, b);
  if (i != 0)
    abort ();
  i = test13 (a, b);
  if (i != 0)
    abort ();
  i = test14 (a, b);
  if (i != 1)
    abort ();
  i = test15 (a, b);
  if (i != 1)
    abort ();

  /* Reverse arguments */
  i = test0 (b, a);
  if (i != 0)
    abort ();
  i = test1 (b, a);
  if (i != 0)
    abort ();
  i = test2 (b, a);
  if (i != 1)
    abort ();
  i = test3 (b, a);
  if (i != 1)
    abort ();
  i = test4 (b, a);
  if (i != 0)
    abort ();
  i = test5 (b, a);
  if (i != 0)
    abort ();
  i = test6 (b, a);
  if (i != 1)
    abort ();
  i = test7 (b, a);
  if (i != 1)
    abort ();
  i = test8 (b, a);
  if (i != 0)
    abort ();
  i = test9 (b, a);
  if (i != 0)
    abort ();
  i = test10 (b, a);
  if (i != 1)
    abort ();
  i = test11 (b, a);
  if (i != 1)
    abort ();
  i = test12 (b, a);
  if (i != 0)
    abort ();
  i = test13 (b, a);
  if (i != 0)
    abort ();
  i = test14 (b, a);
  if (i != 1)
    abort ();
  i = test15 (b, a);
  if (i != 1)
    abort ();

# ifndef __FAST_MATH__

  /* Test all operators */
  a = 1.0/0.0 - 1.0/0.0; // QNaN
  b = 1.0/0.0 - 1.0/0.0; // QNaN

  i = test0 (a, b);
  if (i != 0)
    abort ();
  i = test1 (a, b);
  if (i != 1)
    abort ();
  i = test2 (a, b);
  if (i != 0)
    abort ();
  i = test3 (a, b);
  if (i != 1)
    abort ();
  i = test4 (a, b);
  if (i != 0)
    abort ();
  i = test5 (a, b);
  if (i != 1)
    abort ();
  i = test6 (a, b);
  if (i != 0)
    abort ();
  i = test7 (a, b);
  if (i != 1)
    abort ();
  i = test8 (a, b);
  if (i != 0)
    abort ();
  i = test9 (a, b);
  if (i != 1)
    abort ();
  i = test10 (a, b);
  if (i != 0)
    abort ();
  i = test11 (a, b);
  if (i != 1)
    abort ();
  i = test12 (a, b);
  if (i != 0)
    abort ();
  i = test13 (a, b);
  if (i != 1)
    abort ();
  i = test14 (a, b);
  if (i != 0)
    abort ();
  i = test15 (a, b);
  if (i != 1)
    abort ();

# endif /* !__FAST_MATH__ */

  printf ("Test Passes\n");
  exit (0);
}

int test0 (double a, double b)
{
  return __builtin_mips_cabs_f_d (a, b);
}

int test1 (double a, double b)
{
  return __builtin_mips_cabs_un_d (a, b);
}

int test2 (double a, double b)
{
  return __builtin_mips_cabs_eq_d (a, b);
}

int test3 (double a, double b)
{
  return __builtin_mips_cabs_ueq_d (a, b);
}

int test4 (double a, double b)
{
  return __builtin_mips_cabs_olt_d (a, b);
}

int test5 (double a, double b)
{
  return __builtin_mips_cabs_ult_d (a, b);
}

int test6 (double a, double b)
{
  return __builtin_mips_cabs_ole_d (a, b);
}

int test7 (double a, double b)
{
  return __builtin_mips_cabs_ule_d (a, b);
}

int test8 (double a, double b)
{
  return __builtin_mips_cabs_sf_d (a, b);
}

int test9 (double a, double b)
{
  return __builtin_mips_cabs_ngle_d (a, b);
}

int test10 (double a, double b)
{
  return __builtin_mips_cabs_seq_d (a, b);
}

int test11 (double a, double b)
{
  return __builtin_mips_cabs_ngl_d (a, b);
}

int test12 (double a, double b)
{
  return __builtin_mips_cabs_lt_d (a, b);
}

int test13 (double a, double b)
{
  return __builtin_mips_cabs_nge_d (a, b);
}

int test14 (double a, double b)
{
  return __builtin_mips_cabs_le_d (a, b);
}

int test15 (double a, double b)
{
  return __builtin_mips_cabs_ngt_d (a, b);
}

#else

int main ()
{
  printf ("Unsupported test\n");
  exit (0); 
}

#endif
