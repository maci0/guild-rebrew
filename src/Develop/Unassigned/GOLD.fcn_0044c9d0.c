#include <stdio.h>
#include <string.h>

int __cdecl d3_AppendVfsAssetPath(char*, char*);

/* ADDRESS: GOLD 0x0044c9d0 */
char __cdecl d3_FormatMeshAssetNames(char* a, char* b, int n, char* da, char* db)
{
	int i;
	int k;

	if (n < 0) {
		if ((*(unsigned char*) 0x5fbf78 & 0x80) != 0) {
			strcpy(da, a);
			strcat(da, "_s");
			if (b != 0 && db != 0) {
				strcpy(db, b);
				strcat(db, "_s");
			}
			return 1;
		}
	} else if (n == 0) {
		if ((*(int*) 0x5fbf78 & 0x7f) == 2) {
			for (i = 2; i >= 0; i--) {
				if (i > 0) {
					sprintf(da, "%s_%i", a, i - 1);
					if (b != 0 && db != 0) {
						sprintf(db, "%s_%i", b, i - 1);
					}
				} else {
					strcpy(da, a);
					if (b != 0 && db != 0) {
						strcpy(db, b);
					}
				}
				if (d3_AppendVfsAssetPath(da, ".bgf")) {
					return 1;
				}
			}
		} else {
			strcpy(da, a);
			if (b != 0 && db != 0) {
				strcpy(db, b);
			}
			return 1;
		}
	} else {
		if ((*(int*) 0x5fbf78 & 0x7f) == 2) {
			k = 2 - n;
		} else {
			k = n;
		}
		sprintf(da, "%s_%i", a, k - 1);
		if (b != 0 && db != 0) {
			sprintf(db, "%s_%i", b, k - 1);
		}
		return 1;
	}
	return 0;
}
