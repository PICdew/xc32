/* Definitions of target machine for GNU compiler.  MIPS version.
   Copyright (C) 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998
   1999, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.
   Contributed by A. Lichnewsky (lich@inria.inria.fr).
   Changed by Michael Meissner	(meissner@osf.org).
   64 bit r4000 support by Ian Lance Taylor (ian@cygnus.com) and
   Brendan Eich (brendan@microunity.com).

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */


/* Standard GCC variables that we reference.  */
extern int target_flags;

/* MIPS external variables defined in mips.c.  */

/* comparison type */
enum cmp_type
{
  CMP_SI,				/* compare four byte integers */
  CMP_DI,				/* compare eight byte integers */
  CMP_SF,				/* compare single precision floats */
  CMP_DF,				/* compare double precision floats */
  CMP_MAX				/* max comparison type */
};

/* Which processor to schedule for.  Since there is no difference between
   a R2000 and R3000 in terms of the scheduler, we collapse them into
   just an R3000.  The elements of the enumeration must match exactly
   the cpu attribute in the mips.md machine description.  */

enum processor_type
{
  PROCESSOR_DEFAULT,
  PROCESSOR_4KC,
  PROCESSOR_4KP,
  PROCESSOR_5KC,
  PROCESSOR_20KC,
  PROCESSOR_24K,
  PROCESSOR_24KX,
  PROCESSOR_74K,
  PROCESSOR_74KX,
  PROCESSOR_74KZ,
  PROCESSOR_R3000,
  PROCESSOR_R3900,
  PROCESSOR_R6000,
  PROCESSOR_R4000,
  PROCESSOR_R4100,
  PROCESSOR_R4111,
  PROCESSOR_R4120,
  PROCESSOR_R4300,
  PROCESSOR_R4600,
  PROCESSOR_R4650,
  PROCESSOR_R5000,
  PROCESSOR_R5400,
  PROCESSOR_R5500,
  PROCESSOR_R7000,
  PROCESSOR_R8000,
  PROCESSOR_R9000,
  PROCESSOR_SB1,
  PROCESSOR_SR71000
};

/* Which ABI to use.  ABI_32 (original 32, or o32), ABI_N32 (n32),
   ABI_64 (n64) are all defined by SGI.  ABI_O64 is o32 extended
   to work on a 64 bit machine.  */

#define ABI_32  0
#define ABI_N32 1
#define ABI_64  2
#define ABI_EABI 3
#define ABI_O64  4

/* Information about one recognized processor.  Defined here for the
   benefit of TARGET_CPU_CPP_BUILTINS.  */
struct mips_cpu_info
  {
    /* The 'canonical' name of the processor as far as GCC is concerned.
       It's typically a manufacturer's prefix followed by a numerical
       designation.  It should be lower case.  */
    const char *name;

    /* The internal processor number that most closely matches this
       entry.  Several processors can have the same value, if there's no
       difference between them from GCC's point of view.  */
    enum processor_type cpu;

    /* The ISA level that the processor implements.  */
    int isa;

    /* CPU specific tuning options */
    int options;
#define MIPS_OPT_BRANCHLIKELY	0x00000001
#define MIPS_OPT_PREDICTLIKELY	0x00000002
#define MIPS_OPT_NOBRANCHLIKELY	0x00000004
#define MIPS_OPT_FETCH64	0x00000008
#define MIPS_OPT_DSP		0x00000010
#define MIPS_OPT_SOFTFLOAT	0x00000020
#define MIPS_OPT_SMARTMIPS	0x00000040

    /* Multiplication costs */
    int mulsi_cost;
    int muldi_cost;
    int mulsf_cost;
    int muldf_cost;
  };

extern char mips_reg_names[][8];	/* register names (a0 vs. $4).  */
extern char mips_print_operand_punct[256]; /* print_operand punctuation chars */
extern const char *current_function_file; /* filename current function is in */
extern int num_source_filenames;	/* current .file # */
extern int mips_section_threshold;	/* # bytes of data/sdata cutoff */
extern int sym_lineno;			/* sgi next label # for each stmt */
extern int set_noreorder;		/* # of nested .set noreorder's  */
extern int set_nomacro;			/* # of nested .set nomacro's  */
extern int set_noat;			/* # of nested .set noat's  */
extern int set_volatile;		/* # of nested .set volatile's  */
extern int mips_branch_likely;		/* emit 'l' after br (branch likely) */
extern int mips_dbx_regno[];		/* Map register # to debug register # */
extern GTY(()) rtx branch_cmp[2];	/* operands for compare */
extern enum cmp_type branch_type;	/* what type of branch to use */
extern enum processor_type mips_arch;   /* which cpu to codegen for */
extern enum processor_type mips_tune;   /* which cpu to schedule for */
extern int mips_isa;			/* architectural level */
extern int mips_abi;			/* which ABI to use */
extern int mips16_hard_float;		/* mips16 without -msoft-float */
extern int mips_entry;			/* generate entry/exit for mips16 */
extern const char *mips_arch_string;    /* for -march=<xxx> */
extern const char *mips_tune_string;    /* for -mtune=<xxx> */
extern const char *mips_isa_string;	/* for -mips{1,2,3,4} */
extern const char *mips_abi_string;	/* for -mabi={32,n32,64} */
extern const char *mips_brlikely_string; /* for -mbranch-likely={yes,no,predict} */
extern const char *mips_branch_cost_string; /* for -mbranch-cost=N */
extern const char *mips_no_data_in_code_string; /* for -mno-data-in-code */
extern const char *mips_code_xonly_string;	/* for -mcode-xonly */
extern const char *mips_flip_mips16_string;	/* for -mflip-mips16 */
extern const char *mips_cache_flush_func;/* for -mflush-func= and -mno-flush-func */
extern int mips_string_length;		/* length of strings for mips16 */
extern const struct mips_cpu_info mips_cpu_info_table[];
extern const struct mips_cpu_info *mips_arch_info;
extern const struct mips_cpu_info *mips_tune_info;

/* Macros to silence warnings about numbers being signed in traditional
   C and unsigned in ISO C when compiled on 32-bit hosts.  */

#define BITMASK_HIGH	(((unsigned long)1) << 31)	/* 0x80000000 */
#define BITMASK_UPPER16	((unsigned long)0xffff << 16)	/* 0xffff0000 */
#define BITMASK_LOWER16	((unsigned long)0xffff)		/* 0x0000ffff */


/* Run-time compilation parameters selecting different hardware subsets.  */

/* Macros used in the machine description to test the flags.  */

/* Bits for real switches */
#define MASK_INT64	   0x00000001	/* ints are 64 bits */
#define MASK_LONG64	   0x00000002	/* longs are 64 bits */
#define MASK_SPLIT_ADDR	   0x00000004	/* Address splitting is enabled.  */
#define MASK_NO_FUSED_MADD 0x00000008   /* Don't generate floating point
multiply-add operations.  */
#define MASK_GAS	   0x00000010	/* Gas used instead of MIPS as */
#define MASK_NAME_REGS	   0x00000020	/* Use MIPS s/w reg name convention */
#define MASK_EXPLICIT_RELOCS 0x00000040 /* Use relocation operators.  */
#define MASK_MEMCPY	   0x00000080	/* call memcpy instead of inline code*/
#define MASK_SOFT_FLOAT	   0x00000100	/* software floating point */
#define MASK_FLOAT64	   0x00000200	/* fp registers are 64 bits */
#define MASK_ABICALLS	   0x00000400	/* emit .abicalls/.cprestore/.cpload */
#define MASK_XGOT	   0x00000800	/* emit big-got PIC */
#define MASK_LONG_CALLS	   0x00001000	/* Always call through a register */
#define MASK_64BIT	   0x00002000	/* Use 64 bit GP registers and insns */
#define MASK_EMBEDDED_PIC  0x00004000	/* Generate embedded PIC code */
#define MASK_EMBEDDED_DATA 0x00008000	/* Reduce RAM usage, not fast code */
#define MASK_BIG_ENDIAN	   0x00010000	/* Generate big endian code */
#define MASK_SINGLE_FLOAT  0x00020000	/* Only single precision FPU.  */
#define MASK_MAD	   0x00040000	/* Generate mad/madu as on 4650.  */
#define MASK_4300_MUL_FIX  0x00080000   /* Work-around early Vr4300 CPU bug */
#define MASK_MIPS16	   0x00100000	/* Generate mips16 code */
#define MASK_NO_CHECK_ZERO_DIV \
			   0x00200000	/* divide by zero checking */
#define MASK_FIX_24K_E48   0x00400000	/* Workaround for the 24K E48 bug.  */
#define MASK_UNINIT_CONST_IN_RODATA \
			   0x00800000	/* Store uninitialized
consts in rodata */
#define MASK_FIX_SB1       0x01000000   /* Work around SB-1 errata.  */
#define MASK_PAIRED_SINGLE 0x02000000	/* Support paired single FPU.  */
#define MASK_MIPS3D        0x04000000   /* Support MIPS-3D instructions.  */
#define MASK_SMARTMIPS     0x08000000   /* Support smartmips instructions.  */
#define MASK_MIPS16E       0x10000000   /* Generate mips16e code  */
#define MASK_NO_FLOAT      0x20000000   /* No floating point */
#define MASK_DSP	   0x40000000	/* Support MIPS DSP instructions.  */
#define MASK_DSPR2	   0x80000000	/* Support MIPS DSPR2 instructions.  */
/* Debug switches, not documented */
#define MASK_DEBUG	0		/* unused */
#define MASK_DEBUG_A	0		/* don't allow <label>($reg) addrs */
#define MASK_DEBUG_B	0		/* GO_IF_LEGITIMATE_ADDRESS debug */
#define MASK_DEBUG_C	0		/* don't expand seq, etc.  */
#define MASK_DEBUG_D	0		/* don't do define_split's */
#define MASK_DEBUG_E	0		/* function_arg debug */
#define MASK_DEBUG_F	0		/* ??? */
#define MASK_DEBUG_G	0		/* don't support 64 bit arithmetic */
#define MASK_DEBUG_I	0		/* unused */

#define MCHP_MASK_SMART_IO		(1u<<0)	/* -msmart-io enabled */

/* Dummy switches used only in specs */
#define MASK_MIPS_TFILE	0		/* flag for mips-tfile usage */

/* r4000 64 bit sizes */
#define TARGET_INT64		(target_flags & MASK_INT64)
#define TARGET_LONG64		(target_flags & MASK_LONG64)
#define TARGET_FLOAT64		(target_flags & MASK_FLOAT64)
#define TARGET_64BIT		(target_flags & MASK_64BIT)

/* Mips vs. GNU linker */
#define TARGET_SPLIT_ADDRESSES	(target_flags & MASK_SPLIT_ADDR)

/* Mips vs. GNU assembler */
#define TARGET_GAS		(target_flags & MASK_GAS)
#define TARGET_MIPS_AS		(!TARGET_GAS)

/* Debug Modes */
#define TARGET_DEBUG_MODE	(target_flags & MASK_DEBUG)
#define TARGET_DEBUG_A_MODE	(target_flags & MASK_DEBUG_A)
#define TARGET_DEBUG_B_MODE	(target_flags & MASK_DEBUG_B)
#define TARGET_DEBUG_C_MODE	(target_flags & MASK_DEBUG_C)
#define TARGET_DEBUG_D_MODE	(target_flags & MASK_DEBUG_D)
#define TARGET_DEBUG_E_MODE	(target_flags & MASK_DEBUG_E)
#define TARGET_DEBUG_F_MODE	(target_flags & MASK_DEBUG_F)
#define TARGET_DEBUG_G_MODE	(target_flags & MASK_DEBUG_G)
#define TARGET_DEBUG_I_MODE	(target_flags & MASK_DEBUG_I)

/* Reg. Naming in .s ($21 vs. $a0) */
#define TARGET_NAME_REGS	(target_flags & MASK_NAME_REGS)

/* call memcpy instead of inline code */
#define TARGET_MEMCPY		(target_flags & MASK_MEMCPY)

/* .abicalls, etc from Pyramid V.4 */
#define TARGET_ABICALLS		(target_flags & MASK_ABICALLS)
#define TARGET_XGOT		(target_flags & MASK_XGOT)

/* software floating point */
#define TARGET_SOFT_FLOAT	(target_flags & MASK_SOFT_FLOAT)
#define TARGET_HARD_FLOAT	(! TARGET_SOFT_FLOAT)

/* no floating point */
#define TARGET_NO_FLOAT		(target_flags & MASK_NO_FLOAT)

/* always call through a register */
#define TARGET_LONG_CALLS	(target_flags & MASK_LONG_CALLS)

/* generate embedded PIC code;
   requires gas.  */
#define TARGET_EMBEDDED_PIC	(target_flags & MASK_EMBEDDED_PIC)

/* for embedded systems, optimize for
   reduced RAM space instead of for
   fastest code.  */
#define TARGET_EMBEDDED_DATA	(target_flags & MASK_EMBEDDED_DATA)

/* always store uninitialized const
   variables in rodata, requires
   TARGET_EMBEDDED_DATA.  */
#define TARGET_UNINIT_CONST_IN_RODATA	(target_flags & MASK_UNINIT_CONST_IN_RODATA)

/* don't put any mips16 data
  in code section */
#define TARGET_NO_DATA_IN_CODE	(mips_no_data_in_code_string != NULL)
#define TARGET_DATA_IN_CODE	(! TARGET_NO_DATA_IN_CODE)
/* generate big endian code.  */
/* code section is exec only */
#define TARGET_CODE_XONLY	(mips_code_xonly_string != NULL)
#define TARGET_BIG_ENDIAN	(target_flags & MASK_BIG_ENDIAN)

#define TARGET_SINGLE_FLOAT	(target_flags & MASK_SINGLE_FLOAT)
#define TARGET_DOUBLE_FLOAT	(! TARGET_SINGLE_FLOAT)

#define TARGET_MAD		(target_flags & MASK_MAD)

#define TARGET_FUSED_MADD	(! (target_flags & MASK_NO_FUSED_MADD))

#define TARGET_4300_MUL_FIX     (target_flags & MASK_4300_MUL_FIX)

#define TARGET_CHECK_ZERO_DIV   (!(target_flags & MASK_NO_CHECK_ZERO_DIV))

#define TARGET_FIX_SB1		(target_flags & MASK_FIX_SB1)

#define TARGET_FIX_24K_E48	(target_flags & MASK_FIX_24K_E48)

/* True if we should use NewABI-style relocation operators for
   symbolic addresses.  This is never true for mips16 code,
   which has its own conventions.  */

#define TARGET_EXPLICIT_RELOCS	(target_flags & MASK_EXPLICIT_RELOCS)


/* True if the call patterns should be split into a jalr followed by
   an instruction to restore $gp.  This is only ever true for SVR4 PIC,
   in which $gp is call-clobbered.  It is only safe to split the load
   from the call when every use of $gp is explicit.  */

#define TARGET_SPLIT_CALLS \
  (TARGET_EXPLICIT_RELOCS && TARGET_ABICALLS && !TARGET_NEWABI)

/* True if we can optimize sibling calls.  For simplicity, we only
   handle cases in which call_insn_operand will reject invalid
   sibcall addresses.  There are two cases in which this isn't true:

      - TARGET_MIPS16.  call_insn_operand accepts constant addresses
	but there is no direct jump instruction.  It isn't worth
	using sibling calls in this case anyway; they would usually
	be longer than normal calls.

      - TARGET_ABICALLS && !TARGET_EXPLICIT_RELOCS.  call_insn_operand
	accepts global constants, but "jr $25" is the only allowed
	sibcall.  */

#define TARGET_SIBCALLS \
  (!TARGET_MIPS16 && (!TARGET_ABICALLS || TARGET_EXPLICIT_RELOCS))

/* True if .gpword or .gpdword should be used for switch tables.
   There are some problems with using these directives with the
   native IRIX tools:

      - It has been reported that some versions of the native n32
	assembler mishandle .gpword, complaining that symbols are
	global when they are in fact local.

      - The native assemblers don't understand .gpdword.

      - Although GAS does understand .gpdword, the native linker
	mishandles the relocations GAS generates (R_MIPS_GPREL32
	followed by R_MIPS_64).

   We therefore disable GP-relative switch tables for n32 and n64
   on IRIX targets.  */
#define TARGET_GPWORD (TARGET_ABICALLS && !(TARGET_NEWABI && TARGET_IRIX))

/* Generate mips16 code */
#define TARGET_MIPS16		(target_flags & MASK_MIPS16)
#define TARGET_MIPS16E		(target_flags & MASK_MIPS16E)

/*
 *  TARGET_SMART_IO evaluates to 0,1,2
 *    0 if MCHP_MASK_SMART_IO not set
 *    1 if MCHP_MASK_SMART_IO set and MCHP_MASK_SMART_IO_LVL clear
 *    2 if MCHP_MASK_SMART_IO set and MCHP_MASK_SMART_IO_LVL set
 */
#define MCHP_TARGET_SMART_IO ((mchp_target_flags&MCHP_MASK_SMART_IO) ? (mchp_io_size_val) : 0)

/* MIPS16e save/restore is supported for ABI_32 (o32) only */
#define TARGET_M16E_SAVE	(TARGET_MIPS16E && mips_abi == ABI_32)

/* Generic ISA defines.  */
#define ISA_MIPS1		    (mips_isa == 1)
#define ISA_MIPS2		    (mips_isa == 2)
#define ISA_MIPS3                   (mips_isa == 3)
#define ISA_MIPS4		    (mips_isa == 4)
#define ISA_MIPS32		    (mips_isa == 32)
#define ISA_MIPS32R2		    (mips_isa == 33)
#define ISA_MIPS64                  (mips_isa == 64)
#define ISA_MIPS64R2		    (mips_isa == 65)

/* Architecture target defines.  */
#define TARGET_MIPS20KC             (mips_arch == PROCESSOR_20KC)
#define TARGET_MIPS24K              (mips_arch == PROCESSOR_24K)
#define TARGET_MIPS24KX             (mips_arch == PROCESSOR_24KX)
#define TARGET_MIPS74K              (mips_arch == PROCESSOR_74K     \
				     || mips_arch == PROCESSOR_74KX \
				     || mips_arch == PROCESSOR_74KZ)
#define TARGET_MIPS3900             (mips_arch == PROCESSOR_R3900)
#define TARGET_MIPS4000             (mips_arch == PROCESSOR_R4000)
#define TARGET_MIPS4100             (mips_arch == PROCESSOR_R4100)
#define TARGET_MIPS4120             (mips_arch == PROCESSOR_R4120)
#define TARGET_MIPS4300             (mips_arch == PROCESSOR_R4300)
#define TARGET_MIPS4KC              (mips_arch == PROCESSOR_4KC)
#define TARGET_MIPS4KP              (mips_arch == PROCESSOR_4KP)
#define TARGET_MIPS5400             (mips_arch == PROCESSOR_R5400)
#define TARGET_MIPS5500             (mips_arch == PROCESSOR_R5500)
#define TARGET_MIPS5KC              (mips_arch == PROCESSOR_5KC)
#define TARGET_MIPS7000             (mips_arch == PROCESSOR_R7000)
#define TARGET_MIPS9000             (mips_arch == PROCESSOR_R9000)
#define TARGET_SB1                  (mips_arch == PROCESSOR_SB1)
#define TARGET_SR71K                (mips_arch == PROCESSOR_SR71000)

/* Scheduling target defines.  */
#define TUNE_MIPS24K                (mips_tune == PROCESSOR_24K)
#define TUNE_MIPS24KX               (mips_tune == PROCESSOR_24KX)
#define TUNE_MIPS74K                (mips_tune == PROCESSOR_74K     \
				     || mips_tune == PROCESSOR_74KX \
				     || mips_tune == PROCESSOR_74KZ)
#define TUNE_MIPS20KC               (mips_tune == PROCESSOR_20KC)
#define TUNE_MIPS3000               (mips_tune == PROCESSOR_R3000)
#define TUNE_MIPS3900               (mips_tune == PROCESSOR_R3900)
#define TUNE_MIPS4000               (mips_tune == PROCESSOR_R4000)
#define TUNE_MIPS4KC                (mips_tune == PROCESSOR_4KC)
#define TUNE_MIPS4KP                (mips_tune == PROCESSOR_4KP)
#define TUNE_MIPS5000               (mips_tune == PROCESSOR_R5000)
#define TUNE_MIPS5400               (mips_tune == PROCESSOR_R5400)
#define TUNE_MIPS5500               (mips_tune == PROCESSOR_R5500)
#define TUNE_MIPS5KC                (mips_tune == PROCESSOR_5KC)
#define TUNE_MIPS6000               (mips_tune == PROCESSOR_R6000)
#define TUNE_MIPS7000               (mips_tune == PROCESSOR_R7000)
#define TUNE_MIPS9000               (mips_tune == PROCESSOR_R9000)
#define TUNE_SB1                    (mips_tune == PROCESSOR_SB1)
#define TUNE_SR71K                  (mips_tune == PROCESSOR_SR71000)

#define TARGET_NEWABI		    (mips_abi == ABI_N32 || mips_abi == ABI_64)

#define TARGET_SMARTMIPS	    (target_flags & MASK_SMARTMIPS)
#define TARGET_PAIRED_SINGLE_FLOAT  (target_flags & MASK_PAIRED_SINGLE)
#define TARGET_MIPS3D		    (target_flags & MASK_MIPS3D)
#define TARGET_MIPS_DSP32	    (target_flags & MASK_DSP)
#define TARGET_MIPS_DSP64	    (TARGET_MIPS_DSP32 && TARGET_64BIT)
#define TARGET_MIPS_DSP32R2	    (TARGET_MIPS_DSP32 \
				     && (target_flags & MASK_DSPR2))
#define TARGET_MIPS_DSP64R2	    (TARGET_MIPS_DSP32R2 && TARGET_64BIT)

#define TARGET_GP_OPT		    (mips_section_threshold > 0)

/* Vector types supported by hardware. */
#define VECTOR_MODE_SUPPORTED_P(MODE)  \
  ((((MODE) == V2SFmode && TARGET_PAIRED_SINGLE_FLOAT) \
    || ((MODE) == V2HImode && TARGET_MIPS_DSP32) \
    || ((MODE) == V4QImode && TARGET_MIPS_DSP32) \
    || ((MODE) == V2SImode && TARGET_MIPS_DSP64) \
    || ((MODE) == V4HImode && TARGET_MIPS_DSP64) \
    || ((MODE) == V8QImode && TARGET_MIPS_DSP64)) \
   && !TARGET_MIPS16)


/* Builtin functions for MIPS */
/* NOTE: The order of mips_bdesc[] in mips.c must be the same as the order of
   enum mips_builtins{}. */
enum mips_builtins
{
  MIPS_BUILTIN_PLL_PS,
  MIPS_BUILTIN_PUL_PS,
  MIPS_BUILTIN_PLU_PS,
  MIPS_BUILTIN_PUU_PS,
  MIPS_BUILTIN_CVT_PS_S,
  MIPS_BUILTIN_CVT_S_PL,
  MIPS_BUILTIN_CVT_S_PU,
  MIPS_BUILTIN_ABS_PS,
  MIPS_BUILTIN_ALNV_PS,
  MIPS_BUILTIN_ADDR_PS,
  MIPS_BUILTIN_MULR_PS,
  MIPS_BUILTIN_CVT_PW_PS,
  MIPS_BUILTIN_CVT_PS_PW,

  MIPS_BUILTIN_RECIP1_S,
  MIPS_BUILTIN_RECIP1_D,
  MIPS_BUILTIN_RECIP1_PS,
  MIPS_BUILTIN_RECIP2_S,
  MIPS_BUILTIN_RECIP2_D,
  MIPS_BUILTIN_RECIP2_PS,

  MIPS_BUILTIN_RSQRT1_S,
  MIPS_BUILTIN_RSQRT1_D,
  MIPS_BUILTIN_RSQRT1_PS,
  MIPS_BUILTIN_RSQRT2_S,
  MIPS_BUILTIN_RSQRT2_D,
  MIPS_BUILTIN_RSQRT2_PS,

