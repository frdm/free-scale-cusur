/*============================================================================*/
/*                   CONTINENTAL AUTOMOTIVE SYSTEMS                           */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            stdtypedef.h
* version:         1.0
* created_by:      Continental
* date_created:    May 17 2010
*=============================================================================*/
/* DESCRIPTION : Header file for basic Types definitions                      */
/*============================================================================*/
/* FUNCTION COMMENT : Defines basic data types to be used by project.         */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/may/2010 |                               | Continental      */
/* Initial version for the Smart Car Race 2010 contest using Freescale        */
/* Bolero micro.                                                              */
/*============================================================================*/
#ifndef STDTYPEDEF_H                               /* To avoid double inclusion */
#define STDTYPEDEF_H

/* Register definitions for selected microcontroller */
#include "MPC5604B_M27V.h"


/* Basic Scalar types */

typedef unsigned char     T_UBYTE;
typedef unsigned int      T_UWORD;
typedef unsigned long     T_ULONG;
typedef signed char       T_SBYTE;
typedef signed int        T_SWORD;
typedef signed long       T_SLONG;
typedef unsigned int      T_FLAG_ARRAY;

/* table of entry pochars */
typedef void(*T_PPROC)(void);

/* basic type pointers */
typedef T_UBYTE * PTR_UBYTE ;
typedef T_UWORD * PTR_UWORD;
typedef T_ULONG * PTR_ULONG;
typedef T_SBYTE * PTR_SBYTE ;
typedef T_SWORD * PTR_SWORD;
typedef T_SLONG * PTR_SLONG;


/* Carrier of 8 bits */
#pragma pack(1)
typedef struct {
	unsigned int	bit0:1;
	unsigned int	bit1:1;
	unsigned int	bit2:1;
	unsigned int	bit3:1;
	unsigned int	bit4:1;
	unsigned int	bit5:1;
	unsigned int	bit6:1;
	unsigned int	bit7:1;
}T_BITFLD8;
#pragma pack()


/* Carrier of 16 bits */
#pragma pack(2)
typedef struct {
	unsigned int	bit0:1;
	unsigned int	bit1:1;
	unsigned int	bit2:1;
	unsigned int	bit3:1;
	unsigned int	bit4:1;
	unsigned int	bit5:1;
	unsigned int	bit6:1;
	unsigned int	bit7:1;
	unsigned int	bit8:1;
	unsigned int	bit9:1;
	unsigned int	bit10:1;
	unsigned int	bit11:1;
	unsigned int	bit12:1;
	unsigned int	bit13:1;
	unsigned int	bit14:1;
	unsigned int	bit15:1;
}T_BITFLD16;
#pragma pack()


/* Carrier of 32 bits */
typedef struct {
	unsigned int	bit0:1;
	unsigned int	bit1:1;
	unsigned int	bit2:1;
	unsigned int	bit3:1;
	unsigned int	bit4:1;
	unsigned int	bit5:1;
	unsigned int	bit6:1;
	unsigned int	bit7:1;
	unsigned int	bit8:1;
	unsigned int	bit9:1;
	unsigned int	bit10:1;
	unsigned int	bit11:1;
	unsigned int	bit12:1;
	unsigned int	bit13:1;
	unsigned int	bit14:1;
	unsigned int	bit15:1;
	unsigned int	bit16:1;
	unsigned int	bit17:1;
	unsigned int	bit18:1;
	unsigned int	bit19:1;
	unsigned int	bit20:1;
	unsigned int	bit21:1;
	unsigned int	bit22:1;
	unsigned int	bit23:1;
	unsigned int	bit24:1;
	unsigned int	bit25:1;
	unsigned int	bit26:1;
	unsigned int	bit27:1;
	unsigned int	bit28:1;
	unsigned int	bit29:1;
	unsigned int	bit30:1;
	unsigned int	bit31:1;
}T_BITFLD32;


/* Word with msb and lsb handling */
typedef union{
	T_UWORD	wo;
	struct{
		T_UBYTE	lsb;
		T_UBYTE	msb;
		}by;
}T_BYTEFLD;


/* Long with word and byte handling */
typedef union{
	T_ULONG lo;
    struct {
             T_UBYTE lowword_lsb;
             T_UBYTE lowword_msb;
             T_UBYTE highword_lsb;
             T_UBYTE highword_msb;
            } by;
        
    struct {
             T_UWORD lowword;
             T_UWORD highword;
           } wo;
               
}T_BYTEFLD32;


/* Carrier of 8 bits with byte handling */
typedef union {
	T_UBYTE by;
	T_BITFLD8	bi;
}T_FLAG8;


/* Carrier of 16 bits with word or byte (msb & lsb) carrier handling */
typedef union {
	T_BYTEFLD cr;
	T_BITFLD16	bi;
}T_FLAG16;


/* Carrier of 32 bits with word or byte (msb & lsb) carrier handling */
typedef union {
	T_BYTEFLD32 cr;
	T_BITFLD32	bi;
}T_FLAG32;

typedef enum
{
	FALSE,
	TRUE	
}bool;	/* States for Wheel State Machine */

/* Macros definition */
#define TRUE 1
#define FALSE 0
#ifndef NULL
#define NULL 0
#endif

/* Compiler customization */
///* Memory macros definition */
//
#define PRIVATE_DATA static              /* static data definition */
//
#define INLINE_FCT inline                /* inline function definition */
//


#endif