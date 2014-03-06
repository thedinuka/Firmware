/*
 * quad_8state_kalman_sil.c
 *
 * Automatically generated s-function with I/O interface for:
 * Component: quad_8state_kalman
 * Component Simulink Path: quad_8state_kalman
 * Simulation Mode: SIL
 *
 */

#define S_FUNCTION_NAME quad_8state_kalman_sil
#define S_FUNCTION_LEVEL 2
#if !defined(RTW_GENERATED_S_FUNCTION)
#define RTW_GENERATED_S_FUNCTION
#endif

#include <stdio.h>
#include <string.h>
#include "mex.h"

#include "rtiostream_utils.h"

#include "emlrt.h"
#include "_coder_quad_8state_kalman_info.h"
#define CONSTANT_TID (-2)

emlrtContext emlrtContextGlobal = { true, false, EMLRT_VERSION_INFO, NULL, "quad_8state_kalman", NULL, false, {2045744189U, 2170104910U, 2743257031U, 4284093946U}, NULL};
void * emlrtRootTLSGlobal = NULL;

typedef struct {
    libH_type libH;
    char * lib;
    mxArray * MATLABObject;
    double streamID;
    double recvTimeout;
    double sendTimeout;
} rtIOStreamData;

typedef struct {
    uint8_T * data;
    mwSize size;
} IOBuffer_T;

typedef struct {
    FILE ** Fd;
    mwSize size;
    int32_T fidOffset;
} targetIOFd_T;

static targetIOFd_T *targetIOFdPtr = NULL;
static rtIOStreamData *rtIOStreamDataPtr = NULL;
static IOBuffer_T *IOBufferPtr = NULL;
static int *pCommErrorOccurred = 0;

static boolean_T firstTime=0;

/* implements calls into MATLAB */
static int callMATLAB( 
                      int nlhs, 
                      mxArray * plhs[], 
                      int nrhs, 
                      mxArray * prhs[], 
                      const char * functionName, 
                      int withTrap) {
    int errorOccurred = 0;
    if (withTrap) {
        mxArray * mException;
        mException = mexCallMATLABWithTrap(nlhs, plhs, nrhs, prhs, functionName);
        {
            int i;
            for (i=0; i<nrhs; i++) {
                mxDestroyArray(prhs[i]);
            } /* for */
        }
        if (mException != NULL) {
            mxArray * rhsDisplayMException[1];
            errorOccurred = 1;
            rhsDisplayMException[0] = mException;
            mException = mexCallMATLABWithTrap(0, NULL, 1, rhsDisplayMException, "rtw.pil.SILPILInterface.displayMException");
            mxDestroyArray(rhsDisplayMException[0]);
            if (mException != NULL) {
                mxDestroyArray(mException);
                mexErrMsgTxt( "Error calling rtw.pil.SILPILInterface.displayMException on mException object.");
            } else {
                mexErrMsgTxt( "mexCallMATLABWithTrap failed. See the full MException report in the MATLAB Command Window.");
            } /* if */
        } /* if */
    } else {
        errorOccurred = mexCallMATLAB(nlhs, plhs, nrhs, prhs, functionName);
        {
            int i;
            for (i=0; i<nrhs; i++) {
                mxDestroyArray(prhs[i]);
            } /* for */
        }
        if (errorOccurred) {
            mexErrMsgTxt( "mexCallMATLAB failed!");
        } /* if */
    } /* if */
    return errorOccurred;
}

/* enlarges the dynamically allocated shared I/O buffer
 * IOBufferPtr->data is NULL on failure */
static void growIOBuffer(IOBuffer_T * IOBuffer, mwSize requiredSize) {
    if (IOBuffer->size < requiredSize) {
        IOBuffer->data = mxRealloc(IOBuffer->data, requiredSize * sizeof(uint8_T));
        if (IOBuffer->data == NULL) {
            mexErrMsgTxt( "growIOBuffer: mxRealloc failed.");
        } else {
            mexMakeMemoryPersistent(IOBuffer->data);
            IOBuffer->size = requiredSize;
        } /* if */
    } /* if */
}

/* grow the buffer for target I/O Fd array
 * targetIOFd->Fd is NULL on failure */
static void growTargetIOFd(targetIOFd_T * IOFd, mwSize requiredSize) {
    if (IOFd->size < requiredSize) {
        IOFd->Fd = mxRealloc(IOFd->Fd, requiredSize * sizeof(FILE*));
        if (IOFd->Fd == NULL) {
            mexErrMsgTxt( "growTargetIOFd: mxRealloc failed.");
        } else {
            mexMakeMemoryPersistent(IOFd->Fd);
            IOFd->size = requiredSize;
        } /* if */
    } /* if */
}

static void closeAndFreeTargetIOFd() {
    int i;
    if(targetIOFdPtr != NULL) {
        if (targetIOFdPtr->Fd != NULL) {
            for(i=0; i<targetIOFdPtr->size; i++) {
                if (targetIOFdPtr->Fd[i] != NULL) {
                    fclose(targetIOFdPtr->Fd[i]);
                } /* if */
            } /* for */
            mxFree(targetIOFdPtr->Fd);
        } /* if */
    } /* if */
}

/* implements blocking receive via RtIOStream */
static int blockingRtIOStreamRecv( size_t recvSize, int withTrap, uint8_T * dataIn) {

    int errorOccurred = 0;
    int timeoutOccurred = 0;

    if (rtIOStreamDataPtr == NULL) {
        mexErrMsgTxt( "rtIOStreamDataPtr is NULL.");
        errorOccurred = 1;
        return errorOccurred;
    } /* if */

    if (pCommErrorOccurred == NULL) {
        mexErrMsgTxt( "pCommErrorOccurred is NULL.");
        errorOccurred = 1;
        return errorOccurred;
    } /* if */

    {
        int attemptToReceiveData = 1;
        while(attemptToReceiveData) {
            errorOccurred = 0;
            timeoutOccurred = 0;
            errorOccurred = rtIOStreamBlockingRecv(&rtIOStreamDataPtr->libH, 
               (const int) rtIOStreamDataPtr->streamID, 
               dataIn, 
               recvSize, 
               (const int) rtIOStreamDataPtr->recvTimeout, 
               &timeoutOccurred);

            if (errorOccurred && timeoutOccurred) {
                mxArray *rhs[3];
                mxArray *lhs[1];
                const char * simulinkBlockPath = "/home/dmabeywa/Dropbox/Quadrotor State Estimation/ANU 8 state EKF/codegen/lib/quad_8state_kalman/quad_8state_kalman";
                rhs[ 0 ] = mxCreateString("@coder.connectivity.MATLABInterface.getSILPILInterface");
                rhs[ 1 ] = mxCreateDoubleScalar( 3 );
                rhs[ 2 ] = mxCreateString(simulinkBlockPath);
                callMATLAB( 1, lhs, 3, rhs, "rtw.pil.SILPILInterface.sfunctionIsSILDebugEnabledAndSILExeAlive", 0);
                attemptToReceiveData = (int) *mxGetPr(lhs[0]);
                mxDestroyArray(lhs[0]);
            } else {
                /* rtIOStreamBlockingRecv completed successfully or a non-timeout related error occurred */
                attemptToReceiveData = 0;
            } /* if */
        } /* while */
    }

    *pCommErrorOccurred = 0;
    if (errorOccurred) {
        mxArray *rhs[2];
        rhs[0] = mxCreateDoubleScalar(timeoutOccurred);
        rhs[1] = mxCreateDoubleScalar(rtIOStreamDataPtr->recvTimeout);
        *pCommErrorOccurred = 1;
        errorOccurred = callMATLAB( 0, NULL, 2, rhs, "rtw.pil.SILPILInterface.handleRtIOStreamRecvError", withTrap);
    } /* if */

    return errorOccurred;
}

