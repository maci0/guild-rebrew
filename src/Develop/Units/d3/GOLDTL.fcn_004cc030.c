#include "Develop/Units/d3/d3_object.h"
#include <string.h>

extern int g_6b8010;
extern char g_6b5c60[];

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00413190(int);
void __cdecl fcn_004432d0(int, int);
char* __cdecl fcn_00442910(int, float*, float*, char*);



/* ADDRESS: GOLDTL 0x004cc030 */
int __cdecl fcn_004cc030(char* cmd, char* result)
{
	char* o;
	char* n;
	char* p;
	char* q;
	int saved;
	int keep;

	o = gm_LookupEntityRecordById(*(int*) (cmd + 0x10));
	if (o == 0 || *(char**) (o + 0x184) == 0)
		return 1;
	saved = g_6b8010;
	fcn_004432d0(fcn_00413190(*(int*) (*(char**) (o + 0x184) + 0x88)), 1);
	{
		float pos[4];
		float rot[3];

		pos[0] = *(float*) (*(char**) (*(char**) (o + 0x184) + 0x34) + 0x4c);
		pos[1] = *(float*) (*(char**) (*(char**) (o + 0x184) + 0x34) + 0x50);
		pos[2] = *(float*) (*(char**) (*(char**) (o + 0x184) + 0x34) + 0x54);
		rot[0] = *(float*) (*(char**) (*(char**) (o + 0x184) + 0x34) + 0x84);
		rot[1] = *(float*) (*(char**) (*(char**) (o + 0x184) + 0x34) + 0x88);
		rot[2] = *(float*) (*(char**) (*(char**) (o + 0x184) + 0x34) + 0x8c);
		keep = *(int*) (*(char**) (*(char**) (o + 0x184) + 0x34) + 0x204);
		n = fcn_00442910(0, pos, rot, cmd + 0x14);
	}
	if (n != 0) {
		strcpy(n, *(char**) (*(char**) (o + 0x184) + 0x34));
		strcpy(*(char**) (o + 0x184) + 8, cmd + 0x14);
		d3_DestroyObject((D3_OBJECT*) (*(char**) (*(char**) (o + 0x184) + 0x34)));
		*(char**) (*(char**) (o + 0x184) + 0x34) = n;
		*(int*) (*(char**) (*(char**) (o + 0x184) + 0x34) + 0x204) = keep;
		*(int*) (*(char**) (*(char**) (o + 0x184) + 0x34) + 0x48) = 0x3000000;
		*(unsigned char*) (*(char**) (*(char**) (o + 0x184) + 0x34) + 0x216) =
		    *(unsigned char*) (*(char**) (*(char**) (o + 0x184) + 0x34) + 0x216) & 0xfd | 1;
		*(int*) (*(char**) (*(char**) (o + 0x184) + 0x34) + 0x220) = 2;
		{
			char buf[0x100];

			strcpy(buf, cmd + 0x14);
			p = strrchr(buf, '_');
			if (p != 0) {
				p++;
				q = strrchr(p, '_');
				if (q != 0)
					*q = 0;
				strcpy(*(char**) (o + 0x184) + 0x130, p);
				p[-1] = 0;
				strcpy(*(char**) (o + 0x184) + 0x170, buf);
			} else {
				*(*(char**) (o + 0x184) + 0x130) = g_6b5c60[0];
			}
		}
		fcn_004432d0(saved, 1);
		if (result != 0) {
			result[0] = 2;
			result[1] = 1;
			*(char**) (result + 6) = o;
		}
		return 0;
	}
	fcn_004432d0(saved, 1);
	return 1;
}
