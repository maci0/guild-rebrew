#include <string.h>

extern char* lpGebaeudePROT;
extern char* lpObjektePROT;
extern int g_1040494;

void __cdecl fcn_00475f80(int);
void __cdecl fcn_00475fd0(int);
void __cdecl fcn_00476060(int);
int __cdecl fcn_00475c10(char*);
char* __cdecl fcn_00475000(char*);
int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl fcn_00502cd0(int, int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_00475c10(char*);
int __cdecl fcn_00475780(void*, void*);
void __cdecl fcn_00476a50(int, int, int, void*);
int __cdecl fcn_005053c0(void*);
int __cdecl fcn_00469c30(int, int, int);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl strrchr(const char*, int);

/* ADDRESS: GOLDTL 0x00527540 */
void __cdecl fcn_00527540(void)
{
	char buf[256];
	char key[4];
	char* prefix;
	char* p;
	char* q;
	char* r;
	unsigned char* v8;
	unsigned char* v20;
	int v3;
	int v13;
	int v14;
	int v18;
	int v19;
	int v21;
	int v22;
	int v12;
	short* v4;
	short* v7;
	int v5;
	int v6;
	char c;
	int i;

	prefix = (char*) 0x1015da0;
	v3 = 0;
	c = 0;
	v18 = 0;
	v22 = 0;
	v19 = 0;
	v21 = 0;
	v13 = 0;
	v8 = *(int*) 0x7746c4 ? (unsigned char*) *(int*) 0x7746c4 : (unsigned char*) *(int*) 0x7746c8;
	v20 = v8;
	if (*(int*) 0x774680) {
		fcn_00475f80(*(int*) 0x774680);
		*(int*) 0x774680 = 0;
	}
	if (*(int*) 0x774684) {
		fcn_00475f80(*(int*) 0x774684);
		*(int*) 0x774684 = 0;
	}
	q = (char*) (lpGebaeudePROT + (unsigned int) *v8 * 0x24d);
	p = q + 1;
	r = q;
	sprintf(buf, "%sbmp\\groundplans\\riss_%s.bmp", prefix, p);
	*(int*) 0x774680 = fcn_00475c10(buf);
	if (*(int*) 0x774680)
		goto have_image;
	v3 = gm_GetBuildingTypeCategory(*v8);
	if (v3 == 1) {
		if (*q == 0x16)
			p = "%sbmp\\groundplans\\riss_wirtshaus.bmp";
		else if (*q == 0x0e)
			p = "%sbmp\\groundplans\\riss_parfuemerie.bmp";
		else if (*q == 8)
			p = "%sbmp\\groundplans\\riss_tinkturei.bmp";
		else {
			sprintf(buf, "%sbmp\\groundplans\\riss_%s.bmp", prefix, p);
			*(int*) 0x774680 = fcn_00475c10(buf);
			if (*(int*) 0x774680)
				goto have_image;
			p = "%sbmp\\groundplans\\riss_handwerksbetrieb.";
		}
		goto format_image;
	}
	if (v3 == 2) {
		if (*q == 0x0f)
			p = "%sbmp\\groundplans\\riss_rathaus.bmp";
		else if (*q == 0x01) {
			p = "%sbmp\\groundplans\\Riss_Arbeiterunterkunf";
			sprintf(buf, p, prefix);
		}
		goto format_image;
	}
	if (v3 == 3)
		p = "%sbmp\\groundplans\\riss_zunfthaus.bmp";
	else if (v3 == 5)
		p = "%sbmp\\groundplans\\riss_zunfthaus.bmp";
	else {
		switch (*q) {
		case 0x05:
			p = "%sbmp\\groundplans\\riss_geldleihe.bmp";
			break;
		case 0x09:
			p = "%sbmp\\groundplans\\riss_lagerhaus.bmp";
			break;
		case 0x07:
			p = "%sbmp\\groundplans\\riss_kirche.bmp";
			break;
		case 0x13:
			p = "%sbmp\\groundplans\\riss_stadtwache.bmp";
			break;
		default:
			sprintf(buf, "%sbmp\\groundplans\\riss_%s.bmp", prefix, p);
			v3 = fcn_00475c10(buf);
			*(int*) 0x774680 = v3;
			if (v3)
				goto have_image;
			p = "%sbmp\\groundplans\\riss_handwerksbetrieb.";
			break;
		}
	}
format_image:
	sprintf(buf, p, prefix);
have_image:
	v3 = *(int*) 0x774680;
	if (!v3) {
		v3 = fcn_00475c10(buf);
		*(int*) 0x774680 = v3;
		if (!v3)
			return;
	}
	fcn_00475fd0(v3);
	*(int*) 0x774684 = fcn_00475c10(buf);
	if (*(int*) 0x774680) {
		fcn_00475f80(*(int*) 0x774680);
		*(int*) 0x774680 = 0;
	}
	q = strrchr(buf, '.');
	*q = 0;
	strcpy(buf + strlen(buf), "_C.bmp");
	*(int*) 0x774680 = fcn_00475c10(buf);
	v22 = 0;
	fcn_00475fd0(*(int*) 0x774680);
	v12 = *(int*) 0x774680;
	if (!v12)
		return;
	for (v3 = 0; *(int*) (v12 + 8) > v3; v3++) {
		for (v14 = 0; v14 < *(int*) (v12 + 4); v14++) {
			fcn_00476a50(v14, v3, v12, key);
			if (fcn_00475780(key, &v8))
				continue;
			fcn_00476a50(v14 + 1, v3, *(int*) 0x774680, key);
			for (i = 0, q = (char*) 0x6a24ec; q < (char*) 0x6a2519; q += 3, i++) {
				if (!fcn_00475780(key, q)) {
					if (i > 0xe)
						goto next_row;
					v21 = 0;
					if (*r == 2) {
						v4 = (short*) fcn_00502cd0(*(unsigned int*) (v20 + 0x5d), 1, 4, 2);
						do {
							if (!v4)
								goto next_row;
							if (*v4 != 0xfd) {
								if (i == v21)
									goto found;
								v21++;
							}
							v4 = (short*) gm_NextEntityQueryMatch();
						} while (1);
					}
					v7 = (short*) (r + 0x23);
					for (i = 0; i <= 0x3f; i++) {
						if (*v7 != -1) {
							v5 = *v7 & 0x7fff;
							c = *(char*) (lpObjektePROT + v5 * 0x41);
							if ((c == 2 || c == 6) && v5 != 0xfd) {
								if (v21 == i)
									goto found2;
								v21++;
							}
						}
						v7++;
					}
					goto next_row;
				}
			}
		}
next_row:
		v14 = v19 + 1;
		v19 = v14;
		continue;
found:
		;
found2:
		v12 = fcn_005053c0(v4);
		if (v12 == -1)
			goto next_row;
		v6 = fcn_00469c30((short) (*(int*) 0x1040494 - 0x7e + v19),
			(short) (v18 + 0x4c), v12);
		*(int*) (v22 * 4 + 0x7ea380) = v6;
		v22++;
	}
	fcn_00476060(v12);
}
