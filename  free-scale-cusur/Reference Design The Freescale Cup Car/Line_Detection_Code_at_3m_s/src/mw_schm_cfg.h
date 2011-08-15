#ifndef MW_SCHM_CFG_H
#define MW_SCHM_CFG_H
/******************************************************************************
*
*   Filename:   mw_schm_cfg.h 
*
*   Created_by: 
*       
*   Date_created: 
*
*   Description:  Definitions for Scheduler configuration file
*
*
*******************************************************************************
*   Revision History:
*
*   Date          CQ#           Author    
*   MM-DD-YY      oem00000000   Initials   Description of change.
*   -----------   -----------   --------   ------------------------------------
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/ 
#include "stdtypedef.h"
#include "mw_schm.h"


/******************************************************************************
*   Macro Definitions  
******************************************************************************/
/* Timer Period in ms */
#define TIMER_PERIOD      (T_UWORD)1

/* time execution period */
#define ITBM_schGetModuleTimePeriod(ModuleID) cps_mngTaskList[ModuleID].ExecutionPeriod

/* null constant if not App or Init routine */
#define SCHM_NULL_PTR (T_SCHM_MANAGER_API_TYPE)0
 
/*****************************************************************************
 *  Local Macro Definitions
 *****************************************************************************/

/******************************************************************************
*   Type Definitions
******************************************************************************/
/* Manager/Application ID */

typedef enum {
    TASK_5MS,
    TASK_500MS,
    TASK_1S,
    /* Number of Managers/Applications */
    SCHD_MANAGERS_NUMBER
} E_MODULES_ID_TYPE;

/*Type definition for pointer to main functions of the managers*/
typedef void (*T_SCHM_MANAGER_API_TYPE)(void);

/*Type definition for main functions of the managers and their execution period*/
typedef struct{
    /* the main function */
    T_SCHM_MANAGER_API_TYPE  ManagerAPI; 
    /* the Init function */
    T_SCHM_MANAGER_API_TYPE  ManagerInitAPI; 
    /* delay of submodule execution from Scheduler start in ms */
    const T_TaskDelayType StartUpDelay;
    /* module is executed each 'ExecutionPeriod' time in ms */
    const T_TaskDelayType ExecutionPeriod;

    T_OpModeType UsedInMode; 
     
} S_SCHM_MANAGER_EXEC_TYPE; 

/******************************************************************************
*   External Variables
******************************************************************************/
/* Managers/Application main function List */
extern const S_SCHM_MANAGER_EXEC_TYPE cps_mngTaskList[SCHD_MANAGERS_NUMBER]; 

/******************************************************************************
*   Global Function Prototypes  
******************************************************************************/

#endif /* MW_SCHM_CFG_H */