  MIPS_BUILTIN_ANY_C_F_PS,
  MIPS_BUILTIN_UPPER_C_F_PS,
  MIPS_BUILTIN_LOWER_C_F_PS,
  MIPS_BUILTIN_ALL_C_F_PS,
  MIPS_BUILTIN_ANY_C_UN_PS,
  MIPS_BUILTIN_UPPER_C_UN_PS,
  MIPS_BUILTIN_LOWER_C_UN_PS,
  MIPS_BUILTIN_ALL_C_UN_PS,
  MIPS_BUILTIN_ANY_C_EQ_PS,
  MIPS_BUILTIN_UPPER_C_EQ_PS,
  MIPS_BUILTIN_LOWER_C_EQ_PS,
  MIPS_BUILTIN_ALL_C_EQ_PS,
  MIPS_BUILTIN_ANY_C_UEQ_PS,
  MIPS_BUILTIN_UPPER_C_UEQ_PS,
  MIPS_BUILTIN_LOWER_C_UEQ_PS,
  MIPS_BUILTIN_ALL_C_UEQ_PS,
  MIPS_BUILTIN_ANY_C_OLT_PS,
  MIPS_BUILTIN_UPPER_C_OLT_PS,
  MIPS_BUILTIN_LOWER_C_OLT_PS,
  MIPS_BUILTIN_ALL_C_OLT_PS,
  MIPS_BUILTIN_ANY_C_ULT_PS,
  MIPS_BUILTIN_UPPER_C_ULT_PS,
  MIPS_BUILTIN_LOWER_C_ULT_PS,
  MIPS_BUILTIN_ALL_C_ULT_PS,
  MIPS_BUILTIN_ANY_C_OLE_PS,
  MIPS_BUILTIN_UPPER_C_OLE_PS,
  MIPS_BUILTIN_LOWER_C_OLE_PS,
  MIPS_BUILTIN_ALL_C_OLE_PS,
  MIPS_BUILTIN_ANY_C_ULE_PS,
  MIPS_BUILTIN_UPPER_C_ULE_PS,
  MIPS_BUILTIN_LOWER_C_ULE_PS,
  MIPS_BUILTIN_ALL_C_ULE_PS,
  MIPS_BUILTIN_ANY_C_SF_PS,
  MIPS_BUILTIN_UPPER_C_SF_PS,
  MIPS_BUILTIN_LOWER_C_SF_PS,
  MIPS_BUILTIN_ALL_C_SF_PS,
  MIPS_BUILTIN_ANY_C_NGLE_PS,
  MIPS_BUILTIN_UPPER_C_NGLE_PS,
  MIPS_BUILTIN_LOWER_C_NGLE_PS,
  MIPS_BUILTIN_ALL_C_NGLE_PS,
  MIPS_BUILTIN_ANY_C_SEQ_PS,
  MIPS_BUILTIN_UPPER_C_SEQ_PS,
  MIPS_BUILTIN_LOWER_C_SEQ_PS,
  MIPS_BUILTIN_ALL_C_SEQ_PS,
  MIPS_BUILTIN_ANY_C_NGL_PS,
  MIPS_BUILTIN_UPPER_C_NGL_PS,
  MIPS_BUILTIN_LOWER_C_NGL_PS,
  MIPS_BUILTIN_ALL_C_NGL_PS,
  MIPS_BUILTIN_ANY_C_LT_PS,
  MIPS_BUILTIN_UPPER_C_LT_PS,
  MIPS_BUILTIN_LOWER_C_LT_PS,
  MIPS_BUILTIN_ALL_C_LT_PS,
  MIPS_BUILTIN_ANY_C_NGE_PS,
  MIPS_BUILTIN_UPPER_C_NGE_PS,
  MIPS_BUILTIN_LOWER_C_NGE_PS,
  MIPS_BUILTIN_ALL_C_NGE_PS,
  MIPS_BUILTIN_ANY_C_LE_PS,
  MIPS_BUILTIN_UPPER_C_LE_PS,
  MIPS_BUILTIN_LOWER_C_LE_PS,
  MIPS_BUILTIN_ALL_C_LE_PS,
  MIPS_BUILTIN_ANY_C_NGT_PS,
  MIPS_BUILTIN_UPPER_C_NGT_PS,
  MIPS_BUILTIN_LOWER_C_NGT_PS,
  MIPS_BUILTIN_ALL_C_NGT_PS,
  MIPS_BUILTIN_ANY_CABS_F_PS,
  MIPS_BUILTIN_UPPER_CABS_F_PS,
  MIPS_BUILTIN_LOWER_CABS_F_PS,
  MIPS_BUILTIN_ALL_CABS_F_PS,
  MIPS_BUILTIN_ANY_CABS_UN_PS,
  MIPS_BUILTIN_UPPER_CABS_UN_PS,
  MIPS_BUILTIN_LOWER_CABS_UN_PS,
  MIPS_BUILTIN_ALL_CABS_UN_PS,
  MIPS_BUILTIN_ANY_CABS_EQ_PS,
  MIPS_BUILTIN_UPPER_CABS_EQ_PS,
  MIPS_BUILTIN_LOWER_CABS_EQ_PS,
  MIPS_BUILTIN_ALL_CABS_EQ_PS,
  MIPS_BUILTIN_ANY_CABS_UEQ_PS,
  MIPS_BUILTIN_UPPER_CABS_UEQ_PS,
  MIPS_BUILTIN_LOWER_CABS_UEQ_PS,
  MIPS_BUILTIN_ALL_CABS_UEQ_PS,
  MIPS_BUILTIN_ANY_CABS_OLT_PS,
  MIPS_BUILTIN_UPPER_CABS_OLT_PS,
  MIPS_BUILTIN_LOWER_CABS_OLT_PS,
  MIPS_BUILTIN_ALL_CABS_OLT_PS,
  MIPS_BUILTIN_ANY_CABS_ULT_PS,
  MIPS_BUILTIN_UPPER_CABS_ULT_PS,
  MIPS_BUILTIN_LOWER_CABS_ULT_PS,
  MIPS_BUILTIN_ALL_CABS_ULT_PS,
  MIPS_BUILTIN_ANY_CABS_OLE_PS,
  MIPS_BUILTIN_UPPER_CABS_OLE_PS,
  MIPS_BUILTIN_LOWER_CABS_OLE_PS,
  MIPS_BUILTIN_ALL_CABS_OLE_PS,
  MIPS_BUILTIN_ANY_CABS_ULE_PS,
  MIPS_BUILTIN_UPPER_CABS_ULE_PS,
  MIPS_BUILTIN_LOWER_CABS_ULE_PS,
  MIPS_BUILTIN_ALL_CABS_ULE_PS,
  MIPS_BUILTIN_ANY_CABS_SF_PS,
  MIPS_BUILTIN_UPPER_CABS_SF_PS,
  MIPS_BUILTIN_LOWER_CABS_SF_PS,
  MIPS_BUILTIN_ALL_CABS_SF_PS,
  MIPS_BUILTIN_ANY_CABS_NGLE_PS,
  MIPS_BUILTIN_UPPER_CABS_NGLE_PS,
  MIPS_BUILTIN_LOWER_CABS_NGLE_PS,
  MIPS_BUILTIN_ALL_CABS_NGLE_PS,
  MIPS_BUILTIN_ANY_CABS_SEQ_PS,
  MIPS_BUILTIN_UPPER_CABS_SEQ_PS,
  MIPS_BUILTIN_LOWER_CABS_SEQ_PS,
  MIPS_BUILTIN_ALL_CABS_SEQ_PS,
  MIPS_BUILTIN_ANY_CABS_NGL_PS,
  MIPS_BUILTIN_UPPER_CABS_NGL_PS,
  MIPS_BUILTIN_LOWER_CABS_NGL_PS,
  MIPS_BUILTIN_ALL_CABS_NGL_PS,
  MIPS_BUILTIN_ANY_CABS_LT_PS,
  MIPS_BUILTIN_UPPER_CABS_LT_PS,
  MIPS_BUILTIN_LOWER_CABS_LT_PS,
  MIPS_BUILTIN_ALL_CABS_LT_PS,
  MIPS_BUILTIN_ANY_CABS_NGE_PS,
  MIPS_BUILTIN_UPPER_CABS_NGE_PS,
  MIPS_BUILTIN_LOWER_CABS_NGE_PS,
  MIPS_BUILTIN_ALL_CABS_NGE_PS,
  MIPS_BUILTIN_ANY_CABS_LE_PS,
  MIPS_BUILTIN_UPPER_CABS_LE_PS,
  MIPS_BUILTIN_LOWER_CABS_LE_PS,
  MIPS_BUILTIN_ALL_CABS_LE_PS,
  MIPS_BUILTIN_ANY_CABS_NGT_PS,
  MIPS_BUILTIN_UPPER_CABS_NGT_PS,
  MIPS_BUILTIN_LOWER_CABS_NGT_PS,
  MIPS_BUILTIN_ALL_CABS_NGT_PS,

  MIPS_BUILTIN_ANY_C_F_4S,
  MIPS_BUILTIN_ALL_C_F_4S,
  MIPS_BUILTIN_ANY_C_UN_4S,
  MIPS_BUILTIN_ALL_C_UN_4S,
  MIPS_BUILTIN_ANY_C_EQ_4S,
  MIPS_BUILTIN_ALL_C_EQ_4S,
  MIPS_BUILTIN_ANY_C_UEQ_4S,
  MIPS_BUILTIN_ALL_C_UEQ_4S,
  MIPS_BUILTIN_ANY_C_OLT_4S,
  MIPS_BUILTIN_ALL_C_OLT_4S,
  MIPS_BUILTIN_ANY_C_ULT_4S,
  MIPS_BUILTIN_ALL_C_ULT_4S,
  MIPS_BUILTIN_ANY_C_OLE_4S,
  MIPS_BUILTIN_ALL_C_OLE_4S,
  MIPS_BUILTIN_ANY_C_ULE_4S,
  MIPS_BUILTIN_ALL_C_ULE_4S,
  MIPS_BUILTIN_ANY_C_SF_4S,
  MIPS_BUILTIN_ALL_C_SF_4S,
  MIPS_BUILTIN_ANY_C_NGLE_4S,
  MIPS_BUILTIN_ALL_C_NGLE_4S,
  MIPS_BUILTIN_ANY_C_SEQ_4S,
  MIPS_BUILTIN_ALL_C_SEQ_4S,
  MIPS_BUILTIN_ANY_C_NGL_4S,
  MIPS_BUILTIN_ALL_C_NGL_4S,
  MIPS_BUILTIN_ANY_C_LT_4S,
  MIPS_BUILTIN_ALL_C_LT_4S,
  MIPS_BUILTIN_ANY_C_NGE_4S,
  MIPS_BUILTIN_ALL_C_NGE_4S,
  MIPS_BUILTIN_ANY_C_LE_4S,
  MIPS_BUILTIN_ALL_C_LE_4S,
  MIPS_BUILTIN_ANY_C_NGT_4S,
  MIPS_BUILTIN_ALL_C_NGT_4S,
  MIPS_BUILTIN_ANY_CABS_F_4S,
  MIPS_BUILTIN_ALL_CABS_F_4S,
  MIPS_BUILTIN_ANY_CABS_UN_4S,
  MIPS_BUILTIN_ALL_CABS_UN_4S,
  MIPS_BUILTIN_ANY_CABS_EQ_4S,
  MIPS_BUILTIN_ALL_CABS_EQ_4S,
  MIPS_BUILTIN_ANY_CABS_UEQ_4S,
  MIPS_BUILTIN_ALL_CABS_UEQ_4S,
  MIPS_BUILTIN_ANY_CABS_OLT_4S,
  MIPS_BUILTIN_ALL_CABS_OLT_4S,
  MIPS_BUILTIN_ANY_CABS_ULT_4S,
  MIPS_BUILTIN_ALL_CABS_ULT_4S,
  MIPS_BUILTIN_ANY_CABS_OLE_4S,
  MIPS_BUILTIN_ALL_CABS_OLE_4S,
  MIPS_BUILTIN_ANY_CABS_ULE_4S,
  MIPS_BUILTIN_ALL_CABS_ULE_4S,
  MIPS_BUILTIN_ANY_CABS_SF_4S,
  MIPS_BUILTIN_ALL_CABS_SF_4S,
  MIPS_BUILTIN_ANY_CABS_NGLE_4S,
  MIPS_BUILTIN_ALL_CABS_NGLE_4S,
  MIPS_BUILTIN_ANY_CABS_SEQ_4S,
  MIPS_BUILTIN_ALL_CABS_SEQ_4S,
  MIPS_BUILTIN_ANY_CABS_NGL_4S,
  MIPS_BUILTIN_ALL_CABS_NGL_4S,
  MIPS_BUILTIN_ANY_CABS_LT_4S,
  MIPS_BUILTIN_ALL_CABS_LT_4S,
  MIPS_BUILTIN_ANY_CABS_NGE_4S,
  MIPS_BUILTIN_ALL_CABS_NGE_4S,
  MIPS_BUILTIN_ANY_CABS_LE_4S,
  MIPS_BUILTIN_ALL_CABS_LE_4S,
  MIPS_BUILTIN_ANY_CABS_NGT_4S,
  MIPS_BUILTIN_ALL_CABS_NGT_4S,

  MIPS_BUILTIN_CABS_F_S,
  MIPS_BUILTIN_CABS_UN_S,
  MIPS_BUILTIN_CABS_EQ_S,
  MIPS_BUILTIN_CABS_UEQ_S,
  MIPS_BUILTIN_CABS_OLT_S,
  MIPS_BUILTIN_CABS_ULT_S,
  MIPS_BUILTIN_CABS_OLE_S,
  MIPS_BUILTIN_CABS_ULE_S,
  MIPS_BUILTIN_CABS_SF_S,
  MIPS_BUILTIN_CABS_NGLE_S,
  MIPS_BUILTIN_CABS_SEQ_S,
  MIPS_BUILTIN_CABS_NGL_S,
  MIPS_BUILTIN_CABS_LT_S,
  MIPS_BUILTIN_CABS_NGE_S,
  MIPS_BUILTIN_CABS_LE_S,
  MIPS_BUILTIN_CABS_NGT_S,
  MIPS_BUILTIN_CABS_F_D,
  MIPS_BUILTIN_CABS_UN_D,
  MIPS_BUILTIN_CABS_EQ_D,
  MIPS_BUILTIN_CABS_UEQ_D,
  MIPS_BUILTIN_CABS_OLT_D,
  MIPS_BUILTIN_CABS_ULT_D,
  MIPS_BUILTIN_CABS_OLE_D,
  MIPS_BUILTIN_CABS_ULE_D,
  MIPS_BUILTIN_CABS_SF_D,
  MIPS_BUILTIN_CABS_NGLE_D,
  MIPS_BUILTIN_CABS_SEQ_D,
  MIPS_BUILTIN_CABS_NGL_D,
  MIPS_BUILTIN_CABS_LT_D,
  MIPS_BUILTIN_CABS_NGE_D,
  MIPS_BUILTIN_CABS_LE_D,
  MIPS_BUILTIN_CABS_NGT_D,

  MIPS_BUILTIN_MOVT_C_F_PS,
  MIPS_BUILTIN_MOVT_C_UN_PS,
  MIPS_BUILTIN_MOVT_C_EQ_PS,
  MIPS_BUILTIN_MOVT_C_UEQ_PS,
  MIPS_BUILTIN_MOVT_C_OLT_PS,
  MIPS_BUILTIN_MOVT_C_ULT_PS,
  MIPS_BUILTIN_MOVT_C_OLE_PS,
  MIPS_BUILTIN_MOVT_C_ULE_PS,
  MIPS_BUILTIN_MOVT_C_SF_PS,
  MIPS_BUILTIN_MOVT_C_NGLE_PS,
  MIPS_BUILTIN_MOVT_C_SEQ_PS,
  MIPS_BUILTIN_MOVT_C_NGL_PS,
  MIPS_BUILTIN_MOVT_C_LT_PS,
  MIPS_BUILTIN_MOVT_C_NGE_PS,
  MIPS_BUILTIN_MOVT_C_LE_PS,
  MIPS_BUILTIN_MOVT_C_NGT_PS,
  MIPS_BUILTIN_MOVT_CABS_F_PS,
  MIPS_BUILTIN_MOVT_CABS_UN_PS,
  MIPS_BUILTIN_MOVT_CABS_EQ_PS,
  MIPS_BUILTIN_MOVT_CABS_UEQ_PS,
  MIPS_BUILTIN_MOVT_CABS_OLT_PS,
  MIPS_BUILTIN_MOVT_CABS_ULT_PS,
  MIPS_BUILTIN_MOVT_CABS_OLE_PS,
  MIPS_BUILTIN_MOVT_CABS_ULE_PS,
  MIPS_BUILTIN_MOVT_CABS_SF_PS,
  MIPS_BUILTIN_MOVT_CABS_NGLE_PS,
  MIPS_BUILTIN_MOVT_CABS_SEQ_PS,
  MIPS_BUILTIN_MOVT_CABS_NGL_PS,
  MIPS_BUILTIN_MOVT_CABS_LT_PS,
  MIPS_BUILTIN_MOVT_CABS_NGE_PS,
  MIPS_BUILTIN_MOVT_CABS_LE_PS,
  MIPS_BUILTIN_MOVT_CABS_NGT_PS,
  MIPS_BUILTIN_MOVF_C_F_PS,
  MIPS_BUILTIN_MOVF_C_UN_PS,
  MIPS_BUILTIN_MOVF_C_EQ_PS,
  MIPS_BUILTIN_MOVF_C_UEQ_PS,
  MIPS_BUILTIN_MOVF_C_OLT_PS,
  MIPS_BUILTIN_MOVF_C_ULT_PS,
  MIPS_BUILTIN_MOVF_C_OLE_PS,
  MIPS_BUILTIN_MOVF_C_ULE_PS,
  MIPS_BUILTIN_MOVF_C_SF_PS,
  MIPS_BUILTIN_MOVF_C_NGLE_PS,
  MIPS_BUILTIN_MOVF_C_SEQ_PS,
  MIPS_BUILTIN_MOVF_C_NGL_PS,
  MIPS_BUILTIN_MOVF_C_LT_PS,
  MIPS_BUILTIN_MOVF_C_NGE_PS,
  MIPS_BUILTIN_MOVF_C_LE_PS,
  MIPS_BUILTIN_MOVF_C_NGT_PS,
  MIPS_BUILTIN_MOVF_CABS_F_PS,
  MIPS_BUILTIN_MOVF_CABS_UN_PS,
  MIPS_BUILTIN_MOVF_CABS_EQ_PS,
  MIPS_BUILTIN_MOVF_CABS_UEQ_PS,
  MIPS_BUILTIN_MOVF_CABS_OLT_PS,
  MIPS_BUILTIN_MOVF_CABS_ULT_PS,
  MIPS_BUILTIN_MOVF_CABS_OLE_PS,
  MIPS_BUILTIN_MOVF_CABS_ULE_PS,
  MIPS_BUILTIN_MOVF_CABS_SF_PS,
  MIPS_BUILTIN_MOVF_CABS_NGLE_PS,
  MIPS_BUILTIN_MOVF_CABS_SEQ_PS,
  MIPS_BUILTIN_MOVF_CABS_NGL_PS,
  MIPS_BUILTIN_MOVF_CABS_LT_PS,
  MIPS_BUILTIN_MOVF_CABS_NGE_PS,
  MIPS_BUILTIN_MOVF_CABS_LE_PS,
  MIPS_BUILTIN_MOVF_CABS_NGT_PS,

  /* MIPS DSP ASE Revision 0.98 3/24/2005 */
  /* Table 2-1. MIPS DSP ASE Instructions: Arithmetic */
  /* ADDQ* */
  MIPS_BUILTIN_ADDQ_PH,
  MIPS_BUILTIN_ADDQ_S_PH,
  MIPS_BUILTIN_ADDQ_QH,
  MIPS_BUILTIN_ADDQ_S_QH,
  MIPS_BUILTIN_ADDQ_S_W,
  MIPS_BUILTIN_ADDQ_PW,
  MIPS_BUILTIN_ADDQ_S_PW,
  /* ADDU* */
  MIPS_BUILTIN_ADDU_QB,
  MIPS_BUILTIN_ADDU_S_QB,
  MIPS_BUILTIN_ADDU_OB,
  MIPS_BUILTIN_ADDU_S_OB,
  /* SUBQ* */
  MIPS_BUILTIN_SUBQ_PH,
  MIPS_BUILTIN_SUBQ_S_PH,
  MIPS_BUILTIN_SUBQ_QH,
  MIPS_BUILTIN_SUBQ_S_QH,
  MIPS_BUILTIN_SUBQ_S_W,
  MIPS_BUILTIN_SUBQ_PW,
  MIPS_BUILTIN_SUBQ_S_PW,
  /* SUBU*  */
  MIPS_BUILTIN_SUBU_QB,
  MIPS_BUILTIN_SUBU_S_QB,
  MIPS_BUILTIN_SUBU_OB,
  MIPS_BUILTIN_SUBU_S_OB,
  /* ADDSC */
  MIPS_BUILTIN_ADDSC,
  /* ADDWC */
  MIPS_BUILTIN_ADDWC,
  /* MODSUB  */
  MIPS_BUILTIN_MODSUB,
  /* RADDU* */
  MIPS_BUILTIN_RADDU_W_QB,
  MIPS_BUILTIN_RADDU_L_OB,
  /* ABSQ* */
  MIPS_BUILTIN_ABSQ_S_PH,
  MIPS_BUILTIN_ABSQ_S_W,
  MIPS_BUILTIN_ABSQ_QH,
  MIPS_BUILTIN_ABSQ_S_QH,
  MIPS_BUILTIN_ABSQ_PW,
  MIPS_BUILTIN_ABSQ_S_PW,
  /* PRECRQ* */
  MIPS_BUILTIN_PRECRQ_QB_PH,
  MIPS_BUILTIN_PRECRQ_PH_W,
  MIPS_BUILTIN_PRECRQ_RS_PH_W,
  MIPS_BUILTIN_PRECRQ_OB_QH,
  MIPS_BUILTIN_PRECRQ_QH_PW,
  MIPS_BUILTIN_PRECRQ_RS_QH_PW,
  MIPS_BUILTIN_PRECRQ_PW_L,
  /* PRECRQU* */
  MIPS_BUILTIN_PRECRQU_S_QB_PH,
  MIPS_BUILTIN_PRECRQU_S_OB_QH,
  MIPS_BUILTIN_PRECRQU_S_QH_PW,
  MIPS_BUILTIN_PRECRQU_S_PW_L,
  /* PRECEQ* */
  MIPS_BUILTIN_PRECEQ_W_PHL,
  MIPS_BUILTIN_PRECEQ_W_PHR,
  MIPS_BUILTIN_PRECEQ_PW_QHL,
  MIPS_BUILTIN_PRECEQ_PW_QHR,
  MIPS_BUILTIN_PRECEQ_PW_QHLA,
  MIPS_BUILTIN_PRECEQ_PW_QHRA,
  MIPS_BUILTIN_PRECEQ_L_PWL,
  MIPS_BUILTIN_PRECEQ_L_PWR,
  /* PRECEQU* */
  MIPS_BUILTIN_PRECEQU_PH_QBL,
  MIPS_BUILTIN_PRECEQU_PH_QBR,
  MIPS_BUILTIN_PRECEQU_PH_QBLA,
  MIPS_BUILTIN_PRECEQU_PH_QBRA,
  MIPS_BUILTIN_PRECEQU_QH_OBL,
  MIPS_BUILTIN_PRECEQU_QH_OBR,
  MIPS_BUILTIN_PRECEQU_QH_OBLA,
  MIPS_BUILTIN_PRECEQU_QH_OBRA,
  /* PRECEU* */
  MIPS_BUILTIN_PRECEU_PH_QBL,
  MIPS_BUILTIN_PRECEU_PH_QBR,
  MIPS_BUILTIN_PRECEU_PH_QBLA,
  MIPS_BUILTIN_PRECEU_PH_QBRA,
  /* Table 2-2. MIPS DSP ASE Instructions: Shift */
  /* SHLL* */
  MIPS_BUILTIN_SHLL_QB,
  MIPS_BUILTIN_SHLL_OB,
  MIPS_BUILTIN_SHLL_PH,
  MIPS_BUILTIN_SHLL_S_PH,
  MIPS_BUILTIN_SHLL_QH,
  MIPS_BUILTIN_SHLL_S_QH,
  MIPS_BUILTIN_SHLL_S_W,
  MIPS_BUILTIN_SHLL_PW,
  MIPS_BUILTIN_SHLL_S_PW,
  /* SHRL* */
  MIPS_BUILTIN_SHRL_QB,
  MIPS_BUILTIN_SHRL_OB,
  /* SHRA* */
  MIPS_BUILTIN_SHRA_PH,
  MIPS_BUILTIN_SHRA_R_PH,
  MIPS_BUILTIN_SHRA_R_W,
  MIPS_BUILTIN_SHRA_QH,
  MIPS_BUILTIN_SHRA_R_QH,
  MIPS_BUILTIN_SHRA_PW,
  MIPS_BUILTIN_SHRA_R_PW,
  /* Table 2-3. MIPS DSP ASE Instructions: Multiply */
  /* MULEU* */
  MIPS_BUILTIN_MULEU_S_PH_QBL,
  MIPS_BUILTIN_MULEU_S_PH_QBR,
  /* MULQ* */
  MIPS_BUILTIN_MULQ_RS_PH,
  MIPS_BUILTIN_MULQ_QH,
  MIPS_BUILTIN_MULQ_RS_QH,
  /* MULEQ* */
  MIPS_BUILTIN_MULEQ_S_W_PHL,
  MIPS_BUILTIN_MULEQ_S_W_PHR,
  MIPS_BUILTIN_MULEQ_PW_QHL,
  MIPS_BUILTIN_MULEQ_PW_QHR,
  MIPS_BUILTIN_MULEQ_S_PW_QHL,
  MIPS_BUILTIN_MULEQ_S_PW_QHR,
  /* DPAU* */
  MIPS_BUILTIN_DPAU_H_QBL,
  MIPS_BUILTIN_DPAU_H_QBR,
  MIPS_BUILTIN_DPAU_H_QBL_64,
  MIPS_BUILTIN_DPAU_H_QBR_64,
  /* DPSU* */
  MIPS_BUILTIN_DPSU_H_QBL,
  MIPS_BUILTIN_DPSU_H_QBR,
  MIPS_BUILTIN_DPSU_H_QBL_64,
  MIPS_BUILTIN_DPSU_H_QBR_64,
  /* DPAQ* */
  MIPS_BUILTIN_DPAQ_S_W_PH,
  MIPS_BUILTIN_DPAQ_S_W_PH_64,
  MIPS_BUILTIN_DPAQ_W_QH,
  MIPS_BUILTIN_DPAQ_S_W_QH,
  /* DPSQ* */
  MIPS_BUILTIN_DPSQ_S_W_PH,
  MIPS_BUILTIN_DPSQ_S_W_PH_64,
  MIPS_BUILTIN_DPSQ_W_QH,
  MIPS_BUILTIN_DPSQ_S_W_QH,
  /* MULSAQ* */
  MIPS_BUILTIN_MULSAQ_S_W_PH,
  MIPS_BUILTIN_MULSAQ_S_W_PH_64,
  MIPS_BUILTIN_MULSAQ_W_QH,
  MIPS_BUILTIN_MULSAQ_S_W_QH,
  MIPS_BUILTIN_MULSAQ_L_PW,
  MIPS_BUILTIN_MULSAQ_S_L_PW,
  /* DPAQ* */
  MIPS_BUILTIN_DPAQ_SA_L_W,
  MIPS_BUILTIN_DPAQ_SA_L_W_64,
  MIPS_BUILTIN_DPAQ_L_PW,
  MIPS_BUILTIN_DPAQ_SA_L_PW,
  /* DPSQ* */
  MIPS_BUILTIN_DPSQ_SA_L_W,
  MIPS_BUILTIN_DPSQ_SA_L_W_64,
  MIPS_BUILTIN_DPSQ_L_PW,
  MIPS_BUILTIN_DPSQ_SA_L_PW,
  /* MAQ* */
  MIPS_BUILTIN_MAQ_S_W_PHL,
  MIPS_BUILTIN_MAQ_S_W_PHR,
  MIPS_BUILTIN_MAQ_S_W_PHL_64,
  MIPS_BUILTIN_MAQ_S_W_PHR_64,
  MIPS_BUILTIN_MAQ_W_QHLL,
  MIPS_BUILTIN_MAQ_W_QHLR,
  MIPS_BUILTIN_MAQ_W_QHRL,
  MIPS_BUILTIN_MAQ_W_QHRR,
  MIPS_BUILTIN_MAQ_S_W_QHLL,
  MIPS_BUILTIN_MAQ_S_W_QHLR,
  MIPS_BUILTIN_MAQ_S_W_QHRL,
  MIPS_BUILTIN_MAQ_S_W_QHRR,
  MIPS_BUILTIN_MAQ_L_PWL,
  MIPS_BUILTIN_MAQ_L_PWR,
  MIPS_BUILTIN_MAQ_S_L_PWL,
  MIPS_BUILTIN_MAQ_S_L_PWR,
  /* MAQ_SA* */
  MIPS_BUILTIN_MAQ_SA_W_PHL,
  MIPS_BUILTIN_MAQ_SA_W_PHR,
  MIPS_BUILTIN_MAQ_SA_W_PHL_64,
  MIPS_BUILTIN_MAQ_SA_W_PHR_64,
  /* DMADD* */
  MIPS_BUILTIN_DMADD,
  MIPS_BUILTIN_DMADDU,
  /* DMSUB* */
  MIPS_BUILTIN_DMSUB,
  MIPS_BUILTIN_DMSUBU,
  /* Table 2-4. MIPS DSP ASE Instructions: General Bit/Manipulation */
  /* BITREV */
  MIPS_BUILTIN_BITREV,
  /* INSV */
  MIPS_BUILTIN_INSV,
  MIPS_BUILTIN_DINSV,
  /* REPL* */
  MIPS_BUILTIN_REPL_QB,
  MIPS_BUILTIN_REPL_OB,
  MIPS_BUILTIN_REPL_PH,
  MIPS_BUILTIN_REPL_QH,
  MIPS_BUILTIN_REPL_PW,
  /* Table 2-5. MIPS DSP ASE Instructions: Compare-Pick */
  /* CMPU.* CMP.* */
  MIPS_BUILTIN_CMPU_EQ_QB,
  MIPS_BUILTIN_CMPU_LT_QB,
  MIPS_BUILTIN_CMPU_LE_QB,
  MIPS_BUILTIN_CMPGU_EQ_QB,
  MIPS_BUILTIN_CMPGU_LT_QB,
  MIPS_BUILTIN_CMPGU_LE_QB,
  MIPS_BUILTIN_CMP_EQ_PH,
  MIPS_BUILTIN_CMP_LT_PH,
  MIPS_BUILTIN_CMP_LE_PH,
  MIPS_BUILTIN_CMPU_EQ_OB,
  MIPS_BUILTIN_CMPU_LT_OB,
  MIPS_BUILTIN_CMPU_LE_OB,
  MIPS_BUILTIN_CMP_EQ_QH,
  MIPS_BUILTIN_CMP_LT_QH,
  MIPS_BUILTIN_CMP_LE_QH,
  MIPS_BUILTIN_CMP_EQ_PW,
  MIPS_BUILTIN_CMP_LT_PW,
  MIPS_BUILTIN_CMP_LE_PW,
  /* PICK* */
  MIPS_BUILTIN_PICK_QB,
  MIPS_BUILTIN_PICK_PH,
  MIPS_BUILTIN_PICK_OB,
  MIPS_BUILTIN_PICK_QH,
  MIPS_BUILTIN_PICK_PW,
  /* PACKRL* */
  MIPS_BUILTIN_PACKRL_PH,
  /* Table 2-6. MIPS DSP ASE Instructions: Accumulator and DSPControl Access */
  /* EXTR* */
  MIPS_BUILTIN_EXTR_W,
  MIPS_BUILTIN_EXTR_R_W,
  MIPS_BUILTIN_EXTR_RS_W,
  MIPS_BUILTIN_EXTR_W_64,
  MIPS_BUILTIN_EXTR_R_W_64,
  MIPS_BUILTIN_EXTR_RS_W_64,
  MIPS_BUILTIN_DEXTR_W,
  MIPS_BUILTIN_DEXTR_R_W,
  MIPS_BUILTIN_DEXTR_RS_W,
  MIPS_BUILTIN_DEXTR_L,
  MIPS_BUILTIN_DEXTR_R_L,
  MIPS_BUILTIN_DEXTR_RS_L,
  /* EXTR*_S.H */
  MIPS_BUILTIN_EXTR_S_H,
  MIPS_BUILTIN_EXTR_S_H_64,
  /* EXTL* */
  MIPS_BUILTIN_DEXTL_W,
  MIPS_BUILTIN_DEXTL_S_W,
  MIPS_BUILTIN_DEXTL_L,
  MIPS_BUILTIN_DEXTL_S_L,
  /* EXTP* */
  MIPS_BUILTIN_EXTP,
  MIPS_BUILTIN_EXTPDP,
  MIPS_BUILTIN_EXTP_64,
  MIPS_BUILTIN_EXTPDP_64,
  MIPS_BUILTIN_DEXTP,
  MIPS_BUILTIN_DEXTPDP,
  /* SHILO* */
  MIPS_BUILTIN_SHILO,
  MIPS_BUILTIN_SHILO_64,
  MIPS_BUILTIN_DSHILO,
  /* MTHLIP* */
  MIPS_BUILTIN_MTHLIP,
  MIPS_BUILTIN_MTHLIP_64,
  MIPS_BUILTIN_DMTHLIP,
  /* WRDSP */
  MIPS_BUILTIN_WRDSP,
  /* RDDSP */
  MIPS_BUILTIN_RDDSP,
  /* Table 2-7. MIPS DSP ASE Instructions: Indexed-Load */
  /* L*X */
  MIPS_BUILTIN_LBUX,
  MIPS_BUILTIN_LHX,
  MIPS_BUILTIN_LWX,
  MIPS_BUILTIN_LDX,
  /* Table 2-8. MIPS DSP ASE Instructions: Branch */
  /* BPOSGE32 */
  MIPS_BUILTIN_BPOSGE32,
  MIPS_BUILTIN_BPOSGE64,

