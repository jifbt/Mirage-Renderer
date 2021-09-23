/* Name: utilError.c v0.0.0
 * Date: 2021-09-19
 * Intro: Source for error handling.
 */
#include <stdio.h>
#include "utilError.h"
#if _UTILERROR_H != 0x000000
#error utilError.h version not support
#endif
int32_t mirageErrno;
void miragePerror() {
	switch (mirageErrno) {
		case BMP_INVALID_COLOR_DEPTH: puts("Color depth must be 1~8, 16, 24 or 32"); break;
		case BMP_MANDATORY_PALETTE: puts("Palette is mandatory for color depth <= 8"); break;
		default: printf("Unknown error: %ld", mirageErrno);
	}
}
