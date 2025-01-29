/* Provide Declarations */
#include <stdarg.h>
#include <setjmp.h>
#include <limits.h>
#ifdef NEED_CBEAPINT
#include <autopilot_cbe.h>
#else
#define aesl_fopen fopen
#define aesl_freopen freopen
#define aesl_tmpfile tmpfile
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef __STRICT_ANSI__
#define inline __inline__
#define typeof __typeof__ 
#endif
#define __isoc99_fscanf fscanf
#define __isoc99_sscanf sscanf
#undef ferror
#undef feof
/* get a declaration for alloca */
#if defined(__CYGWIN__) || defined(__MINGW32__)
#define  alloca(x) __builtin_alloca((x))
#define _alloca(x) __builtin_alloca((x))
#elif defined(__APPLE__)
extern void *__builtin_alloca(unsigned long);
#define alloca(x) __builtin_alloca(x)
#define longjmp _longjmp
#define setjmp _setjmp
#elif defined(__sun__)
#if defined(__sparcv9)
extern void *__builtin_alloca(unsigned long);
#else
extern void *__builtin_alloca(unsigned int);
#endif
#define alloca(x) __builtin_alloca(x)
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__arm__)
#define alloca(x) __builtin_alloca(x)
#elif defined(_MSC_VER)
#define inline _inline
#define alloca(x) _alloca(x)
#else
#include <alloca.h>
#endif

#ifndef __GNUC__  /* Can only support "linkonce" vars with GCC */
#define __attribute__(X)
#endif

#if defined(__GNUC__) && defined(__APPLE_CC__)
#define __EXTERNAL_WEAK__ __attribute__((weak_import))
#elif defined(__GNUC__)
#define __EXTERNAL_WEAK__ __attribute__((weak))
#else
#define __EXTERNAL_WEAK__
#endif

#if defined(__GNUC__) && (defined(__APPLE_CC__) || defined(__CYGWIN__) || defined(__MINGW32__))
#define __ATTRIBUTE_WEAK__
#elif defined(__GNUC__)
#define __ATTRIBUTE_WEAK__ __attribute__((weak))
#else
#define __ATTRIBUTE_WEAK__
#endif

#if defined(__GNUC__)
#define __HIDDEN__ __attribute__((visibility("hidden")))
#endif

#ifdef __GNUC__
#define LLVM_NAN(NanStr)   __builtin_nan(NanStr)   /* Double */
#define LLVM_NANF(NanStr)  __builtin_nanf(NanStr)  /* Float */
#define LLVM_NANS(NanStr)  __builtin_nans(NanStr)  /* Double */
#define LLVM_NANSF(NanStr) __builtin_nansf(NanStr) /* Float */
#define LLVM_INF           __builtin_inf()         /* Double */
#define LLVM_INFF          __builtin_inff()        /* Float */
#define LLVM_PREFETCH(addr,rw,locality) __builtin_prefetch(addr,rw,locality)
#define __ATTRIBUTE_CTOR__ __attribute__((constructor))
#define __ATTRIBUTE_DTOR__ __attribute__((destructor))
#define LLVM_ASM           __asm__
#else
#define LLVM_NAN(NanStr)   ((double)0.0)           /* Double */
#define LLVM_NANF(NanStr)  0.0F                    /* Float */
#define LLVM_NANS(NanStr)  ((double)0.0)           /* Double */
#define LLVM_NANSF(NanStr) 0.0F                    /* Float */
#define LLVM_INF           ((double)0.0)           /* Double */
#define LLVM_INFF          0.0F                    /* Float */
#define LLVM_PREFETCH(addr,rw,locality)            /* PREFETCH */
#define __ATTRIBUTE_CTOR__
#define __ATTRIBUTE_DTOR__
#define LLVM_ASM(X)
#endif

#if __GNUC__ < 4 /* Old GCC's, or compilers not GCC */ 
#define __builtin_stack_save() 0   /* not implemented */
#define __builtin_stack_restore(X) /* noop */
#endif

#if __GNUC__ && __LP64__ /* 128-bit integer types */
typedef int __attribute__((mode(TI))) llvmInt128;
typedef unsigned __attribute__((mode(TI))) llvmUInt128;
#endif

#define CODE_FOR_MAIN() /* Any target-specific code for main()*/

#ifndef __cplusplus
typedef unsigned char bool;
#endif