  /* MIPS DSP ASE Rev2 Revision 0.02 5/19/2006 */
  MIPS_BUILTIN_ABSQ_S_QB,
  MIPS_BUILTIN_ADDU_PH,
  MIPS_BUILTIN_ADDU_S_PH,
  MIPS_BUILTIN_ADDUH_QB,
  MIPS_BUILTIN_ADDUH_R_QB,
  MIPS_BUILTIN_APPEND,
  MIPS_BUILTIN_BALIGN,
  MIPS_BUILTIN_CMPGDU_EQ_QB,
  MIPS_BUILTIN_CMPGDU_LT_QB,
  MIPS_BUILTIN_CMPGDU_LE_QB,
  MIPS_BUILTIN_DPA_W_PH,
  MIPS_BUILTIN_DPA_W_PH_64,
  MIPS_BUILTIN_DPS_W_PH,
  MIPS_BUILTIN_DPS_W_PH_64,
  MIPS_BUILTIN_MADD,
  MIPS_BUILTIN_MADDU,
  MIPS_BUILTIN_MSUB,
  MIPS_BUILTIN_MSUBU,
  MIPS_BUILTIN_MUL_PH,
  MIPS_BUILTIN_MUL_S_PH,
  MIPS_BUILTIN_MULQ_RS_W,
  MIPS_BUILTIN_MULQ_S_PH,
  MIPS_BUILTIN_MULQ_S_W,
  MIPS_BUILTIN_MULSA_W_PH,
  MIPS_BUILTIN_MULSA_W_PH_64,
  MIPS_BUILTIN_MULT,
  MIPS_BUILTIN_MULTU,
  MIPS_BUILTIN_PRECR_QB_PH,
  MIPS_BUILTIN_PRECR_SRA_PH_W,
  MIPS_BUILTIN_PRECR_SRA_R_PH_W,
  MIPS_BUILTIN_PREPEND,
  MIPS_BUILTIN_SHRA_QB,
  MIPS_BUILTIN_SHRA_R_QB,
  MIPS_BUILTIN_SHRL_PH,
  MIPS_BUILTIN_SUBU_PH,
  MIPS_BUILTIN_SUBU_S_PH,
  MIPS_BUILTIN_SUBUH_QB,
  MIPS_BUILTIN_SUBUH_R_QB,
  MIPS_BUILTIN_ADDQH_PH,
  MIPS_BUILTIN_ADDQH_R_PH,
  MIPS_BUILTIN_ADDQH_W,
  MIPS_BUILTIN_ADDQH_R_W,
  MIPS_BUILTIN_SUBQH_PH,
  MIPS_BUILTIN_SUBQH_R_PH,
  MIPS_BUILTIN_SUBQH_W,
  MIPS_BUILTIN_SUBQH_R_W,
  MIPS_BUILTIN_DPAX_W_PH,
  MIPS_BUILTIN_DPSX_W_PH,
  MIPS_BUILTIN_DPAQX_S_W_PH,
  MIPS_BUILTIN_DPAQX_SA_W_PH,
  MIPS_BUILTIN_DPSQX_S_W_PH,
  MIPS_BUILTIN_DPSQX_SA_W_PH,
  MIPS_BUILTIN_DPAX_W_PH_64,
  MIPS_BUILTIN_DPSX_W_PH_64,
  MIPS_BUILTIN_DPAQX_S_W_PH_64,
  MIPS_BUILTIN_DPAQX_SA_W_PH_64,
  MIPS_BUILTIN_DPSQX_S_W_PH_64,
  MIPS_BUILTIN_DPSQX_SA_W_PH_64,

  MIPS_BUILTIN_NOP,
  MIPS_BUILTIN_MFC0,
  MIPS_BUILTIN_MTC0,
  MIPS_BUILTIN_MXC0,
  MIPS_BUILTIN_BCC0,
  MIPS_BUILTIN_BSC0,
  MIPS_BUILTIN_BCSC0,

  /* THE LAST BUILTIN */
  MIPS_BUILTIN_MAX_BUILTIN
};

/* MIPS builtin function types */
enum mips_function_type
{
  MIPS_V2SF_FTYPE_V2SF,                 /* v2sf func (v2sf); */
  MIPS_V2SF_FTYPE_V2SF_V2SF,            /* v2sf func (v2sf, v2sf); */
  MIPS_V2SF_FTYPE_V2SF_V2SF_INT,        /* v2sf func (v2sf, v2sf, int); */
  MIPS_V2SF_FTYPE_V2SF_V2SF_V2SF_V2SF,  /* v2sf func (v2sf, v2sf, v2sf, v2sf);*/
  MIPS_V2SF_FTYPE_SF_SF,                /* v2sf func (float, float); */
  MIPS_INT_FTYPE_V2SF_V2SF,             /* int func (v2sf, v2sf); */
  MIPS_INT_FTYPE_V2SF_V2SF_V2SF_V2SF,   /* int func (v2sf, v2sf, v2sf, v2sf); */
  MIPS_INT_FTYPE_SF_SF,                 /* int func (float, float); */
  MIPS_INT_FTYPE_DF_DF,                 /* int func (double, double); */
  MIPS_SF_FTYPE_V2SF,                   /* float func (v2sf); */
  MIPS_SF_FTYPE_SF,                     /* float func (float); */
  MIPS_SF_FTYPE_SF_SF,                  /* float func (float, float); */
  MIPS_DF_FTYPE_DF,                     /* double func (double); */
  MIPS_DF_FTYPE_DF_DF,                  /* double func (double, double); */

  /* For MIPS DSP ASE  */
  MIPS_V2HI_FTYPE_V2HI_V2HI,
  MIPS_V4HI_FTYPE_V4HI_V4HI,
  MIPS_SI_FTYPE_SI_SI,
  MIPS_V2SI_FTYPE_V2SI_V2SI,
  MIPS_V4QI_FTYPE_V4QI_V4QI,
  MIPS_V8QI_FTYPE_V8QI_V8QI,
  MIPS_SI_FTYPE_V4QI,
  MIPS_DI_FTYPE_V8QI,
  MIPS_V2HI_FTYPE_V2HI,
  MIPS_SI_FTYPE_SI,
  MIPS_V4HI_FTYPE_V4HI,
  MIPS_V2SI_FTYPE_V2SI,
  MIPS_V4QI_FTYPE_V2HI_V2HI,
  MIPS_V2HI_FTYPE_SI_SI,
  MIPS_V8QI_FTYPE_V4HI_V4HI,
  MIPS_V4HI_FTYPE_V2SI_V2SI,
  MIPS_V2SI_FTYPE_DI_DI,
  MIPS_SI_FTYPE_V2HI,
  MIPS_V2SI_FTYPE_V4HI,
  MIPS_DI_FTYPE_V2SI,
  MIPS_V2HI_FTYPE_V4QI,
  MIPS_V4HI_FTYPE_V8QI,
  MIPS_V4QI_FTYPE_V4QI_SI,
  MIPS_V8QI_FTYPE_V8QI_DI,
  MIPS_V2HI_FTYPE_V2HI_SI,
  MIPS_V4HI_FTYPE_V4HI_DI,
  MIPS_V2SI_FTYPE_V2SI_DI,
  MIPS_V2HI_FTYPE_V4QI_V2HI,
  MIPS_SI_FTYPE_V2HI_V2HI,
  MIPS_V2SI_FTYPE_V4HI_V4HI,
  MIPS_DI_FTYPE_DI_V4QI_V4QI,
  MIPS_TI_FTYPE_TI_V4QI_V4QI,
  MIPS_DI_FTYPE_DI_V2HI_V2HI,
  MIPS_TI_FTYPE_TI_V2HI_V2HI,
  MIPS_TI_FTYPE_TI_V4HI_V4HI,
  MIPS_TI_FTYPE_TI_V2SI_V2SI,
  MIPS_DI_FTYPE_DI_SI_SI,
  MIPS_TI_FTYPE_TI_SI_SI,
  MIPS_TI_FTYPE_TI_DI_DI,
  MIPS_TI_FTYPE_TI_UDI_UDI,
  MIPS_DI_FTYPE_DI_DI,
  MIPS_V4QI_FTYPE_SI,
  MIPS_V8QI_FTYPE_DI,
  MIPS_V2HI_FTYPE_SI,
  MIPS_V4HI_FTYPE_DI,
  MIPS_V2SI_FTYPE_DI,
  MIPS_VOID_FTYPE_V4QI_V4QI,
  MIPS_SI_FTYPE_V4QI_V4QI,
  MIPS_VOID_FTYPE_V2HI_V2HI,
  MIPS_VOID_FTYPE_V8QI_V8QI,
  MIPS_VOID_FTYPE_V4HI_V4HI,
  MIPS_VOID_FTYPE_V2SI_V2SI,
  MIPS_SI_FTYPE_DI_SI,
  MIPS_SI_FTYPE_TI_SI,
  MIPS_DI_FTYPE_TI_DI,
  MIPS_DI_FTYPE_DI_SI,
  MIPS_TI_FTYPE_TI_SI,
  MIPS_TI_FTYPE_TI_DI,
  MIPS_VOID_FTYPE_SI_SI,
  MIPS_SI_FTYPE_PTR_SI,
  MIPS_DI_FTYPE_PTR_DI,
  MIPS_SI_FTYPE_VOID,

  MIPS_V4QI_FTYPE_V4QI,
  MIPS_SI_FTYPE_SI_SI_SI,
  MIPS_DI_FTYPE_SI_SI,
  MIPS_V2HI_FTYPE_SI_SI_SI,
  MIPS_DI_FTYPE_DI_USI_USI,
  MIPS_DI_FTYPE_USI_USI,

  MIPS_VOID_FTYPE_VOID,
  MIPS_USI_FTYPE_USI_USI,
  MIPS_VOID_FTYPE_USI_USI_USI,
  MIPS_USI_FTYPE_USI_USI_USI,
  MIPS_USI_FTYPE_USI_USI_USI_USI,

  /* The last type */
  MIPS_MAX_FTYPE_MAX
};

/* MIPS compare choices used for MIPS builtin functions */
enum mips_cmp_choice
{
  MIPS_CMP_ANY,    /* Check if any result is true */
  MIPS_CMP_UPPER,  /* Check if the upper one of two results is true */
  MIPS_CMP_LOWER,  /* Check if the lower one of two results is true */
  MIPS_CMP_ALL,    /* Check if all results are true */

  MIPS_CMP_MOVT,   /* Conditional move if true */
  MIPS_CMP_MOVF,   /* Conditional move if false */

  MIPS_CMP_MAX
};

/* IRIX specific stuff.  */
#define TARGET_IRIX	   0
#define TARGET_IRIX5	   0
#define TARGET_SGI_O32_AS  (TARGET_IRIX && mips_abi == ABI_32 && !TARGET_GAS)

/* Define preprocessor macros for the -march and -mtune options.
   PREFIX is either _MIPS_ARCH or _MIPS_TUNE, INFO is the selected
   processor.  If INFO's canonical name is "foo", define PREFIX to
   be "foo", and define an additional macro PREFIX_FOO.  */
#define MIPS_CPP_SET_PROCESSOR(PREFIX, INFO)			\
  do								\
    {								\
      char *macro, *p;						\
								\
      macro = concat ((PREFIX), "_", (INFO)->name, NULL);	\
      for (p = macro; *p != 0; p++)				\
	*p = TOUPPER (*p);					\
								\
      builtin_define (macro);					\
      builtin_define_with_value ((PREFIX), (INFO)->name, 1);	\
      free (macro);						\
    }								\
  while (0)

/* Target CPU builtins.  */
#define TARGET_CPU_CPP_BUILTINS()				\
  do								\
    {								\
      builtin_assert ("cpu=mips");				\
      builtin_define ("__mips__");     				\
      builtin_define ("_mips");					\
								\
      /* We do this here because __mips is defined below	\
	 and so we can't use builtin_define_std.  */		\
      if (!flag_iso)						\
	builtin_define ("mips");				\
								\
      /* Treat _R3000 and _R4000 like register-size defines,	\
	 which is how they've historically been used.  */	\
      if (TARGET_64BIT)						\
	{							\
	  builtin_define ("__mips64");     			\
	  builtin_define_std ("R4000");				\
	  builtin_define ("_R4000");				\
	}							\
      else							\
	{							\
	  builtin_define_std ("R3000");				\
	  builtin_define ("_R3000");				\
	}							\
      if (TARGET_FLOAT64)					\
	builtin_define ("__mips_fpr=64");			\
      else							\
	builtin_define ("__mips_fpr=32");			\
								\
      if (TARGET_MIPS16)					\
	builtin_define ("__mips16");				\
								\
      if (TARGET_MIPS16E)					\
	builtin_define ("__mips16e");				\
								\
      MIPS_CPP_SET_PROCESSOR ("_MIPS_ARCH", mips_arch_info);	\
      MIPS_CPP_SET_PROCESSOR ("_MIPS_TUNE", mips_tune_info);	\
								\
      if (ISA_MIPS1)						\
	{							\
	  builtin_define ("__mips=1");				\
	  builtin_define ("_MIPS_ISA=_MIPS_ISA_MIPS1");		\
	}							\
      else if (ISA_MIPS2)					\
	{							\
	  builtin_define ("__mips=2");				\
	  builtin_define ("_MIPS_ISA=_MIPS_ISA_MIPS2");		\
	}							\
      else if (ISA_MIPS3)					\
	{							\
	  builtin_define ("__mips=3");				\
	  builtin_define ("_MIPS_ISA=_MIPS_ISA_MIPS3");		\
	}							\
      else if (ISA_MIPS4)					\
	{							\
	  builtin_define ("__mips=4");				\
	  builtin_define ("_MIPS_ISA=_MIPS_ISA_MIPS4");		\
	}							\
      else if (ISA_MIPS32)					\
	{							\
	  builtin_define ("__mips=32");				\
	  builtin_define ("__mips_isa_rev=1");			\
	  builtin_define ("_MIPS_ISA=_MIPS_ISA_MIPS32");	\
	}							\
      else if (ISA_MIPS32R2)					\
	{							\
	  builtin_define ("__mips=32");				\
	  builtin_define ("__mips_isa_rev=2");			\
	  builtin_define ("_MIPS_ISA=_MIPS_ISA_MIPS32");	\
	}							\
      else if (ISA_MIPS64)					\
	{							\
	  builtin_define ("__mips=64");				\
	  builtin_define ("__mips_isa_rev=1");			\
	  builtin_define ("_MIPS_ISA=_MIPS_ISA_MIPS64");	\
	}							\
      else if (ISA_MIPS64R2)					\
	{							\
	  builtin_define ("__mips=64");				\
	  builtin_define ("__mips_isa_rev=2");			\
	  builtin_define ("_MIPS_ISA=_MIPS_ISA_MIPS64");	\
        }							\
                                                                \
      if (TARGET_HARD_FLOAT || mips16_hard_float)		\
	builtin_define ("__mips_hard_float");			\
      else if (TARGET_SOFT_FLOAT)				\
	builtin_define ("__mips_soft_float");			\
                                                                \
      if (TARGET_SINGLE_FLOAT)					\
	builtin_define ("__mips_single_float");			\
								\
      if (TARGET_PAIRED_SINGLE_FLOAT)				\
	builtin_define ("__mips_paired_single_float");		\
								\
      if (TARGET_MIPS_DSP32) 				        \
	builtin_define ("__mips_dsp");               		\
								\
      if (TARGET_MIPS3D)					\
	builtin_define ("__mips3d");				\
								\
      if (TARGET_SMARTMIPS)					\
	builtin_define ("__mips_smartmips");			\
								\
      if (TARGET_BIG_ENDIAN)					\
	{							\
	  builtin_define_std ("MIPSEB");			\
	  builtin_define ("_MIPSEB");				\
	}							\
      else							\
	{							\
	  builtin_define_std ("MIPSEL");			\
	  builtin_define ("_MIPSEL");				\
	}							\
								\
        /* Macros dependent on the C dialect.  */		\
      if (preprocessing_asm_p ())				\
	{							\
          builtin_define_std ("LANGUAGE_ASSEMBLY");		\
	  builtin_define ("_LANGUAGE_ASSEMBLY");		\
	}							\
      else if (c_dialect_cxx ())				\
        {							\
	  builtin_define ("_LANGUAGE_C_PLUS_PLUS");		\
          builtin_define ("__LANGUAGE_C_PLUS_PLUS");		\
          builtin_define ("__LANGUAGE_C_PLUS_PLUS__");		\
        }							\
      else							\
	{							\
          builtin_define_std ("LANGUAGE_C");			\
	  builtin_define ("_LANGUAGE_C");			\
	}							\
      if (c_dialect_objc ())					\
        {							\
	  builtin_define ("_LANGUAGE_OBJECTIVE_C");		\
          builtin_define ("__LANGUAGE_OBJECTIVE_C");		\
	  /* Bizarre, but needed at least for Irix.  */		\
	  builtin_define_std ("LANGUAGE_C");			\
	  builtin_define ("_LANGUAGE_C");			\
        }							\
								\
      if (mips_abi == ABI_EABI)					\
	builtin_define ("__mips_eabi");				\
								\
} while (0)



/* Macro to define tables used to set the flags.
   This is a list in braces of pairs in braces,
   each pair being { "NAME", VALUE }
   where VALUE is the bits to set or minus the bits to clear.
   An empty string NAME is used to identify the default VALUE.  */

#define TARGET_SWITCHES							\
{									\
  SUBTARGET_TARGET_SWITCHES                                             \
  {"int64",		  MASK_INT64 | MASK_LONG64,			\
     N_("Use 64-bit int type")},					\
  {"long64",		  MASK_LONG64,					\
     N_("Use 64-bit long type")},					\
  {"long32",		 -(MASK_LONG64 | MASK_INT64),			\
     N_("Use 32-bit long type")},					\
  {"split-addresses",	  MASK_SPLIT_ADDR,				\
     N_("Optimize lui/addiu address loads")},				\
  {"no-split-addresses", -MASK_SPLIT_ADDR,				\
     N_("Don't optimize lui/addiu address loads")},			\
  {"mips-as",		 -MASK_GAS,					\
     N_("Use MIPS as")},						\
  {"gas",		  MASK_GAS,					\
     N_("Use GNU as")},							\
  {"rnames",		  MASK_NAME_REGS,				\
     N_("Use symbolic register names")},				\
  {"no-rnames",		 -MASK_NAME_REGS,				\
     N_("Don't use symbolic register names")},				\
  {"gpOPT",		  0,						\
     N_("Use GP relative sdata/sbss sections (now ignored)")},		\
  {"gpopt",		  0,						\
     N_("Use GP relative sdata/sbss sections (now ignored)")},		\
  {"no-gpOPT",		  0,					        \
     N_("Don't use GP relative sdata/sbss sections (now ignored)")},	\
  {"no-gpopt",		  0,					        \
     N_("Don't use GP relative sdata/sbss sections (now ignored)")},	\
  {"stats",		  0,						\
     N_("Output compiler statistics (now ignored)")},			\
  {"no-stats",		  0,						\
     N_("Don't output compiler statistics")},				\
  {"memcpy",		  MASK_MEMCPY,					\
     N_("Don't optimize block moves")},					\
  {"no-memcpy",		 -MASK_MEMCPY,					\
     N_("Optimize block moves")},					\
  {"mips-tfile",	  MASK_MIPS_TFILE,				\
     N_("Use mips-tfile asm postpass")},				\
  {"no-mips-tfile",	 -MASK_MIPS_TFILE,				\
     N_("Don't use mips-tfile asm postpass")},				\
  {"soft-float",	  MASK_SOFT_FLOAT,				\
     N_("Use software floating point")},				\
  {"hard-float",	 -MASK_SOFT_FLOAT,				\
     N_("Use hardware floating point")},				\
  {"fp64",		  MASK_FLOAT64,					\
     N_("Use 64-bit FP registers")},					\
  {"fp32",		 -MASK_FLOAT64,					\
     N_("Use 32-bit FP registers")},					\
  {"gp64",		  MASK_64BIT,					\
     N_("Use 64-bit general registers")},				\
  {"gp32",		 -MASK_64BIT,					\
     N_("Use 32-bit general registers")},				\
  {"abicalls",		  MASK_ABICALLS,				\
     N_("Use Irix PIC")},						\
  {"no-abicalls",	 -MASK_ABICALLS,				\
     N_("Don't use Irix PIC")},						\
  {"long-calls",	  MASK_LONG_CALLS,				\
     N_("Use indirect calls")},						\
  {"no-long-calls",	 -MASK_LONG_CALLS,				\
     N_("Don't use indirect calls")},					\
  {"embedded-pic",	  MASK_EMBEDDED_PIC,				\
     N_("Use embedded PIC")},						\
  {"no-embedded-pic",	 -MASK_EMBEDDED_PIC,				\
     N_("Don't use embedded PIC")},					\
  {"embedded-data",	  MASK_EMBEDDED_DATA,				\
     N_("Use ROM instead of RAM")},					\
  {"no-embedded-data",	 -MASK_EMBEDDED_DATA,				\
     N_("Don't use ROM instead of RAM")},				\
  {"uninit-const-in-rodata", MASK_UNINIT_CONST_IN_RODATA,		\
     N_("Put uninitialized constants in ROM (needs -membedded-data)")},	\
  {"no-uninit-const-in-rodata", -MASK_UNINIT_CONST_IN_RODATA,		\
     N_("Don't put uninitialized constants in ROM")},			\
  {"eb",		  MASK_BIG_ENDIAN,				\
     N_("Use big-endian byte order")},					\
  {"el",		 -MASK_BIG_ENDIAN,				\
     N_("Use little-endian byte order")},				\
  {"single-float",	  MASK_SINGLE_FLOAT,				\
     N_("Use single (32-bit) FP only")},				\
  {"double-float",	 -MASK_SINGLE_FLOAT,				\
     N_("Don't use single (32-bit) FP only")},				\
  {"paired-single",       MASK_PAIRED_SINGLE,				\
     N_("Use paired-single floating point instructions")},		\
  {"no-paired-single",   -MASK_PAIRED_SINGLE,				\
     N_("Don't use paired-single floating point instructions")},	\
  {"ips3d",               MASK_MIPS3D,					\
     N_("Use MIPS-3D instructions")},					\
  {"no-mips3d",          -MASK_MIPS3D,					\
     N_("Don't use MIPS-3D instructions")},				\
  {"smartmips",           MASK_SMARTMIPS,				\
     N_("Use SmartMIPS instructions")},					\
  {"no-smartmips",        -MASK_SMARTMIPS,				\
     N_("Don't use SmartMIPS instructions")},				\
  {"dsp",		  MASK_DSP,					\
     N_("Use MIPS DSP ASE instructions")},				\
  {"no-dsp",		  -MASK_DSP,					\
     N_("Don't use MIPS DSP ASE instructions")},			\
  {"mad",		  MASK_MAD,					\
     N_("Use multiply accumulate")},					\
  {"no-mad",		 -MASK_MAD,					\
     N_("Don't use multiply accumulate")},				\
  {"no-fused-madd",       MASK_NO_FUSED_MADD,                           \
     N_("Don't generate fused multiply/add instructions")},		\
  {"fused-madd",         -MASK_NO_FUSED_MADD,                           \
     N_("Generate fused multiply/add instructions")},			\
  {"fix4300",             MASK_4300_MUL_FIX,				\
     N_("Work around early 4300 hardware bug")},			\
  {"no-fix4300",         -MASK_4300_MUL_FIX,				\
     N_("Don't work around early 4300 hardware bug")},			\
  {"fix-sb1",             MASK_FIX_SB1,					\
     N_("Work around errata for early SB-1 revision 2 cores")},		\
  {"no-fix-sb1",         -MASK_FIX_SB1,					\
     N_("Don't work around errata for early SB-1 revision 2 cores")},	\
  {"fix-24k-e48",         MASK_FIX_24K_E48,   				\
     N_("Work around the 24K errata no. 48")},		                \
  {"no-fix-24k-e48",     -MASK_FIX_24K_E48,   				\
     N_("Don't work around the 24K errata no. 48")},		        \
  {"check-zero-division",-MASK_NO_CHECK_ZERO_DIV,			\
     N_("Trap on integer divide by zero")},				\
  {"no-check-zero-division", MASK_NO_CHECK_ZERO_DIV,			\
     N_("Don't trap on integer divide by zero")},			\
  {"explicit-relocs",	  MASK_EXPLICIT_RELOCS,				\
     N_("Use NewABI-style %reloc() assembly operators")},		\
  {"no-explicit-relocs", -MASK_EXPLICIT_RELOCS,				\
     N_("Use assembler macros instead of relocation operators")},	\
  {"ips16",		  MASK_MIPS16,					\
     N_("Generate mips16 code") },					\
  {"no-mips16",		 -MASK_MIPS16,					\
     N_("Generate normal-mode code") },					\
  {"ips16e",		  MASK_MIPS16E,					\
     N_("Generate mips16e code") },					\
  {"xgot",		  MASK_XGOT,					\
     N_("Lift restrictions on GOT size") },				\
  {"no-xgot",		 -MASK_XGOT,					\
     N_("Do not lift restrictions on GOT size") },			\
  {"debug",		  MASK_DEBUG,					\
     NULL},								\
  {"debuga",		  MASK_DEBUG_A,					\
     NULL},								\
  {"debugb",		  MASK_DEBUG_B,					\
     NULL},								\
  {"debugc",		  MASK_DEBUG_C,					\
     NULL},								\
  {"debugd",		  MASK_DEBUG_D,					\
     NULL},								\
  {"debuge",		  MASK_DEBUG_E,					\
     NULL},								\
  {"debugf",		  MASK_DEBUG_F,					\
     NULL},								\
  {"debugg",		  MASK_DEBUG_G,					\
     NULL},								\
  {"debugi",		  MASK_DEBUG_I,					\
     NULL},								\
  {"",			  (TARGET_DEFAULT				\
			   | TARGET_CPU_DEFAULT				\
			   | TARGET_ENDIAN_DEFAULT),			\
     NULL},								\
}

