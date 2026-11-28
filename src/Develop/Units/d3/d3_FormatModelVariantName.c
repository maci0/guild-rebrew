extern char g_67adf0[];
#include <stdio.h>
#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d3_AppendVfsAssetPath(char*, char*);

/* ADDRESS: GOLDTL 0x00449db0 */
/* ADDRESS: GOLDDE 0x00440490 */
char __cdecl d3_FormatModelVariantName(char* baseName, int altName, int mode, char* key, char* val)
{
	int i;

	if (mode < 0) {
		if ((*(unsigned char*) &d3_LODMode & 0x80) != 0) {
			strcpy(key, baseName);
			strcat(key, "_s");
			if (altName != 0 && val != 0) {
				strcpy(val, (char*) altName);
				strcat(val, "_s");
			}
			return 1;
		}
		return 0;
	}
	if (mode == 0) {
		if ((d3_LODMode & 0x7f) == 2) {
			i = 2;
			do {
				if (i > 0) {
					sprintf(key, (char*) &g_67adf0, baseName, i - 1);
					if (altName != 0 && val != 0) {
						sprintf(val, (char*) &g_67adf0, (char*) altName, i - 1);
					}
				} else {
					strcpy(key, baseName);
					if (altName != 0 && val != 0) {
						strcpy(val, (char*) altName);
					}
				}
				if (d3_AppendVfsAssetPath(key, ".bgf")) {
					return 1;
				}
			} while (--i >= 0);
			return 0;
		}
		strcpy(key, baseName);
		if (altName != 0 && val != 0) {
			strcpy(val, (char*) altName);
		}
	} else {
		if ((d3_LODMode & 0x7f) == 2) {
			i = 2 - mode;
		} else {
			i = mode;
		}
		sprintf(key, (char*) &g_67adf0, baseName, i - 1);
		if (altName != 0 && val != 0) {
			sprintf(val, (char*) &g_67adf0, (char*) altName, i - 1);
		}
	}
	return 1;
}