/* Support for floating point constants */
typedef unsigned long long ConstantDoubleTy;
typedef unsigned int        ConstantFloatTy;
typedef struct { unsigned long long f1; unsigned short f2; unsigned short pad[3]; } ConstantFP80Ty;
typedef struct { unsigned long long f1; unsigned long long f2; } ConstantFP128Ty;


/* Global Declarations */
/* Helper union for bitcasts */
typedef union {
  unsigned int Int32;
  unsigned long long Int64;
  float Float;
  double Double;
} llvmBitCastUnion;

/* External Global Variable Declarations */

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
void error_and_exit( char *llvm_cbe_str);
void print_block( char (*llvm_cbe_b)[8]);
void print_dct(signed short (*llvm_cbe_b)[8]);
void print_bitstream(signed int llvm_cbe_num_bytes,  char *llvm_cbe_bitstream);


/* Global Variable Definitions and Initialization */
static  char aesl_internal__OC_str[11] = "Error: %s\n";
static  char aesl_internal__OC_str3[4] = "%d\n";
static  char aesl_internal__OC_str2[4] = "%u\n";
static  char aesl_internal__OC_str1[4] = "%d,";
static  char aesl_internal__OC_str4[3] = "%u";


/* Function Bodies */
static inline int llvm_fcmp_ord(double X, double Y) { return X == X && Y == Y; }
static inline int llvm_fcmp_uno(double X, double Y) { return X != X || Y != Y; }
static inline int llvm_fcmp_ueq(double X, double Y) { return X == Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_une(double X, double Y) { return X != Y; }
static inline int llvm_fcmp_ult(double X, double Y) { return X <  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ugt(double X, double Y) { return X >  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ule(double X, double Y) { return X <= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_uge(double X, double Y) { return X >= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_oeq(double X, double Y) { return X == Y ; }
static inline int llvm_fcmp_one(double X, double Y) { return X != Y && llvm_fcmp_ord(X, Y); }
static inline int llvm_fcmp_olt(double X, double Y) { return X <  Y ; }
static inline int llvm_fcmp_ogt(double X, double Y) { return X >  Y ; }
static inline int llvm_fcmp_ole(double X, double Y) { return X <= Y ; }
static inline int llvm_fcmp_oge(double X, double Y) { return X >= Y ; }

void error_and_exit( char *llvm_cbe_str) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  unsigned int llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @error_and_exit\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([11 x i8]* @aesl_internal_.str, i64 0, i64 0), i8* %%str) nounwind, !dbg !6 for 0x%I64xth hint within @error_and_exit  --> \n", ++aesl_llvm_cbe_3_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 11
#endif
])), ( char *)llvm_cbe_str);
if (AESL_DEBUG_TRACE) {
printf("\nReturn  = 0x%X",llvm_cbe_tmp__1);
}
if (AESL_DEBUG_TRACE)
printf("\n  tail call void @exit(i32 -1) noreturn nounwind, !dbg !6 for 0x%I64xth hint within @error_and_exit  --> \n", ++aesl_llvm_cbe_4_count);
   /*tail*/ exit(4294967295u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",4294967295u);
}
  /*UNREACHABLE*/;
}


void print_block( char (*llvm_cbe_b)[8]) {
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_count = 0;
  unsigned int llvm_cbe_storemerge3;
  unsigned int llvm_cbe_storemerge3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  unsigned long long llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge12_count = 0;
  unsigned int llvm_cbe_storemerge12;
  unsigned int llvm_cbe_storemerge12__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
   char *llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  unsigned char llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  unsigned int llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  unsigned int llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  unsigned long long llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
   char *llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  unsigned char llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  unsigned int llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  unsigned int llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  unsigned int llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  unsigned int llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond4_count = 0;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @print_block\n");
  llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader;

  do {     /* Syntactic loop '.preheader' to make GCC happy */
llvm_cbe__2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3 = phi i32 [ 0, %%0 ], [ %%16, %%15  for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_storemerge3_count);
  llvm_cbe_storemerge3 = (unsigned int )llvm_cbe_storemerge3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3 = 0x%X",llvm_cbe_storemerge3);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__13);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = sext i32 %%storemerge3 to i64, !dbg !6 for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_20_count);
  llvm_cbe_tmp__2 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__2);
  llvm_cbe_storemerge12__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__14;

llvm_cbe_tmp__15:
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = add nsw i32 %%storemerge3, 1, !dbg !7 for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_36_count);
  llvm_cbe_tmp__13 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__13&4294967295ull)));
  if (((llvm_cbe_tmp__13&4294967295U) == (8u&4294967295U))) {
    goto llvm_cbe_tmp__16;
  } else {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__13;   /* for PHI node */
    goto llvm_cbe__2e_preheader;
  }