/* Default target_flags if no switches are specified  */

#ifndef TARGET_DEFAULT
#define TARGET_DEFAULT 0
#endif

#ifndef TARGET_CPU_DEFAULT
#define TARGET_CPU_DEFAULT 0
#endif

#ifndef TARGET_ENDIAN_DEFAULT
#define TARGET_ENDIAN_DEFAULT MASK_BIG_ENDIAN
#endif

/* 'from-abi' makes a good default: you get whatever the ABI requires.  */
#ifndef MIPS_ISA_DEFAULT
#ifndef MIPS_CPU_STRING_DEFAULT
#define MIPS_CPU_STRING_DEFAULT "from-abi"
#endif
#endif

#ifdef IN_LIBGCC2
#undef TARGET_64BIT
/* Make this compile time constant for libgcc2 */
#ifdef __mips64
#define TARGET_64BIT		1
#else
#define TARGET_64BIT		0
#endif
#endif /* IN_LIBGCC2 */

#ifndef MULTILIB_ENDIAN_DEFAULT
#if TARGET_ENDIAN_DEFAULT == 0
#define MULTILIB_ENDIAN_DEFAULT "EL"
#else
#define MULTILIB_ENDIAN_DEFAULT "EB"
#endif
#endif

#ifndef MULTILIB_ISA_DEFAULT
#  if MIPS_ISA_DEFAULT == 1
#    define MULTILIB_ISA_DEFAULT "mips1"
#  else
#    if MIPS_ISA_DEFAULT == 2
#      define MULTILIB_ISA_DEFAULT "mips2"
#    else
#      if MIPS_ISA_DEFAULT == 3
#        define MULTILIB_ISA_DEFAULT "mips3"
#      else
#        if MIPS_ISA_DEFAULT == 4
#          define MULTILIB_ISA_DEFAULT "mips4"
#        else
#          if MIPS_ISA_DEFAULT == 32
#            define MULTILIB_ISA_DEFAULT "mips32"
#          else
#            if MIPS_ISA_DEFAULT == 33
#              define MULTILIB_ISA_DEFAULT "mips32r2"
#            else
#              if MIPS_ISA_DEFAULT == 64
#                define MULTILIB_ISA_DEFAULT "mips64"
#              else
#                if MIPS_ISA_DEFAULT == 65
#                  define MULTILIB_ISA_DEFAULT "mips64r2"
#                else
#                  define MULTILIB_ISA_DEFAULT "mips1"
#                endif
#              endif
#            endif
#          endif
#        endif
#      endif
#    endif
#  endif
#endif

#ifndef MULTILIB_DEFAULTS
#define MULTILIB_DEFAULTS \
    { MULTILIB_ENDIAN_DEFAULT, MULTILIB_ISA_DEFAULT, MULTILIB_ABI_DEFAULT }
#endif

/* We must pass -EL to the linker by default for little endian embedded
   targets using linker scripts with a OUTPUT_FORMAT line.  Otherwise, the
   linker will default to using big-endian output files.  The OUTPUT_FORMAT
   line must be in the linker script, otherwise -EB/-EL will not work.  */

#ifndef ENDIAN_SPEC
#if TARGET_ENDIAN_DEFAULT == 0
#define ENDIAN_SPEC "%{!EB:%{!meb:-EL}} %{EB|meb:-EB}"
#else
#define ENDIAN_SPEC "%{!EL:%{!mel:-EB}} %{EL|mel:-EL}"
#endif
#endif

#define TARGET_OPTIONS							\
{									\
  SUBTARGET_TARGET_OPTIONS						\
  { "tune=",    &mips_tune_string,			                \
      N_("Specify CPU for scheduling purposes"), 0},                    \
  { "arch=",    &mips_arch_string,                                      \
      N_("Specify CPU for code generation purposes"), 0},               \
  { "abi=", &mips_abi_string,						\
      N_("Specify an ABI"), 0},						\
  { "ips",	&mips_isa_string,					\
      N_("Specify a Standard MIPS ISA"), 0},				\
  { "no-flush-func", &mips_cache_flush_func,				\
      N_("Don't call any cache flush functions"), 0},			\
  { "flush-func=", &mips_cache_flush_func,				\
      N_("Specify cache flush function"), 0},				\
  { "branch-likely", &mips_brlikely_string,				\
      N_("Specify when to use branch likely instructions"), 0},		\
  { "no-branch-likely", &mips_brlikely_string,				\
      N_("Alias for -mbranch-likely=no"), "=no"},			\
  { "branch-cost=", &mips_branch_cost_string,				\
      N_("Specify cost of branch instructions"), 0},			\
  { "no-data-in-code", &mips_no_data_in_code_string,			\
      N_("Don't place MIPS16 constant data in the code section"), 0},	\
  { "code-xonly", &mips_code_xonly_string,				\
      N_("Execute-only MIPS16 code, strings and jump tables in data seg"), 0},\
  { "flip-mips16", &mips_flip_mips16_string,				\
      0, 0} \
}

/* This is meant to be redefined in the host dependent files.  */
#define SUBTARGET_TARGET_OPTIONS

/* Support for a compile-time default CPU, et cetera.  The rules are:
   --with-arch is ignored if -march is specified or a -mips is specified
     (other than -mips16).
   --with-tune is ignored if -mtune is specified.
   --with-abi is ignored if -mabi is specified.
   --with-float is ignored if -mhard-float or -msoft-float are
     specified.  */
#define OPTION_DEFAULT_SPECS \
  {"arch", "%{!march=*:%{mips16:-march=%(VALUE)}%{!mips*:-march=%(VALUE)}}" }, \
  {"tune", "%{!mtune=*:-mtune=%(VALUE)}" }, \
  {"abi", "%{!mabi=*:-mabi=%(VALUE)}" }, \
  {"float", "%{!msoft-float:%{!mhard-float:-m%(VALUE)-float}}" }


/* Enumerator must match "branch_likely" attribute in mips.md */
enum mips_brlikely
{
  BRLIKELY_NO, 		/* never permissible */
  BRLIKELY_YES, 	/* always permissible */
  BRLIKELY_PREDICT	/* only when "very likely" */
};

/* Branch likely state maintained in mips.c */
extern enum mips_brlikely mips_brlikely;
#define GENERATE_BRANCHLIKELY   (mips_brlikely == BRLIKELY_YES		\
				 && ! TARGET_MIPS16)
#define PREDICT_BRANCHLIKELY    (mips_brlikely == BRLIKELY_PREDICT	\
				 && ! TARGET_MIPS16)

/* Generate three-operand multiply instructions for SImode.  */
#define GENERATE_MULT3_SI       ((TARGET_MIPS3900                    \
                                  || TARGET_MIPS5400                    \
                                  || TARGET_MIPS5500                    \
                                  || TARGET_MIPS7000                    \
                                  || TARGET_MIPS9000                    \
                                  || ISA_MIPS32	                        \
                                  || ISA_MIPS32R2                       \
                                  || ISA_MIPS64                         \
                                  || ISA_MIPS64R2)                      \
                                 && !TARGET_MIPS16)

/* Generate three-operand multiply instructions for DImode.  */
#define GENERATE_MULT3_DI       ((TARGET_MIPS3900)                      \
				 && !TARGET_MIPS16)

/* Macros to decide whether certain features are available or not,
   depending on the instruction set architecture level.  */

#define HAVE_SQRT_P()		(!ISA_MIPS1)

/* True if the ABI can only work with 64-bit integer registers.  We
   generally allow ad-hoc variations for TARGET_SINGLE_FLOAT, but
   otherwise floating-point registers must also be 64-bit.  */
#define ABI_NEEDS_64BIT_REGS	(mips_abi == ABI_64			\
				 || mips_abi == ABI_O64			\
				 || mips_abi == ABI_N32)

/* Likewise for 32-bit regs.  */
#define ABI_NEEDS_32BIT_REGS	(mips_abi == ABI_32)

/* True if symbols are 64 bits wide.  At present, n64 is the only
   ABI for which this is true.  */
#define ABI_HAS_64BIT_SYMBOLS	(mips_abi == ABI_64)

/* ISA has instructions for managing 64 bit fp and gp regs (eg. mips3).  */
#define ISA_HAS_64BIT_REGS	(ISA_MIPS3				\
				 || ISA_MIPS4				\
                                 || ISA_MIPS64                          \
                                 || ISA_MIPS64R2)

/* ISA has branch likely instructions (eg. mips2).  */
/* Disable branchlikely for tx39 until compare rewrite.  They haven't
   been generated up to this point.  */
#define ISA_HAS_BRANCHLIKELY	(!ISA_MIPS1                             \
				 && !TARGET_MIPS5500)

/* ISA has the conditional move instructions introduced in mips4.  */
#define ISA_HAS_CONDMOVE        ((ISA_MIPS4				\
				  || ISA_MIPS32	                        \
				  || ISA_MIPS32R2                       \
				  || ISA_MIPS64 			\
 				  || ISA_MIPS64R2)                      \
                                && !TARGET_MIPS5500                     \
				 && !TARGET_MIPS16)

/* ISA has just the integer condition move instructions (movn,movz) */
#define ISA_HAS_INT_CONDMOVE     0

/* ISA has the mips4 FP condition code instructions: FP-compare to CC,
   branch on CC, and move (both FP and non-FP) on CC.  */
#define ISA_HAS_8CC		(ISA_MIPS4				\
                         	 || ISA_MIPS32	                        \
                         	 || ISA_MIPS32R2                        \
				 || ISA_MIPS64                          \
                         	 || ISA_MIPS64R2)

/* This is a catch all for other mips4 instructions: indexed load, the
   FP madd and msub instructions, and the FP recip and recip sqrt
   instructions.  */
#define ISA_HAS_FP4             ((ISA_MIPS4				\
				  || (ISA_MIPS32R2 && TARGET_FLOAT64)   \
				  || ISA_MIPS64                         \
				  || ISA_MIPS64R2)     			\
 				 && !TARGET_MIPS16)

/* ISA can hold an SFmode value in odd-numbered 32 bit fp regs */
#define ISA_HAS_ODD_SF_REG	(ISA_MIPS32 				\
				 || ISA_MIPS32R2			\
				 || ISA_MIPS64                          \
				 || ISA_MIPS64R2)

/* ISA has instructions for accessing top part of 64 bit fp regs */
#define ISA_HAS_MXHC1		(ISA_MIPS32R2				\
				 || ISA_MIPS64R2)

/* ISA supports MIPS16e extensions to MIPS16. */
#define ISA_HAS_MIPS16E		(ISA_MIPS32 				\
				 || ISA_MIPS32R2			\
				 || ISA_MIPS64                          \
				 || ISA_MIPS64R2)

/* ISA has conditional trap instructions.  */
#define ISA_HAS_COND_TRAP	(!ISA_MIPS1				\
				 && !TARGET_MIPS16)

/* ISA has integer multiply-accumulate instructions, madd and msub.  */
#define ISA_HAS_MADD_MSUB       ((ISA_MIPS32				\
				  || ISA_MIPS32R2			\
				  || ISA_MIPS64				\
				  || ISA_MIPS64R2			\
				  ) && !TARGET_MIPS16)

/* ISA has floating-point nmadd and nmsub instructions.  */
#define ISA_HAS_NMADD_NMSUB	((ISA_MIPS4				\
				  || ISA_MIPS64       			\
				  || ISA_MIPS64R2                       \
     				  || (ISA_MIPS32R2 && TARGET_FLOAT64))  \
                                 && (!TARGET_MIPS5400 || TARGET_MAD)    \
				 && ! TARGET_MIPS16)

/* ISA has count leading zeroes/ones instruction (not implemented).  */
#define ISA_HAS_CLZ_CLO         ((ISA_MIPS32				\
                                  || ISA_MIPS32R2			\
                                  || ISA_MIPS64				\
                                  || ISA_MIPS64R2			\
                                 ) && !TARGET_MIPS16)

/* ISA has double-word count leading zeroes/ones instruction (not
   implemented).  */
#define ISA_HAS_DCLZ_DCLO       ((ISA_MIPS64 || ISA_MIPS64R2)		\
				 && !TARGET_MIPS16)

/* ISA has three operand multiply instructions that put
   the high part in an accumulator: mulhi or mulhiu.  */
#define ISA_HAS_MULHI           (TARGET_MIPS5400                        \
                                 || TARGET_MIPS5500                     \
                                 || TARGET_SR71K                        \
                                 )

/* ISA has three operand multiply instructions that
   negates the result and puts the result in an accumulator.  */
#define ISA_HAS_MULS            (TARGET_MIPS5400                        \
                                 || TARGET_MIPS5500                     \
                                 || TARGET_SR71K                        \
                                 )

/* ISA has three operand multiply instructions that subtracts the
   result from a 4th operand and puts the result in an accumulator.  */
#define ISA_HAS_MSAC            (TARGET_MIPS5400                        \
                                 || TARGET_MIPS5500                     \
                                 || TARGET_SR71K                        \
                                 )
/* ISA has three operand multiply instructions that  the result
   from a 4th operand and puts the result in an accumulator.  */
#define ISA_HAS_MACC            ((TARGET_MIPS4120 && !TARGET_MIPS16)	\
                                 || TARGET_MIPS5400                     \
                                 || TARGET_MIPS5500                     \
                                 || TARGET_SR71K                        \
                                 )

/* ISA has 32-bit rotate right instruction.  */
#define ISA_HAS_ROTR_SI         (!TARGET_MIPS16                         \
                                 && (ISA_MIPS32R2                       \
                                     || ISA_MIPS64R2                    \
                                     || TARGET_MIPS5400                 \
                                     || TARGET_MIPS5500                 \
                                     || TARGET_SR71K                    \
                                     || TARGET_SMARTMIPS                \
                                     ))

/* ISA has 64-bit rotate right instruction.  */
#define ISA_HAS_ROTR_DI         (TARGET_64BIT                           \
                                 && !TARGET_MIPS16                      \
                                 && (ISA_MIPS64R2			\
				     || TARGET_MIPS5400                 \
                                     || TARGET_MIPS5500                 \
                                     || TARGET_SR71K                    \
                                     ))

/* ISA has data prefetch instructions.  This controls use of 'pref'.  */
#define ISA_HAS_PREFETCH	((ISA_MIPS4				\
				  || ISA_MIPS32				\
				  || ISA_MIPS32R2			\
				  || ISA_MIPS64 	       		\
				  || ISA_MIPS64R2)	       		\
				 && !TARGET_MIPS16)

/* ISA has data indexed prefetch instructions.  This controls use of
   'prefx', along with TARGET_HARD_FLOAT and TARGET_FLOAT64.
   (prefx is a cop1x instruction, so can only be used if FP is
   enabled.)  */
#define ISA_HAS_PREFETCHX       ((ISA_MIPS4				\
				  || ISA_MIPS32R2			\
				  || ISA_MIPS64       			\
				  || ISA_MIPS64R2)     			\
 				 && !TARGET_MIPS16)

/* True if trunc.w.s and trunc.w.d are real (not synthetic)
   instructions.  Both require TARGET_HARD_FLOAT, and trunc.w.d
   also requires TARGET_DOUBLE_FLOAT.  */
#define ISA_HAS_TRUNC_W		(!ISA_MIPS1)

/* ISA includes the MIPS32r2 seb and seh instructions.  */
#define ISA_HAS_SEB_SEH         (!TARGET_MIPS16				\
                                 && (ISA_MIPS32R2			\
                                     || ISA_MIPS64R2			\
                                     ))

/* ISA includes the MIPS64r2 dins instructions.  */
#define ISA_HAS_INSV            (ISA_MIPS64R2)

/* True if the result of a load is not available to the next instruction.
   A nop will then be needed between instructions like "lw $4,..."
   and "addiu $4,$4,1".  */
#define ISA_HAS_LOAD_DELAY	(mips_isa == 1				\
				 && !TARGET_MIPS3900			\
				 && !TARGET_MIPS16)

/* Likewise mtc1 and mfc1.  */
#define ISA_HAS_XFER_DELAY	(mips_isa <= 3)

/* Likewise floating-point comparisons.  */
#define ISA_HAS_FCMP_DELAY	(mips_isa <= 3)

/* True if mflo and mfhi can be immediately followed by instructions
   which write to the HI and LO registers.  Most targets require a
   two-instruction gap.  */
#define ISA_HAS_HILO_INTERLOCKS	(ISA_MIPS32                             \
				 || ISA_MIPS32R2                        \
				 || ISA_MIPS64                          \
				 || ISA_MIPS64R2                         \
				 || TARGET_MIPS7000                     \
				 || TARGET_MIPS5500                     \
				 || TARGET_SB1)

/* Add -G xx support.  */

#undef  SWITCH_TAKES_ARG
#define SWITCH_TAKES_ARG(CHAR)						\
  (DEFAULT_SWITCH_TAKES_ARG (CHAR) || (CHAR) == 'G')

#define OVERRIDE_OPTIONS override_options ()

#define CONDITIONAL_REGISTER_USAGE mips_conditional_register_usage ()

/* Show we can debug even without a frame pointer.  */
#define CAN_DEBUG_WITHOUT_FP

/* Tell collect what flags to pass to nm.  */
#ifndef NM_FLAGS
#define NM_FLAGS "-Bn"
#endif

/* Assembler specs.  */

/* MIPS_AS_ASM_SPEC is passed when using the MIPS assembler rather
   than gas.  */

#define MIPS_AS_ASM_SPEC "\
%{!.s:-nocpp} %{.s: %{cpp} %{nocpp}} \
%{pipe: %e-pipe is not supported} \
%{K} %(subtarget_mips_as_asm_spec)"

/* SUBTARGET_MIPS_AS_ASM_SPEC is passed when using the MIPS assembler
   rather than gas.  It may be overridden by subtargets.  */

#ifndef SUBTARGET_MIPS_AS_ASM_SPEC
#define SUBTARGET_MIPS_AS_ASM_SPEC "%{v}"
#endif

/* GAS_ASM_SPEC is passed when using gas, rather than the MIPS
   assembler.  */

#define GAS_ASM_SPEC "%{mtune=*} %{v}"

#define SUBTARGET_TARGET_SWITCHES

#ifndef MIPS_ABI_DEFAULT
#define MIPS_ABI_DEFAULT ABI_32
#endif

/* Use the most portable ABI flag for the ASM specs.  */

#if MIPS_ABI_DEFAULT == ABI_32
#define MULTILIB_ABI_DEFAULT "mabi=32"
#define ASM_ABI_DEFAULT_SPEC "-32"
#endif

#if MIPS_ABI_DEFAULT == ABI_O64
#define MULTILIB_ABI_DEFAULT "mabi=o64"
#define ASM_ABI_DEFAULT_SPEC "-mabi=o64"
#endif

#if MIPS_ABI_DEFAULT == ABI_N32
#define MULTILIB_ABI_DEFAULT "mabi=n32"
#define ASM_ABI_DEFAULT_SPEC "-n32"
#endif

#if MIPS_ABI_DEFAULT == ABI_64
#define MULTILIB_ABI_DEFAULT "mabi=64"
#define ASM_ABI_DEFAULT_SPEC "-64"
#endif

#if MIPS_ABI_DEFAULT == ABI_EABI
#define MULTILIB_ABI_DEFAULT "mabi=eabi"
#define ASM_ABI_DEFAULT_SPEC "-mabi=eabi"
#endif

/* Only ELF targets can switch the ABI.  */
#ifndef OBJECT_FORMAT_ELF
#undef ASM_ABI_DEFAULT_SPEC
#define ASM_ABI_DEFAULT_SPEC ""
#endif

/* TARGET_ASM_SPEC is used to select either MIPS_AS_ASM_SPEC or
   GAS_ASM_SPEC as the default, depending upon the value of
   TARGET_DEFAULT.  */

#if ((TARGET_CPU_DEFAULT | TARGET_DEFAULT) & MASK_GAS) != 0
/* GAS */

#define TARGET_ASM_SPEC "\
%{mmips-as: %(mips_as_asm_spec)} \
%{!mmips-as: %(gas_asm_spec)}"

#else /* not GAS */

#define TARGET_ASM_SPEC "\
%{!mgas: %(mips_as_asm_spec)} \
%{mgas: %(gas_asm_spec)}"

#endif /* not GAS */

/* SUBTARGET_ASM_OPTIMIZING_SPEC handles passing optimization options
   to the assembler.  It may be overridden by subtargets.  */
#ifndef SUBTARGET_ASM_OPTIMIZING_SPEC
#define SUBTARGET_ASM_OPTIMIZING_SPEC "\
%{noasmopt:-O0} \
%{!noasmopt:%{O:-O2} %{O1:-O2} %{O2:-O2} %{O3:-O3}}"
#endif

/* SUBTARGET_ASM_DEBUGGING_SPEC handles passing debugging options to
   the assembler.  It may be overridden by subtargets.  */
#ifndef SUBTARGET_ASM_DEBUGGING_SPEC
#define SUBTARGET_ASM_DEBUGGING_SPEC "\
%{g} %{g0} %{g1} %{g2} %{g3} \
%{ggdb:-g} %{ggdb0:-g0} %{ggdb1:-g1} %{ggdb2:-g2} %{ggdb3:-g3} \
%{gstabs:-g} %{gstabs0:-g0} %{gstabs1:-g1} %{gstabs2:-g2} %{gstabs3:-g3} \
%{gstabs+:-g} %{gstabs+0:-g0} %{gstabs+1:-g1} %{gstabs+2:-g2} %{gstabs+3:-g3} \
%{gcoff:-g} %{gcoff0:-g0} %{gcoff1:-g1} %{gcoff2:-g2} %{gcoff3:-g3} \
%(mdebug_asm_spec)"
#endif

/* Beginning with gas 2.13, -mdebug must be passed to correctly handle COFF
   debugging info.  */
#if ((TARGET_CPU_DEFAULT | TARGET_DEFAULT) & MASK_GAS) != 0
/* GAS */
#define MDEBUG_ASM_SPEC "%{gcoff*:-mdebug} \
                         %{!gcoff*:-no-mdebug}"
#else /* not GAS */
#define MDEBUG_ASM_SPEC ""
#endif /* not GAS */

/* SUBTARGET_ASM_SPEC is always passed to the assembler.  It may be
   overridden by subtargets.  */

#ifndef SUBTARGET_ASM_SPEC
#define SUBTARGET_ASM_SPEC ""
#endif

/* ASM_SPEC is the set of arguments to pass to the assembler.  Note: we
   pass -mgp32, -mgp64, -march, -mabi=eabi and -meabi=o64 regardless of
   whether we're using GAS.  These options can only be used properly
   with GAS, and it is better to get an error from a non-GAS assembler
   than to silently generate bad code.  */

#undef ASM_SPEC
#define ASM_SPEC "\
%{G*} %(endian_spec) %{mips1} %{mips2} %{mips3} %{mips4} \
%{mips32} %{mips32r2} %{mips64} %{mips64r2}\
%{mips16:%{!mno-mips16:-mips16}} %{mno-mips16:-no-mips16} \
%{mips3d} \
%{mips16e} \
%{msmartmips} %{mno-smartmips} \
%{mfix-24k-e48} %{mno-fix-24k-e48} \
%{mdsp} %{mno-dsp} \
%{mt} %{mmt} %{mno-mt} \
%(subtarget_asm_optimizing_spec) \
%(subtarget_asm_debugging_spec) \
%{membedded-pic} \
%{mabi=32:-32}%{mabi=n32:-n32}%{mabi=64:-64}%{mabi=n64:-64} \
%{mabi=eabi} %{mabi=o64} %{!mabi*: %(asm_abi_default_spec)} \
%{mgp32} %{mgp64} %{mfp32} %{mfp64} %{march=*} %{mxgot:-xgot} \
%(target_asm_spec) \
%(subtarget_asm_spec)"

/* Extra switches sometimes passed to the linker.  */
/* ??? The bestGnum will never be passed to the linker, because the gcc driver
  will interpret it as a -b option.  */

#ifndef LINK_SPEC
#define LINK_SPEC "\
%(endian_spec) \
%{G*} %{mips1} %{mips2} %{mips3} %{mips4} %{mips32} %{mips32r2} %{mips64} %{mips64r2} \
%{bestGnum} %{shared} %{non_shared}"
#endif  /* LINK_SPEC defined */


/* Specs for the compiler proper */

/* SUBTARGET_CC1_SPEC is passed to the compiler proper.  It may be
   overridden by subtargets.  */
#ifndef SUBTARGET_CC1_SPEC
#define SUBTARGET_CC1_SPEC ""
#endif

/* CC1_SPEC is the set of arguments to pass to the compiler proper.  */

#ifndef CC1_SPEC
#define CC1_SPEC "\
%{gline:%{!g:%{!g0:%{!g1:%{!g2: -g1}}}}} \
%{mips16*:%{!fno-section-relative-addressing:-fsection-relative-addressing -fno-common}} \
%{fsection-relative-addressing:-fno-common} \
%{G*} %{EB:-meb} %{EL:-mel} %{EB:%{EL:%emay not use both -EB and -EL}} \
%{save-temps: } \
%(subtarget_cc1_spec)"
#endif

/* Preprocessor specs.  */

/* SUBTARGET_CPP_SPEC is passed to the preprocessor.  It may be
   overridden by subtargets.  */
#ifndef SUBTARGET_CPP_SPEC
#define SUBTARGET_CPP_SPEC ""
#endif

#define CPP_SPEC "%(subtarget_cpp_spec)"

/* The MIPS assembly language uses dollar as part of the register
   name, so it needs to be treated by CPP as part of a symbol name for
   concatenation etc to work correctly. */

#define DOLLARS_IN_ASM_IDENTIFIERS true

/* This macro defines names of additional specifications to put in the specs
   that can be used in various specifications like CC1_SPEC.  Its definition
   is an initializer with a subgrouping for each command option.

   Each subgrouping contains a string constant, that defines the
   specification name, and a string constant that used by the GCC driver
   program.

   Do not define this macro if it does not need to do anything.  */

