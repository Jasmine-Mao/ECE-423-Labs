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
extern signed short Yquant[8][8];
extern signed short Cquant[8][8];
extern signed int zigzag_table[64];

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);


/* Global Variable Definitions and Initialization */
signed short Yquant[8][8] = { { ((unsigned short )16), ((unsigned short )11), ((unsigned short )10), ((unsigned short )16), ((unsigned short )24), ((unsigned short )40), ((unsigned short )51), ((unsigned short )61) }, { ((unsigned short )12), ((unsigned short )12), ((unsigned short )14), ((unsigned short )19), ((unsigned short )26), ((unsigned short )58), ((unsigned short )60), ((unsigned short )55) }, { ((unsigned short )14), ((unsigned short )13), ((unsigned short )16), ((unsigned short )24), ((unsigned short )40), ((unsigned short )57), ((unsigned short )69), ((unsigned short )56) }, { ((unsigned short )14), ((unsigned short )17), ((unsigned short )22), ((unsigned short )29), ((unsigned short )51), ((unsigned short )87), ((unsigned short )80), ((unsigned short )62) }, { ((unsigned short )18), ((unsigned short )22), ((unsigned short )37), ((unsigned short )56), ((unsigned short )68), ((unsigned short )109), ((unsigned short )103), ((unsigned short )77) }, { ((unsigned short )24), ((unsigned short )35), ((unsigned short )55), ((unsigned short )64), ((unsigned short )81), ((unsigned short )104), ((unsigned short )113), ((unsigned short )92) }, { ((unsigned short )49), ((unsigned short )64), ((unsigned short )78), ((unsigned short )87), ((unsigned short )103), ((unsigned short )121), ((unsigned short )120), ((unsigned short )101) }, { ((unsigned short )72), ((unsigned short )92), ((unsigned short )95), ((unsigned short )98), ((unsigned short )112), ((unsigned short )100), ((unsigned short )103), ((unsigned short )99) } };
signed short Cquant[8][8] = { { ((unsigned short )17), ((unsigned short )18), ((unsigned short )24), ((unsigned short )47), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99) }, { ((unsigned short )18), ((unsigned short )21), ((unsigned short )26), ((unsigned short )66), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99) }, { ((unsigned short )24), ((unsigned short )26), ((unsigned short )56), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99) }, { ((unsigned short )47), ((unsigned short )66), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99) }, { ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99) }, { ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99) }, { ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99) }, { ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99), ((unsigned short )99) } };
signed int zigzag_table[64] = { 0u, 1u, 8u, 16u, 9u, 2u, 3u, 10u, 17u, 24u, 32u, 25u, 18u, 11u, 4u, 5u, 12u, 19u, 26u, 33u, 40u, 48u, 41u, 34u, 27u, 20u, 13u, 6u, 7u, 14u, 21u, 28u, 35u, 42u, 49u, 56u, 57u, 50u, 43u, 36u, 29u, 22u, 15u, 23u, 30u, 37u, 44u, 51u, 58u, 59u, 52u, 45u, 38u, 31u, 39u, 46u, 53u, 60u, 61u, 54u, 47u, 55u, 62u, 63u };


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