/* implements blocking send via RtIOStream */
static int blockingRtIOStreamSend(uint8_T * dataOut, size_t sendSize, int withTrap) {

    int errorOccurred = 0;
    int timeoutOccurred = 0;

    if (rtIOStreamDataPtr == NULL) {
        mexErrMsgTxt( "rtIOStreamDataPtr is NULL.");
        errorOccurred = 1;
        return errorOccurred;
    } /* if */

    if (pCommErrorOccurred == NULL) {
        mexErrMsgTxt( "pCommErrorOccurred is NULL.");
        errorOccurred = 1;
        return errorOccurred;
    } /* if */

    {
        int attemptToSendData = 1;
        while(attemptToSendData) {
            errorOccurred = 0;
            timeoutOccurred = 0;
            errorOccurred = rtIOStreamBlockingSend(&rtIOStreamDataPtr->libH, 
               (const int) rtIOStreamDataPtr->streamID, 
               dataOut, 
               sendSize, 
               (const int) rtIOStreamDataPtr->sendTimeout, 
               &timeoutOccurred);

            if (errorOccurred && timeoutOccurred) {
                mxArray *rhs[3];
                mxArray *lhs[1];
                const char * simulinkBlockPath = "/home/dmabeywa/Dropbox/Quadrotor State Estimation/ANU 8 state EKF/codegen/lib/quad_8state_kalman/quad_8state_kalman";
                rhs[ 0 ] = mxCreateString("@coder.connectivity.MATLABInterface.getSILPILInterface");
                rhs[ 1 ] = mxCreateDoubleScalar( 3 );
                rhs[ 2 ] = mxCreateString(simulinkBlockPath);
                callMATLAB( 1, lhs, 3, rhs, "rtw.pil.SILPILInterface.sfunctionIsSILDebugEnabledAndSILExeAlive", 0);
                attemptToSendData = (int) *mxGetPr(lhs[0]);
                mxDestroyArray(lhs[0]);
            } else {
                /* rtIOStreamBlockingSend completed successfully or a non-timeout related error occurred */
                attemptToSendData = 0;
            } /* if */
        } /* while */
    }

    *pCommErrorOccurred = 0;
    if (errorOccurred) {
        mxArray *rhs[2];
        rhs[0] = mxCreateDoubleScalar(timeoutOccurred);
        rhs[1] = mxCreateDoubleScalar(rtIOStreamDataPtr->sendTimeout);
        *pCommErrorOccurred = 1;
        errorOccurred = callMATLAB( 0, NULL, 2, rhs, "rtw.pil.SILPILInterface.handleRtIOStreamSendError", withTrap);
    } /* if */

    return errorOccurred;
}

/* implements command dispatch layer */
static int commandDispatch(IOBuffer_T * IOBuffer, mwSize dataOutSize, mwSize * dataInSize, int withTrap) {
    int errorOccurred = 0;
    uint8_T * mxMemUnitPtr;
    mwSize responseSize = 0;
    uint8_T responseHeaderData[5];
    uint8_T COMMAND_COMPLETE = 0;
    *dataInSize = 0;
    errorOccurred = blockingRtIOStreamSend(IOBuffer->data, dataOutSize, withTrap);
    if (errorOccurred) {
        return errorOccurred;
    } /* if */
    while (!COMMAND_COMPLETE) {
        uint32_T WRITE_DATA_AVAIL;
        errorOccurred = blockingRtIOStreamRecv(5, withTrap, &responseHeaderData[0]);
        if (errorOccurred) {
            return errorOccurred;
        } /* if */
        mxMemUnitPtr = (uint8_T *) &responseHeaderData[0];
        {
            uint8_T * simDataMemUnitPtr;
            simDataMemUnitPtr = (uint8_T *) &WRITE_DATA_AVAIL;
            {
                size_t num_elements = 1;
                size_t bytes_consumed = num_elements * sizeof(uint32_T);
                memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
            }
        }
        {
            uint8_T * simDataMemUnitPtr;
            simDataMemUnitPtr = (uint8_T *) &COMMAND_COMPLETE;
            {
                size_t num_elements = 1;
                size_t bytes_consumed = num_elements * sizeof(uint8_T);
                memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
            }
        }
        if (WRITE_DATA_AVAIL) {
            growIOBuffer(IOBuffer, responseSize + (mwSize) WRITE_DATA_AVAIL);
            if (IOBuffer->data == NULL) {
                mexErrMsgTxt( "commandDispatch: growIOBuffer failed.");
                errorOccurred = 1;
                return errorOccurred;
            } /* if */
            errorOccurred = blockingRtIOStreamRecv(WRITE_DATA_AVAIL, withTrap, &IOBuffer->data[responseSize]);
            if (errorOccurred) {
                return errorOccurred;
            } /* if */
            responseSize += WRITE_DATA_AVAIL;
        } /* if */
    } /* while */
    *dataInSize = responseSize;
    return errorOccurred;
}