#define EXTRA_SPECS							\
  { "subtarget_cc1_spec", SUBTARGET_CC1_SPEC },				\
  { "subtarget_cpp_spec", SUBTARGET_CPP_SPEC },				\
  { "mips_as_asm_spec", MIPS_AS_ASM_SPEC },				\
  { "gas_asm_spec", GAS_ASM_SPEC },					\
  { "target_asm_spec", TARGET_ASM_SPEC },				\
  { "subtarget_mips_as_asm_spec", SUBTARGET_MIPS_AS_ASM_SPEC }, 	\
  { "subtarget_asm_optimizing_spec", SUBTARGET_ASM_OPTIMIZING_SPEC },	\
  { "subtarget_asm_debugging_spec", SUBTARGET_ASM_DEBUGGING_SPEC },	\
  { "mdebug_asm_spec", MDEBUG_ASM_SPEC },				\
  { "subtarget_asm_spec", SUBTARGET_ASM_SPEC },				\
  { "asm_abi_default_spec", ASM_ABI_DEFAULT_SPEC },			\
  { "endian_spec", ENDIAN_SPEC },					\
  SUBTARGET_EXTRA_SPECS

#ifndef SUBTARGET_EXTRA_SPECS
#define SUBTARGET_EXTRA_SPECS
#endif

/* If defined, this macro is an additional prefix to try after
   `STANDARD_EXEC_PREFIX'.  */

#ifndef MD_EXEC_PREFIX
#define MD_EXEC_PREFIX "/usr/lib/cmplrs/cc/"
#endif

#ifndef MD_STARTFILE_PREFIX
#define MD_STARTFILE_PREFIX "/usr/lib/cmplrs/cc/"
#endif


#define DBX_DEBUGGING_INFO 1		/* generate stabs (OSF/rose) */
#define MIPS_DEBUGGING_INFO 1		/* MIPS specific debugging info */
#define DWARF2_DEBUGGING_INFO 1         /* dwarf2 debugging info */

#ifndef PREFERRED_DEBUGGING_TYPE
#define PREFERRED_DEBUGGING_TYPE DWARF2_DEBUG
#endif

/* By default, turn on GDB extensions.  */
#define DEFAULT_GDB_EXTENSIONS 1

/* If we are passing smuggling stabs through the MIPS ECOFF object
   format, put a comment in front of the .stab<x> operation so
   that the MIPS assembler does not choke.  The mips-tfile program
   will correctly put the stab into the object file.  */

#define ASM_STABS_OP	((TARGET_GAS) ? "\t.stabs\t" : " #.stabs\t")
#define ASM_STABN_OP	((TARGET_GAS) ? "\t.stabn\t" : " #.stabn\t")
#define ASM_STABD_OP	((TARGET_GAS) ? "\t.stabd\t" : " #.stabd\t")

/* Local compiler-generated symbols must have a prefix that the assembler
   understands.   By default, this is $, although some targets (e.g.,
   NetBSD-ELF) need to override this.  */

#ifndef LOCAL_LABEL_PREFIX
#define LOCAL_LABEL_PREFIX	"$"
#endif

/* By default on the mips, external symbols do not have an underscore
   prepended, but some targets (e.g., NetBSD) require this.  */

#ifndef USER_LABEL_PREFIX
#define USER_LABEL_PREFIX	""
#endif

/* On Sun 4, this limit is 2048.  We use 1500 to be safe,
   since the length can run past this up to a continuation point.  */
#undef DBX_CONTIN_LENGTH
#define DBX_CONTIN_LENGTH 1500

/* How to renumber registers for dbx and gdb.  */
#define DBX_REGISTER_NUMBER(REGNO) mips_dbx_regno[ (REGNO) ]

/* The max callee-saved register number in a stack frame. */
#define DWARF_FRAME_REGISTERS (FP_REG_LAST + 2)

/* The mapping from gcc register number to DWARF 2 CFA column number.  */
/* The HI and LO registers are always in big-endian order. */
#define DWARF_FRAME_REGNUM(REG)	\
  ((REG) == HI_REGNUM ? MD0_REGNUM \
   : (REG) == LO_REGNUM ? MD1_REGNUM \
   : (REG))

/* The DWARF 2 CFA column which tracks the return address.  */
#define DWARF_FRAME_RETURN_COLUMN (GP_REG_FIRST + 31)

/* The DWARF 2 CFA column which tracks the return address from a
   signal handler context.  */
#define SIGNAL_UNWIND_RETURN_COLUMN (FP_REG_LAST + 1)

/* Before the prologue, RA lives in r31.  */
#define INCOMING_RETURN_ADDR_RTX  gen_rtx_REG (VOIDmode, GP_REG_FIRST + 31)

/* Describe how we implement __builtin_eh_return.  */
#define EH_RETURN_DATA_REGNO(N) \
  ((N) < (TARGET_MIPS16 ? 2 : 4) ? (N) + GP_ARG_FIRST : INVALID_REGNUM)

#define EH_RETURN_STACKADJ_RTX  gen_rtx_REG (Pmode, GP_REG_FIRST + 3)

/* Offsets recorded in opcodes are a multiple of this alignment factor.
   The default for this in 64-bit mode is 8, which causes problems with
   SFmode register saves.  */
#define DWARF_CIE_DATA_ALIGNMENT 4

/* Correct the offset of automatic variables and arguments.  Note that
   the MIPS debug format wants all automatic variables and arguments
   to be in terms of the virtual frame pointer (stack pointer before
   any adjustment in the function), while the MIPS 3.0 linker wants
   the frame pointer to be the stack pointer after the initial
   adjustment.  */

#define DEBUGGER_AUTO_OFFSET(X)				\
  mips_debugger_offset (X, (HOST_WIDE_INT) 0)
#define DEBUGGER_ARG_OFFSET(OFFSET, X)			\
  mips_debugger_offset (X, (HOST_WIDE_INT) OFFSET)

/* Target machine storage layout */

#define BITS_BIG_ENDIAN 0
#define BYTES_BIG_ENDIAN (TARGET_BIG_ENDIAN != 0)
#define WORDS_BIG_ENDIAN (TARGET_BIG_ENDIAN != 0)

/* Define this to set the endianness to use in libgcc2.c, which can
   not depend on target_flags.  */
#if !defined(MIPSEL) && !defined(__MIPSEL__)
#define LIBGCC2_WORDS_BIG_ENDIAN 1
#else
#define LIBGCC2_WORDS_BIG_ENDIAN 0
#endif

#define MAX_BITS_PER_WORD 64

/* Width of a word, in units (bytes).  */
#define UNITS_PER_WORD (TARGET_64BIT ? 8 : 4)
#define MIN_UNITS_PER_WORD 4

/* For MIPS, width of a floating point register.  */
#define UNITS_PER_FPREG (TARGET_FLOAT64 ? 8 : 4)

/* If register $f0 holds a floating-point value, $f(0 + FP_INC) is
   the next available register.  */
#define FP_INC (TARGET_FLOAT64 || TARGET_SINGLE_FLOAT ? 1 : 2)

/* The largest size of value that can be held in floating-point
   registers and moved with a single instruction.  */
#define UNITS_PER_HWFPVALUE (TARGET_SOFT_FLOAT ? 0 : FP_INC * UNITS_PER_FPREG)

/* Like TARGET_SOFT_FLOAT, but not true when compiling MIPS16 code
   with hard float (i.e. in "pseudo soft-float" mode). */
#define TARGET_REALLY_SOFT_FLOAT (TARGET_SOFT_FLOAT && ! mips16_hard_float)

/* The largest size of value that can be held in floating-point
   registers.  */
#define UNITS_PER_FPVALUE			\
  (TARGET_REALLY_SOFT_FLOAT ? 0		\
   : TARGET_SINGLE_FLOAT ? UNITS_PER_FPREG	\
   : LONG_DOUBLE_TYPE_SIZE / BITS_PER_UNIT)

/* The number of bytes in a double.  */
#define UNITS_PER_DOUBLE (TYPE_PRECISION (double_type_node) / BITS_PER_UNIT)

/* Tell the preprocessor the maximum size of wchar_t.  */
#ifndef MAX_WCHAR_TYPE_SIZE
#ifndef WCHAR_TYPE_SIZE
#define MAX_WCHAR_TYPE_SIZE 64
#endif
#endif

/* Set the sizes of the core types.  */
#define SHORT_TYPE_SIZE 16
#define INT_TYPE_SIZE (TARGET_INT64 ? 64 : 32)
#define LONG_TYPE_SIZE (TARGET_LONG64 ? 64 : 32)
#define LONG_LONG_TYPE_SIZE 64

#define MAX_LONG_TYPE_SIZE 64

#define FLOAT_TYPE_SIZE 32
#define DOUBLE_TYPE_SIZE 64
#define LONG_DOUBLE_TYPE_SIZE \
  (mips_abi == ABI_N32 || mips_abi == ABI_64 ? 128 : 64)

/* long double is not a fixed mode, but the idea is that, if we
   support long double, we also want a 128-bit integer type.  */
#define MAX_FIXED_MODE_SIZE LONG_DOUBLE_TYPE_SIZE

#ifdef IN_LIBGCC2
#if  (defined _ABIN32 && _MIPS_SIM == _ABIN32) \
  || (defined _ABI64 && _MIPS_SIM == _ABI64)
#  define LIBGCC2_LONG_DOUBLE_TYPE_SIZE 128
# else
#  define LIBGCC2_LONG_DOUBLE_TYPE_SIZE 64
# endif
#endif

/* Width in bits of a pointer.  */
#ifndef POINTER_SIZE
#define POINTER_SIZE ((TARGET_LONG64 && TARGET_64BIT) ? 64 : 32)
#endif

#define POINTERS_EXTEND_UNSIGNED 0

/* Allocation boundary (in *bits*) for storing arguments in argument list.  */
#define PARM_BOUNDARY ((mips_abi == ABI_O64 || mips_abi == ABI_N32 \
			|| mips_abi == ABI_64 \
			|| (mips_abi == ABI_EABI && TARGET_64BIT)) ? 64 : 32)


/* Allocation boundary (in *bits*) for the code of a function.  */
#define FUNCTION_BOUNDARY 32

/* Alignment of field after `int : 0' in a structure.  */
#define EMPTY_FIELD_BOUNDARY 32

/* Every structure's size must be a multiple of this.  */
/* 8 is observed right on a DECstation and on riscos 4.02.  */
#define STRUCTURE_SIZE_BOUNDARY 8

/* There is no point aligning anything to a rounder boundary than this.  */
#define BIGGEST_ALIGNMENT LONG_DOUBLE_TYPE_SIZE

/* All accesses must be aligned.  */
#define STRICT_ALIGNMENT 1

/* Define this if you wish to imitate the way many other C compilers
   handle alignment of bitfields and the structures that contain
   them.

   The behavior is that the type written for a bit-field (`int',
   `short', or other integer type) imposes an alignment for the
   entire structure, as if the structure really did contain an
   ordinary field of that type.  In addition, the bit-field is placed
   within the structure so that it would fit within such a field,
   not crossing a boundary for it.

   Thus, on most machines, a bit-field whose type is written as `int'
   would not cross a four-byte boundary, and would force four-byte
   alignment for the whole structure.  (The alignment used may not
   be four bytes; it is controlled by the other alignment
   parameters.)

   If the macro is defined, its definition should be a C expression;
   a nonzero value for the expression enables this behavior.  */

#define PCC_BITFIELD_TYPE_MATTERS 1

/* If defined, a C expression to compute the alignment given to a
   constant that is being placed in memory.  CONSTANT is the constant
   and ALIGN is the alignment that the object would ordinarily have.
   The value of this macro is used instead of that alignment to align
   the object.

   If this macro is not defined, then ALIGN is used.

   The typical use of this macro is to increase alignment for string
   constants to be word aligned so that `strcpy' calls that copy
   constants can be done inline.  */

#define CONSTANT_ALIGNMENT(EXP, ALIGN)					\
  ((TREE_CODE (EXP) == STRING_CST  || TREE_CODE (EXP) == CONSTRUCTOR)	\
   && (ALIGN) < BITS_PER_WORD ? BITS_PER_WORD : (ALIGN))

/* If defined, a C expression to compute the alignment for a static
   variable.  TYPE is the data type, and ALIGN is the alignment that
   the object would ordinarily have.  The value of this macro is used
   instead of that alignment to align the object.

   If this macro is not defined, then ALIGN is used.

   One use of this macro is to increase alignment of medium-size
   data to make it all fit in fewer cache lines.  Another is to
   cause character arrays to be word-aligned so that `strcpy' calls
   that copy constants to character arrays can be done inline.  */

#undef DATA_ALIGNMENT
#define DATA_ALIGNMENT(TYPE, ALIGN)					\
  ((((ALIGN) < BITS_PER_WORD)						\
    && (TREE_CODE (TYPE) == ARRAY_TYPE					\
	|| TREE_CODE (TYPE) == UNION_TYPE				\
	|| TREE_CODE (TYPE) == RECORD_TYPE)) ? BITS_PER_WORD : (ALIGN))


#define PAD_VARARGS_DOWN \
  (FUNCTION_ARG_PADDING (TYPE_MODE (type), type) == downward)

/* Arguments declared as 'char' or 'short' in a prototype should be
   passed as 'int's.  */
#define PROMOTE_PROTOTYPES 1

/* Define if operations between registers always perform the operation
   on the full register even if a narrower mode is specified.  */
#define WORD_REGISTER_OPERATIONS

/* When in 64 bit mode, move insns will sign extend SImode and CCmode
   moves.  All other references are zero extended.  */
#define LOAD_EXTEND_OP(MODE) \
  (TARGET_64BIT && ((MODE) == SImode || (MODE) == CCmode) \
   ? SIGN_EXTEND : ZERO_EXTEND)

/* Define this macro if it is advisable to hold scalars in registers
   in a wider mode than that declared by the program.  In such cases,
   the value is constrained to be within the bounds of the declared
   type, but kept valid in the wider mode.  The signedness of the
   extension may differ from that of the type.  */

#define PROMOTE_MODE(MODE, UNSIGNEDP, TYPE)	\
  if (GET_MODE_CLASS (MODE) == MODE_INT		\
      && GET_MODE_SIZE (MODE) < UNITS_PER_WORD) \
    {                                           \
      if ((MODE) == SImode)                     \
        (UNSIGNEDP) = 0;                        \
      (MODE) = Pmode;                           \
    }

/* Define if loading short immediate values into registers sign extends.  */
#define SHORT_IMMEDIATES_SIGN_EXTEND


/* Define this if function arguments should also be promoted using the above
   procedure.  */
#define PROMOTE_FUNCTION_ARGS

/* Likewise, if the function return value is promoted.  */
#define PROMOTE_FUNCTION_RETURN


/* Standard register usage.  */

/* Number of hardware registers.  We have:

   - 32 integer registers
   - 32 floating point registers
   - 8 condition code registers
   - 2 accumulator registers (hi and lo)
   - 32 registers each for coprocessors 0, 2 and 3
   - 3 fake registers:
	- ARG_POINTER_REGNUM
	- FRAME_POINTER_REGNUM
	- FAKE_CALL_REGNO (see the comment above load_callsi for details)
   - 3 dummy entries that were used at various times in the past.
   - 6 DSP accumulator registers (3 hi-lo pairs) for MIPS DSP ASE
   - 6 DSP control register */

#define FIRST_PSEUDO_REGISTER 188

/* By default, fix the kernel registers ($26 and $27), the global
   pointer ($28) and the stack pointer ($29).  This can change
   depending on the command-line options.

   Regarding coprocessor registers: without evidence to the contrary,
   it's best to assume that each coprocessor register has a unique
   use.  This can be overridden, in, e.g., override_options() or
   CONDITIONAL_REGISTER_USAGE should the assumption be inappropriate
   for a particular target.  */

#define FIXED_REGISTERS							\
{									\
  1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			\
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,			\
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			\
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			\
  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,			\
  /* COP0 registers */							\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  /* COP2 registers */							\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  /* COP3 registers */							\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  /* 6 DSP accumulator registers & 6 control registers */		\
  0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 					\
}


/* Set up this array for o32 by default.

   Note that we don't mark $31 as a call-clobbered register.  The idea is
   that it's really the call instructions themselves which clobber $31.
   We don't care what the called function does with it afterwards.

   This approach makes it easier to implement sibcalls.  Unlike normal
   calls, sibcalls don't clobber $31, so the register reaches the
   called function in tact.  EPILOGUE_USES says that $31 is useful
   to the called function.  */

#define CALL_USED_REGISTERS						\
{									\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0,			\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  /* COP0 registers */							\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  /* COP2 registers */							\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  /* COP3 registers */							\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  /* 6 DSP accumulator registers & 6 control registers */		\
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1					\
}


/* Define this since $28, though fixed, is call-saved in many ABIs.  */

#define CALL_REALLY_USED_REGISTERS                                      \
{ /* General registers.  */                                             \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,                       \
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0,                       \
  /* Floating-point registers.  */                                      \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			\
  /* Others.  */                                                        \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,			\
  /* COP0 registers */							\
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			\
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			\
  /* COP2 registers */							\
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			\
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			\
  /* COP3 registers */							\
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			\
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,			\
  /* 6 DSP accumulator Registers & 6 control registers */		\
  1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 					\
}

/* Internal macros to classify a register number as to whether it's a
   general purpose register, a floating point register, a
   multiply/divide register, or a status register.  */

#define GP_REG_FIRST 0
#define GP_REG_LAST  31
#define GP_REG_NUM   (GP_REG_LAST - GP_REG_FIRST + 1)
#define GP_DBX_FIRST 0

#define FP_REG_FIRST 32
#define FP_REG_LAST  63
#define FP_REG_NUM   (FP_REG_LAST - FP_REG_FIRST + 1)
#define FP_DBX_FIRST ((write_symbols == DBX_DEBUG) ? 38 : 32)

#define MD_REG_FIRST 64
#define MD_REG_LAST  65
#define MD_REG_NUM   (MD_REG_LAST - MD_REG_FIRST + 1)
#define MD_DBX_FIRST (FP_DBX_FIRST + FP_REG_NUM)

#define ST_REG_FIRST 67
#define ST_REG_LAST  74
#define ST_REG_NUM   (ST_REG_LAST - ST_REG_FIRST + 1)


/* FIXME: renumber.  */
#define COP0_REG_FIRST 80
#define COP0_REG_LAST 111
#define COP0_REG_NUM (COP0_REG_LAST - COP0_REG_FIRST + 1)

#define COP2_REG_FIRST 112
#define COP2_REG_LAST 143
#define COP2_REG_NUM (COP2_REG_LAST - COP2_REG_FIRST + 1)

#define COP3_REG_FIRST 144
#define COP3_REG_LAST 175
#define COP3_REG_NUM (COP3_REG_LAST - COP3_REG_FIRST + 1)
/* ALL_COP_REG_NUM assumes that COP0,2,and 3 are numbered consecutively.  */
#define ALL_COP_REG_NUM (COP3_REG_LAST - COP0_REG_FIRST + 1)

#define DSP_ACC_REG_FIRST 176
#define DSP_ACC_REG_LAST 181
#define DSP_ACC_REG_NUM (DSP_ACC_REG_LAST - DSP_ACC_REG_FIRST + 1)
#define DSP_ACC_DBX_FIRST (MD_DBX_FIRST + MD_REG_NUM)

#define DSP_CONTROL_PO_REGNUM 182
#define DSP_CONTROL_SC_REGNUM 183
#define DSP_CONTROL_CA_REGNUM 184
#define DSP_CONTROL_OU_REGNUM 185
#define DSP_CONTROL_CC_REGNUM 186
#define DSP_CONTROL_EF_REGNUM 187

#define AT_REGNUM	(GP_REG_FIRST + 1)
#define V0_REGNUM	(GP_REG_FIRST + 2)
#define V1_REGNUM	(GP_REG_FIRST + 3)
#define RA_REGNUM	(GP_REG_FIRST + 31)
#define MD0_REGNUM	(MD_REG_FIRST + 0)
#define MD1_REGNUM	(MD_REG_FIRST + 1)
#define HI_REGNUM	(WORDS_BIG_ENDIAN ? MD0_REGNUM : MD1_REGNUM)
#define LO_REGNUM	(WORDS_BIG_ENDIAN ? MD1_REGNUM : MD0_REGNUM)
#define T0_REGNUM       (GP_REG_FIRST + 8)
#define T1_REGNUM       (GP_REG_FIRST + 9)
#define K0_REGNUM       (GP_REG_FIRST + 26)
#define K1_REGNUM       (GP_REG_FIRST + 27)
#define SR_REGNUM       (COP0_REG_FIRST + 12)
#define CAUSE_REGNUM    (COP0_REG_FIRST + 13)
#define EPC_REGNUM      (COP0_REG_FIRST + 14)

/* A few bitfield locations for the coprocessor registers */
#define CAUSE_IPL       10
#define SR_IPL          10
#define SR_IE           0
#define SR_EXL          1
#define SR_ERL          2


/* FPSW_REGNUM is the single condition code used if !ISA_HAS_8CC.
   If ISA_HAS_8CC, it should not be used, and an arbitrary ST_REG
   should be used instead.  */
#define FPSW_REGNUM	ST_REG_FIRST

#define GP_REG_P(REGNO)	\
  ((unsigned int) ((int) (REGNO) - GP_REG_FIRST) < GP_REG_NUM)
#define M16_REG_P(REGNO) \
  (((REGNO) >= 2 && (REGNO) <= 7) || (REGNO) == 16 || (REGNO) == 17)
#define FP_REG_P(REGNO)  \
  ((unsigned int) ((int) (REGNO) - FP_REG_FIRST) < FP_REG_NUM)
#define MD_REG_P(REGNO) \
  ((unsigned int) ((int) (REGNO) - MD_REG_FIRST) < MD_REG_NUM)
#define ST_REG_P(REGNO) \
  ((unsigned int) ((int) (REGNO) - ST_REG_FIRST) < ST_REG_NUM)
#define COP0_REG_P(REGNO) \
  ((unsigned int) ((int) (REGNO) - COP0_REG_FIRST) < COP0_REG_NUM)
#define COP2_REG_P(REGNO) \
  ((unsigned int) ((int) (REGNO) - COP2_REG_FIRST) < COP2_REG_NUM)
#define COP3_REG_P(REGNO) \
  ((unsigned int) ((int) (REGNO) - COP3_REG_FIRST) < COP3_REG_NUM)
#define ALL_COP_REG_P(REGNO) \
  ((unsigned int) ((int) (REGNO) - COP0_REG_FIRST) < ALL_COP_REG_NUM)
#define DSP_ACC_REG_P(REGNO) \
  ((unsigned int) ((int) (REGNO) - DSP_ACC_REG_FIRST) < DSP_ACC_REG_NUM)
#define DSP_CONTROL_REG_P(REGNO) \
  ((REGNO) >= DSP_CONTROL_PO_REGNUM && (REGNO) <= DSP_CONTROL_EF_REGNUM)

#define FP_REG_RTX_P(X) (GET_CODE (X) == REG && FP_REG_P (REGNO (X)))

/* Return coprocessor number from register number.  */

#define COPNUM_AS_CHAR_FROM_REGNUM(REGNO) 				\
  (COP0_REG_P (REGNO) ? '0' : COP2_REG_P (REGNO) ? '2'			\
   : COP3_REG_P (REGNO) ? '3' : '?')


#define HARD_REGNO_NREGS(REGNO, MODE) mips_hard_regno_nregs (REGNO, MODE)

/* To make the code simpler, HARD_REGNO_MODE_OK just references an
   array built in override_options.  Because machmodes.h is not yet
   included before this file is processed, the MODE bound can't be
   expressed here.  */

extern char mips_hard_regno_mode_ok[][FIRST_PSEUDO_REGISTER];

#define HARD_REGNO_MODE_OK(REGNO, MODE)					\
  mips_hard_regno_mode_ok[ (int)(MODE) ][ (REGNO) ]

/* Value is 1 if it is a good idea to tie two pseudo registers
   when one has mode MODE1 and one has mode MODE2.
   If HARD_REGNO_MODE_OK could produce different values for MODE1 and MODE2,
   for any hard reg, then this must be 0 for correct output.  */
#define MODES_TIEABLE_P(MODE1, MODE2)					\
  ((GET_MODE_CLASS (MODE1) == MODE_FLOAT ||				\
    GET_MODE_CLASS (MODE1) == MODE_COMPLEX_FLOAT)			\
   == (GET_MODE_CLASS (MODE2) == MODE_FLOAT ||				\
       GET_MODE_CLASS (MODE2) == MODE_COMPLEX_FLOAT))

/* Register to use for pushing function arguments.  */
#define STACK_POINTER_REGNUM (GP_REG_FIRST + 29)

/* These two registers don't really exist: they get eliminated to either
   the stack or hard frame pointer.  */
#define ARG_POINTER_REGNUM 77
#define FRAME_POINTER_REGNUM 78

/* $30 is not available on the mips16, so we use $17 as the frame
   pointer.  */
#define HARD_FRAME_POINTER_REGNUM \
  (TARGET_MIPS16 ? GP_REG_FIRST + 17 : GP_REG_FIRST + 30)

/* Value should be nonzero if functions must have frame pointers.
   Zero means the frame pointer need not be set up (and parms
   may be accessed via the stack pointer) in functions that seem suitable.
   This is computed in `reload', in reload1.c.  */
#define FRAME_POINTER_REQUIRED (current_function_calls_alloca)

/* Register in which static-chain is passed to a function.  */
#define STATIC_CHAIN_REGNUM (GP_REG_FIRST + 2)

/* Pass structure addresses as an "invisible" first argument.  */
#define STRUCT_VALUE 0

/* Registers used as temporaries in prologue/epilogue code.  If we're
   generating mips16 code, these registers must come from the core set
   of 8.  The prologue register mustn't conflict with any incoming
   arguments, the static chain pointer, or the frame pointer.  The
   epilogue temporary mustn't conflict with the return registers, the
   frame pointer, the EH stack adjustment, or the EH data registers.  */

#define MIPS_PROLOGUE_TEMP_REGNUM (GP_REG_FIRST + 3)
#define MIPS_EPILOGUE_TEMP_REGNUM (GP_REG_FIRST + (TARGET_MIPS16 ? 6 : 8))

#define MIPS_PROLOGUE_TEMP(MODE) gen_rtx_REG (MODE, MIPS_PROLOGUE_TEMP_REGNUM)
#define MIPS_EPILOGUE_TEMP(MODE) gen_rtx_REG (MODE, MIPS_EPILOGUE_TEMP_REGNUM)

/* Define this macro if it is as good or better to call a constant
   function address than to call an address kept in a register.  */
#define NO_FUNCTION_CSE 1

/* Define this macro if it is as good or better for a function to
   call itself with an explicit address than to call an address
   kept in a register.  */
#define NO_RECURSIVE_FUNCTION_CSE 1

/* The ABI-defined global pointer.  Sometimes we use a different
   register in leaf functions: see PIC_OFFSET_TABLE_REGNUM.  */
#define GLOBAL_POINTER_REGNUM (GP_REG_FIRST + 28)

/* We normally use $28 as the global pointer.  However, when generating
   n32/64 PIC, it is better for leaf functions to use a call-clobbered
   register instead.  They can then avoid saving and restoring $28
   and perhaps avoid using a frame at all.

   When a leaf function uses something other than $28, mips_expand_prologue
   will modify pic_offset_table_rtx in place.  Take the register number
   from there after reload.  */
#define PIC_OFFSET_TABLE_REGNUM \
  (reload_completed ? REGNO (pic_offset_table_rtx) : GLOBAL_POINTER_REGNUM)

#define PIC_FUNCTION_ADDR_REGNUM (GP_REG_FIRST + 25)

