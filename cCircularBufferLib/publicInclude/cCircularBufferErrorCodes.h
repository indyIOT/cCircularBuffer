/** ***********************************************
 * @file cCircularBufferErrorCodes.h
 * @brief Public interface for the circular buffer error codes
 * @author Anthony Garza
 * @copyright All rights reserved 2026
*************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "cErrorDriverPub.h"
#ifndef C_CIRCULAR_BUFFER_ERROR_CODES_H
#define C_CIRCULAR_BUFFER_ERROR_CODES_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ERROR_NONE
#undef ERROR_NONE
#endif

/** Enumeration of Common Error Codes These are always going to be the first error 
 * codes of every Errorcode Enumeration */
typedef enum 
{
} eCircularBufferErrorCodes_t;

/**
 * @brief Function to get the error message corresponding to a common error code.
 * @param errorCode The common error code to get the message for.
 * @param errorMessage Pointer to a buffer to store the error message.
 * @returns A pointer to the error message string.
 */
extern sErrorCompact_t getCircularBufferErrorMessageFromErrorCode( uint16_t const errorCode,
                                                        uint8_t const * errorMessage );

                                                       
#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* C_CIRCULAR_BUFFER_ERROR_CODES_H */