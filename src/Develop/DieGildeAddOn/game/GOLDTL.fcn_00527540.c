#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern char* lpGebaeudePROT;
extern char* lpObjektePROT;
extern int g_1040494;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
void __cdecl fcn_00475f80(int);
void __cdecl fcn_00475fd0(int);
void __cdecl d2_UnlockSurface(int);
int __cdecl fcn_00475c10(char*);
char* __cdecl fcn_00475000(char*);
int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl fcn_00502cd0(int, int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_00475c10(char*);
int __cdecl fcn_00475780(void*, void*);
void __cdecl fcn_00476a50(int, int, int, void*);
int __cdecl fcn_005053c0(void*);
int __cdecl fcn_00469c30(short, short, int);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl strrchr(const char*, int);

/* ADDRESS: GOLDTL 0x00527540 */
void __cdecl fcn_00527540(void)
{
	char buf[256];
	char key[4];
	char white[3];
	char* prefix;
	char* p;
	char* q;
	char* r;
	unsigned char* v8;
	unsigned char* v20;
	int v3;
	int v13;
	int v14;
	int j;
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

	white[0] = (char) 0xff;
	white[1] = (char) 0xff;
	white[2] = (char) 0xff;
	prefix = (char*) 0x1015da0;
	v3 = 0;
	c = 0;

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
	q = (char*) (((char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned int) *v8]));
	p = q + 1;
	r = q;
	sprintf(buf, "%sbmp\\groundplans\\riss_%s.bmp", prefix, p);
	*(int*) 0x774680 = fcn_00475c10(buf);
	if (*(int*) 0x774680)
		goto have_image;
	v3 = gm_GetBuildingTypeCategory(*v8);
	if (v3 == 1) {
		if (*q == 0x16)
			sprintf(buf, "%sbmp\\groundplans\\riss_wirtshaus.bmp", prefix);
		else if (*q == 0x0e)
			sprintf(buf, "%sbmp\\groundplans\\riss_parfuemerie.bmp", prefix);
		else if (*q == 8)
			sprintf(buf, "%sbmp\\groundplans\\riss_tinkturei.bmp", prefix);
		else {
			sprintf(buf, "%sbmp\\groundplans\\riss_%s.bmp", prefix, p);
			*(int*) 0x774680 = fcn_00475c10(buf);
			if (*(int*) 0x774680)
				goto have_image;
			sprintf(buf, "%sbmp\\groundplans\\riss_handwerksbetrieb.bmp", prefix);
		}
		goto have_image;
	} else if (v3 == 3) {
		if (*q == 0x0f)
			sprintf(buf, "%sbmp\\groundplans\\riss_rathaus.bmp", prefix);
		else if (*q == 0x01)
			sprintf(buf, "%sbmp\\groundplans\\Riss_Arbeiterunterkunft.bmp", prefix);
		goto have_image;
	} else if (v3 == 5)
		sprintf(buf, "%sbmp\\groundplans\\riss_zunfthaus.bmp", prefix);
	else {
		if (*q == 0x05)
			sprintf(buf, "%sbmp\\groundplans\\riss_geldleihe.bmp", prefix);
		else if (*q == 0x09)
			sprintf(buf, "%sbmp\\groundplans\\riss_lagerhaus.bmp", prefix);
		else if (*q == 0x07)
			sprintf(buf, "%sbmp\\groundplans\\riss_kirche.bmp", prefix);
		else if (*q == 0x13)
			sprintf(buf, "%sbmp\\groundplans\\riss_stadtwache.bmp", prefix);
		else {
			sprintf(buf, "%sbmp\\groundplans\\riss_%s.bmp", prefix, p);
			v3 = fcn_00475c10(buf);
			*(int*) 0x774680 = v3;
			if (v3)
				goto have_image;
			sprintf(buf, "%sbmp\\groundplans\\riss_handwerksbetrieb.bmp", prefix);
		}
	}
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
	strcat(buf, "_C.bmp");
	*(int*) 0x774680 = fcn_00475c10(buf);
	v22 = 0;
	fcn_00475fd0(*(int*) 0x774680);
	v12 = *(int*) 0x774680;
	v3 = 0;
	if (!v12)
		return;
	for (; v3 < *(int*) (v12 + 8); v3++) {
		for (v14 = 0; v14 < *(int*) (v12 + 4); v14++) {
			fcn_00476a50(v14, v3, v12, key);
			if (fcn_00475780(key, white))
				goto next_pixel;
			fcn_00476a50(v14 + 1, v3, *(int*) 0x774680, key);
			for (i = 0, q = (char*) 0x6a24ec; q < (char*) 0x6a2519; q += 3, i++) {
				if (!fcn_00475780(key, q)) {
					if (i >= 0xf)
						goto next_pixel;
					v21 = 0;
					if (*r == 2) {
						v4 = (short*) fcn_00502cd0(*(unsigned int*) (v20 + 0x5d), 1, 4, 2);
						do {
							if (!v4)
								goto next_pixel;
							if (*v4 != 0xfd) {
								if (v21 == i)
									goto found;
								v21++;
							}
							v4 = (short*) gm_NextEntityQueryMatch();
						} while (1);
					}
					v7 = (short*) (r + 0x23);
					for (j = 0; j < 0x40; j++) {
						if (*v7 != -1) {
							v5 = *v7 & 0x7fff;
							c = *(char*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[v5]));
							if ((c == 2 || c == 6) && v5 != 0xfd) {
								if (v21 == i)
									goto found2;
								v21++;
							}
						}
						v7++;
					}
					goto next_pixel;
				}
			}
			goto next_pixel;
found2:
			v4 = (short*) fcn_00502cd0(*(unsigned int*) (v20 + 0x5d), 1, 0, v5);
found:
			if (v4 != 0) {
				v13 = fcn_005053c0(v4);
				if (v13 != -1) {
					v6 = fcn_00469c30(*(int*) 0x1040494 + v14 - 0x7e,
						v3 + 0x4c, v13);
					*(int*) (v22 * 4 + 0x7ea380) = v6;
					v22++;
				}
			}
next_pixel:
			v12 = *(int*) 0x774680;
		}
	}
	d2_UnlockSurface(v12);
}