/* Define the classes of registers for register constraints in the
   machine description.  Also define ranges of constants.

   One of the classes must always be named ALL_REGS and include all hard regs.
   If there is more than one class, another class must be named NO_REGS
   and contain no registers.

   The name GENERAL_REGS must be the name of a class (or an alias for
   another name such as ALL_REGS).  This is the class of registers
   that is allowed by "g" or "r" in a register constraint.
   Also, registers outside this class are allocated only when
   instructions express preferences for them.

   The classes must be numbered in nondecreasing order; that is,
   a larger-numbered class must never be contained completely
   in a smaller-numbered class.

   For any two classes, it is very desirable that there be another
   class that represents their union.  */

enum reg_class
{
  NO_REGS,			/* no registers in set */
  M16_NA_REGS,			/* mips16 regs not used to pass args */
  M16_REGS,			/* mips16 directly accessible registers */
  T_REG,			/* mips16 T register ($24) */
  SP_REG,			/* mips16 stack pointer ($29) */
  M16_T_REGS,			/* mips16 registers plus T register */
  M16_SP_REGS,			/* mips16 regs plus stack pointer */
  PIC_FN_ADDR_REG,		/* SVR4 PIC function address register */
  LEA_REGS,			/* Every GPR except $25 */
  GR_REGS,			/* integer registers */
  FP_REGS,			/* floating point registers */
  MD0_REG,			/* multiply/divide register 0 */
  MD1_REG,			/* multiply/divide register 1 */
  MD_REGS,			/* multiply/divide registers (hi/lo) */
  COP0_REGS,			/* generic coprocessor classes */
  COP2_REGS,
  COP3_REGS,
  MD0_AND_GR_REGS,		/* union classes */
  MD1_AND_GR_REGS,
  COP0_AND_GR_REGS,
  COP2_AND_GR_REGS,
  COP3_AND_GR_REGS,
  ALL_COP_REGS,
  ALL_COP_AND_GR_REGS,
  ST_REGS,			/* status registers (fp status) */
  DSP_ACC_REGS,			/* DSP accumulator registers */
  MD_AND_DSP_ACC_REGS,		/* Hi/Lo and DSP accumulator registers */
  DSP_CNTL_REG,			/* DSP control register */
  ALL_REGS,			/* all registers */
  LIM_REG_CLASSES		/* max value + 1 */
};

#define N_REG_CLASSES (int) LIM_REG_CLASSES

#define GENERAL_REGS GR_REGS

/* An initializer containing the names of the register classes as C
   string constants.  These names are used in writing some of the
   debugging dumps.  */

#define REG_CLASS_NAMES							\
{									\
  "NO_REGS",								\
  "M16_NA_REGS",							\
  "M16_REGS",								\
  "T_REG",								\
  "SP_REG",								\
  "M16_T_REGS",								\
  "M16_SP_REGS",							\
  "PIC_FN_ADDR_REG",							\
  "LEA_REGS",								\
  "GR_REGS",								\
  "FP_REGS",								\
  "MD0_REG",								\
  "MD1_REG",								\
  "MD_REGS",								\
  /* coprocessor registers */						\
  "COP0_REGS",								\
  "COP2_REGS",								\
  "COP3_REGS",								\
  "MD0_AND_GR_REGS",							\
  "MD1_AND_GR_REGS",							\
  "COP0_AND_GR_REGS",							\
  "COP2_AND_GR_REGS",							\
  "COP3_AND_GR_REGS",							\
  "ALL_COP_REGS",							\
  "ALL_COP_AND_GR_REGS",						\
  "ST_REGS",								\
  "DSP_ACC_REGS",							\
  "MD_AND_DSP_ACC_REGS",						\
  "DSP_CONTROL_REG",							\
  "ALL_REGS"								\
}

/* An initializer containing the contents of the register classes,
   as integers which are bit masks.  The Nth integer specifies the
   contents of class N.  The way the integer MASK is interpreted is
   that register R is in the class if `MASK & (1 << R)' is 1.

   When the machine has more than 32 registers, an integer does not
   suffice.  Then the integers are replaced by sub-initializers,
   braced groupings containing several integers.  Each
   sub-initializer must be suitable as an initializer for the type
   `HARD_REG_SET' which is defined in `hard-reg-set.h'.  */

#define REG_CLASS_CONTENTS						                                \
{									                                \
  { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },	/* no registers */	\
  { 0x0003000c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },	/* mips16 nonarg regs */\
  { 0x000300fc, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },	/* mips16 registers */	\
  { 0x01000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },	/* mips16 T register */	\
  { 0x20000000, 0x00000000, 0x00000000,	0x00000000, 0x00000000, 0x00000000 },	/* mips16 SP register */ \
  { 0x010300fc, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },	/* mips16 and T regs */ \
  { 0x200300fc, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },	/* mips16 and SP regs */ \
  { 0x02000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },	/* SVR4 PIC function address register */ \
  { 0xfdffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },	/* Every other GPR */   \
  { 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },	/* integer registers */	\
  { 0x00000000, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000 },	/* floating registers*/	\
  { 0x00000000, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000000 },	/* md0 register */	\
  { 0x00000000, 0x00000000, 0x00000002, 0x00000000, 0x00000000, 0x00000000 },	/* md1 register */	\
  { 0x00000000, 0x00000000, 0x00000003, 0x00000000, 0x00000000, 0x00000000 },	/* mul/div registers */	\
  { 0x00000000, 0x00000000, 0xffff0000, 0x0000ffff, 0x00000000, 0x00000000 },   /* cop0 registers */    \
  { 0x00000000, 0x00000000, 0x00000000, 0xffff0000, 0x0000ffff, 0x00000000 },   /* cop2 registers */    \
  { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffff0000, 0x0000ffff },   /* cop3 registers */    \
  { 0xffffffff, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000000 },	/* union classes */     \
  { 0xffffffff, 0x00000000, 0x00000002, 0x00000000, 0x00000000, 0x00000000 },				\
  { 0xffffffff, 0x00000000, 0xffff0000, 0x0000ffff, 0x00000000, 0x00000000 },			        \
  { 0xffffffff, 0x00000000, 0x00000000, 0xffff0000, 0x0000ffff, 0x00000000 },	                        \
  { 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xffff0000, 0x0000ffff },                           \
  { 0x00000000, 0x00000000, 0xffff0000, 0xffffffff, 0xffffffff, 0x0000ffff },                           \
  { 0xffffffff, 0x00000000, 0xffff0000, 0xffffffff, 0xffffffff, 0x0000ffff },                           \
  { 0x00000000, 0x00000000, 0x000007f8, 0x00000000, 0x00000000, 0x00000000 },	/* status registers */	\
  { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x003f0000 },   /* dsp accumulator registers */     \
  { 0x00000000, 0x00000000, 0x00000003, 0x00000000, 0x00000000, 0x003f0000 },   /* hi/lo and dsp accumulator registers */     \
  { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0fc00000 },   /* dsp control registers */     \
  { 0xffffffff, 0xffffffff, 0xffff07ff, 0xffffffff, 0xffffffff, 0x0fffffff }	/* all registers */	\
}


/* A C expression whose value is a register class containing hard
   register REGNO.  In general there is more that one such class;
   choose a class which is "minimal", meaning that no smaller class
   also contains the register.  */

extern const enum reg_class mips_regno_to_class[];

#define REGNO_REG_CLASS(REGNO) mips_regno_to_class[ (REGNO) ]

/* A macro whose definition is the name of the class to which a
   valid base register must belong.  A base register is one used in
   an address which is the register value plus a displacement.  */

#define BASE_REG_CLASS  (TARGET_MIPS16 ? M16_REGS : GR_REGS)

/* A macro whose definition is the name of the class to which a
   valid index register must belong.  An index register is one used
   in an address where its value is either multiplied by a scale
   factor or added to another register (as well as added to a
   displacement).  */

#define INDEX_REG_CLASS NO_REGS

/* When SMALL_REGISTER_CLASSES is nonzero, the compiler allows
   registers explicitly used in the rtl to be used as spill registers
   but prevents the compiler from extending the lifetime of these
   registers.  */

#define SMALL_REGISTER_CLASSES (TARGET_MIPS16)

/* This macro is used later on in the file.  */
#define GR_REG_CLASS_P(CLASS)						\
  ((CLASS) == GR_REGS || (CLASS) == M16_REGS || (CLASS) == T_REG	\
   || (CLASS) == M16_T_REGS || (CLASS) == M16_NA_REGS			\
   || (CLASS) == SP_REG || (CLASS) == M16_SP_REGS 			\
   || (CLASS) == PIC_FN_ADDR_REG || (CLASS) == LEA_REGS)

/* This macro is also used later on in the file.  */
#define COP_REG_CLASS_P(CLASS)						\
  ((CLASS)  == COP0_REGS || (CLASS) == COP2_REGS || (CLASS) == COP3_REGS)

/* REG_ALLOC_ORDER is to order in which to allocate registers.  This
   is the default value (allocate the registers in numeric order).  We
   define it just so that we can override it for the mips16 target in
   ORDER_REGS_FOR_LOCAL_ALLOC.  */

#define REG_ALLOC_ORDER							\
{  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,	\
  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,	\
  32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,	\
  48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,	\
  64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,	\
  80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,	\
  96, 97, 98, 99, 100,101,102,103,104,105,106,107,108,109,110,111,	\
  112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,	\
  128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,	\
  144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,	\
  160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,	\
  176,177,178,179,180,181,182,183,184,185,186,187			\
}

/* ORDER_REGS_FOR_LOCAL_ALLOC is a macro which permits reg_alloc_order
   to be rearranged based on a particular function.  On the mips16, we
   want to allocate $24 (T_REG) before other registers for
   instructions for which it is possible.  */

#define ORDER_REGS_FOR_LOCAL_ALLOC mips_order_regs_for_local_alloc ()

/* REGISTER AND CONSTANT CLASSES */

/* Get reg_class from a letter such as appears in the machine
   description.

   DEFINED REGISTER CLASSES:

   'd'  General (aka integer) registers
        Normally this is GR_REGS, but in mips16 mode this is M16_REGS
   'y'  General registers (in both mips16 and non mips16 mode)
   'e'	mips16 non argument registers (M16_NA_REGS)
   't'  mips16 temporary register ($24)
   'f'	Floating point registers
   'h'	Hi register
   'l'	Lo register
   'x'	Multiply/divide registers
   'z'	FP Status register
   'B'  Cop0 register
   'C'  Cop2 register
   'D'  Cop3 register
   'a'  MD registers and DSP accumulator registers
   'b'	All registers */

extern enum reg_class mips_char_to_class[256];

#define REG_CLASS_FROM_LETTER(C) mips_char_to_class[(unsigned char)(C)]

/* True if VALUE is a signed 16-bit number.  */

#define SMALL_OPERAND(VALUE) \
  ((unsigned HOST_WIDE_INT) (VALUE) + 0x8000 < 0x10000)

/* True if VALUE is a signed 32-bit number.  */

#define BIG_OPERAND(VALUE) \
  ((unsigned HOST_WIDE_INT) (VALUE) + 0x80000000 < 0x100000000LL)

/* True if VALUE is an unsigned 16-bit number.  */

#define SMALL_OPERAND_UNSIGNED(VALUE) \
  (((VALUE) & ~(unsigned HOST_WIDE_INT) 0xffff) == 0)

/* True if VALUE is an unsigned 32-bit number.  */

#define BIG_OPERAND_UNSIGNED(VALUE) \
  (((VALUE) & ~(unsigned HOST_WIDE_INT) 0xffffffff) == 0)

/* True if VALUE can be loaded into a register using LUI.  */

#define LUI_OPERAND(VALUE)					\
  (!TARGET_MIPS16                                               \
   && (((VALUE) | 0x7fff0000) == 0x7fff0000			\
       || ((VALUE) | 0x7fff0000) + 0x10000 == 0))

/* Return a value X with the low 16 bits clear, and such that
   VALUE - X is a signed 16-bit value.  */

#define CONST_HIGH_PART(VALUE) \
  (((VALUE) + 0x8000) & ~(unsigned HOST_WIDE_INT) 0xffff)

#define CONST_LOW_PART(VALUE) \
  ((VALUE) - CONST_HIGH_PART (VALUE))

#define SMALL_INT(X) SMALL_OPERAND (INTVAL (X))
#define SMALL_INT_UNSIGNED(X) SMALL_OPERAND_UNSIGNED (INTVAL (X))
#define LUI_INT(X) LUI_OPERAND (INTVAL (X))

/* The letters I, J, K, L, M, N, O, and P in a register constraint
   string can be used to stand for particular ranges of immediate
   operands.  This macro defines what the ranges are.  C is the
   letter, and VALUE is a constant value.  Return 1 if VALUE is
   in the range specified by C.  */

/* For MIPS:

   `I'	is used for the range of constants an arithmetic insn can
	actually contain (16 bits signed integers).

   `J'	is used for the range which is just zero (ie, $r0).

   `K'	is used for the range of constants a logical insn can actually
	contain (16 bit zero-extended integers).

   `L'	is used for the range of constants that be loaded with lui
	(ie, the bottom 16 bits are zero).

   `M'	is used for the range of constants that take two words to load
	(ie, not matched by `I', `K', and `L').

   `N'	is used for negative 16 bit constants other than -65536.

   `O'	is a 15 bit signed integer.

   `P'	is used for positive 16 bit constants.  */

#define CONST_OK_FOR_LETTER_P(VALUE, C)					\
  ((C) == 'I' ? SMALL_OPERAND (VALUE)					\
   : (C) == 'J' ? ((VALUE) == 0)					\
   : (C) == 'K' ? SMALL_OPERAND_UNSIGNED (VALUE)			\
   : (C) == 'L' ? LUI_OPERAND (VALUE)					\
   : (C) == 'M' ? (!SMALL_OPERAND (VALUE)				\
		   && !SMALL_OPERAND_UNSIGNED (VALUE)			\
		   && !LUI_OPERAND (VALUE))				\
   : (C) == 'N' ? ((unsigned HOST_WIDE_INT) ((VALUE) + 0xffff) < 0xffff) \
   : (C) == 'O' ? ((unsigned HOST_WIDE_INT) ((VALUE) + 0x4000) < 0x8000) \
   : (C) == 'P' ? ((VALUE) != 0 && (((VALUE) & ~0x0000ffff) == 0))	\
   : 0)

/* Similar, but for floating constants, and defining letters G and H.
   Here VALUE is the CONST_DOUBLE rtx itself.  */

/* For Mips

  'G'	: Floating point 0 */

#define CONST_DOUBLE_OK_FOR_LETTER_P(VALUE, C)				\
  ((C) == 'G'								\
   && (VALUE) == CONST0_RTX (GET_MODE (VALUE)))

/* Letters in the range `Q' through `U' may be defined in a
   machine-dependent fashion to stand for arbitrary operand types.
   The machine description macro `EXTRA_CONSTRAINT' is passed the
   operand as its first argument and the constraint letter as its
   second operand.

   `Q' is for signed 16-bit constants.
   `R' is for single-instruction memory references.  Note that this
	 constraint has often been used in linux and glibc code.
   `S' is for legitimate constant call addresses.
   `T' is for constant move_operands that cannot be safely loaded into $25.
   `U' is for constant move_operands that can be safely loaded into $25.
   `W' is for memory references that are based on a member of BASE_REG_CLASS.
	 This is true for all non-mips16 references (although it can somtimes
	 be indirect if !TARGET_EXPLICIT_RELOCS).  For mips16, it excludes
	 stack and constant-pool references.
   `Y' is for 0 valued vector constants.  */

#define EXTRA_CONSTRAINT(OP,CODE)					\
  (((CODE) == 'Q')	  ? const_arith_operand (OP, VOIDmode)		\
   : ((CODE) == 'R')	  ? (GET_CODE (OP) == MEM			\
			     && mips_fetch_insns (OP) == 1)		\
   : ((CODE) == 'S')	  ? (CONSTANT_P (OP)				\
			     && call_insn_operand (OP, VOIDmode))	\
   : ((CODE) == 'T')	  ? (CONSTANT_P (OP)				\
			     && move_operand (OP, VOIDmode)		\
			     && mips_dangerous_for_la25_p (OP))		\
   : ((CODE) == 'U')	  ? (CONSTANT_P (OP)				\
			     && move_operand (OP, VOIDmode)		\
			     && !mips_dangerous_for_la25_p (OP))	\
   : ((CODE) == 'W')	  ? (GET_CODE (OP) == MEM			\
			     && memory_operand (OP, VOIDmode)		\
			     && (!TARGET_MIPS16				\
				 || (!stack_operand (OP, VOIDmode)	\
				     && !CONSTANT_P (XEXP (OP, 0)))))	\
   : ((CODE) == 'Y')      ? (GET_CODE (OP) == CONST_VECTOR              \
                             && (OP) == CONST0_RTX (GET_MODE (OP)))     \
   : FALSE)

/* Say which of the above are memory constraints.  */
#define EXTRA_MEMORY_CONSTRAINT(C, STR) ((C) == 'R' || (C) == 'W')

#define PREFERRED_RELOAD_CLASS(X,CLASS)					\
  mips_preferred_reload_class (X, CLASS)

/* Certain machines have the property that some registers cannot be
   copied to some other registers without using memory.  Define this
   macro on those machines to be a C expression that is nonzero if
   objects of mode MODE in registers of CLASS1 can only be copied to
   registers of class CLASS2 by storing a register of CLASS1 into
   memory and loading that memory location into a register of CLASS2.

   Do not define this macro if its value would always be zero.  */
#if 0
#define SECONDARY_MEMORY_NEEDED(CLASS1, CLASS2, MODE)			\
  ((!TARGET_DEBUG_H_MODE						\
    && GET_MODE_CLASS (MODE) == MODE_INT				\
    && ((CLASS1 == FP_REGS && GR_REG_CLASS_P (CLASS2))			\
	|| (GR_REG_CLASS_P (CLASS1) && CLASS2 == FP_REGS)))		\
   || (TARGET_FLOAT64 && !TARGET_64BIT && (MODE) == DFmode		\
       && ((GR_REG_CLASS_P (CLASS1) && CLASS2 == FP_REGS)		\
	   || (GR_REG_CLASS_P (CLASS2) && CLASS1 == FP_REGS))))
#endif
/* The HI and LO registers can only be reloaded via the general
   registers.  Condition code registers can only be loaded to the
   general registers, and from the floating point registers.  */

#define SECONDARY_INPUT_RELOAD_CLASS(CLASS, MODE, X)			\
  mips_secondary_reload_class (CLASS, MODE, X, 1)
#define SECONDARY_OUTPUT_RELOAD_CLASS(CLASS, MODE, X)			\
  mips_secondary_reload_class (CLASS, MODE, X, 0)

/* Return the maximum number of consecutive registers
   needed to represent mode MODE in a register of class CLASS.  */

#define CLASS_MAX_NREGS(CLASS, MODE) mips_class_max_nregs (CLASS, MODE)

#define CANNOT_CHANGE_MODE_CLASS(FROM, TO, CLASS) \
  mips_cannot_change_mode_class (FROM, TO, CLASS)

/* Stack layout; function entry, exit and calling.  */

#define STACK_GROWS_DOWNWARD

/* The offset of the first local variable from the beginning of the frame.
   See compute_frame_size for details about the frame layout.

   ??? If flag_profile_values is true, and we are generating 32-bit code, then
   we assume that we will need 16 bytes of argument space.  This is because
   the value profiling code may emit calls to cmpdi2 in leaf functions.
   Without this hack, the local variables will start at sp+8 and the gp save
   area will be at sp+16, and thus they will overlap.  compute_frame_size is
   OK because it uses STARTING_FRAME_OFFSET to compute cprestore_size, which
   will end up as 24 instead of 8.  This won't be needed if profiling code is
   inserted before virtual register instantiation.  */

#define STARTING_FRAME_OFFSET						\
  ((flag_profile_values && ! TARGET_64BIT				\
    ? MAX (REG_PARM_STACK_SPACE(NULL), current_function_outgoing_args_size) \
    : current_function_outgoing_args_size)				\
   + (TARGET_ABICALLS && !TARGET_NEWABI					\
      ? MIPS_STACK_ALIGN (UNITS_PER_WORD) : 0))

#define RETURN_ADDR_RTX mips_return_addr

/* Since the mips16 ISA mode is encoded in the least-significant bit
   of the address, mask it off return addresses for purposes of
   finding exception handling regions.  */

#define MASK_RETURN_ADDR GEN_INT (-2)


/* Similarly, don't use the least-significant bit to tell pointers to
   code from vtable index.  */

#define TARGET_PTRMEMFUNC_VBIT_LOCATION ptrmemfunc_vbit_in_delta

/* The eliminations to $17 are only used for mips16 code.  See the
   definition of HARD_FRAME_POINTER_REGNUM.  */

#define ELIMINABLE_REGS							\
{{ ARG_POINTER_REGNUM,   STACK_POINTER_REGNUM},				\
 { ARG_POINTER_REGNUM,   GP_REG_FIRST + 30},				\
 { ARG_POINTER_REGNUM,   GP_REG_FIRST + 17},				\
 { FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM},				\
 { FRAME_POINTER_REGNUM, GP_REG_FIRST + 30},				\
 { FRAME_POINTER_REGNUM, GP_REG_FIRST + 17}}

/* We can always eliminate to the hard frame pointer.  We can eliminate
   to the stack pointer unless a frame pointer is needed.

   In mips16 mode, we need a frame pointer for a large frame; otherwise,
   reload may be unable to compute the address of a local variable,
   since there is no way to add a large constant to the stack pointer
   without using a temporary register.  */
#define CAN_ELIMINATE(FROM, TO)						\
  ((TO) == HARD_FRAME_POINTER_REGNUM 				        \
   || ((TO) == STACK_POINTER_REGNUM && !frame_pointer_needed		\
       && (!TARGET_MIPS16						\
	   || compute_frame_size (get_frame_size ()) < 32768)))

#define INITIAL_ELIMINATION_OFFSET(FROM, TO, OFFSET) \
  (OFFSET) = mips_initial_elimination_offset ((FROM), (TO))

/* Allocate stack space for arguments at the beginning of each function.  */
#define ACCUMULATE_OUTGOING_ARGS 1

/* The argument pointer always points to the first argument.  */
#define FIRST_PARM_OFFSET(FNDECL) 0

/* o32 and o64 reserve stack space for all argument registers.  */
#define REG_PARM_STACK_SPACE(FNDECL) 			\
  ((mips_abi == ABI_32 || mips_abi == ABI_O64)		\
   ? (MAX_ARGS_IN_REGISTERS * UNITS_PER_WORD)		\
   : 0)

/* Define this if it is the responsibility of the caller to
   allocate the area reserved for arguments passed in registers.
   If `ACCUMULATE_OUTGOING_ARGS' is also defined, the only effect
   of this macro is to determine whether the space is included in
   `current_function_outgoing_args_size'.  */
#define OUTGOING_REG_PARM_STACK_SPACE

#define STACK_BOUNDARY \
  ((mips_abi == ABI_32 || mips_abi == ABI_O64 || mips_abi == ABI_EABI) \
   ? 64 : 128)


#define RETURN_POPS_ARGS(FUNDECL,FUNTYPE,SIZE) 0

/* Symbolic macros for the registers used to return integer and floating
   point values.  */

#define GP_RETURN (GP_REG_FIRST + 2)
#define FP_RETURN ((TARGET_SOFT_FLOAT) ? GP_RETURN : (FP_REG_FIRST + 0))

#define MAX_ARGS_IN_REGISTERS \
  ((mips_abi == ABI_32 || mips_abi == ABI_O64) ? 4 : 8)

/* Largest possible value of MAX_ARGS_IN_REGISTERS.  */

#define BIGGEST_MAX_ARGS_IN_REGISTERS 8

/* Symbolic macros for the first/last argument registers.  */

#define GP_ARG_FIRST (GP_REG_FIRST + 4)
#define GP_ARG_LAST  (GP_ARG_FIRST + MAX_ARGS_IN_REGISTERS - 1)
#define FP_ARG_FIRST (FP_REG_FIRST + 12)
#define FP_ARG_LAST  (FP_ARG_FIRST + MAX_ARGS_IN_REGISTERS - 1)

#define LIBCALL_VALUE(MODE) \
  mips_function_value (NULL_TREE, NULL, (MODE))

#define FUNCTION_VALUE(VALTYPE, FUNC) \
  mips_function_value ((VALTYPE), (FUNC), VOIDmode)

/* 1 if N is a possible register number for a function value.
   On the MIPS, R2 R3 and F0 F2 are the only register thus used.
   Currently, R2 and F0 are only implemented here (C has no complex type)  */

#define FUNCTION_VALUE_REGNO_P(N) ((N) == GP_RETURN || (N) == FP_RETURN \
  || (LONG_DOUBLE_TYPE_SIZE == 128 && FP_RETURN != GP_RETURN \
      && (N) == FP_RETURN + 2))

/* 1 if N is a possible register number for function argument passing.
   We have no FP argument registers when soft-float.  When FP registers
   are 32 bits, we can't directly reference the odd numbered ones.  */

#define FUNCTION_ARG_REGNO_P(N)					\
  ((IN_RANGE((N), GP_ARG_FIRST, GP_ARG_LAST)			\
    || (IN_RANGE((N), FP_ARG_FIRST, FP_ARG_LAST)		\
	&& ((N) % FP_INC == 0) && mips_abi != ABI_O64))		\
   && !fixed_regs[N])

#define RETURN_IN_MEMORY(TYPE) mips_return_in_memory (TYPE)

#define SETUP_INCOMING_VARARGS(CUM,MODE,TYPE,PRETEND_SIZE,NO_RTL)	\
	(PRETEND_SIZE) = mips_setup_incoming_varargs (&(CUM), (MODE),	\
						      (TYPE), (NO_RTL))

#define STRICT_ARGUMENT_NAMING (mips_abi != ABI_32 && mips_abi != ABI_O64)

/* This structure has to cope with two different argument allocation
   schemes.  Most MIPS ABIs view the arguments as a structure, of which
   the first N words go in registers and the rest go on the stack.  If I
   < N, the Ith word might go in Ith integer argument register or in a
   floating-point register.  For these ABIs, we only need to remember
   the offset of the current argument into the structure.

   The EABI instead allocates the integer and floating-point arguments
   separately.  The first N words of FP arguments go in FP registers,
   the rest go on the stack.  Likewise, the first N words of the other
   arguments go in integer registers, and the rest go on the stack.  We
   need to maintain three counts: the number of integer registers used,
   the number of floating-point registers used, and the number of words
   passed on the stack.

   We could keep separate information for the two ABIs (a word count for
   the standard ABIs, and three separate counts for the EABI).  But it
   seems simpler to view the standard ABIs as forms of EABI that do not
   allocate floating-point registers.

   So for the standard ABIs, the first N words are allocated to integer
   registers, and function_arg decides on an argument-by-argument basis
   whether that argument should really go in an integer register, or in
   a floating-point one.  */

typedef struct mips_args
  {
    /* Always true for varargs functions.  Otherwise true if at least
       one argument has been passed in an integer register.  */
    int gp_reg_found;

    /* The number of arguments seen so far.  */
    unsigned int arg_number;

    /* The number of integer registers used so far.  For all ABIs except
       EABI, this is the number of words that have been added to the
       argument structure, limited to MAX_ARGS_IN_REGISTERS.  */
    unsigned int num_gprs;

    /* For EABI, the number of floating-point registers used so far.  */
    unsigned int num_fprs;

    /* The number of words passed on the stack.  */
    unsigned int stack_words;

    /* On the mips16, we need to keep track of which floating point
       arguments were passed in general registers, but would have been
       passed in the FP regs if this were a 32 bit function, so that we
       can move them to the FP regs if we wind up calling a 32 bit
       function.  We record this information in fp_code, encoded in base
       four.  A zero digit means no floating point argument, a one digit
       means an SFmode argument, and a two digit means a DFmode argument,
       and a three digit is not used.  The low order digit is the first
       argument.  Thus 6 == 1 * 4 + 2 means a DFmode argument followed by
       an SFmode argument.  ??? A more sophisticated approach will be
       needed if MIPS_ABI != ABI_32.  */
    int fp_code;

    /* True if the function has a prototype.  */
    int prototype;
  } CUMULATIVE_ARGS;

