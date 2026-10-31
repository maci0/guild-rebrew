extern char g_7f4c00[];

#pragma pack(push, 2)
typedef struct {
	int a;
	int b;
	int c;
	short d;
} NAME14;
#pragma pack(pop)
extern char g_7f4ca0[];
extern char lpGebaeudePROT[];

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_00529160(int, int, unsigned int, int);
int __cdecl fcn_00546190(char*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_004c5da0(int, unsigned int, int, int, int, int);
int __cdecl fcn_00500bb0(int*, int, int, int);
float __cdecl fcn_00507e70(char*, char*, int);
float __cdecl gm_RandomFloat01(void);
int __cdecl gm_RandomMod(void);
void __cdecl fcn_005782f0(char*, int, int);
void __cdecl fcn_005b2f60(char*);
void __cdecl fcn_005b2fb0(char*);
float __cdecl gm_GetEntitySkill(char*, int);
void __cdecl fcn_005b3000(char*, char*, char*, int);
void __cdecl fcn_005b30c0(char*, char*, char*);

/* ADDRESS: GOLDTL 0x00578a10 */
int __cdecl fcn_00578a10(char* a1)
{
	char* p;
	char* q;
	char* r;
	char* o;
	char* m;
	char* n;
	char* tbl;
	unsigned char c;
	float t;
	int s;

	p = gm_LookupEntityRecordById(*(int*) (a1 + 0xb4));
	s = -1;
	if (*(int*) (a1 + 0x70) == s || *(int*) (a1 + 0x70) == -2) {
		goto tail1;
	}
	if (p == 0) {
		goto tail2;
	}
	switch (*(int*) (a1 + 0x70)) {
	case 0:
		fcn_00529160(0, 0, *(unsigned short*) p, (int) a1);
		*(int*) (a1 + 0x84) = s;
		return *(int*) (a1 + 0x70) = *(int*) (a1 + 0x70) + 1;
	case 1:
		q = gm_StartFilteredEntitySearch(1, 1, *(int*) (a1 + 0xac));
		if (q == 0) {
			*(int*) (a1 + 0x70) = s;
			return;
		}
		fcn_004c5da0(*(int*) (a1 + 0xb4), *(unsigned int*) (q + 1), s, 0, 1, 0x6a7ef4);
		return *(int*) (a1 + 0x70) = *(int*) (a1 + 0x70) + 1;
	case 2:
		gm_StartFilteredEntitySearch(1, 1, *(int*) (a1 + 0xac));
		p = gm_LookupEntityRecordById(*(int*) (a1 + 0xb4));
		if (p == 0) {
			*(int*) (a1 + 0x70) = s;
			return;
		}
		r = *(char**) (p + 0x184);
		if (*(int*) (r + 0x128) != 0) {
			*(NAME14*) (a1 + 0x52) = *(NAME14*) g_7f4c00;
			return fcn_00500bb0((int*) (a1 + 0x52), 0, 4, 0);
		}
		*(NAME14*) (a1 + 0x52) = *(NAME14*) g_7f4c00;
		fcn_00500bb0((int*) (a1 + 0x52), 1, 0, 0);
		n = gm_LookupEntityRecordById(*(int*) (a1 + 0xb0));
		m = gm_LookupEntityRecordById(*(int*) (a1 + 0xb4));
		t = fcn_00507e70(m, n, 2);
		if (n != 0) {
			if (t + gm_RandomFloat01() > 0.0) {
				o = *(char**) (m + 0x16c);
				c = *(unsigned char*) o;
				*(int*) (a1 + 0xbc) = 1;
				fcn_005782f0(n, *(unsigned char*) (lpGebaeudePROT + c * 0x24d + 0x247) * 2 + (unsigned short) gm_RandomMod() + *(signed char*) (o + 0x5c) / 50, 3);
				fcn_005b2f60(n);
				return *(int*) (a1 + 0x70) = *(int*) (a1 + 0x70) + 1;
			}
			fcn_005b2fb0(n);
			*(int*) (a1 + 0xbc) = 0;
		}
		return *(int*) (a1 + 0x70) = *(int*) (a1 + 0x70) + 1;
	case 3:
		m = gm_LookupEntityRecordById(*(int*) (a1 + 0xb4));
		if (m == 0) {
			*(int*) (a1 + 0x70) = s;
			return;
		}
		o = *(char**) (m + 0x16c);
		if (o == 0) {
			*(int*) (a1 + 0x70) = s;
			return;
		}
		fcn_004c5da0(*(int*) (a1 + 0xb4), *(unsigned int*) (o + 1), s, 0, 0, 0x6a7ef4);
		return *(int*) (a1 + 0x70) = *(int*) (a1 + 0x70) + 1;
	case 4:
		m = gm_LookupEntityRecordById(*(int*) (a1 + 0xb4));
		if (m == 0) {
			*(int*) (a1 + 0x70) = -1;
			return;
		}
		o = *(char**) (m + 0x16c);
		if (o == 0) {
			*(int*) (a1 + 0x70) = -1;
			return;
		}
		r = *(char**) (m + 0x184);
		if (*(int*) (r + 0x128) != 0) {
			*(NAME14*) (a1 + 0x52) = *(NAME14*) g_7f4c00;
			return fcn_00500bb0((int*) (a1 + 0x52), 0, 4, 0);
		}
		gm_StartFilteredEntitySearch(1, 1, *(int*) (a1 + 0xac));
		n = gm_LookupEntityRecordById(*(int*) (a1 + 0xb0));
		tbl = (char*) g_7f4ca0 + *(unsigned short*) (a1 + 8) * 0x21c;
		m = gm_LookupEntityRecordById(*(int*) (a1 + 0xb4));
		if (n == 0 || tbl == 0 || m == 0) {
			*(int*) (a1 + 0x70) = -1;
			return;
		}
		if (*(int*) (a1 + 0xbc) != 0) {
			t = *(float*) 0x6628a0 - gm_GetEntitySkill(m, 1);
			fcn_005b3000(tbl, m, n, t + gm_RandomFloat01() > 0.0 ? 0 : 1);
			*(int*) (a1 + 0x70) = -1;
			return;
		}
		fcn_005b30c0(tbl, m, n);
		*(int*) (a1 + 0x70) = -1;
		return;
	}
	return;
tail1:
	if (p != 0) {
		fcn_00529160(0, 0, *(unsigned short*) p, 0);
	}
tail2:
	return fcn_00546190(a1);
}
