#include <math.h>
#include <string.h>

extern int g_67dac0;
#include "Develop/DieGildeAddOn/game/game_data.h"


/* ADDRESS: GOLDTL 0x0047a570 */
int __cdecl d2_ComputeShapeSheetSizes(int shapeCount, int cellW, int cellH, int* countOut, int* sizesOut, int allowSplit)
{
	int tmp[8];
	int n;
	int size;
	int cols;
	int rows;
	int prod;
	int sheetCount;

	unsigned int i;
	int k;

	if (cellW > cellH) {
		n = cellW;
	}
	else {
		n = cellH;
	}
	if (shapeCount > 1) {
		cols = (int) (sqrt((double) shapeCount) + 1.0);
	}
	else {
		cols = shapeCount;
	}
	n = cols * n;
	i = n;
	size = 0;
	do {
		if (i <= 0) break; i >>= 1;
		size++;
	} while (size < 0x18);
	size--;
	if (size < 1) {
		size = 1;
	}
	size = 1 << size;
	if (size < n) {
		size += size;
	}
	if (g_67dac0 < size) {
		size = g_67dac0;
	}
	if ((float) n / (float) size < 0.9f && size > 0x40 && allowSplit != 0
	    && size / 2 > cellW && size / 2 > cellH) {
		size >>= 1;
	}
	cols = size / cellW;
	cols = (int) (1.0f > (float) cols + 0.5f ? 1.0f : (float) cols + 0.5f);
	rows = size / cellH;
	rows = (int) (1.0f > (float) rows + 0.5f ? 1.0f : (float) rows + 0.5f);
	prod = cols * rows;
	sheetCount = shapeCount / prod < 1 ? 1 : shapeCount / prod;
	for (k = 0; k < sheetCount; k++) {
		sizesOut[k] = size;
	}
	if (sheetCount >= 1 && shapeCount % prod != 0 && shapeCount > prod && allowSplit != 0) {

		d2_ComputeShapeSheetSizes(shapeCount % prod, cellW, cellH, &shapeCount, tmp, 0);
		if (shapeCount > 0) {
			memcpy(&sizesOut[sheetCount], tmp, shapeCount * 4);
			sheetCount += shapeCount;
		}
	}
	*countOut = sheetCount;
	return 1;
}