/* Initialize a variable CUM of type CUMULATIVE_ARGS
   for a call to a function whose data type is FNTYPE.
   For a library call, FNTYPE is 0.  */

#define INIT_CUMULATIVE_ARGS(CUM, FNTYPE, LIBNAME, INDIRECT, N_NAMED_ARGS) \
  init_cumulative_args (&CUM, FNTYPE, LIBNAME)				\
 
/* Update the data in CUM to advance over an argument
of mode MODE and data type TYPE.
(TYPE is null for libcalls where that information may not be available.)  */

#define FUNCTION_ARG_ADVANCE(CUM, MODE, TYPE, NAMED)			\
  function_arg_advance (&CUM, MODE, TYPE, NAMED)

/* Determine where to put an argument to a function.
   Value is zero to push the argument on the stack,
   or a hard register in which to store the argument.

   MODE is the argument's machine mode.
   TYPE is the data type of the argument (as a tree).
    This is null for libcalls where that information may
    not be available.
   CUM is a variable of type CUMULATIVE_ARGS which gives info about
    the preceding args and about the function being called.
   NAMED is nonzero if this argument is a named parameter
    (otherwise it is an extra parameter matching an ellipsis).  */

#define FUNCTION_ARG(CUM, MODE, TYPE, NAMED) \
  function_arg( &CUM, MODE, TYPE, NAMED)

/* For an arg passed partly in registers and partly in memory,
   this is the number of registers used.
   For args passed entirely in registers or entirely in memory, zero.  */

#define FUNCTION_ARG_PARTIAL_NREGS(CUM, MODE, TYPE, NAMED) \
  function_arg_partial_nregs (&CUM, MODE, TYPE, NAMED)

/* If defined, a C expression that gives the alignment boundary, in
   bits, of an argument with the specified mode and type.  If it is
   not defined,  `PARM_BOUNDARY' is used for all arguments.  */

#define FUNCTION_ARG_BOUNDARY(MODE, TYPE)				\
  (((TYPE) != 0)							\
	? ((TYPE_ALIGN(TYPE) <= PARM_BOUNDARY)				\
		? PARM_BOUNDARY						\
		: TYPE_ALIGN(TYPE))					\
	: ((GET_MODE_ALIGNMENT(MODE) <= PARM_BOUNDARY)			\
		? PARM_BOUNDARY						\
		: GET_MODE_ALIGNMENT(MODE)))

#define FUNCTION_ARG_PASS_BY_REFERENCE(CUM, MODE, TYPE, NAMED)		\
  function_arg_pass_by_reference (&CUM, MODE, TYPE, NAMED)

#define FUNCTION_ARG_PADDING(MODE, TYPE)		\
  (mips_pad_arg_upward (MODE, TYPE) ? upward : downward)

#define BLOCK_REG_PADDING(MODE, TYPE, FIRST)		\
  (mips_pad_reg_upward (MODE, TYPE) ? upward : downward)

#define FUNCTION_ARG_CALLEE_COPIES(CUM, MODE, TYPE, NAMED)		\
  (mips_abi == ABI_EABI && (NAMED)					\
   && FUNCTION_ARG_PASS_BY_REFERENCE (CUM, MODE, TYPE, NAMED))

/* Modified version of the macro in expr.h.  Only return true if
   the type has a variable size or if the front end requires it
   to be passed by reference.  */
#define MUST_PASS_IN_STACK(MODE,TYPE)			\
  ((TYPE) != 0						\
   && (TREE_CODE (TYPE_SIZE (TYPE)) != INTEGER_CST	\
       || TREE_ADDRESSABLE (TYPE)))

/* True if using EABI and varargs can be passed in floating-point
   registers.  Under these conditions, we need a more complex form
   of va_list, which tracks GPR, FPR and stack arguments separately.  */
#define EABI_FLOAT_VARARGS_P \
	(mips_abi == ABI_EABI && UNITS_PER_FPVALUE >= UNITS_PER_DOUBLE)


/* Say that the epilogue uses the return address register.  Note that
   in the case of sibcalls, the values "used by the epilogue" are
   considered live at the start of the called function.  */
#define EPILOGUE_USES(REGNO) (mchp_epilogue_uses (REGNO))


/* Treat LOC as a byte offset from the stack pointer and round it up
   to the next fully-aligned offset.  */
#define MIPS_STACK_ALIGN(LOC)						\
  ((mips_abi == ABI_32 || mips_abi == ABI_O64 || mips_abi == ABI_EABI)	\
   ? ((LOC) + 7) & ~7							\
   : ((LOC) + 15) & ~15)


/* Implement `va_start' for varargs and stdarg.  */
#define EXPAND_BUILTIN_VA_START(valist, nextarg) \
  mips_va_start (valist, nextarg)

/* Implement `va_arg'.  */
#define EXPAND_BUILTIN_VA_ARG(valist, type) \
  mips_va_arg (valist, type)

/* Tell final.c that we don't need a label passed to mcount.  */
#define NO_PROFILE_COUNTERS 1

/* Output assembler code to FILE to increment profiler label # LABELNO
   for profiling a function entry.  */

#define FUNCTION_PROFILER(FILE, LABELNO)				\
{									\
  if (TARGET_MIPS16)							\
    sorry ("mips16 function profiling");				\
  fprintf (FILE, "\t.set\tnoat\n");					\
  fprintf (FILE, "\tmove\t%s,%s\t\t# save current return address\n",	\
	   reg_names[GP_REG_FIRST + 1], reg_names[GP_REG_FIRST + 31]);	\
  if (mips_abi != ABI_N32 && mips_abi != ABI_64)			\
    {									\
      fprintf (FILE,							\
	       "\t%s\t%s,%s,%d\t\t# _mcount pops 2 words from  stack\n", \
	       TARGET_64BIT ? "dsubu" : "subu",				\
	       reg_names[STACK_POINTER_REGNUM],				\
	       reg_names[STACK_POINTER_REGNUM],				\
	       Pmode == DImode ? 16 : 8);				\
    }									\
  fprintf (FILE, "\tjal\t_mcount\n");                                   \
  fprintf (FILE, "\t.set\tat\n");					\
}

/* Define this macro if the code for function profiling should come
   before the function prologue.  Normally, the profiling code comes
   after.  */

/* #define PROFILE_BEFORE_PROLOGUE */

/* EXIT_IGNORE_STACK should be nonzero if, when returning from a function,
   the stack pointer does not matter.  The value is tested only in
   functions that have frame pointers.
   No definition is equivalent to always zero.  */

#define EXIT_IGNORE_STACK 1


/* A C statement to output, on the stream FILE, assembler code for a
   block of data that contains the constant parts of a trampoline.
   This code should not include a label--the label is taken care of
   automatically.  */

#define TRAMPOLINE_TEMPLATE(STREAM)					 \
{									 \
  fprintf (STREAM, "\t.word\t0x03e00821\t\t# move   $1,$31\n");		\
  fprintf (STREAM, "\t.word\t0x04110001\t\t# bgezal $0,.+8\n");		\
  fprintf (STREAM, "\t.word\t0x00000000\t\t# nop\n");			\
  if (ptr_mode == DImode)						\
    {									\
      fprintf (STREAM, "\t.word\t0xdfe30014\t\t# ld     $3,20($31)\n");	\
      fprintf (STREAM, "\t.word\t0xdfe2001c\t\t# ld     $2,28($31)\n");	\
    }									\
  else									\
    {									\
      fprintf (STREAM, "\t.word\t0x8fe30014\t\t# lw     $3,20($31)\n");	\
      fprintf (STREAM, "\t.word\t0x8fe20018\t\t# lw     $2,24($31)\n");	\
    }									\
  fprintf (STREAM, "\t.word\t0x0060c821\t\t# move   $25,$3 (abicalls)\n"); \
  fprintf (STREAM, "\t.word\t0x00600008\t\t# jr     $3\n");		\
  fprintf (STREAM, "\t.word\t0x0020f821\t\t# move   $31,$1\n");		\
  if (ptr_mode == DImode)						\
    {									\
      fprintf (STREAM, "\t.dword\t0x00000000\t\t# <function address>\n"); \
      fprintf (STREAM, "\t.dword\t0x00000000\t\t# <static chain value>\n"); \
    }									\
  else									\
    {									\
      fprintf (STREAM, "\t.word\t0x00000000\t\t# <function address>\n"); \
      fprintf (STREAM, "\t.word\t0x00000000\t\t# <static chain value>\n"); \
    }									\
}

/* A C expression for the size in bytes of the trampoline, as an
   integer.  */

#define TRAMPOLINE_SIZE (32 + GET_MODE_SIZE (ptr_mode) * 2)

/* Alignment required for trampolines, in bits.  */

#define TRAMPOLINE_ALIGNMENT GET_MODE_BITSIZE (ptr_mode)

/* INITIALIZE_TRAMPOLINE calls this library function to flush
   program and data caches.  */

#ifndef CACHE_FLUSH_FUNC
#define CACHE_FLUSH_FUNC "_flush_cache"
#endif

#ifndef MIPS_ICACHE_SYNC
#define MIPS_ICACHE_SYNC(ADDR, SIZE)					    \
  /* Flush both caches.  We need to flush the data cache in case	    \
     the system has a write-back cache.  */				    \
  /* ??? Should check the return value for errors.  */			    \
  if (mips_cache_flush_func && mips_cache_flush_func[0])		    \
    emit_library_call (gen_rtx_SYMBOL_REF (Pmode, mips_cache_flush_func),   \
		       0, VOIDmode, 3, ADDR, Pmode,			    \
		       GEN_INT (SIZE), TYPE_MODE (integer_type_node),	    \
		       GEN_INT (3), TYPE_MODE (integer_type_node))
#endif

/* A C statement to initialize the variable parts of a trampoline.
   ADDR is an RTX for the address of the trampoline; FNADDR is an
   RTX for the address of the nested function; STATIC_CHAIN is an
   RTX for the static chain value that should be passed to the
   function when it is called.  */

#define INITIALIZE_TRAMPOLINE(ADDR, FUNC, CHAIN)			    \
{									    \
  rtx func_addr, chain_addr;						    \
									    \
  func_addr = plus_constant (ADDR, 32);					    \
  chain_addr = plus_constant (func_addr, GET_MODE_SIZE (ptr_mode));	    \
  emit_move_insn (gen_rtx_MEM (ptr_mode, func_addr), FUNC);		    \
  emit_move_insn (gen_rtx_MEM (ptr_mode, chain_addr), CHAIN);		    \
  MIPS_ICACHE_SYNC (ADDR, TRAMPOLINE_SIZE);				    \
}

/* Addressing modes, and classification of registers for them.  */

#define REGNO_OK_FOR_INDEX_P(REGNO) 0
#define REGNO_MODE_OK_FOR_BASE_P(REGNO, MODE) \
  mips_regno_mode_ok_for_base_p (REGNO, MODE, 1)

/* The macros REG_OK_FOR..._P assume that the arg is a REG rtx
   and check its validity for a certain class.
   We have two alternate definitions for each of them.
   The usual definition accepts all pseudo regs; the other rejects them all.
   The symbol REG_OK_STRICT causes the latter definition to be used.

   Most source files want to accept pseudo regs in the hope that
   they will get allocated to the class that the insn wants them to be in.
   Some source files that are used after register allocation
   need to be strict.  */

#ifndef REG_OK_STRICT
#define REG_MODE_OK_FOR_BASE_P(X, MODE) \
  mips_regno_mode_ok_for_base_p (REGNO (X), MODE, 0)
#else
#define REG_MODE_OK_FOR_BASE_P(X, MODE) \
  mips_regno_mode_ok_for_base_p (REGNO (X), MODE, 1)
#endif

#define REG_OK_FOR_INDEX_P(X) 0


/* Maximum number of registers that can appear in a valid memory address.  */

#define MAX_REGS_PER_ADDRESS 1

/* A C compound statement with a conditional `goto LABEL;' executed
   if X (an RTX) is a legitimate memory address on the target
   machine for a memory operand of mode MODE.  */

#if 1
#define GO_PRINTF(x)	fprintf(stderr, (x))
#define GO_PRINTF2(x,y)	fprintf(stderr, (x), (y))
#define GO_DEBUG_RTX(x) debug_rtx(x)

#else
#define GO_PRINTF(x)
#define GO_PRINTF2(x,y)
#define GO_DEBUG_RTX(x)
#endif

#ifdef REG_OK_STRICT
#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, ADDR)	\
{						\
  if (mips_legitimate_address_p (MODE, X, 1))	\
    goto ADDR;					\
}
#else
#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, ADDR)	\
{						\
  if (mips_legitimate_address_p (MODE, X, 0))	\
    goto ADDR;					\
}
#endif

/* Check for constness inline but use mips_legitimate_address_p
   to check whether a constant really is an address.  */

#define CONSTANT_ADDRESS_P(X) \
  (CONSTANT_P (X) && mips_legitimate_address_p (SImode, X, 0))

#define LEGITIMATE_CONSTANT_P(X) (mips_const_insns (X) > 0)

#define LEGITIMIZE_ADDRESS(X,OLDX,MODE,WIN)			\
  do {								\
    if (mips_legitimize_address (&(X), MODE))			\
      goto WIN;							\
  } while (0)


/* A C statement or compound statement with a conditional `goto
   LABEL;' executed if memory address X (an RTX) can have different
   meanings depending on the machine mode of the memory reference it
   is used for.

   Autoincrement and autodecrement addresses typically have
   mode-dependent effects because the amount of the increment or
   decrement is the size of the operand being addressed.  Some
   machines have other mode-dependent addresses.  Many RISC machines
   have no mode-dependent addresses.

   You may assume that ADDR is a valid address for the machine.  */

#define GO_IF_MODE_DEPENDENT_ADDRESS(ADDR,LABEL) {}

/* This handles the magic '..CURRENT_FUNCTION' symbol, which means
   'the start of the function that this code is output in'.  */

#define ASM_OUTPUT_LABELREF(FILE,NAME)  \
  if (strcmp (NAME, "..CURRENT_FUNCTION") == 0)				\
    asm_fprintf ((FILE), "%U%s",					\
		 XSTR (XEXP (DECL_RTL (current_function_decl), 0), 0));	\
  else									\
    asm_fprintf ((FILE), "%U%s", (NAME))

/* The mips16 wants the constant pool to be after the function,
   because the PC relative load instructions use unsigned offsets.  */

#define CONSTANT_POOL_BEFORE_FUNCTION \
  (! TARGET_MIPS16)

extern void  mips_output_pool_epilogue (void);
#define ASM_OUTPUT_POOL_EPILOGUE(FILE, FNNAME, FNDECL, SIZE)	\
  mips_output_pool_epilogue()


/* Specify the machine mode that this machine uses
   for the index in the tablejump instruction.
   ??? Using HImode in mips16 mode can cause overflow.  */
#define CASE_VECTOR_MODE \
  (TARGET_MIPS16 && TARGET_DATA_IN_CODE && ! TARGET_CODE_XONLY\
   ? HImode : ptr_mode)

/* Define as C expression which evaluates to nonzero if the tablejump
   instruction expects the table to contain offsets from the address of the
   table.
   Do not define this if the table should contain absolute addresses.  */
#define CASE_VECTOR_PC_RELATIVE \
  (TARGET_MIPS16 && TARGET_DATA_IN_CODE && ! TARGET_CODE_XONLY)

/* Define this as 1 if `char' should by default be signed; else as 0.  */
#ifndef DEFAULT_SIGNED_CHAR
#define DEFAULT_SIGNED_CHAR 1
#endif

/* Max number of bytes we can move from memory to memory
   in one reasonably fast instruction.  */
#define MOVE_MAX (TARGET_64BIT ? 8 : 4)
#define MAX_MOVE_MAX 8

/* Define this macro as a C expression which is nonzero if
   accessing less than a word of memory (i.e. a `char' or a
   `short') is no faster than accessing a word of memory, i.e., if
   such access require more than one instruction or if there is no
   difference in cost between byte and (aligned) word loads.

   On RISC machines, it tends to generate better code to define
   this as 1, since it avoids making a QI or HI mode register.  */
#define SLOW_BYTE_ACCESS (!TARGET_MIPS16)

/* Define this to be nonzero if shift instructions ignore all but the low-order
   few bits.  */
#define SHIFT_COUNT_TRUNCATED 1

/* Value is 1 if truncating an integer of INPREC bits to OUTPREC bits
   is done just by pretending it is already truncated.  */
#define TRULY_NOOP_TRUNCATION(OUTPREC, INPREC) \
  (TARGET_64BIT ? ((INPREC) <= 32 || (OUTPREC) > 32) : 1)


/* Specify the machine mode that pointers have.
   After generation of rtl, the compiler makes no further distinction
   between pointers and any other objects of this machine mode.  */

#ifndef Pmode
#define Pmode (TARGET_64BIT && TARGET_LONG64 ? DImode : SImode)
#endif

/* Give call MEMs SImode since it is the "most permissive" mode
   for both 32-bit and 64-bit targets.  */

#define FUNCTION_MODE SImode


/* The cost of loading values from the constant pool.  It should be
   larger than the cost of any constant we want to synthesize in-line.  */

#define CONSTANT_POOL_COST COSTS_N_INSNS (8)

/* A C expression for the cost of moving data from a register in
   class FROM to one in class TO.  The classes are expressed using
   the enumeration values such as `GENERAL_REGS'.  A value of 2 is
   the default; other values are interpreted relative to that.

   It is not required that the cost always equal 2 when FROM is the
   same as TO; on some machines it is expensive to move between
   registers if they are not general registers.

   If reload sees an insn consisting of a single `set' between two
   hard registers, and if `REGISTER_MOVE_COST' applied to their
   classes returns a value of 2, reload does not check to ensure
   that the constraints of the insn are met.  Setting a cost of
   other than 2 will allow reload to verify that the constraints are
   met.  You should do this if the `movM' pattern's constraints do
   not allow such copying.  */

#define REGISTER_MOVE_COST(MODE, FROM, TO)				\
  mips_register_move_cost (MODE, FROM, TO)

/* ??? Fix this to be right for the R8000.  */
#define MEMORY_MOVE_COST(MODE,CLASS,TO_P) \
  (((TUNE_MIPS4000 || TUNE_MIPS6000) ? 6 : 4) \
   + memory_move_secondary_cost ((MODE), (CLASS), (TO_P)))

/* Define if copies to/from condition code registers should be avoided.

   This is needed for the MIPS because reload_outcc is not complete;
   it needs to handle cases where the source is a general or another
   condition code register.  */
#define AVOID_CCMODE_COPIES

/* A C expression for the cost of a branch instruction.  A value of
   1 is the default; other values are interpreted relative to that.  */

extern int mips_branch_cost;
#define BRANCH_COST mips_branch_cost

/* If defined, modifies the length assigned to instruction INSN as a
   function of the context in which it is used.  LENGTH is an lvalue
   that contains the initially computed length of the insn and should
   be updated with the correct length of the insn.  */
#define ADJUST_INSN_LENGTH(INSN, LENGTH) \
  ((LENGTH) = mips_adjust_insn_length ((INSN), (LENGTH)))


/* Optionally define this if you have added predicates to
   `MACHINE.c'.  This macro is called within an initializer of an
   array of structures.  The first field in the structure is the
   name of a predicate and the second field is an array of rtl
   codes.  For each predicate, list all rtl codes that can be in
   expressions matched by the predicate.  The list should have a
   trailing comma.  Here is an example of two entries in the list
   for a typical RISC machine:

   #define PREDICATE_CODES \
     {"gen_reg_rtx_operand", {SUBREG, REG}},  \
     {"reg_or_short_cint_operand", {SUBREG, REG, CONST_INT}},

   Defining this macro does not affect the generated code (however,
   incorrect definitions that omit an rtl code that may be matched
   by the predicate can cause the compiler to malfunction).
   Instead, it allows the table built by `genrecog' to be more
   compact and efficient, thus speeding up the compiler.  The most
   important predicates to include in the list specified by this
   macro are thoses used in the most insn patterns.  */

#define PREDICATE_CODES							\
  {"uns_arith_operand",		{ REG, CONST_INT, SUBREG, ADDRESSOF }},	\
  {"symbolic_operand",		{ CONST, SYMBOL_REF, LABEL_REF }},	\
  {"global_got_operand",	{ CONST, SYMBOL_REF, LABEL_REF }},	\
  {"local_got_operand",		{ CONST, SYMBOL_REF, LABEL_REF }},	\
  {"const_arith_operand",	{ CONST_INT }},				\
  {"small_data_pattern",	{ SET, PARALLEL, UNSPEC,		\
				  UNSPEC_VOLATILE }},			\
  {"arith_operand",		{ REG, CONST_INT, CONST, SUBREG, ADDRESSOF }},	\
  {"reg_or_0_operand",		{ REG, CONST_INT, CONST_DOUBLE, SUBREG, ADDRESSOF }}, \
  {"reg_simm10_operand",	{ REG, CONST_INT, SUBREG }},		\
  {"small_int",			{ CONST_INT }},				\
  {"m16_simm4_1",		{ CONST_INT }},				\
  {"m16_simm8_1",		{ CONST_INT }},				\
  {"mips_const_double_ok",	{ CONST_DOUBLE }},			\
  {"const_float_1_operand",	{ CONST_DOUBLE }},			\
  {"reg_or_const_float_1_operand", { CONST_DOUBLE, REG}},               \
  {"simple_memory_operand",	{ MEM, SUBREG }},			\
  {"equality_op",		{ EQ, NE }},				\
  {"cmp_op",			{ EQ, NE, GT, GE, GTU, GEU, LT, LE,	\
				  LTU, LEU }},				\
  {"trap_cmp_op",		{ EQ, NE, GE, GEU, LT, LTU }},		\
  {"pc_or_label_operand",	{ PC, LABEL_REF }},			\
  {"call_insn_operand",		{ CONST, SYMBOL_REF, LABEL_REF, REG }},	\
  {"move_operand", 		{ CONST_INT, CONST_DOUBLE, CONST,	\
				  SYMBOL_REF, LABEL_REF, SUBREG,	\
				  REG, MEM}},				\
  {"stack_operand",		{ MEM }},				\
  {"consttable_operand",	{ LABEL_REF, SYMBOL_REF, CONST_INT,	\
				  CONST_DOUBLE, CONST }},		\
  {"fcc_register_operand",	{ REG, SUBREG }},			\
  {"hilo_operand",		{ REG }},				\
  {"extend_operator",		{ ZERO_EXTEND, SIGN_EXTEND }},

/* A list of predicates that do special things with modes, and so
   should not elicit warnings for VOIDmode match_operand.  */

#define SPECIAL_MODE_PREDICATES \
  "pc_or_label_operand",

/* Control the assembler format that we output.  */

/* Output to assembler file text saying following lines
   may contain character constants, extra white space, comments, etc.  */

#ifndef ASM_APP_ON
#define ASM_APP_ON " #APP\n"
#endif

/* Output to assembler file text saying following lines
   no longer contain unusual constructs.  */

#ifndef ASM_APP_OFF
#define ASM_APP_OFF " #NO_APP\n"
#endif

/* How to refer to registers in assembler output.
   This sequence is indexed by compiler's hard-register-number (see above).

   In order to support the two different conventions for register names,
   we use the name of a table set up in mips.c, which is overwritten
   if -mrnames is used.  */

#define REGISTER_NAMES							\
{									\
  &mips_reg_names[ 0][0],						\
  &mips_reg_names[ 1][0],						\
  &mips_reg_names[ 2][0],						\
  &mips_reg_names[ 3][0],						\
  &mips_reg_names[ 4][0],						\
  &mips_reg_names[ 5][0],						\
  &mips_reg_names[ 6][0],						\
  &mips_reg_names[ 7][0],						\
  &mips_reg_names[ 8][0],						\
  &mips_reg_names[ 9][0],						\
  &mips_reg_names[10][0],						\
  &mips_reg_names[11][0],						\
  &mips_reg_names[12][0],						\
  &mips_reg_names[13][0],						\
  &mips_reg_names[14][0],						\
  &mips_reg_names[15][0],						\
  &mips_reg_names[16][0],						\
  &mips_reg_names[17][0],						\
  &mips_reg_names[18][0],						\
  &mips_reg_names[19][0],						\
  &mips_reg_names[20][0],						\
  &mips_reg_names[21][0],						\
  &mips_reg_names[22][0],						\
  &mips_reg_names[23][0],						\
  &mips_reg_names[24][0],						\
  &mips_reg_names[25][0],						\
  &mips_reg_names[26][0],						\
  &mips_reg_names[27][0],						\
  &mips_reg_names[28][0],						\
  &mips_reg_names[29][0],						\
  &mips_reg_names[30][0],						\
  &mips_reg_names[31][0],						\
  &mips_reg_names[32][0],						\
  &mips_reg_names[33][0],						\
  &mips_reg_names[34][0],						\
  &mips_reg_names[35][0],						\
  &mips_reg_names[36][0],						\
  &mips_reg_names[37][0],						\
  &mips_reg_names[38][0],						\
  &mips_reg_names[39][0],						\
  &mips_reg_names[40][0],						\
  &mips_reg_names[41][0],						\
  &mips_reg_names[42][0],						\
  &mips_reg_names[43][0],						\
  &mips_reg_names[44][0],						\
  &mips_reg_names[45][0],						\
  &mips_reg_names[46][0],						\
  &mips_reg_names[47][0],						\
  &mips_reg_names[48][0],						\
  &mips_reg_names[49][0],						\
  &mips_reg_names[50][0],						\
  &mips_reg_names[51][0],						\
  &mips_reg_names[52][0],						\
  &mips_reg_names[53][0],						\
  &mips_reg_names[54][0],						\
  &mips_reg_names[55][0],						\
  &mips_reg_names[56][0],						\
  &mips_reg_names[57][0],						\
  &mips_reg_names[58][0],						\
  &mips_reg_names[59][0],						\
  &mips_reg_names[60][0],						\
  &mips_reg_names[61][0],						\
  &mips_reg_names[62][0],						\
  &mips_reg_names[63][0],						\
  &mips_reg_names[64][0],						\
  &mips_reg_names[65][0],						\
  &mips_reg_names[66][0],						\
  &mips_reg_names[67][0],						\
  &mips_reg_names[68][0],						\
  &mips_reg_names[69][0],						\
  &mips_reg_names[70][0],						\
  &mips_reg_names[71][0],						\
  &mips_reg_names[72][0],						\
  &mips_reg_names[73][0],						\
  &mips_reg_names[74][0],						\
  &mips_reg_names[75][0],						\
  &mips_reg_names[76][0],						\
  &mips_reg_names[77][0],						\
  &mips_reg_names[78][0],						\
  &mips_reg_names[79][0],						\
  &mips_reg_names[80][0],						\
  &mips_reg_names[81][0],						\
  &mips_reg_names[82][0],						\
  &mips_reg_names[83][0],						\
  &mips_reg_names[84][0],						\
  &mips_reg_names[85][0],						\
  &mips_reg_names[86][0],						\
  &mips_reg_names[87][0],						\
  &mips_reg_names[88][0],						\
  &mips_reg_names[89][0],						\
  &mips_reg_names[90][0],						\
  &mips_reg_names[91][0],						\
  &mips_reg_names[92][0],						\
  &mips_reg_names[93][0],						\
  &mips_reg_names[94][0],						\
  &mips_reg_names[95][0],						\
  &mips_reg_names[96][0],						\
  &mips_reg_names[97][0],						\
  &mips_reg_names[98][0],						\
  &mips_reg_names[99][0],						\
  &mips_reg_names[100][0],						\
  &mips_reg_names[101][0],						\
  &mips_reg_names[102][0],						\
  &mips_reg_names[103][0],						\
  &mips_reg_names[104][0],						\
  &mips_reg_names[105][0],						\
  &mips_reg_names[106][0],						\
  &mips_reg_names[107][0],						\
  &mips_reg_names[108][0],						\
  &mips_reg_names[109][0],						\
  &mips_reg_names[110][0],						\
  &mips_reg_names[111][0],						\
  &mips_reg_names[112][0],						\
  &mips_reg_names[113][0],						\
  &mips_reg_names[114][0],						\
  &mips_reg_names[115][0],						\
  &mips_reg_names[116][0],						\
  &mips_reg_names[117][0],						\
  &mips_reg_names[118][0],						\
  &mips_reg_names[119][0],						\
  &mips_reg_names[120][0],						\
  &mips_reg_names[121][0],						\
  &mips_reg_names[122][0],						\
  &mips_reg_names[123][0],						\
  &mips_reg_names[124][0],						\
  &mips_reg_names[125][0],						\
  &mips_reg_names[126][0],						\
  &mips_reg_names[127][0],						\
  &mips_reg_names[128][0],						\
  &mips_reg_names[129][0],						\
  &mips_reg_names[130][0],						\
  &mips_reg_names[131][0],						\
  &mips_reg_names[132][0],						\
  &mips_reg_names[133][0],						\
  &mips_reg_names[134][0],						\
  &mips_reg_names[135][0],						\
  &mips_reg_names[136][0],						\
  &mips_reg_names[137][0],						\
  &mips_reg_names[138][0],						\
  &mips_reg_names[139][0],						\
  &mips_reg_names[140][0],						\
  &mips_reg_names[141][0],						\
  &mips_reg_names[142][0],						\
  &mips_reg_names[143][0],						\
  &mips_reg_names[144][0],						\
  &mips_reg_names[145][0],						\
  &mips_reg_names[146][0],						\
  &mips_reg_names[147][0],						\
  &mips_reg_names[148][0],						\
  &mips_reg_names[149][0],						\
  &mips_reg_names[150][0],						\
  &mips_reg_names[151][0],						\
  &mips_reg_names[152][0],						\
  &mips_reg_names[153][0],						\
  &mips_reg_names[154][0],						\
  &mips_reg_names[155][0],						\
  &mips_reg_names[156][0],						\
  &mips_reg_names[157][0],						\
  &mips_reg_names[158][0],						\
  &mips_reg_names[159][0],						\
  &mips_reg_names[160][0],						\
  &mips_reg_names[161][0],						\
  &mips_reg_names[162][0],						\
  &mips_reg_names[163][0],						\
  &mips_reg_names[164][0],						\
  &mips_reg_names[165][0],						\
  &mips_reg_names[166][0],						\
  &mips_reg_names[167][0],						\
  &mips_reg_names[168][0],						\
  &mips_reg_names[169][0],						\
  &mips_reg_names[170][0],						\
  &mips_reg_names[171][0],						\
  &mips_reg_names[172][0],						\
  &mips_reg_names[173][0],						\
  &mips_reg_names[174][0],						\
  &mips_reg_names[175][0],						\
  &mips_reg_names[176][0],						\
  &mips_reg_names[177][0],						\
  &mips_reg_names[178][0],						\
  &mips_reg_names[179][0],						\
  &mips_reg_names[180][0],						\
  &mips_reg_names[181][0],						\
  &mips_reg_names[182][0],						\
  &mips_reg_names[183][0],						\
  &mips_reg_names[184][0],						\
  &mips_reg_names[185][0],						\
  &mips_reg_names[186][0],						\
  &mips_reg_names[187][0]						\
}