static void mdlInitializeSizes(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    {
        mxArray * lhs[1];
        mxArray * error = NULL;
        char * installVersion;
        error = mexCallMATLABWithTrap(1, lhs, 0, NULL, "rtw.pil.SILPILInterface.getPILVersion");
        if (error != NULL) {
            mxDestroyArray(error);
            mexErrMsgTxt( "Failed to determine the installed In-the-Loop version for comparison against the In-the-Loop s-function version (release 6.5 (R2013b)_11). To avoid this error, remove the In-the-Loop s-function from your MATLAB path (e.g. delete it or move to a clean working directory).");
            return;
        } /* if */
        if (mxIsEmpty(lhs[0])) {
            mexErrMsgTxt( "rtw.pil.SILPILInterface.getPILVersion returned empty!");
            return;
        } /* if */
        installVersion = mxArrayToString(lhs[0]);
        mxDestroyArray(lhs[0]);
        if (installVersion == NULL) {
            mexErrMsgTxt( "Failed to determine installed In-the-Loop version.");
            return;
        } /* if */
        if (strcmp(installVersion, "6.5 (R2013b)_11") != 0) {
            mexErrMsgTxt( "The In-the-Loop s-function is incompatible with the installed In-the-Loop version (see ver('ecoder')); it was generated for release 6.5 (R2013b)_11. To avoid this error, remove the In-the-Loop s-function from your MATLAB path (e.g. delete it or move to a clean working directory)");
            return;
        } /* if */
        mxFree(installVersion);
    }

}