llvm_cbe__2e_thread:
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds [8 x i8]* %%b, i64 %%1, i64 7, !dbg !6 for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_24_count);
  llvm_cbe_tmp__3 = ( char *)(&llvm_cbe_b[(((signed long long )llvm_cbe_tmp__2))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )7ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__2));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )7ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'b' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load i8* %%4, align 1, !dbg !6 for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_25_count);
  llvm_cbe_tmp__4 = (unsigned char )*llvm_cbe_tmp__3;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = zext i8 %%5 to i32, !dbg !6 for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_26_count);
  llvm_cbe_tmp__5 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__4&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @aesl_internal_.str2, i64 0, i64 0), i32 %%6) nounwind, !dbg !6 for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_27_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str2[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 4
#endif
])), llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__5);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__6);
}
  goto llvm_cbe_tmp__15;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__14:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge12 = phi i32 [ 0, %%.preheader ], [ %%14, %%8  for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_storemerge12_count);
  llvm_cbe_storemerge12 = (unsigned int )llvm_cbe_storemerge12__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge12 = 0x%X",llvm_cbe_storemerge12);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__12);
}
  if (((llvm_cbe_storemerge12&4294967295U) == (7u&4294967295U))) {
    goto llvm_cbe__2e_thread;
  } else {
    goto llvm_cbe_tmp__17;
  }

llvm_cbe_tmp__17:
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = sext i32 %%storemerge12 to i64, !dbg !6 for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__7 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge12);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__7);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds [8 x i8]* %%b, i64 %%1, i64 %%9, !dbg !6 for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_30_count);
  llvm_cbe_tmp__8 = ( char *)(&llvm_cbe_b[(((signed long long )llvm_cbe_tmp__2))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__7))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__2));
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__7));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__7) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'b' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load i8* %%10, align 1, !dbg !6 for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_31_count);
  llvm_cbe_tmp__9 = (unsigned char )*llvm_cbe_tmp__8;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = zext i8 %%11 to i32, !dbg !6 for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_32_count);
  llvm_cbe_tmp__10 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__9&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__10);
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @aesl_internal_.str1, i64 0, i64 0), i32 %%12) nounwind, !dbg !6 for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_33_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str1[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 4
#endif
])), llvm_cbe_tmp__10);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__10);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__11);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = add nsw i32 %%storemerge12, 1, !dbg !7 for 0x%I64xth hint within @print_block  --> \n", ++aesl_llvm_cbe_34_count);
  llvm_cbe_tmp__12 = (unsigned int )((unsigned int )(llvm_cbe_storemerge12&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__12&4294967295ull)));
  if (((llvm_cbe_tmp__12&4294967295U) == (8u&4294967295U))) {
    goto llvm_cbe_tmp__15;
  } else {
    llvm_cbe_storemerge12__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__12;   /* for PHI node */
    goto llvm_cbe_tmp__14;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.preheader' */
llvm_cbe_tmp__16:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @print_block}\n");
  return;
}


void print_dct(signed short (*llvm_cbe_b)[8]) {
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_count = 0;
  unsigned int llvm_cbe_storemerge3;
  unsigned int llvm_cbe_storemerge3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  unsigned long long llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge12_count = 0;
  unsigned int llvm_cbe_storemerge12;
  unsigned int llvm_cbe_storemerge12__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  signed short *llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  unsigned short llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  unsigned int llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  unsigned int llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  unsigned long long llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  signed short *llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  unsigned short llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  unsigned int llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  unsigned int llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  unsigned int llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  unsigned int llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond4_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @print_dct\n");
  llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader;

  do {     /* Syntactic loop '.preheader' to make GCC happy */
llvm_cbe__2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3 = phi i32 [ 0, %%0 ], [ %%16, %%15  for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_storemerge3_count);
  llvm_cbe_storemerge3 = (unsigned int )llvm_cbe_storemerge3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3 = 0x%X",llvm_cbe_storemerge3);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__29);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = sext i32 %%storemerge3 to i64, !dbg !6 for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_58_count);
  llvm_cbe_tmp__18 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__18);
  llvm_cbe_storemerge12__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__30;

llvm_cbe_tmp__31:
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = add nsw i32 %%storemerge3, 1, !dbg !7 for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_74_count);
  llvm_cbe_tmp__29 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__29&4294967295ull)));
  if (((llvm_cbe_tmp__29&4294967295U) == (8u&4294967295U))) {
    goto llvm_cbe_tmp__32;
  } else {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__29;   /* for PHI node */
    goto llvm_cbe__2e_preheader;
  }