/* If defined, a C initializer for an array of structures
   containing a name and a register number.  This macro defines
   additional names for hard registers, thus allowing the `asm'
   option in declarations to refer to registers using alternate
   names.

   TODO: needs to be done some different way, which takes account
   of the different ABI software register name conventions.

   We define both names for the integer registers here.  */

#define ADDITIONAL_REGISTER_NAMES					\
{									\
  { "$0",	 0 + GP_REG_FIRST },					\
  { "$1",	 1 + GP_REG_FIRST },					\
  { "$2",	 2 + GP_REG_FIRST },					\
  { "$3",	 3 + GP_REG_FIRST },					\
  { "$4",	 4 + GP_REG_FIRST },					\
  { "$5",	 5 + GP_REG_FIRST },					\
  { "$6",	 6 + GP_REG_FIRST },					\
  { "$7",	 7 + GP_REG_FIRST },					\
  { "$8",	 8 + GP_REG_FIRST },					\
  { "$9",	 9 + GP_REG_FIRST },					\
  { "$10",	10 + GP_REG_FIRST },					\
  { "$11",	11 + GP_REG_FIRST },					\
  { "$12",	12 + GP_REG_FIRST },					\
  { "$13",	13 + GP_REG_FIRST },					\
  { "$14",	14 + GP_REG_FIRST },					\
  { "$15",	15 + GP_REG_FIRST },					\
  { "$16",	16 + GP_REG_FIRST },					\
  { "$17",	17 + GP_REG_FIRST },					\
  { "$18",	18 + GP_REG_FIRST },					\
  { "$19",	19 + GP_REG_FIRST },					\
  { "$20",	20 + GP_REG_FIRST },					\
  { "$21",	21 + GP_REG_FIRST },					\
  { "$22",	22 + GP_REG_FIRST },					\
  { "$23",	23 + GP_REG_FIRST },					\
  { "$24",	24 + GP_REG_FIRST },					\
  { "$25",	25 + GP_REG_FIRST },					\
  { "$26",	26 + GP_REG_FIRST },					\
  { "$27",	27 + GP_REG_FIRST },					\
  { "$28",	28 + GP_REG_FIRST },					\
  { "$29",	29 + GP_REG_FIRST },					\
  { "$30",	30 + GP_REG_FIRST },					\
  { "$31",	31 + GP_REG_FIRST },					\
  { "$sp",	29 + GP_REG_FIRST },					\
  { "$fp",	30 + GP_REG_FIRST },					\
  { "at",	 1 + GP_REG_FIRST },					\
  { "v0",	 2 + GP_REG_FIRST },					\
  { "v1",	 3 + GP_REG_FIRST },					\
  { "a0",	 4 + GP_REG_FIRST },					\
  { "a1",	 5 + GP_REG_FIRST },					\
  { "a2",	 6 + GP_REG_FIRST },					\
  { "a3",	 7 + GP_REG_FIRST },					\
  { "t0",	 8 + GP_REG_FIRST },					\
  { "t1",	 9 + GP_REG_FIRST },					\
  { "t2",	10 + GP_REG_FIRST },					\
  { "t3",	11 + GP_REG_FIRST },					\
  { "t4",	12 + GP_REG_FIRST },					\
  { "t5",	13 + GP_REG_FIRST },					\
  { "t6",	14 + GP_REG_FIRST },					\
  { "t7",	15 + GP_REG_FIRST },					\
  { "s0",	16 + GP_REG_FIRST },					\
  { "s1",	17 + GP_REG_FIRST },					\
  { "s2",	18 + GP_REG_FIRST },					\
  { "s3",	19 + GP_REG_FIRST },					\
  { "s4",	20 + GP_REG_FIRST },					\
  { "s5",	21 + GP_REG_FIRST },					\
  { "s6",	22 + GP_REG_FIRST },					\
  { "s7",	23 + GP_REG_FIRST },					\
  { "t8",	24 + GP_REG_FIRST },					\
  { "t9",	25 + GP_REG_FIRST },					\
  { "k0",	26 + GP_REG_FIRST },					\
  { "k1",	27 + GP_REG_FIRST },					\
  { "gp",	28 + GP_REG_FIRST },					\
  { "sp",	29 + GP_REG_FIRST },					\
  { "s8",	30 + GP_REG_FIRST },					\
  { "fp",	30 + GP_REG_FIRST },					\
  { "ra",	31 + GP_REG_FIRST },					\
  { "$sp",	29 + GP_REG_FIRST },					\
  { "$fp",	30 + GP_REG_FIRST }					\
  ALL_COP_ADDITIONAL_REGISTER_NAMES					\
}

/* This is meant to be redefined in the host dependent files.  It is a
   set of alternative names and regnums for mips coprocessors.  */

#define ALL_COP_ADDITIONAL_REGISTER_NAMES

/* A C compound statement to output to stdio stream STREAM the
   assembler syntax for an instruction operand X.  X is an RTL
   expression.

   CODE is a value that can be used to specify one of several ways
   of printing the operand.  It is used when identical operands
   must be printed differently depending on the context.  CODE
   comes from the `%' specification that was used to request
   printing of the operand.  If the specification was just `%DIGIT'
   then CODE is 0; if the specification was `%LTR DIGIT' then CODE
   is the ASCII code for LTR.

   If X is a register, this macro should print the register's name.
   The names can be found in an array `reg_names' whose type is
   `char *[]'.  `reg_names' is initialized from `REGISTER_NAMES'.

   When the machine description has a specification `%PUNCT' (a `%'
   followed by a punctuation character), this macro is called with
   a null pointer for X and the punctuation character for CODE.

   See mips.c for the MIPS specific codes.  */

#define PRINT_OPERAND(FILE, X, CODE) print_operand (FILE, X, CODE)

/* A C expression which evaluates to true if CODE is a valid
   punctuation character for use in the `PRINT_OPERAND' macro.  If
   `PRINT_OPERAND_PUNCT_VALID_P' is not defined, it means that no
   punctuation characters (except for the standard one, `%') are
   used in this way.  */

#define PRINT_OPERAND_PUNCT_VALID_P(CODE) mips_print_operand_punct[CODE]

/* A C compound statement to output to stdio stream STREAM the
   assembler syntax for an instruction operand that is a memory
   reference whose address is ADDR.  ADDR is an RTL expression.  */

#define PRINT_OPERAND_ADDRESS(FILE, ADDR) print_operand_address (FILE, ADDR)

/*
** Easy access check for function beginning
**/
#define NOTE_INSN_FUNCTION_BEG_P(INSN) \
  ((GET_CODE(INSN) == NOTE) && \
   (NOTE_LINE_NUMBER (INSN) == NOTE_INSN_FUNCTION_BEG))

/* A C statement, to be executed after all slot-filler instructions
   have been output.  If necessary, call `dbr_sequence_length' to
   determine the number of slots filled in a sequence (zero if not
   currently outputting a sequence), to decide how many no-ops to
   output, or whatever.

   Don't define this macro if it has nothing to do, but it is
   helpful in reading assembly output if the extent of the delay
   sequence is made explicit (e.g. with white space).

   Note that output routines for instructions with delay slots must
   be prepared to deal with not being output as part of a sequence
   (i.e.  when the scheduling pass is not run, or when no slot
   fillers could be found.)  The variable `final_sequence' is null
   when not processing a sequence, otherwise it contains the
   `sequence' rtx being output.  */

#define DBR_OUTPUT_SEQEND(STREAM)					\
do									\
  {									\
    if (set_nomacro > 0 && --set_nomacro == 0)				\
      fputs ("\t.set\tmacro\n", STREAM);				\
									\
    if (set_noreorder > 0 && --set_noreorder == 0)			\
      fputs ("\t.set\treorder\n", STREAM);				\
									\
    fputs ("\n", STREAM);						\
  }									\
while (0)


/* How to tell the debugger about changes of source files.  */

#ifndef SET_FILE_NUMBER
#define SET_FILE_NUMBER() ++num_source_filenames
#endif

#define ASM_OUTPUT_SOURCE_FILENAME(STREAM, NAME)			\
  mips_output_filename (STREAM, NAME)

/* This is defined so that it can be overridden in iris6.h.  */
#define ASM_OUTPUT_FILENAME(STREAM, NUM_SOURCE_FILENAMES, NAME) \
do								\
  {								\
    fprintf (STREAM, "\t.file\t%d ", NUM_SOURCE_FILENAMES);	\
    output_quoted_string (STREAM, NAME);			\
    fputs ("\n", STREAM);					\
  }								\
while (0)

/* This is how to output a note the debugger telling it the line number
   to which the following sequence of instructions corresponds.
   Silicon graphics puts a label after each .loc.  */

#ifndef LABEL_AFTER_LOC
#define LABEL_AFTER_LOC(STREAM)
#endif

#ifndef ASM_OUTPUT_SOURCE_LINE
#define ASM_OUTPUT_SOURCE_LINE(STREAM, LINE, COUNTER)		\
  mips_output_lineno (STREAM, LINE)
#endif

/* The MIPS implementation uses some labels for its own purpose.  The
   following lists what labels are created, and are all formed by the
   pattern $L[a-z].*.  The machine independent portion of GCC creates
   labels matching:  $L[A-Z][0-9]+ and $L[0-9]+.

	LM[0-9]+	Silicon Graphics/ECOFF stabs label before each stmt.
	$Lb[0-9]+	Begin blocks for MIPS debug support
	$Lc[0-9]+	Label for use in s<xx> operation.
	$Le[0-9]+	End blocks for MIPS debug support  */

#undef ASM_DECLARE_OBJECT_NAME
#define ASM_DECLARE_OBJECT_NAME(STREAM, NAME, DECL) \
  mips_declare_object (STREAM, NAME, "", ":\n", 0)

/* Globalizing directive for a label.  */
#define GLOBAL_ASM_OP "\t.globl\t"

/* This says how to define a global common symbol.  */

#define ASM_OUTPUT_ALIGNED_DECL_COMMON mips_output_aligned_decl_common

/* This says how to define a local common symbol (ie, not visible to
   linker).  */

#define ASM_OUTPUT_ALIGNED_DECL_LOCAL mips_output_aligned_decl_local

#ifndef ASM_OUTPUT_ALIGNED_LOCAL
#define ASM_OUTPUT_ALIGNED_LOCAL(STREAM, NAME, SIZE, ALIGN) \
  mips_declare_common_object (STREAM, NAME, "\n\t.lcomm\t", SIZE, ALIGN, false)
#endif

/* This says how to output an external.  It would be possible not to
   output anything and let undefined symbol become external. However
   the assembler uses length information on externals to allocate in
   data/sdata bss/sbss, thereby saving exec time.  */

#define ASM_OUTPUT_EXTERNAL(STREAM,DECL,NAME) \
  mips_output_external(STREAM,DECL,NAME)

/* This is how to declare a function name.  The actual work of
   emitting the label is moved to function_prologue, so that we can
   get the line number correctly emitted before the .ent directive,
   and after any .file directives.  Define as empty so that the function
   is not declared before the .ent directive elsewhere.  */

#undef ASM_DECLARE_FUNCTION_NAME
#define ASM_DECLARE_FUNCTION_NAME(STREAM,NAME,DECL)

#ifndef FUNCTION_NAME_ALREADY_DECLARED
#define FUNCTION_NAME_ALREADY_DECLARED 0
#endif

/* This is how to store into the string LABEL
   the symbol_ref name of an internal numbered label where
   PREFIX is the class of label and NUM is the number within the class.
   This is suitable for output with `assemble_name'.  */

#undef ASM_GENERATE_INTERNAL_LABEL
#define ASM_GENERATE_INTERNAL_LABEL(LABEL,PREFIX,NUM)			\
  sprintf ((LABEL), "*%s%s%ld", (LOCAL_LABEL_PREFIX), (PREFIX), (long)(NUM))

/* This is how to output an element of a case-vector that is absolute.  */

#define ASM_OUTPUT_ADDR_VEC_ELT(STREAM, VALUE)				\
  fprintf (STREAM, "\t%s\t%sL%d\n",					\
	   ptr_mode == DImode ? ".dword" : ".word",			\
	   LOCAL_LABEL_PREFIX,						\
	   VALUE)

#define ADDR_VEC_ALIGN(ADDR_VEC) mips_addr_vec_align (ADDR_VEC)

/* This is how to output an element of a case-vector that is relative.
   This is used for pc-relative code (e.g. when TARGET_ABICALLS or
   TARGET_EMBEDDED_PIC).  */

#define ASM_OUTPUT_ADDR_DIFF_ELT(STREAM, BODY, VALUE, REL)		\
do {									\
  if (TARGET_MIPS16)							\
    fprintf (STREAM, "\t.half\t%sL%d-%sL%d\n",				\
	     LOCAL_LABEL_PREFIX, VALUE, LOCAL_LABEL_PREFIX, REL);	\
  else if (TARGET_EMBEDDED_PIC)						\
    fprintf (STREAM, "\t%s\t%sL%d-%sLS%d\n",				\
	     ptr_mode == DImode ? ".dword" : ".word",			\
	     LOCAL_LABEL_PREFIX, VALUE, LOCAL_LABEL_PREFIX, REL);	\
  else if (TARGET_GPWORD)						\
    fprintf (STREAM, "\t%s\t%sL%d\n",					\
	     ptr_mode == DImode ? ".gpdword" : ".gpword",		\
	     LOCAL_LABEL_PREFIX, VALUE);				\
  else									\
    fprintf (STREAM, "\t%s\t%sL%d\n",					\
	     ptr_mode == DImode ? ".dword" : ".word",			\
	     LOCAL_LABEL_PREFIX, VALUE);				\
} while (0)

/* When generating embedded PIC or mips16 code we want to put the jump
   table in the .text section.  In all other cases, we want to put the
   jump table in the .rdata section. */
#define JUMP_TABLES_IN_TEXT_SECTION 					\
  (TARGET_EMBEDDED_PIC 							\
   || (TARGET_MIPS16 && TARGET_DATA_IN_CODE && ! TARGET_CODE_XONLY))

/* Defined to also emit an .align in elfos.h.  We don't want that.  */
#undef  ASM_OUTPUT_CASE_LABEL

/* This is how to output an assembler line
   that says to advance the location counter
   to a multiple of 2**LOG bytes.  */

#define ASM_OUTPUT_ALIGN(STREAM,LOG)					\
  fprintf (STREAM, "\t.align\t%d\n", (LOG))

/* This is how to output an assembler line to advance the location
   counter by SIZE bytes.  */

#undef ASM_OUTPUT_SKIP
#define ASM_OUTPUT_SKIP(STREAM,SIZE)					\
  fprintf (STREAM, "\t.space\t"HOST_WIDE_INT_PRINT_UNSIGNED"\n", (SIZE))

/* This is how to output a string.  */
#undef ASM_OUTPUT_ASCII
#define ASM_OUTPUT_ASCII(STREAM, STRING, LEN)				\
  mips_output_ascii (STREAM, STRING, LEN, "\t.ascii\t")

/* Output #ident as a in the read-only data section.  */
#undef  ASM_OUTPUT_IDENT
#define ASM_OUTPUT_IDENT(FILE, STRING)					\
{									\
  const char *p = STRING;						\
  int size = strlen (p) + 1;						\
  readonly_data_section ();						\
  assemble_string (p, size);						\
}

/* Default to -G 8 */
#ifndef MIPS_DEFAULT_GVALUE
#define MIPS_DEFAULT_GVALUE 8
#endif

/* Define the strings to put out for each section in the object file.  */
#define TEXT_SECTION_ASM_OP	"\t.text"	/* instructions */
#define DATA_SECTION_ASM_OP	"\t.data"	/* large data */
#define SDATA_SECTION_ASM_OP	"\t.sdata"	/* small data */

#undef READONLY_DATA_SECTION_ASM_OP
#define READONLY_DATA_SECTION_ASM_OP	"\t.rdata"	/* read-only data */

/* Given a decl node or constant node, choose the section to output it in
   and select that section.  */

#undef  TARGET_ASM_SELECT_SECTION
#define TARGET_ASM_SELECT_SECTION  mips_select_section

#define ASM_OUTPUT_REG_PUSH(STREAM,REGNO)				\
do									\
  {									\
    fprintf (STREAM, "\t%s\t%s,%s,-8\n\t%s\t%s,0(%s)\n",		\
	     TARGET_64BIT ? "daddiu" : "addiu",				\
	     reg_names[STACK_POINTER_REGNUM],				\
	     reg_names[STACK_POINTER_REGNUM],				\
	     TARGET_64BIT ? "sd" : "sw",				\
	     reg_names[REGNO],						\
	     reg_names[STACK_POINTER_REGNUM]);				\
  }									\
while (0)

#define ASM_OUTPUT_REG_POP(STREAM,REGNO)				\
do									\
  {									\
    if (! set_noreorder)						\
      fprintf (STREAM, "\t.set\tnoreorder\n");				\
									\
    fprintf (STREAM, "\t%s\t%s,0(%s)\n\t%s\t%s,%s,8\n",			\
	     TARGET_64BIT ? "ld" : "lw",				\
	     reg_names[REGNO],						\
	     reg_names[STACK_POINTER_REGNUM],				\
	     TARGET_64BIT ? "daddu" : "addu",				\
	     reg_names[STACK_POINTER_REGNUM],				\
	     reg_names[STACK_POINTER_REGNUM]);				\
									\
    if (! set_noreorder)						\
      fprintf (STREAM, "\t.set\treorder\n");				\
  }									\
while (0)

/* How to start an assembler comment.
   The leading space is important (the mips native assembler requires it).  */
#ifndef ASM_COMMENT_START
#define ASM_COMMENT_START " #"
#endif

/* Default definitions for size_t and ptrdiff_t.  We must override the
   definitions from ../svr4.h on mips-*-linux-gnu.  */

#undef SIZE_TYPE
#define SIZE_TYPE (POINTER_SIZE == 64 ? "long unsigned int" : "unsigned int")

#undef PTRDIFF_TYPE
#define PTRDIFF_TYPE (POINTER_SIZE == 64 ? "long int" : "int")

/* See mips_expand_prologue's use of loadgp for when this should be
   true.  */

#define DONT_ACCESS_GBLS_AFTER_EPILOGUE (TARGET_ABICALLS 		\
					 && mips_abi != ABI_32		\
					 && mips_abi != ABI_O64)


#define DFMODE_NAN \
	unsigned short DFbignan[4] = {0x7ff7, 0xffff, 0xffff, 0xffff}; \
	unsigned short DFlittlenan[4] = {0xffff, 0xffff, 0xffff, 0xfff7}
#define SFMODE_NAN \
	unsigned short SFbignan[2] = {0x7fbf, 0xffff}; \
	unsigned short SFlittlenan[2] = {0xffff, 0xffbf}

/* Generate calls to memcpy, etc., not bcopy, etc.  */
#define TARGET_MEM_FUNCTIONS

/* Define MOVE_RATIO to encourage use of inline movstr when enabled,
   since it should always generate code at least as good as
   move_by_pieces(). But when inline movstr pattern is disabled,
   instead represent the length of a memcpy call sequence (~6 insns),
   so that move_by_pieces will generate inline code if it is shorter
   than a function call. Note that move_by_pieces_ninsns() counts
   memory-to-memory moves, but we'll have to generate a load/store
   pair for each, so further halve the value to take that into
   account. */

#define MOVE_RATIO	((TARGET_MIPS16 || TARGET_MEMCPY) ? 3 : 1)

/* For CLEAR_RATIO use a better estimate of the length of a memset
   call when optimizing for size. */

#define CLEAR_RATIO	(optimize_size ? 5 : 15)

/* STORE_BY_PIECES_P can be used when copying a constant string, but
   in that case each word takes 3 insns (lui, ori, sw), or more in
   64-bit mode, instead of 2 (lw, sw). So better to always fail this
   and let the move_by_pieces code copy the string from read-only
   memory. */

#define STORE_BY_PIECES_P(SIZE, ALIGN) 0

/* SET_BY_PIECES_P is equivalent to CLEAR_BY_PIECES_P, but for a
   non-zero constant, so when optimizing for size it needs to adjust
   the ratio to account for the overhead of loading the constant and
   replicating it across the word - in fact in that case it is never
   worth inlining, since calling memset should always be smaller. */

#define SET_RATIO	(optimize_size ? 3 : 15)
#define SET_BY_PIECES_P(SIZE, ALIGN) \
  (move_by_pieces_ninsns (SIZE, ALIGN) < (unsigned int) SET_RATIO)


#ifndef __mips16
/* Since the bits of the _init and _fini function is spread across
   many object files, each potentially with its own GP, we must assume
   we need to load our GP.  We don't preserve $gp or $ra, since each
   init/fini chunk is supposed to initialize $gp, and crti/crtn
   already take care of preserving $ra and, when appropriate, $gp.  */
#if (defined _ABIO32 && _MIPS_SIM == _ABIO32)
#define CRT_CALL_STATIC_FUNCTION(SECTION_OP, FUNC)	\
   asm (SECTION_OP "\n\
	.set noreorder\n\
	bal 1f\n\
	nop\n\
1:	.cpload $31\n\
	.set reorder\n\
	jal " USER_LABEL_PREFIX #FUNC "\n\
	" TEXT_SECTION_ASM_OP);
#endif /* Switch to #elif when we're no longer limited by K&R C.  */
#if (defined _ABIN32 && _MIPS_SIM == _ABIN32) \
   || (defined _ABI64 && _MIPS_SIM == _ABI64)
#define CRT_CALL_STATIC_FUNCTION(SECTION_OP, FUNC)	\
   asm (SECTION_OP "\n\
	.set noreorder\n\
	bal 1f\n\
	nop\n\
1:	.set reorder\n\
	.cpsetup $31, $2, 1b\n\
	jal " USER_LABEL_PREFIX #FUNC "\n\
	" TEXT_SECTION_ASM_OP);
#endif
#endif

/* The MIPS32 clz instruction defined to return 32 and MIPS64 dclz 64.  */
#define CLZ_DEFINED_VALUE_AT_ZERO(MODE, VALUE) \
  (VALUE = ((MODE) == DImode ? 64 : 32))

/* The synthesised MIPS32 ctz instruction will return these daft values. */
#define CTZ_DEFINED_VALUE_AT_ZERO(MODE, VALUE) \
  (VALUE = ((MODE) == DImode ? (64 ^ 63) : (32 ^ 31)))

/* Optimization specific conditions */

/* Disables constant folding of expression (A & C) != 0 where C is a
   single bit (power of 2), which gets converted into ((A >> C2) & 1),
   Where C2 = log2(C).  */
#define DISABLE_POWER2_BIT_MASK_TEST 1

#define AGGRESSIVE_COMBINE_GIVS 1

#if 0
/* Return nonzero if MODE implies a floating point inequality can be
   reversed.  */

#define REVERSIBLE_CC_MODE(MODE) 1

/* A C expression whose value is reversed condition code of the CODE for
   comparison done in CC_MODE mode.  MIPS supports unordered comparisons,
   so this is safe. */

#define REVERSE_CONDITION(CODE, MODE) \
  reverse_condition_maybe_unordered (CODE)
#endif

/* Set if this symbol is a "longcall" function.  */
#define SYMBOL_FLAG_LONGCALL	(SYMBOL_FLAG_MACH_DEP << 0)
#define SYMBOL_REF_LONGCALL_P(RTX) \
  ((SYMBOL_REF_FLAGS (RTX) & SYMBOL_FLAG_LONGCALL) != 0)

/* Is this symbol is a "mips16" function.  */
#define SYMBOL_FLAG_MIPS16	(SYMBOL_FLAG_MACH_DEP << 1)
#define SYMBOL_REF_MIPS16_P(RTX) \
  ((SYMBOL_REF_FLAGS (RTX) & SYMBOL_FLAG_MIPS16) != 0)
