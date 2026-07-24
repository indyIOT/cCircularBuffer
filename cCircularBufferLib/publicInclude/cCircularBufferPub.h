/** ***********************************************
 * @file cCircularBufferPub.h
 * @brief Public interface for the circular buffer
 * @author Anthony Garza
 * @copyright All rights reserved 2026
*************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "cErrorDriverPub.h"
#ifndef C_CIRCULAR_BUFFER_PUB_H
#define C_CIRCULAR_BUFFER_PUB_H
#ifdef __cplusplus
extern "C" {
#endif

/*************************************** Typedefs **************************************/
typedef struct
{
    uint8_t * _bufferStartAddress;
    uint32_t _bufferSizeInBytes;
    uint32_t _headIndex;
    uint32_t _tailIndex;
    size_t _elementSizeInBytes;
    bool _isFull;
} cCircularBufferControlBlock_t;

/**************************** HELPER MACROS ***********************************************/
/**************************** External Function Prototypes ********************************/
/**
 * @brief Function to initialize the circular buffer.
 *        This function will initialize the circular buffer along with the file module enum, line number, log type, and logKey.
 * @param logKey The log key associated with this message
 * @param logMessage The message to log
 * @return an error info structure indicating success or failure.
 *
 */
extern sErrorInfo_t cCircularBufferInit( uint16_t fileModuleEnum, 
                                uint16_t lineNumber,
                                eLoggingType_t logType,
                                char const * const logMessage, 
                                ... );


/**
 * @brief Function to get the number of log messages currently stored in the logging driver.
 * @param errorCount Pointer to a uint16_t variable to store the number of log messages.
 * @return An error if one occurrred.
 */
extern sErrorInfo_t getLogCount( uint16_t * const errorCount );

/**
 * @brief Function to clear all log messages from the logging driver.
 */
extern void clearLogMessages( void );

/**
 * @brief Function to print all log messages currently stored in the logging driver.
 */
extern void printAllLogMessages( void );

/**
 * @brief Function to initialize the logging driver. This should be called before any other functions are used.
 * @param readMemory Pointer to a function that reads memory for the logging driver. 
 *                   This is used to read the log information from the circular buffer.
 * @param writeMemory Pointer to a function for writing memory for the logging driver.
 * @param stdOutputFunction Pointer to a function for outputting log messages to the standard output.
 * @param scratchBuffer Pointer to a buffer that can be used for temporary storage of log messages.
 * @param scratchBufferSize Variable that holds the size of the scratch buffer.
 * @param memoryAddress The starting address of the memory to be used by the logging driver.
 * @param memorySizeInBytes Size of the memory in bytes
 * @return sErrorInfo_t structure containing the error information if an error occurred.
 */
extern sErrorInfo_t initLoggingDriver( uint16_t * readMemory, 
                                       uint16_t * writeMemory,
                                       uint16_t * stdOutputFunction,
                                       uint8_t  * scratchBuffer,
                                       size_t   const scratchBufferSize,
                                       uint32_t const memoryAddress,
                                       uint16_t const memorySizeInBytes,
                                       uint16_t const maxLogCount );

/**
 * @brief Function to check if the logging driver has been initialized.
 * @return true if the logging driver is initialized, false otherwise.
 */
extern bool isLoggingDriverInitialized( void );


/**
 * @brief Function to get the ID of a registered module.
 * @param moduleName The name of the module
 * @param moduleId Pointer to store the module ID
 * @return an error uint16_t code if successful
 */
extern uint16_t getModuleId( const char * moduleName, uint16_t * const moduleId );

/**
 * @brief Function to get the version string of the module.
 * @return Pointer to a string containing the version of the module.
 */
extern uint8_t const * getModuleVersionString( void );

/**
 * @brief Function to get the logging module name as a string of uint8_t array.
 * @return Pointer to a string containing the module name.
 */
extern uint8_t const * const getModuleName( void );

#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif /* C_LOGGING_DRIVER_PUB_H */