llvm_cbe__2e_thread:
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds [8 x i16]* %%b, i64 %%1, i64 7, !dbg !6 for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_62_count);
  llvm_cbe_tmp__19 = (signed short *)(&llvm_cbe_b[(((signed long long )llvm_cbe_tmp__18))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )7ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__18));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )7ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'b' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load i16* %%4, align 2, !dbg !6 for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_63_count);
  llvm_cbe_tmp__20 = (unsigned short )*llvm_cbe_tmp__19;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = sext i16 %%5 to i32, !dbg !6 for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_64_count);
  llvm_cbe_tmp__21 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__21);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @aesl_internal_.str3, i64 0, i64 0), i32 %%6) nounwind, !dbg !6 for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_65_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str3[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 4
#endif
])), llvm_cbe_tmp__21);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__21);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__22);
}
  goto llvm_cbe_tmp__31;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__30:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge12 = phi i32 [ 0, %%.preheader ], [ %%14, %%8  for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_storemerge12_count);
  llvm_cbe_storemerge12 = (unsigned int )llvm_cbe_storemerge12__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge12 = 0x%X",llvm_cbe_storemerge12);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__28);
}
  if (((llvm_cbe_storemerge12&4294967295U) == (7u&4294967295U))) {
    goto llvm_cbe__2e_thread;
  } else {
    goto llvm_cbe_tmp__33;
  }

llvm_cbe_tmp__33:
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = sext i32 %%storemerge12 to i64, !dbg !6 for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_67_count);
  llvm_cbe_tmp__23 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge12);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__23);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds [8 x i16]* %%b, i64 %%1, i64 %%9, !dbg !6 for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_68_count);
  llvm_cbe_tmp__24 = (signed short *)(&llvm_cbe_b[(((signed long long )llvm_cbe_tmp__18))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__23))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__18));
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__23));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__23) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'b' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load i16* %%10, align 2, !dbg !6 for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_69_count);
  llvm_cbe_tmp__25 = (unsigned short )*llvm_cbe_tmp__24;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__25);
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = sext i16 %%11 to i32, !dbg !6 for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_70_count);
  llvm_cbe_tmp__26 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__25);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__26);
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @aesl_internal_.str1, i64 0, i64 0), i32 %%12) nounwind, !dbg !6 for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_71_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str1[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 4
#endif
])), llvm_cbe_tmp__26);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__26);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__27);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = add nsw i32 %%storemerge12, 1, !dbg !7 for 0x%I64xth hint within @print_dct  --> \n", ++aesl_llvm_cbe_72_count);
  llvm_cbe_tmp__28 = (unsigned int )((unsigned int )(llvm_cbe_storemerge12&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__28&4294967295ull)));
  if (((llvm_cbe_tmp__28&4294967295U) == (8u&4294967295U))) {
    goto llvm_cbe_tmp__31;
  } else {
    llvm_cbe_storemerge12__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__28;   /* for PHI node */
    goto llvm_cbe_tmp__30;
  }

  } while (1); /* end of syntactic loop '' */
  } while (1); /* end of syntactic loop '.preheader' */
llvm_cbe_tmp__32:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @print_dct}\n");
  return;
}


