/*
 * File: xil_interface.c
 *
 * SIL generated interface for code: "quad_8state_kalman"
 *
 */

#include "xil_interface.h"
#include "quad_8state_kalman.h"
#include "quad_8state_kalman_initialize.h"
#include "quad_8state_kalman_terminate.h"
/* Functions with a C call interface */
#ifdef __cplusplus
extern "C" {
#endif
#include "xil_data_stream.h"
#ifdef __cplusplus
}
#endif

/* interface data */
float a[2];

/* interface data */
float g[3];

/* interface data */
float delta_t;

/* interface data */
float gyro_rp;

/* interface data */
float gyro_y;

/* interface data */
float v_xy;

/* interface data */
float gb_rp;

/* interface data */
float gb_y;

/* interface data */
float acc_xy;

/* interface data */
float k_1;

/* interface data */
float y[8];

static XILIOData xil_fcnid0_task1_u[11];

static XILIOData xil_fcnid0_task1_y[2];

static XILIOData xil_fcnid0_init_y[2];

static XILIOData xil_fcnid0_term_y[2];


/* In-the-Loop Interface functions - see xil_interface.h */

XIL_INTERFACE_ERROR_CODE xilProcessParams(uint32_T xilFcnId) {
    /* Single In-the-Loop Component */
    if (xilFcnId != 0) {
       return XIL_INTERFACE_UNKNOWN_FCNID;
    }
    return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilGetDataTypeInfo(void) {
    {
        /* send response id code */
        MemUnit_T memUnitData = XIL_RESPONSE_TYPE_SIZE;
        if (xilWriteData(&memUnitData, sizeof(memUnitData)) != XIL_DATA_STREAM_SUCCESS) {
            return XIL_INTERFACE_COMMS_FAILURE;
        }
        /* send type id */
        memUnitData = 7;
        if (xilWriteData(&memUnitData, sizeof(memUnitData)) != XIL_DATA_STREAM_SUCCESS) {
            return XIL_INTERFACE_COMMS_FAILURE;
        }
        /* PIL_FLOAT_SIZE should only be already defined for MathWorks testing */
        #ifndef PIL_FLOAT_SIZE
            #define PIL_FLOAT_SIZE sizeof(float)
        #endif
        /* send size in bytes */
        memUnitData = (MemUnit_T) PIL_FLOAT_SIZE;
        #ifndef HOST_WORD_ADDRESSABLE_TESTING
        /* convert MemUnits to bytes */
        memUnitData *= MEM_UNIT_BYTES;
        #endif
        if (xilWriteData(&memUnitData, sizeof(memUnitData)) != XIL_DATA_STREAM_SUCCESS) {
            return XIL_INTERFACE_COMMS_FAILURE;
        }
    }
    return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilInitialize(uint32_T xilFcnId) {
    XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;
    /* initialize output storage owned by In-the-Loop */
    {
        {
            uint32_T elementIdx;
            for (elementIdx=0; elementIdx<8; elementIdx++) {
                y[elementIdx] = 0;
            }
        }
    }
    /* Single In-the-Loop Component */
    if (xilFcnId == 0) {
        quad_8state_kalman_initialize();
    }
    else {
        errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
    }
    return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilInitializeConditions(uint32_T xilFcnId) {
    XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;
    /* Single In-the-Loop Component */
    if (xilFcnId == 0) {
        /* No Initialize Conditions Function to Call */
    }
    else {
        errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
    }
    return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilGetUIOData(uint32_T xilFcnId, XIL_COMMAND_TYPE_ENUM xilCommandType, uint32_T xilCommandIdx, XILIOData ** xilIOData) {
    XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;
    *xilIOData = 0;
    /* Single In-the-Loop Component */
    if (xilFcnId != 0) {
       errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
       return errorCode;
    }
    switch(xilCommandType) {
        case XIL_STEP_COMMAND: {
            static int initComplete = 0;
            if (!initComplete) {
                uint32_T tableIdx = 0;
                {
                    void * dataAddress = (void *) &(a[0]);
                    xil_fcnid0_task1_u[tableIdx].memUnitLength = 2 * sizeof(real32_T);
                    xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                {
                    void * dataAddress = (void *) &(g[0]);
                    xil_fcnid0_task1_u[tableIdx].memUnitLength = 3 * sizeof(real32_T);
                    xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                {
                    void * dataAddress = (void *) &(delta_t);
                    xil_fcnid0_task1_u[tableIdx].memUnitLength = 1 * sizeof(real32_T);
                    xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                {
                    void * dataAddress = (void *) &(gyro_rp);
                    xil_fcnid0_task1_u[tableIdx].memUnitLength = 1 * sizeof(real32_T);
                    xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                {
                    void * dataAddress = (void *) &(gyro_y);
                    xil_fcnid0_task1_u[tableIdx].memUnitLength = 1 * sizeof(real32_T);
                    xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                {
                    void * dataAddress = (void *) &(v_xy);
                    xil_fcnid0_task1_u[tableIdx].memUnitLength = 1 * sizeof(real32_T);
                    xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                {
                    void * dataAddress = (void *) &(gb_rp);
                    xil_fcnid0_task1_u[tableIdx].memUnitLength = 1 * sizeof(real32_T);
                    xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                {
                    void * dataAddress = (void *) &(gb_y);
                    xil_fcnid0_task1_u[tableIdx].memUnitLength = 1 * sizeof(real32_T);
                    xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                {
                    void * dataAddress = (void *) &(acc_xy);
                    xil_fcnid0_task1_u[tableIdx].memUnitLength = 1 * sizeof(real32_T);
                    xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                {
                    void * dataAddress = (void *) &(k_1);
                    xil_fcnid0_task1_u[tableIdx].memUnitLength = 1 * sizeof(real32_T);
                    xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                xil_fcnid0_task1_u[tableIdx].memUnitLength = 0;
                xil_fcnid0_task1_u[tableIdx++].address = (MemUnit_T *) 0;
                initComplete = 1;
            }
            *xilIOData = &xil_fcnid0_task1_u[0];
            break;
        }
        default:
           errorCode = XIL_INTERFACE_UNKNOWN_TID;
           break;
    }
    UNUSED_PARAMETER(xilCommandIdx);
    return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilOutput(uint32_T xilFcnId, uint32_T xilTID) {
    /* Single In-the-Loop Component */
    if (xilFcnId != 0) {
       return XIL_INTERFACE_UNKNOWN_FCNID;
    }
    switch(xilTID) {
        case 1:
            quad_8state_kalman(a, g, delta_t, gyro_rp, gyro_y, v_xy, gb_rp, gb_y, acc_xy, k_1, y);
            break;
        default:
           return XIL_INTERFACE_UNKNOWN_TID;
    }
    return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilUpdate(uint32_T xilFcnId, uint32_T xilTID) {
    /* Single In-the-Loop Component */
    if (xilFcnId != 0) {
       return XIL_INTERFACE_UNKNOWN_FCNID;
    }
    /* No Update Function */
    UNUSED_PARAMETER(xilTID);
    return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilGetYIOData(uint32_T xilFcnId, XIL_COMMAND_TYPE_ENUM xilCommandType, uint32_T xilCommandIdx, XILIOData ** xilIOData) {
    XIL_INTERFACE_ERROR_CODE errorCode = XIL_INTERFACE_SUCCESS;
    /* Single In-the-Loop Component */
    *xilIOData = 0;
    if (xilFcnId != 0) {
       errorCode = XIL_INTERFACE_UNKNOWN_FCNID;
       return errorCode;
    }
    switch(xilCommandType) {
        case XIL_INITIALIZE_COMMAND: {
            static int initComplete = 0;
            if (!initComplete) {
                uint32_T tableIdx = 0;
                {
                    void * dataAddress = (void *) &(y[0]);
                    xil_fcnid0_init_y[tableIdx].memUnitLength = 8 * sizeof(real32_T);
                    xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                xil_fcnid0_init_y[tableIdx].memUnitLength = 0;
                xil_fcnid0_init_y[tableIdx++].address = (MemUnit_T *) 0;
                initComplete = 1;
            }
            *xilIOData = &xil_fcnid0_init_y[0];
            break;
        }
        case XIL_TERMINATE_COMMAND: {
            static int initComplete = 0;
            if (!initComplete) {
                uint32_T tableIdx = 0;
                {
                    void * dataAddress = (void *) &(y[0]);
                    xil_fcnid0_term_y[tableIdx].memUnitLength = 8 * sizeof(real32_T);
                    xil_fcnid0_term_y[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                xil_fcnid0_term_y[tableIdx].memUnitLength = 0;
                xil_fcnid0_term_y[tableIdx++].address = (MemUnit_T *) 0;
                initComplete = 1;
            }
            *xilIOData = &xil_fcnid0_term_y[0];
            break;
        }
        case XIL_STEP_COMMAND: {
            static int initComplete = 0;
            if (!initComplete) {
                uint32_T tableIdx = 0;
                {
                    void * dataAddress = (void *) &(y[0]);
                    xil_fcnid0_task1_y[tableIdx].memUnitLength = 8 * sizeof(real32_T);
                    xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) dataAddress;
                }
                xil_fcnid0_task1_y[tableIdx].memUnitLength = 0;
                xil_fcnid0_task1_y[tableIdx++].address = (MemUnit_T *) 0;
                initComplete = 1;
            }
            *xilIOData = &xil_fcnid0_task1_y[0];
            break;
        }
        default:
           errorCode = XIL_INTERFACE_UNKNOWN_TID;
           break;
    }
    UNUSED_PARAMETER(xilCommandIdx);
    return errorCode;
}

XIL_INTERFACE_ERROR_CODE xilTerminate(uint32_T xilFcnId) {
   /* Single In-the-Loop Component */
   if (xilFcnId != 0) {
      return XIL_INTERFACE_UNKNOWN_FCNID;
   }
   quad_8state_kalman_terminate();

   return XIL_INTERFACE_SUCCESS;
}

XIL_INTERFACE_ERROR_CODE xilEnable(uint32_T xilFcnId, uint32_T xilTID) {
    /* Single In-the-Loop Component */
    if (xilFcnId != 0) {
       return XIL_INTERFACE_UNKNOWN_FCNID;
    }
    UNUSED_PARAMETER(xilTID);
    /* No Enable Function - this function should never be called */
    return XIL_INTERFACE_UNKNOWN_TID;
}

XIL_INTERFACE_ERROR_CODE xilDisable(uint32_T xilFcnId, uint32_T xilTID) {
    /* Single In-the-Loop Component */
    if (xilFcnId != 0) {
       return XIL_INTERFACE_UNKNOWN_FCNID;
    }
    UNUSED_PARAMETER(xilTID);
    /* No Disable Function - this function should never be called */
    return XIL_INTERFACE_UNKNOWN_TID;
}

