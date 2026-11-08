#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_7f4ca0[];

unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_005b2220(char*, char*, void*, int);
typedef struct {
	char pad[0x10];
	int tag;
	int value;
	int name;
} T_4cd090;

extern char* g_773da8;

int __cdecl fcn_00503fe0(int a, int b, int c);
int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
void __cdecl fcn_00549c50(int a, int b, int c, int d);

/* ADDRESS: GOLDTL 0x004ccf10 */
int __cdecl fcn_004ccf10(int cmd, char* result)
{
	void* entity;
	void* site;
	char* rec;
	int target;
	int i;

	if (result != (char*) 0x0) {
		*result = '\x02';
		result[1] = '\0';
		*(int*) (result + 6) = 0;
	}

	if (*(int*) (cmd + 0x10) == 0x636c6572) {
		entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x18));
		if (entity == (void*) 0x0) {
			return 1;
		}
		entity = gm_ff_Objekt(*(int*) ((char*) entity + 0x5d), 2, 6, 0, 0x12c);
		if (entity == (void*) 0x0) {
			return 1;
		}
		if ((*(int*)&g_7f4c00) - *(int*) ((char*) entity + 0x28) > 1) {
			*(int*) ((char*) entity + 0x1c) = -1;
			*(int*) ((char*) entity + 0x20) = -1;
			*(int*) ((char*) entity + 0x24) = -1;
			*(int*) ((char*) entity + 0x28) = (*(int*)&g_7f4c00) - 1;
		}
		else {
			return 1;
		}
	}
	else if (*(int*) (cmd + 0x10) == 0x62757920) {
		rec = gm_LookupEntityRecordById(*(int*) (cmd + 0x14));
		if (rec == 0) {
			return 1;
		}

		site = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x18));
		if (site == (void*) 0x0) {
			return 1;
		}
		entity = gm_ff_Objekt(*(int*) ((char*) site + 0x5d), 2, 6, 0, 0x12c);
		if (entity == (void*) 0x0) {
			return 1;
		}

		target = *(int*) (cmd + 0x1c);
		for (i = 0; i < 3; i++) {
			if (*(int*) ((char*) entity + 0x1c + i * 4) == target) {
				break;
			}
		}
		if (i >= 3) {
			return 1;
		}
		*(int*) ((char*) entity + 0x1c + i * 4) = -1;
		if (g_774970 == *(unsigned short*) ((char*) site + 0x27))
			fcn_005b2220(rec, g_7f4ca0 + g_774970 * 540, site, *(int*) (cmd + 0x20));
	}

	if (result != (char*) 0x0) {
		*result = '\x01';
	}
	return 0;
}

/* ADDRESS: GOLDTL 0x004cd090 */
int __cdecl fcn_004cd090(T_4cd090* s, char* out)
{
	int h;
	int p;
	int i;
	int* q;

	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	if (s->tag == 0x6a6f696e) {
		h = fcn_00503fe0(1, 1, s->name);
		if (h == 0) {
			return 1;
		}
		p = fcn_00502cd0(*(int*) (h + 0x5d), 2, 6, 0, 0x12d);
		if (p == 0) {
			return 1;
		}
		for (i = 0; i < 4; i++) {
			if (*(int*) (p + 0x1c + i * 4) == s->value) {
				return 1;
			}
		}
		for (i = 0; i < 4; i++) {
			if (*(int*) (p + 0x1c + i * 4) == -1) {
				break;
			}
		}
		if (i >= 4) {
			return 1;
		}
		if (out != 0) {
			out[0] = 1;
			fcn_00549c50(s->tag, h, p, s->value);
		}
		*(int*) (p + 0x1c + i * 4) = s->value;
		return 0;
	}
	if (s->tag == 0x6c656176) {
		h = fcn_00503fe0(1, 1, s->name);
		if (h == 0) {
			return 1;
		}
		p = fcn_00502cd0(*(int*) (h + 0x5d), 2, 6, 0, 0x12d);
		if (p == 0) {
			return 1;
		}
		for (i = 0, q = (int*) (p + 0x1c); i < 4; i++, q++) {
			if (*q == s->value) {
				break;
			}
		}
		if (i >= 4) {
			return 1;
		}
		if (out != 0) {
			out[0] = 1;
			fcn_00549c50(s->tag, h, p, s->value);
		}
		*(int*) (p + 0x1c + i * 4) = -1;
		return 0;
	}
	if (s->tag == 0x636c6572) {
		char* e;

		h = fcn_00503fe0(1, 1, s->name);
		if (h == 0) {
			return 1;
		}
		if (*(unsigned short*) (h + 0x27) != 0xffff) {
			e = g_7f4ca0 + *(unsigned short*) (h + 0x27) * 0x21c;
			if (e != 0 && e != g_773da8 &&
			    *(char*) (e + 8) != 0 &&
			    *(unsigned char*) (e + 2) != 0xf) {
				return 1;
			}
		}
		p = fcn_00502cd0(*(int*) (h + 0x5d), 2, 6, 0, 0x12d);
		if (p == 0) {
			return 1;
		}
		if (out != 0) {
			out[0] = 1;
			fcn_00549c50(s->tag, h, p, s->value);
		}
		q = (int*) (p + 0x1c);
		for (i = 4; i != 0; i--) {
			if (*q == s->value) {
				*q = -1;
			}
			q++;
		}
		return 0;
	}
	return 1;
}
