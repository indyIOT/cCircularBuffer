/** ***********************************************
 * @file cLoggingDriver.c
 * @brief Implementation of the logging driver
 * @author Anthony Garza
 * @copyright All rights reserved 2026
*************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "commonMacros.h"
#include "cLoggingDriver.h"
#include "cLoggingDriverPub.h"
#include "cLoggingDriverVersion.h"
#include "cLoggingErrorCodes.h"
#ifndef ERROR_NONE
#define ERROR_NONE 0U
#endif

#ifndef NO_ERROR
#define NO_ERROR 0U
#endif

 
static const uint8_t moduleName[] = "ErrorDriver";


typedef struct
{
    uint16_t * readMemory; /* Pointer to a function that reads memory for the error driver */
    uint16_t * writeMemory; /* Pointer to a function for writing memory for the error driver */
    uint32_t memoryAddress; /* The starting address of the memory to be used by the error driver */
    uint16_t memorySizeInBytes; /* Size of the memory in bytes */
    uint8_t const * const moduleName; /* Name of the module */
    uint16_t moduleID; /* ID of the module */
    bool isInitialized; /* Whether or not the error driver has been initialized */
} sErrorDriverControlStruct_t;


static sErrorDriverControlStruct_t errorDriverControlStruct = { NULL, NULL, 0, 0, moduleName, 0, false };
static sErrorDriverControlStruct_t * const THIS = &errorDriverControlStruct;

/** 
 * @brief Get the name of the error module.
 * @return Pointer to a string containing the module name.
 */
uint8_t const * const getModuleName( void )
{
    return (uint8_t const * const)moduleName;
}

/**
 * @brief Get the version string of the error module.
 * @return Pointer to a string containing the version of the module.
 */
uint8_t const * getModuleVersionString( void )
{
    return (uint8_t const *)ERROR_DRIVER_VERSION_STRING;
}

/**
 * @brief Enter a spin loop after a debug assert failure.
 * @note A debugger can change keepSpinning to false to escape the loop.
 */
void cErrorDriverDebugAssertSpin( char const * const expression,
                                  char const * const fileName,
                                  unsigned int lineNumber )
{
    static volatile bool keepSpinning = true;

    AG_UNUSED( expression );
    AG_UNUSED( fileName );
    AG_UNUSED( lineNumber );

    while( keepSpinning )
    {
        AG_NOP();
    }
}

/**
 * @brief Function to initialize the error driver. This should be called before any other functions are used.
 * @param readMemory Pointer to a function that reads memory for the error driver. 
 *                   This is used to read the error information from the circular buffer.
 * @param writeMemory Pointer to a function for writing memory for the error driver.
 * @param memoryAddress The starting address of the memory to be used by the error driver.
 * @param memorySizeInBytes Size of the memory in bytes
 * @return an error structure if unsuccessful, or ERROR_NONE if successful.
 */
sErrorInfo_t initErrorDriver( uint16_t * readMemory, 
                                 uint16_t * writeMemory,
                                 uint32_t memoryAddress,
                                 uint16_t memorySizeInBytes )
{
    sErrorInfo_t retValue = BLANK_ERROR_STRUCT;
    if( THIS->isInitialized == false )
    {
        if( readMemory == NULL || writeMemory == NULL )
        {
            retValue = CREATE_ERROR( ERROR_NULL_POINTER, "" );
        }
        else
        {
            THIS->readMemory = readMemory;
            THIS->writeMemory = writeMemory;
            THIS->memoryAddress = memoryAddress;
            THIS->memorySizeInBytes = memorySizeInBytes;
            THIS->isInitialized = true;
        }
    }
    else
    {
        retValue = CREATE_ERROR( ERROR_ALREADY_INITIALIZED, "" );
    }
    return retValue;
}

/**
 * @brief Function to create an ERROR structure given an error code, line number, filename, 
 *        and an error message.
 * @param errorMessage A message describing the error
 * @param fileModuleEnum The module ID where the error occurred.
 * @param moduleName The name of the module where the error occurred.
 * @param lineNumber The line number where the error occurred
 */
sErrorInfo_t createErrorInfo( uint16_t errorCode, 
                                 uint16_t fileModuleEnum, 
                                 uint16_t lineNumber, 
                                 uint8_t const * const errorMessage, 
                                 uint8_t const * const moduleName )
{
    sErrorInfo_t retValue = BLANK_ERROR_STRUCT;
    sErrorInfo_t commonErrorInfo = BLANK_ERROR_STRUCT;
    size_t errorMessageLength = 0;
    uint8_t const * errorMessagePtr = errorMessage;
    /** Only fill this structure out if the error code is non-zero */
    if( errorCode != ERROR_NONE )
    {
        retValue._compact._errorCode = errorCode;
        retValue._compact._fileModuleEnum = fileModuleEnum;
        retValue._compact._lineNumber = lineNumber;
        /** Common Errors are just that. */
        if( errorCode < END_OF_COMMON_ERRORS )
        {
            commonErrorInfo = getCommonErrorMessageFromErrorCode( errorCode, errorMessagePtr );
        }

        /* If there was no error retrieving the common error message or it was not a common
           error. */
        if( ( commonErrorInfo._compact._errorCode == ERROR_NONE ) && 
            ( errorMessagePtr != NULL ) )
        {
            errorMessageLength = strnlen( (const char *)errorMessagePtr, MAX_ERROR_MESSAGE_LENGTH_BYTES - 1 );
            (void)memcpy( (void*)&retValue._errorMessage[0], (void*)errorMessagePtr, errorMessageLength );
            retValue._errorMessage[errorMessageLength] = '\0';
        }
        else
        {
            retValue = commonErrorInfo;
        }
    }

    return retValue;
}



