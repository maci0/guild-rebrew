#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_773d8c, g_773d94, g_868058, g_69938c;
extern unsigned int g_699390;
extern unsigned short g_699394;
extern unsigned char g_773d90, g_773d98, g_773d99, g_773d9a, g_699396[2];
extern unsigned short* g_773da4;
int __cdecl gm_GetEntityType(void*);

/* ADDRESS: GOLDTL 0x00502a20 */
int* __cdecl fcn_00502a20(void)
{
	char* p;
	char* q;
	int limit;
	int save;
	int next;
	char b;
	char arr;
	char hit;
	int v;

	hit = 0;
	if (!lpObjektePROT) {
		return 0;
	}
	p = (char*) g_773da4;
	if (!p) {
		return 0;
	}
	limit = g_773d8c;
	b = g_773d99;
	if (g_773d90) {
		g_773d90 = 0;
		if (b && *(int*) (p + 0x14)) {
			save = g_868058;
			*(int*) (save * 4 + 0x8f9500) = *(int*) (p + 0x14);
			save++;
			g_868058 = save;
		}
		else {
			save = g_868058;
		}
		if (*(unsigned short*) p) {
			g_773d94 = 1;
		}
		goto match;
	}
	arr = g_773d98;
	if (arr) {
		p += 0x43;
		g_773da4 = (unsigned short*) p;
		if (*(unsigned short*) p) {
			(g_773d94)++;
		}
		if (g_773d94 >= limit) {
			return 0;
		}
		while (*(unsigned short*) p == 0) {
			p += 0x43;
			g_773da4 = (unsigned short*) p;
		}
	}
	if (g_773d94 >= limit) {
		return 0;
	}
	if (!arr) {
		p = (char*) *(int*) (p + 0x3f);
		g_773da4 = (unsigned short*) p;
		if (!p) {
			if (!b) {
				return 0;
			}
			save = g_868058;
			if (!save) {
				return 0;
			}
			p = (char*) *(int*) (save * 4 + 0x8f94fc);
			save--;
			g_868058 = save;
			g_773da4 = (unsigned short*) p;
			if (*(int*) (p + 0x14)) {
				*(int*) (save * 4 + 0x8f9500) = *(int*) (p + 0x14);
				save++;
				g_868058 = save;
			}
			goto match;
		}
		if (b && *(int*) (p + 0x14)) {
			save = g_868058;
			*(int*) (save * 4 + 0x8f9500) = *(int*) (p + 0x14);
			save++;
			g_868058 = save;
			goto match;
		}
	}
	save = g_868058;
match:
	if (g_773d94 >= limit) {
		return 0;
	}
	do {
		if (g_773d9a) {
			hit = 1;
		}
		next = save;
		if (g_69938c != 0x7fff) {
			if ((int) *(unsigned short*) p != g_69938c) {
				goto fail;
			}
			hit = 1;
		}
		if (g_699390 != -1) {
			if (*(int*) (p + 2) != g_699390) {
				goto fail;
			}
			hit = 1;
		}
		if (g_699394 != 0xffff) {
			v = gm_GetEntityType(p);
			limit = g_773d8c;
			save = g_868058;
			b = g_773d99;
			p = (char*) g_773da4;
			if ((unsigned short) v != g_699394) {
				goto fail;
			}
			hit = 1;
		}
		if (*(char*) g_699396 != -1) {
			if (*(char*) (lpObjektePROT + *(unsigned short*) p * 0x41) != *(char*) g_699396) {
				goto fail;
			}
			hit = 1;
			goto found;
		}
		if (!hit) {
			goto fail;
		}
found:
		q = p;
		goto nextcheck;
fail:
		hit = 0;
		arr = g_773d98;
		if (arr) {
			p += 0x43;
			g_773da4 = (unsigned short*) p;
			if (*(unsigned short*) p) {
				(g_773d94)++;
			}
			if (g_773d94 >= limit) {
				goto nextcheck;
			}
			while (*(unsigned short*) p == 0) {
				p += 0x43;
				g_773da4 = (unsigned short*) p;
			}
			goto nextcheck;
		}
		p = (char*) *(int*) (p + 0x3f);
		g_773da4 = (unsigned short*) p;
		if (!p) {
			goto unlink;
		}
		if (b && *(int*) (p + 0x14)) {
			*(int*) (save * 4 + 0x8f9500) = *(int*) (p + 0x14);
			save++;
			g_868058 = save;
		}
nextcheck:
		if (p) {
			goto decide;
		}
unlink:
		if (!b) {
			return 0;
		}
		if (!save) {
			return 0;
		}
		p = (char*) *(int*) (save * 4 + 0x8f94fc);
		save--;
		g_868058 = save;
		g_773da4 = (unsigned short*) p;
		if (*(int*) (p + 0x14)) {
			*(int*) (save * 4 + 0x8f9500) = *(int*) (p + 0x14);
			save++;
			g_868058 = save;
		}
decide:
		if (hit) {
			return (int*) p;
		}
		if (g_773d94 > limit) {
			g_773da4 = 0;
			return 0;
		}
		if ((unsigned int) p < (unsigned int) ((char*) lpObjekteINST + 0x14f218)) {
			continue;
		}
		g_773da4 = 0;
		return 0;
	} while (1);
}
