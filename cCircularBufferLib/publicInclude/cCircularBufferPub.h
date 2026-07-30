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
#include "commonTypes.h"
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
extern sErrorCompact_t cCircularBufferInit( uint16_t fileModuleEnum, 
                                uint16_t lineNumber,
                                eLoggingType_t logType,
                                char const * const logMessage, 
                                ... );


/**
 * @brief Function to get the error driver information. This will return a structure containing the error driver information.
 * @return sCommonDriverAccessorStruct_t structure containing the error driver information.
 */
extern sCommonDriverAccessorStruct_t const * const getCircularBufferDriverInfo( void );

#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif /* C_CIRCULAR_BUFFER_PUB_H */