/* forward declaration for mdlProcessParameters */
#define MDL_PROCESS_PARAMETERS  /* Change to #undef to remove function */
#if defined(MDL_PROCESS_PARAMETERS)
static void mdlProcessParameters(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);
#endif /* MDL_PROCESS_PARAMETERS */
#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START)
static void mdlStart(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    {
        {
            pCommErrorOccurred = (int *) mxCalloc(1, sizeof(int));
            if (pCommErrorOccurred == NULL) {
                mexErrMsgTxt( "Error in allocating memory for pCommErrorOccurred through mxCalloc.");
                return;
            } /* if */
            *pCommErrorOccurred = 0;
            mexMakeMemoryPersistent(pCommErrorOccurred);
        }
    }
    {
        {
            mxArray *rhs[4];
            const char * simulinkBlockPath = "/home/dmabeywa/Dropbox/Quadrotor State Estimation/ANU 8 state EKF/codegen/lib/quad_8state_kalman/quad_8state_kalman";
            rhs[ 0 ] = mxCreateString("@coder.connectivity.MATLABInterface.getSILPILInterface");
            rhs[ 1 ] = mxCreateDoubleScalar( 3 );
            rhs[ 2 ] = mxCreateString(simulinkBlockPath);
            rhs[3] = mxCreateString("uint8");
            callMATLAB( 0, NULL, 4, rhs, "rtw.pil.SILPILInterface.sfunctionPILStartHook", 0);
        }
    }
    {
        mxArray *rhs[3];
        mxArray *lhs[5];
        const char * simulinkBlockPath = "/home/dmabeywa/Dropbox/Quadrotor State Estimation/ANU 8 state EKF/codegen/lib/quad_8state_kalman/quad_8state_kalman";
        rhs[ 0 ] = mxCreateString("@coder.connectivity.MATLABInterface.getSILPILInterface");
        rhs[ 1 ] = mxCreateDoubleScalar( 3 );
        rhs[ 2 ] = mxCreateString(simulinkBlockPath);
        callMATLAB( 5, lhs, 3, rhs, "rtw.pil.SILPILInterface.sfunctionGetRtIOStreamInfoHook", 0);
        {
            rtIOStreamDataPtr = (rtIOStreamData *) mxCalloc(1, sizeof(rtIOStreamData));
            if (rtIOStreamDataPtr == NULL) {
                mexErrMsgTxt( "Error in allocating memory through mxCalloc.");
                return;
            } /* if */
            rtIOStreamDataPtr->lib = mxArrayToString(lhs[0]);
            rtIOStreamDataPtr->MATLABObject = mxDuplicateArray(lhs[1]);
            mexMakeMemoryPersistent(rtIOStreamDataPtr);
            mexMakeMemoryPersistent(rtIOStreamDataPtr->lib);
            mexMakeArrayPersistent(rtIOStreamDataPtr->MATLABObject);
            rtIOStreamDataPtr->streamID = *mxGetPr(lhs[2]);
            rtIOStreamDataPtr->recvTimeout = *mxGetPr(lhs[3]);
            rtIOStreamDataPtr->sendTimeout = *mxGetPr(lhs[4]);
            {
                int errorStatus = rtIOStreamLoadLib(&rtIOStreamDataPtr->libH, rtIOStreamDataPtr->lib);
                if (errorStatus) {
                    mexErrMsgTxt( "rtIOStreamLoadLib failed.");
                    return;
                } /* if */
            }
        }
        {
            int i;
            for (i=0; i<5; i++) {
                mxDestroyArray(lhs[i]);
            } /* for */
        }
    }
    {
        IOBufferPtr = (IOBuffer_T *) mxCalloc(1, sizeof(IOBuffer_T));
        if (IOBufferPtr == NULL) {
            mexErrMsgTxt( "Error in allocating memory through mxCalloc.");
            return;
        } /* if */
        mexMakeMemoryPersistent(IOBufferPtr);
    }
    {
        targetIOFdPtr = (targetIOFd_T *) mxCalloc(1, sizeof(targetIOFd_T));
        if (targetIOFdPtr == NULL) {
            return;
        } /* if */
        mexMakeMemoryPersistent(targetIOFdPtr);
        targetIOFdPtr->size = 0;
        targetIOFdPtr->Fd = NULL;
        targetIOFdPtr->fidOffset = -1;
    }
    {
        uint8_T * mxMemUnitPtr;
        mwSize dataInSize = 0;
        if (IOBufferPtr != NULL) {
            growIOBuffer(IOBufferPtr, 5);
            if (IOBufferPtr->data != NULL) {
                mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                /* write command id */
                *mxMemUnitPtr = 0;
                mxMemUnitPtr++;
                {
                    uint8_T * simDataMemUnitPtr;
                    uint32_T commandDataFcnid = 0;
                    simDataMemUnitPtr = (uint8_T *) &commandDataFcnid;
                    {
                        size_t num_elements = 1;
                        size_t bytes_consumed = num_elements * sizeof(uint32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    int errorOccurred;
                    errorOccurred = commandDispatch(IOBufferPtr, 5, &dataInSize, 0);
                    if (errorOccurred) {
                        return;
                    } /* if */
                }
                if (dataInSize > 0) {
                    size_t dataInMemUnitSize = dataInSize;
                    uint8_T responseId;
                    uint8_T * mxMemUnitPtrEnd;
                    #define RESPONSE_ERROR 0
                    #define RESPONSE_PRINTF 3
                    #define RESPONSE_FOPEN 4
                    #define RESPONSE_FPRINTF 5
                    #define TARGET_IO_SUCCESS 0
                    #define RESPONSE_TYPE_SIZE 6
                    mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                    mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                    while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                        /* read response id */
                        responseId = *mxMemUnitPtr;
                        mxMemUnitPtr++;
                        switch (responseId) {
                            case RESPONSE_ERROR: {
                                uint8_T errorId = *mxMemUnitPtr;
                                mxMemUnitPtr++;
                                if (errorId) {
                                    {
                                        mxArray * prhs[ 2 ];
                                        prhs[0] = mxCreateString("PIL:pilverification:PILError");
                                        prhs[1] = mxCreateDoubleScalar(errorId);
                                        callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                        return;
                                    }
                                } /* if */
                                break;
                            }
                            case RESPONSE_PRINTF: {
                                uint8_T PRINTF_ERROR;
                                uint16_T PRINTF_SIZE;
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &PRINTF_ERROR;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint8_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &PRINTF_SIZE;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                if (PRINTF_ERROR != TARGET_IO_SUCCESS) {
                                    {
                                        mxArray * prhs[ 2 ];
                                        prhs[0] = mxCreateString("PIL:pil:TargetIOError");
                                        prhs[1] = mxCreateDoubleScalar(PRINTF_ERROR);
                                        callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                        return;
                                    }
                                } else {
                                    uint8_T *pPrintBuff;
                                    pPrintBuff = mxMemUnitPtr;
                                    if (pPrintBuff[PRINTF_SIZE-1] == '\0') {
                                        mexPrintf("%s", pPrintBuff);
                                    } /* if */
                                } /* if */
                                mxMemUnitPtr = mxMemUnitPtr + PRINTF_SIZE;
                                break;
                            }
                            case RESPONSE_FOPEN: {
                                uint16_T FOPEN_FID;
                                uint16_T FOPEN_NAME_SIZE;
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FOPEN_FID;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FOPEN_NAME_SIZE;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                if (targetIOFdPtr != NULL) {
                                    /* check fid increments by 1 */
                                    if (targetIOFdPtr->fidOffset + 1 == FOPEN_FID) {
                                        targetIOFdPtr->fidOffset = FOPEN_FID;
                                        growTargetIOFd(targetIOFdPtr, targetIOFdPtr->fidOffset + 1);
                                        if (targetIOFdPtr->Fd != NULL)  {
                                            uint8_T *pFopenBuff;
                                            targetIOFdPtr->Fd[targetIOFdPtr->fidOffset] = NULL;
                                            pFopenBuff = mxMemUnitPtr;
                                            if (pFopenBuff[FOPEN_NAME_SIZE-1] == '\0') {
                                                FILE * tmpFd = NULL;
                                                tmpFd = fopen((char *) pFopenBuff,"w");
                                                if (tmpFd != NULL) {
                                                    /* save the file descriptor */
                                                    targetIOFdPtr->Fd[targetIOFdPtr->fidOffset] = tmpFd;
                                                } else {
                                                    {
                                                        mxArray * prhs[ 2 ];
                                                        prhs[0] = mxCreateString("PIL:pil:TargetIOFopenError");
                                                        prhs[1] = mxCreateString((char *) pFopenBuff);
                                                        callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                                        return;
                                                    }
                                                } /* if */
                                            } /* if */
                                        } /* if */
                                    } else {
                                        {
                                            mxArray * prhs[ 2 ];
                                            prhs[0] = mxCreateString("PIL:pil:TargetIOFopenFidError");
                                            prhs[1] = mxCreateDoubleScalar(FOPEN_FID);
                                            callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                            return;
                                        }
                                    } /* if */
                                } /* if */
                                mxMemUnitPtr = mxMemUnitPtr + FOPEN_NAME_SIZE;
                                break;
                            }
                            case RESPONSE_FPRINTF: {
                                uint8_T FPRINTF_ERROR;
                                uint16_T FPRINTF_FID;
                                uint16_T FPRINTF_SIZE;
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FPRINTF_ERROR;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint8_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FPRINTF_FID;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FPRINTF_SIZE;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                if (FPRINTF_ERROR != TARGET_IO_SUCCESS) {
                                    {
                                        mxArray * prhs[ 2 ];
                                        prhs[0] = mxCreateString("PIL:pil:TargetIOError");
                                        prhs[1] = mxCreateDoubleScalar(FPRINTF_ERROR);
                                        callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                        return;
                                    }
                                } else {
                                    if (targetIOFdPtr != NULL) {
                                        if (targetIOFdPtr->size > FPRINTF_FID) {
                                            if (targetIOFdPtr->Fd[FPRINTF_FID] != NULL) {
                                                uint8_T *pFprintfBuff;
                                                pFprintfBuff = mxMemUnitPtr;
                                                if (pFprintfBuff[FPRINTF_SIZE-1] == '\0') {
                                                    fprintf(targetIOFdPtr->Fd[FPRINTF_FID], "%s", pFprintfBuff);
                                                } /* if */
                                            } /* if */
                                        } /* if */
                                    } /* if */
                                } /* if */
                                mxMemUnitPtr = mxMemUnitPtr + FPRINTF_SIZE;
                                break;
                            }
                            case RESPONSE_TYPE_SIZE: {
                                uint8_T typeId = *mxMemUnitPtr;
                                uint8_T typeBytes;
                                mxMemUnitPtr++;
                                typeBytes = *mxMemUnitPtr;
                                mxMemUnitPtr++;
                                switch (typeId) {
                                    case mxSINGLE_CLASS: {
                                        if (typeBytes != 4) {
                                            {
                                                mxArray * prhs[ 3 ];
                                                prhs[0] = mxCreateString("PIL:pilverification:SingleUnsupported");
                                                prhs[1] = mxCreateDoubleScalar(4);
                                                prhs[2] = mxCreateDoubleScalar(typeBytes);
                                                callMATLAB( 0, NULL, 3, prhs, "DAStudio.error", 0);
                                                return;
                                            }
                                        } /* if */
                                        break;
                                    }
                                    case mxDOUBLE_CLASS: {
                                        if (typeBytes != 8) {
                                            {
                                                mxArray * prhs[ 3 ];
                                                prhs[0] = mxCreateString("PIL:pilverification:DoubleUnsupported");
                                                prhs[1] = mxCreateDoubleScalar(8);
                                                prhs[2] = mxCreateDoubleScalar(typeBytes);
                                                callMATLAB( 0, NULL, 3, prhs, "DAStudio.error", 0);
                                                return;
                                            }
                                        } /* if */
                                        break;
                                    }
                                    default: {
                                        {
                                            mxArray * prhs[ 2 ];
                                            prhs[0] = mxCreateString("PIL:pilverification:UnknownTypeId");
                                            prhs[1] = mxCreateDoubleScalar(typeId);
                                            callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                            return;
                                        }
                                        break;
                                    }
                                } /* switch */
                                break;
                            }
                            default: {
                                {
                                    mxArray * prhs[ 2 ];
                                    prhs[0] = mxCreateString("PIL:pilverification:UnknownResponseId");
                                    prhs[1] = mxCreateDoubleScalar(responseId);
                                    callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                    return;
                                }
                                break;
                            }
                        } /* switch */
                    } /* while */
                } /* if */
            } /* if */
        } /* if */
    }
    /* initialize parameters */
    mdlProcessParameters(nlhs, plhs, nrhs, prhs);
    {
        uint8_T * mxMemUnitPtr;
        mwSize dataInSize = 0;
        if (IOBufferPtr != NULL) {
            growIOBuffer(IOBufferPtr, 5);
            if (IOBufferPtr->data != NULL) {
                mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                /* write command id */
                *mxMemUnitPtr = 1;
                mxMemUnitPtr++;
                {
                    uint8_T * simDataMemUnitPtr;
                    uint32_T commandDataFcnid = 0;
                    simDataMemUnitPtr = (uint8_T *) &commandDataFcnid;
                    {
                        size_t num_elements = 1;
                        size_t bytes_consumed = num_elements * sizeof(uint32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    int errorOccurred;
                    errorOccurred = commandDispatch(IOBufferPtr, 5, &dataInSize, 0);
                    if (errorOccurred) {
                        return;
                    } /* if */
                }
                if (dataInSize > 0) {
                    size_t dataInMemUnitSize = dataInSize;
                    uint8_T responseId;
                    uint8_T * mxMemUnitPtrEnd;
                    #define RESPONSE_ERROR 0
                    #define RESPONSE_OUTPUT_DATA 1
                    #define RESPONSE_PRINTF 3
                    #define RESPONSE_FOPEN 4
                    #define RESPONSE_FPRINTF 5
                    #define TARGET_IO_SUCCESS 0
                    mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                    mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                    while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                        /* read response id */
                        responseId = *mxMemUnitPtr;
                        mxMemUnitPtr++;
                        switch (responseId) {
                            case RESPONSE_ERROR: {
                                uint8_T errorId = *mxMemUnitPtr;
                                mxMemUnitPtr++;
                                if (errorId) {
                                    {
                                        mxArray * prhs[ 2 ];
                                        prhs[0] = mxCreateString("PIL:pilverification:PILError");
                                        prhs[1] = mxCreateDoubleScalar(errorId);
                                        callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                        return;
                                    }
                                } /* if */
                                break;
                            }
                            case RESPONSE_PRINTF: {
                                uint8_T PRINTF_ERROR;
                                uint16_T PRINTF_SIZE;
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &PRINTF_ERROR;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint8_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &PRINTF_SIZE;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                if (PRINTF_ERROR != TARGET_IO_SUCCESS) {
                                    {
                                        mxArray * prhs[ 2 ];
                                        prhs[0] = mxCreateString("PIL:pil:TargetIOError");
                                        prhs[1] = mxCreateDoubleScalar(PRINTF_ERROR);
                                        callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                        return;
                                    }
                                } else {
                                    uint8_T *pPrintBuff;
                                    pPrintBuff = mxMemUnitPtr;
                                    if (pPrintBuff[PRINTF_SIZE-1] == '\0') {
                                        mexPrintf("%s", pPrintBuff);
                                    } /* if */
                                } /* if */
                                mxMemUnitPtr = mxMemUnitPtr + PRINTF_SIZE;
                                break;
                            }
                            case RESPONSE_FOPEN: {
                                uint16_T FOPEN_FID;
                                uint16_T FOPEN_NAME_SIZE;
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FOPEN_FID;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FOPEN_NAME_SIZE;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                if (targetIOFdPtr != NULL) {
                                    /* check fid increments by 1 */
                                    if (targetIOFdPtr->fidOffset + 1 == FOPEN_FID) {
                                        targetIOFdPtr->fidOffset = FOPEN_FID;
                                        growTargetIOFd(targetIOFdPtr, targetIOFdPtr->fidOffset + 1);
                                        if (targetIOFdPtr->Fd != NULL)  {
                                            uint8_T *pFopenBuff;
                                            targetIOFdPtr->Fd[targetIOFdPtr->fidOffset] = NULL;
                                            pFopenBuff = mxMemUnitPtr;
                                            if (pFopenBuff[FOPEN_NAME_SIZE-1] == '\0') {
                                                FILE * tmpFd = NULL;
                                                tmpFd = fopen((char *) pFopenBuff,"w");
                                                if (tmpFd != NULL) {
                                                    /* save the file descriptor */
                                                    targetIOFdPtr->Fd[targetIOFdPtr->fidOffset] = tmpFd;
                                                } else {
                                                    {
                                                        mxArray * prhs[ 2 ];
                                                        prhs[0] = mxCreateString("PIL:pil:TargetIOFopenError");
                                                        prhs[1] = mxCreateString((char *) pFopenBuff);
                                                        callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                                        return;
                                                    }
                                                } /* if */
                                            } /* if */
                                        } /* if */
                                    } else {
                                        {
                                            mxArray * prhs[ 2 ];
                                            prhs[0] = mxCreateString("PIL:pil:TargetIOFopenFidError");
                                            prhs[1] = mxCreateDoubleScalar(FOPEN_FID);
                                            callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                            return;
                                        }
                                    } /* if */
                                } /* if */
                                mxMemUnitPtr = mxMemUnitPtr + FOPEN_NAME_SIZE;
                                break;
                            }
                            case RESPONSE_FPRINTF: {
                                uint8_T FPRINTF_ERROR;
                                uint16_T FPRINTF_FID;
                                uint16_T FPRINTF_SIZE;
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FPRINTF_ERROR;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint8_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FPRINTF_FID;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FPRINTF_SIZE;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                if (FPRINTF_ERROR != TARGET_IO_SUCCESS) {
                                    {
                                        mxArray * prhs[ 2 ];
                                        prhs[0] = mxCreateString("PIL:pil:TargetIOError");
                                        prhs[1] = mxCreateDoubleScalar(FPRINTF_ERROR);
                                        callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                        return;
                                    }
                                } else {
                                    if (targetIOFdPtr != NULL) {
                                        if (targetIOFdPtr->size > FPRINTF_FID) {
                                            if (targetIOFdPtr->Fd[FPRINTF_FID] != NULL) {
                                                uint8_T *pFprintfBuff;
                                                pFprintfBuff = mxMemUnitPtr;
                                                if (pFprintfBuff[FPRINTF_SIZE-1] == '\0') {
                                                    fprintf(targetIOFdPtr->Fd[FPRINTF_FID], "%s", pFprintfBuff);
                                                } /* if */
                                            } /* if */
                                        } /* if */
                                    } /* if */
                                } /* if */
                                mxMemUnitPtr = mxMemUnitPtr + FPRINTF_SIZE;
                                break;
                            }
                            case RESPONSE_OUTPUT_DATA: {
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = ( uint8_T *) mxGetData( plhs[ 0 ] );
                                    {
                                        size_t num_elements = 8;
                                        size_t bytes_consumed = num_elements * sizeof(real32_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                break;
                            }
                            default: {
                                {
                                    mxArray * prhs[ 2 ];
                                    prhs[0] = mxCreateString("PIL:pilverification:UnknownResponseId");
                                    prhs[1] = mxCreateDoubleScalar(responseId);
                                    callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                    return;
                                }
                                break;
                            }
                        } /* switch */
                    } /* while */
                } /* if */
            } /* if */
        } /* if */
    }
}
#endif /* MDL_START */

#if defined(MDL_PROCESS_PARAMETERS)
static void mdlProcessParameters(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    int isOkToProcessParams;
    {
        {
            mxArray *rhs[3];
            mxArray *lhs[1];
            const char * simulinkBlockPath = "/home/dmabeywa/Dropbox/Quadrotor State Estimation/ANU 8 state EKF/codegen/lib/quad_8state_kalman/quad_8state_kalman";
            rhs[ 0 ] = mxCreateString("@coder.connectivity.MATLABInterface.getSILPILInterface");
            rhs[ 1 ] = mxCreateDoubleScalar( 3 );
            rhs[ 2 ] = mxCreateString(simulinkBlockPath);
            callMATLAB( 1, lhs, 3, rhs, "rtw.pil.SILPILInterface.sfunctionIsOkToProcessParamsHook", 0);
            isOkToProcessParams = (int) (*mxGetPr(lhs[0]));
            mxDestroyArray(lhs[0]);
        }
    }
    if (isOkToProcessParams) {
    } /* if */
}
#endif /* MDL_PROCESS_PARAMETERS */

static void mdlOutputs(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[], int_T tid) {
    {
        uint8_T * mxMemUnitPtr;
        mwSize dataInSize = 0;
        if (IOBufferPtr != NULL) {
            growIOBuffer(IOBufferPtr, 61);
            if (IOBufferPtr->data != NULL) {
                mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                /* write command id */
                *mxMemUnitPtr = 3;
                mxMemUnitPtr++;
                {
                    uint8_T * simDataMemUnitPtr;
                    uint32_T commandDataFcnidTID[2] = {0, 1};
                    simDataMemUnitPtr = (uint8_T *) &commandDataFcnidTID[0];
                    {
                        size_t num_elements = 2;
                        size_t bytes_consumed = num_elements * sizeof(uint32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    uint8_T * simDataMemUnitPtr;
                    simDataMemUnitPtr = ( uint8_T *) mxGetData( prhs[ 0 ] );
                    {
                        size_t num_elements = 2;
                        size_t bytes_consumed = num_elements * sizeof(real32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    uint8_T * simDataMemUnitPtr;
                    simDataMemUnitPtr = ( uint8_T *) mxGetData( prhs[ 1 ] );
                    {
                        size_t num_elements = 3;
                        size_t bytes_consumed = num_elements * sizeof(real32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    uint8_T * simDataMemUnitPtr;
                    simDataMemUnitPtr = ( uint8_T *) mxGetData( prhs[ 2 ] );
                    {
                        size_t num_elements = 1;
                        size_t bytes_consumed = num_elements * sizeof(real32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    uint8_T * simDataMemUnitPtr;
                    simDataMemUnitPtr = ( uint8_T *) mxGetData( prhs[ 3 ] );
                    {
                        size_t num_elements = 1;
                        size_t bytes_consumed = num_elements * sizeof(real32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    uint8_T * simDataMemUnitPtr;
                    simDataMemUnitPtr = ( uint8_T *) mxGetData( prhs[ 4 ] );
                    {
                        size_t num_elements = 1;
                        size_t bytes_consumed = num_elements * sizeof(real32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    uint8_T * simDataMemUnitPtr;
                    simDataMemUnitPtr = ( uint8_T *) mxGetData( prhs[ 5 ] );
                    {
                        size_t num_elements = 1;
                        size_t bytes_consumed = num_elements * sizeof(real32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    uint8_T * simDataMemUnitPtr;
                    simDataMemUnitPtr = ( uint8_T *) mxGetData( prhs[ 6 ] );
                    {
                        size_t num_elements = 1;
                        size_t bytes_consumed = num_elements * sizeof(real32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    uint8_T * simDataMemUnitPtr;
                    simDataMemUnitPtr = ( uint8_T *) mxGetData( prhs[ 7 ] );
                    {
                        size_t num_elements = 1;
                        size_t bytes_consumed = num_elements * sizeof(real32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    uint8_T * simDataMemUnitPtr;
                    simDataMemUnitPtr = ( uint8_T *) mxGetData( prhs[ 8 ] );
                    {
                        size_t num_elements = 1;
                        size_t bytes_consumed = num_elements * sizeof(real32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    uint8_T * simDataMemUnitPtr;
                    simDataMemUnitPtr = ( uint8_T *) mxGetData( prhs[ 9 ] );
                    {
                        size_t num_elements = 1;
                        size_t bytes_consumed = num_elements * sizeof(real32_T);
                        memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                    }
                }
                {
                    int errorOccurred;
                    errorOccurred = commandDispatch(IOBufferPtr, 61, &dataInSize, 0);
                    if (errorOccurred) {
                        return;
                    } /* if */
                }
                if (dataInSize > 0) {
                    size_t dataInMemUnitSize = dataInSize;
                    uint8_T responseId;
                    uint8_T * mxMemUnitPtrEnd;
                    #define RESPONSE_ERROR 0
                    #define RESPONSE_OUTPUT_DATA 1
                    #define RESPONSE_PRINTF 3
                    #define RESPONSE_FOPEN 4
                    #define RESPONSE_FPRINTF 5
                    #define TARGET_IO_SUCCESS 0
                    mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                    mxMemUnitPtrEnd = mxMemUnitPtr + dataInMemUnitSize - 1;
                    while (mxMemUnitPtr <= mxMemUnitPtrEnd) {
                        /* read response id */
                        responseId = *mxMemUnitPtr;
                        mxMemUnitPtr++;
                        switch (responseId) {
                            case RESPONSE_ERROR: {
                                uint8_T errorId = *mxMemUnitPtr;
                                mxMemUnitPtr++;
                                if (errorId) {
                                    {
                                        mxArray * prhs[ 2 ];
                                        prhs[0] = mxCreateString("PIL:pilverification:PILError");
                                        prhs[1] = mxCreateDoubleScalar(errorId);
                                        callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                        return;
                                    }
                                } /* if */
                                break;
                            }
                            case RESPONSE_PRINTF: {
                                uint8_T PRINTF_ERROR;
                                uint16_T PRINTF_SIZE;
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &PRINTF_ERROR;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint8_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &PRINTF_SIZE;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                if (PRINTF_ERROR != TARGET_IO_SUCCESS) {
                                    {
                                        mxArray * prhs[ 2 ];
                                        prhs[0] = mxCreateString("PIL:pil:TargetIOError");
                                        prhs[1] = mxCreateDoubleScalar(PRINTF_ERROR);
                                        callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                        return;
                                    }
                                } else {
                                    uint8_T *pPrintBuff;
                                    pPrintBuff = mxMemUnitPtr;
                                    if (pPrintBuff[PRINTF_SIZE-1] == '\0') {
                                        mexPrintf("%s", pPrintBuff);
                                    } /* if */
                                } /* if */
                                mxMemUnitPtr = mxMemUnitPtr + PRINTF_SIZE;
                                break;
                            }
                            case RESPONSE_FOPEN: {
                                uint16_T FOPEN_FID;
                                uint16_T FOPEN_NAME_SIZE;
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FOPEN_FID;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FOPEN_NAME_SIZE;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                if (targetIOFdPtr != NULL) {
                                    /* check fid increments by 1 */
                                    if (targetIOFdPtr->fidOffset + 1 == FOPEN_FID) {
                                        targetIOFdPtr->fidOffset = FOPEN_FID;
                                        growTargetIOFd(targetIOFdPtr, targetIOFdPtr->fidOffset + 1);
                                        if (targetIOFdPtr->Fd != NULL)  {
                                            uint8_T *pFopenBuff;
                                            targetIOFdPtr->Fd[targetIOFdPtr->fidOffset] = NULL;
                                            pFopenBuff = mxMemUnitPtr;
                                            if (pFopenBuff[FOPEN_NAME_SIZE-1] == '\0') {
                                                FILE * tmpFd = NULL;
                                                tmpFd = fopen((char *) pFopenBuff,"w");
                                                if (tmpFd != NULL) {
                                                    /* save the file descriptor */
                                                    targetIOFdPtr->Fd[targetIOFdPtr->fidOffset] = tmpFd;
                                                } else {
                                                    {
                                                        mxArray * prhs[ 2 ];
                                                        prhs[0] = mxCreateString("PIL:pil:TargetIOFopenError");
                                                        prhs[1] = mxCreateString((char *) pFopenBuff);
                                                        callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                                        return;
                                                    }
                                                } /* if */
                                            } /* if */
                                        } /* if */
                                    } else {
                                        {
                                            mxArray * prhs[ 2 ];
                                            prhs[0] = mxCreateString("PIL:pil:TargetIOFopenFidError");
                                            prhs[1] = mxCreateDoubleScalar(FOPEN_FID);
                                            callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                            return;
                                        }
                                    } /* if */
                                } /* if */
                                mxMemUnitPtr = mxMemUnitPtr + FOPEN_NAME_SIZE;
                                break;
                            }
                            case RESPONSE_FPRINTF: {
                                uint8_T FPRINTF_ERROR;
                                uint16_T FPRINTF_FID;
                                uint16_T FPRINTF_SIZE;
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FPRINTF_ERROR;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint8_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FPRINTF_FID;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = (uint8_T *) &FPRINTF_SIZE;
                                    {
                                        size_t num_elements = 1;
                                        size_t bytes_consumed = num_elements * sizeof(uint16_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                if (FPRINTF_ERROR != TARGET_IO_SUCCESS) {
                                    {
                                        mxArray * prhs[ 2 ];
                                        prhs[0] = mxCreateString("PIL:pil:TargetIOError");
                                        prhs[1] = mxCreateDoubleScalar(FPRINTF_ERROR);
                                        callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                        return;
                                    }
                                } else {
                                    if (targetIOFdPtr != NULL) {
                                        if (targetIOFdPtr->size > FPRINTF_FID) {
                                            if (targetIOFdPtr->Fd[FPRINTF_FID] != NULL) {
                                                uint8_T *pFprintfBuff;
                                                pFprintfBuff = mxMemUnitPtr;
                                                if (pFprintfBuff[FPRINTF_SIZE-1] == '\0') {
                                                    fprintf(targetIOFdPtr->Fd[FPRINTF_FID], "%s", pFprintfBuff);
                                                } /* if */
                                            } /* if */
                                        } /* if */
                                    } /* if */
                                } /* if */
                                mxMemUnitPtr = mxMemUnitPtr + FPRINTF_SIZE;
                                break;
                            }
                            case RESPONSE_OUTPUT_DATA: {
                                {
                                    uint8_T * simDataMemUnitPtr;
                                    simDataMemUnitPtr = ( uint8_T *) mxGetData( plhs[ 0 ] );
                                    {
                                        size_t num_elements = 8;
                                        size_t bytes_consumed = num_elements * sizeof(real32_T);
                                        memcpy((void *) simDataMemUnitPtr, (void *) mxMemUnitPtr, bytes_consumed);
                                        mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                                    }
                                }
                                break;
                            }
                            default: {
                                {
                                    mxArray * prhs[ 2 ];
                                    prhs[0] = mxCreateString("PIL:pilverification:UnknownResponseId");
                                    prhs[1] = mxCreateDoubleScalar(responseId);
                                    callMATLAB( 0, NULL, 2, prhs, "DAStudio.error", 0);
                                    return;
                                }
                                break;
                            }
                        } /* switch */
                    } /* while */
                } /* if */
            } /* if */
        } /* if */
    }
}

static void mdlTerminate() {
    int isOkToTerminate;
    int commErrorOccurred = 0;

    {
        if (pCommErrorOccurred != NULL) {
            commErrorOccurred = *pCommErrorOccurred;
        } /* if */
    }

    {
        {
            mxArray *rhs[3];
            mxArray *lhs[1];
            const char * simulinkBlockPath = "/home/dmabeywa/Dropbox/Quadrotor State Estimation/ANU 8 state EKF/codegen/lib/quad_8state_kalman/quad_8state_kalman";
            rhs[ 0 ] = mxCreateString("@coder.connectivity.MATLABInterface.getSILPILInterface");
            rhs[ 1 ] = mxCreateDoubleScalar( 3 );
            rhs[ 2 ] = mxCreateString(simulinkBlockPath);
            callMATLAB( 1, lhs, 3, rhs, "rtw.pil.SILPILInterface.sfunctionIsOkToTerminateHook", 0);
            isOkToTerminate = (int) (*mxGetPr(lhs[0]));
            mxDestroyArray(lhs[0]);
        }
    }
    if (isOkToTerminate) {
        if (!commErrorOccurred) {
            {
                uint8_T * mxMemUnitPtr;
                mwSize dataInSize = 0;
                if (IOBufferPtr != NULL) {
                    growIOBuffer(IOBufferPtr, 5);
                    if (IOBufferPtr->data != NULL) {
                        mxMemUnitPtr = (uint8_T *) IOBufferPtr->data;
                        /* write command id */
                        *mxMemUnitPtr = 4;
                        mxMemUnitPtr++;
                        {
                            uint8_T * simDataMemUnitPtr;
                            uint32_T commandDataFcnid = 0;
                            simDataMemUnitPtr = (uint8_T *) &commandDataFcnid;
                            {
                                size_t num_elements = 1;
                                size_t bytes_consumed = num_elements * sizeof(uint32_T);
                                memcpy((void *) mxMemUnitPtr, (void *) simDataMemUnitPtr, bytes_consumed);
                                mxMemUnitPtr+=(bytes_consumed/sizeof(*mxMemUnitPtr));
                            }
                        }
                        {
                            int errorOccurred;
                            errorOccurred = commandDispatch(IOBufferPtr, 5, &dataInSize, 1);
                            if (errorOccurred) {
                                /* continue */
                            } /* if */
                        }
                    } /* if */
                } /* if */
            }
        } /* if */
        closeAndFreeTargetIOFd();
        {
            {
                mxArray *rhs[3];
                const char * simulinkBlockPath = "/home/dmabeywa/Dropbox/Quadrotor State Estimation/ANU 8 state EKF/codegen/lib/quad_8state_kalman/quad_8state_kalman";
                rhs[ 0 ] = mxCreateString("@coder.connectivity.MATLABInterface.getSILPILInterface");
                rhs[ 1 ] = mxCreateDoubleScalar( 3 );
                rhs[ 2 ] = mxCreateString(simulinkBlockPath);
                callMATLAB( 0, NULL, 3, rhs, "rtw.pil.SILPILInterface.sfunctionPILStopHook", 0);
            }
        }
    } /* if */
    if (rtIOStreamDataPtr != NULL) {
        {
            int errorStatus = rtIOStreamUnloadLib(&rtIOStreamDataPtr->libH);
            if (errorStatus) {
                mexErrMsgTxt( "rtIOStreamUnloadLib failed.");
            } /* if */
        }
        mxFree(rtIOStreamDataPtr->lib);
        mxDestroyArray(rtIOStreamDataPtr->MATLABObject);
        mxFree(rtIOStreamDataPtr);
    } /* if */
    if (IOBufferPtr != NULL) {
        mxFree(IOBufferPtr->data);
        mxFree(IOBufferPtr);
    } /* if */
    closeAndFreeTargetIOFd();
}

/* the gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[]) {
    int32_T idx[ 2 ];
    {
        int32_T dimVar[ 1 ] = { 8 };
        plhs[ 0 ] = mxCreateNumericArray( 1, dimVar, mxSINGLE_CLASS, mxREAL);
    }

    /* Register Terminate Function */
    mexAtExit(mdlTerminate);

    if (!firstTime) {
        firstTime = 1;
        mdlInitializeSizes(nlhs, plhs, nrhs, prhs);
        mdlStart(nlhs, plhs, nrhs, prhs);
    } /* if */

    emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
    if (nrhs < 0) {
        emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:TooFewInputsConstants", 9, mxCHAR_CLASS, 22, "quad_8state_kalman_sil", mxCHAR_CLASS, 18, "quad_8state_kalman", mxCHAR_CLASS, 18, "quad_8state_kalman");
    } /* if */
    if (nrhs != 10) {
        emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:WrongNumberOfInputs", 5, mxINT32_CLASS, 10, mxCHAR_CLASS, 18, "quad_8state_kalman");
    } else if (nlhs > 1) {
        emlrtErrMsgIdAndTxt(emlrtRootTLSGlobal, "EMLRT:runTime:TooManyOutputArguments", 3, mxCHAR_CLASS, 18, "quad_8state_kalman");
    } /* if */
    {
        /* Check Inputs are Valid */
        {
            int_T dimStr[ 2 ] = { 1, 2 };
            emlrtMsgIdentifier msgId;
            msgId.fIdentifier = "a";
            msgId.fParent = NULL;
            emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, &msgId, prhs[ 0 ], "single", false, 2U, dimStr);
        }
        {
            int_T dimStr[ 2 ] = { 1, 3 };
            emlrtMsgIdentifier msgId;
            msgId.fIdentifier = "g";
            msgId.fParent = NULL;
            emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, &msgId, prhs[ 1 ], "single", false, 2U, dimStr);
        }
        {
            int_T dimStr[ 1 ] = { 1 };
            emlrtMsgIdentifier msgId;
            msgId.fIdentifier = "delta_t";
            msgId.fParent = NULL;
            emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, &msgId, prhs[ 2 ], "single", false, 1U, dimStr);
        }
        {
            int_T dimStr[ 1 ] = { 1 };
            emlrtMsgIdentifier msgId;
            msgId.fIdentifier = "gyro_rp";
            msgId.fParent = NULL;
            emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, &msgId, prhs[ 3 ], "single", false, 1U, dimStr);
        }
        {
            int_T dimStr[ 1 ] = { 1 };
            emlrtMsgIdentifier msgId;
            msgId.fIdentifier = "gyro_y";
            msgId.fParent = NULL;
            emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, &msgId, prhs[ 4 ], "single", false, 1U, dimStr);
        }
        {
            int_T dimStr[ 1 ] = { 1 };
            emlrtMsgIdentifier msgId;
            msgId.fIdentifier = "v_xy";
            msgId.fParent = NULL;
            emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, &msgId, prhs[ 5 ], "single", false, 1U, dimStr);
        }
        {
            int_T dimStr[ 1 ] = { 1 };
            emlrtMsgIdentifier msgId;
            msgId.fIdentifier = "gb_rp";
            msgId.fParent = NULL;
            emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, &msgId, prhs[ 6 ], "single", false, 1U, dimStr);
        }
        {
            int_T dimStr[ 1 ] = { 1 };
            emlrtMsgIdentifier msgId;
            msgId.fIdentifier = "gb_y";
            msgId.fParent = NULL;
            emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, &msgId, prhs[ 7 ], "single", false, 1U, dimStr);
        }
        {
            int_T dimStr[ 1 ] = { 1 };
            emlrtMsgIdentifier msgId;
            msgId.fIdentifier = "acc_xy";
            msgId.fParent = NULL;
            emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, &msgId, prhs[ 8 ], "single", false, 1U, dimStr);
        }
        {
            int_T dimStr[ 1 ] = { 1 };
            emlrtMsgIdentifier msgId;
            msgId.fIdentifier = "k_1";
            msgId.fParent = NULL;
            emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, &msgId, prhs[ 9 ], "single", false, 1U, dimStr);
        }
    }


    mdlOutputs(nlhs, plhs, nrhs, prhs, CONSTANT_TID);

    emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}
