/* Name: utilError.h v0.0.0
 * Date: 2021-09-19
 * Intro: Header for error handling.
 */
#ifndef _UTILERROR_H
#define _UTILERROR_H 0x000000

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int32_t mirageErrno;
void miragePerror();

#define BMP_BASE_ERR 10000
#define BMP_INVALID_COLOR_DEPTH ((BMP_BASE_ERR) + 1)
#define BMP_MANDATORY_PALETTE ((BMP_BASE_ERR) + 2)


#ifdef __cplusplus
}
#endif

#endif
