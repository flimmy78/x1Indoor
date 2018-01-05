// Microsoft version of 'inline'
#define inline __inline

// Visual Studio support alloca(), but it always align variables to 16-bit
// boundary, while SSE need 128-bit alignment. So we disable alloca() when
// SSE is enabled.
#ifndef _USE_SSE
#  define USE_ALLOCA
#endif
#define FIXED_POINT

//#define ARM5E_ASM
//#define ARM4_ASM

#ifdef FIXED_POINT
#  define USE_KISS_FFT
#endif

/* Default to floating point */
#ifndef FIXED_POINT
#  define FLOATING_POINT
#  define USE_SMALLFT
#endif