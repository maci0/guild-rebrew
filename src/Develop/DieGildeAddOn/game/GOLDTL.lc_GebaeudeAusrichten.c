#include <string.h>

extern unsigned char lpGebaeudePROT[];
extern unsigned char lpObjektePROT[];
extern unsigned short g_774970;

unsigned char *__cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char *__cdecl gm_FindNextFilteredEntity(void);
void __cdecl fcn_0051af00(char *, int, ...);
int __cdecl fcn_00526120(char *, int);

/* ADDRESS: GOLDTL 0x005988b0 */
int __cdecl lc_GebaeudeAusrichten(int a1, void *a2, int a3, int a4)
{
	char loc[0x4110];
	unsigned char *p;
	char *type_name;
	int type;

	type = a1;
	type_name = (char *) (lpGebaeudePROT + type * 0x24d + 1);
	p = 0;
	if (lpGebaeudePROT[type * 0x24d] == 2) {
		p = gm_StartFilteredEntitySearch(1, 5, 0);
		while (p != 0) {
			if (*p == a1) {
				fcn_0051af00(loc, 0x1a00, type_name);
				if (fcn_00526120(loc, 0) == 0) {
					return 0;
				}
				break;
			}
			p = gm_FindNextFilteredEntity();
		}
	}
	(void) a2;
	(void) a3;
	(void) a4;
	(void) p;
	memset(loc, 0, sizeof(loc));
	return 0;
}
