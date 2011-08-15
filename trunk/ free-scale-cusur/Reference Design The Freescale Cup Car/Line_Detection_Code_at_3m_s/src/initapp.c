/*============================================================================*/
/*                             Smart Car Race                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* %name:            %	initapp.c
* %version:         %	1.0
* %created_by:      %   Mr. Template
* %date_created:    %
*=============================================================================*/
/* DESCRIPTION : Ports handling                                               */
/*============================================================================*/
/* FUNCTION COMMENT : Provices APIs to configure and use cpu of PIC micro     */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/YYYY  |                               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "stdtypedef.h"
#include "mw_delay.h"
#include "app_ports.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 


/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */

/* Private functions prototypes */
/* ---------------------------- */

/* Exported functions prototypes */
/* ----------------------------- */
void initapp_init1(void);
void initapp_init2(void);

/**************************************************************
*  Name                 : initapp_1
*  Description          : 
*  Parameters           :  none
*  Return               :  none
*  Critical/explanation :  No
**************************************************************/
void initapp_init1(void)
{
	app_ports_init(PE4);
	app_ports_init(PE5);
	app_ports_init(PE6);
}


/**************************************************************
*  Name                 : initapp_2
*  Description          : 
*  Parameters           :  none
*  Return               :  none
*  Critical/explanation :  No
**************************************************************/
void initapp_init2(void)
{
	
}