void print_bitstream(signed int llvm_cbe_num_bytes,  char *llvm_cbe_bitstream) {
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_count = 0;
  unsigned int llvm_cbe_storemerge3;
  unsigned int llvm_cbe_storemerge3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  unsigned long long llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
   char *llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  unsigned char llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  unsigned int llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  unsigned int llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  unsigned int llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  unsigned char llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  unsigned char llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  unsigned int llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  unsigned int llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  unsigned int llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  unsigned char llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  unsigned char llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  unsigned int llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  unsigned int llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  unsigned int llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  unsigned char llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  unsigned char llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  unsigned int llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  unsigned int llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  unsigned int llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  unsigned char llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  unsigned char llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  unsigned int llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  unsigned int llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  unsigned int llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  unsigned char llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  unsigned char llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  unsigned int llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  unsigned int llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  unsigned int llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  unsigned char llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  unsigned char llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  unsigned int llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  unsigned int llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  unsigned int llvm_cbe_tmp__69;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  unsigned char llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  unsigned char llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  unsigned int llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  unsigned int llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  unsigned int llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  unsigned int llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_putchar_count = 0;
  unsigned int llvm_cbe_putchar;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @print_bitstream\n");
  if ((((signed int )llvm_cbe_num_bytes) > ((signed int )0u))) {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
    goto llvm_cbe__2e_preheader;
  } else {
    goto llvm_cbe__2e__crit_edge;
  }

  do {     /* Syntactic loop '.preheader' to make GCC happy */
llvm_cbe__2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3 = phi i32 [ %%43, %%.preheader ], [ 0, %%0  for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_storemerge3_count);
  llvm_cbe_storemerge3 = (unsigned int )llvm_cbe_storemerge3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3 = 0x%X",llvm_cbe_storemerge3);
printf("\n = 0x%X",llvm_cbe_tmp__75);
printf("\n = 0x%X",0u);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = sext i32 %%storemerge3 to i64, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_95_count);
  llvm_cbe_tmp__34 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds i8* %%bitstream, i64 %%2, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_96_count);
  llvm_cbe_tmp__35 = ( char *)(&llvm_cbe_bitstream[(((signed long long )llvm_cbe_tmp__34))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__34));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load i8* %%3, align 1, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_97_count);
  llvm_cbe_tmp__36 = (unsigned char )*llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = zext i8 %%4 to i32, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_98_count);
  llvm_cbe_tmp__37 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__36&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__37);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = lshr i32 %%5, 7, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_99_count);
  llvm_cbe_tmp__38 = (unsigned int )((unsigned int )(((unsigned int )(llvm_cbe_tmp__37&4294967295ull)) >> ((unsigned int )(7u&4294967295ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__38&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str4, i64 0, i64 0), i32 %%6) nounwind, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_100_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])), llvm_cbe_tmp__38);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__38);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__39);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load i8* %%3, align 1, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_105_count);
  llvm_cbe_tmp__40 = (unsigned char )*llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__40);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = shl i8 %%8, 1, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_106_count);
  llvm_cbe_tmp__41 = (unsigned char )((unsigned char )(llvm_cbe_tmp__40 << ((unsigned char )1)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__41);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = zext i8 %%9 to i32, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_107_count);
  llvm_cbe_tmp__42 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__41&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__42);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = lshr i32 %%10, 7, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__43 = (unsigned int )((unsigned int )(((unsigned int )(llvm_cbe_tmp__42&4294967295ull)) >> ((unsigned int )(7u&4294967295ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__43&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str4, i64 0, i64 0), i32 %%11) nounwind, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_109_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])), llvm_cbe_tmp__43);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__43);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__44);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = load i8* %%3, align 1, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_114_count);
  llvm_cbe_tmp__45 = (unsigned char )*llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__45);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = shl i8 %%13, 2, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_115_count);
  llvm_cbe_tmp__46 = (unsigned char )((unsigned char )(llvm_cbe_tmp__45 << ((unsigned char )2)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = zext i8 %%14 to i32, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_116_count);
  llvm_cbe_tmp__47 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__46&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = lshr i32 %%15, 7, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_117_count);
  llvm_cbe_tmp__48 = (unsigned int )((unsigned int )(((unsigned int )(llvm_cbe_tmp__47&4294967295ull)) >> ((unsigned int )(7u&4294967295ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__48&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str4, i64 0, i64 0), i32 %%16) nounwind, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_118_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])), llvm_cbe_tmp__48);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__48);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__49);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = load i8* %%3, align 1, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_123_count);
  llvm_cbe_tmp__50 = (unsigned char )*llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__50);
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = shl i8 %%18, 3, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_124_count);
  llvm_cbe_tmp__51 = (unsigned char )((unsigned char )(llvm_cbe_tmp__50 << ((unsigned char )3)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = zext i8 %%19 to i32, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_125_count);
  llvm_cbe_tmp__52 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__51&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__52);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = lshr i32 %%20, 7, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_126_count);
  llvm_cbe_tmp__53 = (unsigned int )((unsigned int )(((unsigned int )(llvm_cbe_tmp__52&4294967295ull)) >> ((unsigned int )(7u&4294967295ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__53&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str4, i64 0, i64 0), i32 %%21) nounwind, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_127_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])), llvm_cbe_tmp__53);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__53);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__54);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = load i8* %%3, align 1, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__55 = (unsigned char )*llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__55);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = shl i8 %%23, 4, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__56 = (unsigned char )((unsigned char )(llvm_cbe_tmp__55 << ((unsigned char )4)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__56);
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = zext i8 %%24 to i32, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_134_count);
  llvm_cbe_tmp__57 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__56&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__57);
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = lshr i32 %%25, 7, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_135_count);
  llvm_cbe_tmp__58 = (unsigned int )((unsigned int )(((unsigned int )(llvm_cbe_tmp__57&4294967295ull)) >> ((unsigned int )(7u&4294967295ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__58&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str4, i64 0, i64 0), i32 %%26) nounwind, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_136_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])), llvm_cbe_tmp__58);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__58);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__59);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = load i8* %%3, align 1, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_141_count);
  llvm_cbe_tmp__60 = (unsigned char )*llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__60);
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = shl i8 %%28, 5, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_142_count);
  llvm_cbe_tmp__61 = (unsigned char )((unsigned char )(llvm_cbe_tmp__60 << ((unsigned char )5)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__61);
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = zext i8 %%29 to i32, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_143_count);
  llvm_cbe_tmp__62 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__61&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = lshr i32 %%30, 7, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_144_count);
  llvm_cbe_tmp__63 = (unsigned int )((unsigned int )(((unsigned int )(llvm_cbe_tmp__62&4294967295ull)) >> ((unsigned int )(7u&4294967295ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__63&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str4, i64 0, i64 0), i32 %%31) nounwind, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_145_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])), llvm_cbe_tmp__63);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__63);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__64);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = load i8* %%3, align 1, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__65 = (unsigned char )*llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__65);
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = shl i8 %%33, 6, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_151_count);
  llvm_cbe_tmp__66 = (unsigned char )((unsigned char )(llvm_cbe_tmp__65 << ((unsigned char )6)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__66);
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = zext i8 %%34 to i32, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_152_count);
  llvm_cbe_tmp__67 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__66&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__67);
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = lshr i32 %%35, 7, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_153_count);
  llvm_cbe_tmp__68 = (unsigned int )((unsigned int )(((unsigned int )(llvm_cbe_tmp__67&4294967295ull)) >> ((unsigned int )(7u&4294967295ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__68&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str4, i64 0, i64 0), i32 %%36) nounwind, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_154_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])), llvm_cbe_tmp__68);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__68);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__69);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = load i8* %%3, align 1, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_159_count);
  llvm_cbe_tmp__70 = (unsigned char )*llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__70);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = shl i8 %%38, 7, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_160_count);
  llvm_cbe_tmp__71 = (unsigned char )((unsigned char )(llvm_cbe_tmp__70 << ((unsigned char )7)));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__71);
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = zext i8 %%39 to i32, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_161_count);
  llvm_cbe_tmp__72 = (unsigned int )((unsigned int )(unsigned char )llvm_cbe_tmp__71&255U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__72);
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = lshr exact i32 %%40, 7, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_162_count);
  llvm_cbe_tmp__73 = (unsigned int )((unsigned int )(((unsigned int )(llvm_cbe_tmp__72&4294967295ull)) >> ((unsigned int )(7u&4294967295ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__73&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @aesl_internal_.str4, i64 0, i64 0), i32 %%41) nounwind, !dbg !6 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_163_count);
   /*tail*/ printf(( char *)((&aesl_internal__OC_str4[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 3
#endif
])), llvm_cbe_tmp__73);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",llvm_cbe_tmp__73);
printf("\nReturn  = 0x%X",llvm_cbe_tmp__74);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = add nsw i32 %%storemerge3, 1, !dbg !7 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_168_count);
  llvm_cbe_tmp__75 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__75&4294967295ull)));
  if (((llvm_cbe_tmp__75&4294967295U) == (llvm_cbe_num_bytes&4294967295U))) {
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__75;   /* for PHI node */
    goto llvm_cbe__2e_preheader;
  }

  } while (1); /* end of syntactic loop '.preheader' */
llvm_cbe__2e__crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%putchar = tail call i32 @putchar(i32 10) nounwind, !dbg !7 for 0x%I64xth hint within @print_bitstream  --> \n", ++aesl_llvm_cbe_putchar_count);
   /*tail*/ putchar(10u);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = 0x%X",10u);
printf("\nReturn putchar = 0x%X",llvm_cbe_putchar);
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @print_bitstream}\n");
  return;
}

