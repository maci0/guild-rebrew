#include "Develop/DieGildeAddOn/game/building_prototype.h"
int __cdecl fcn_004e4730(char *);
int __cdecl d3_UpdateSeasonTextures(void);
int __cdecl fcn_00536bb0(void);
void __cdecl fcn_00459710(int, int);
int __cdecl sb_LoadSampleBank(char *, int);
void *__cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_004d5450(void *);
int __cdecl fcn_004c3100(char *, int);
int __cdecl fcn_0044c310(char *, char *);
int __cdecl fcn_0045b700(int, int, int);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004d1cf0(void);
void __cdecl cm_BeginCommandSync(void);
void __cdecl fcn_004c51f0(int, int, int, int, int, int);
void __cdecl cm_EndCommandSync(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_00535960(void);
int __cdecl fcn_004d1970(int, char *);
void __cdecl SelectTextureSet(int, int, int, int);
void __cdecl d3_TraverseSceneObjects(int, int, int, int);
int __cdecl fcn_0064d41a(char *, char *, ...);
int __cdecl fcn_00445600(int, int, int, char *);
void __cdecl fcn_00442c00(int, int);
void __cdecl gm_GenerateShuffledByteIndices(int, void *);
void __cdecl d3_SetSubtreeVisible(int, int);
int __cdecl fcn_00502cd0(int, int, ...);
void __cdecl gm_FindRecordById(int);
int __cdecl gm_NextEntityQueryMatch(void);
void __cdecl d3_TransformPoint(int, int, void *);
int __cdecl fcn_004488e0(char *, int, int);
void __cdecl fcn_00438b40(int, void *);
void __cdecl fcn_0045b290(int, int);
int __cdecl gm_GetBuildingTechEffect(int, int, int);
int __cdecl gm_CheckEntityType(void *);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern double g_664ef8;
extern int g_6b89c0; extern char g_6a2574[];
typedef struct BuildingRow4d1ff0 { unsigned char kind; char fields[0x24c]; } BuildingRow4d1ff0;
/* ADDRESS: GOLDTL 0x004d1ff0 */
void __cdecl fcn_004d1ff0(void *arg)
{
	int first;
	int cur;
	int base;
	int mode;
	int i;
	int j;
	int k;
	int n;
	int m;
	int *p;
	int ent;
	int e;
	int t;
	int r;
	int h;
	int containerId;
	int v10;
	int slots[3];
	char ids[12];
	unsigned char c;
	unsigned char ty;
	short *sp;
	int **pp;
	unsigned char *o;
	unsigned char pathbuf[0x10];
	char buf[0x100];
	o = (unsigned char *) arg;
	mode = 0xa;
	if ((o[0x7c] & 1) != 0) {
		if ((o[0x7c] & 8) != 0)
			fcn_004e4730("Kampfszenario_STADT.ed3");
		else
			fcn_004e4730("Kampfszenario_BERGPASS.ed3");
	} else {
		if ((o[0x7c] & 4) != 0) {
			fcn_004e4730("Kampfszenario_BERGPASS.ed3");
		} else {
			ent = (int) gm_StartFilteredEntitySearch(1, 1, *(int *) (o + 0x14));
			r = gm_CheckEntityType((void *) ent);
			ty = *(unsigned char *) ent;
			if (r != 0) {
				c = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[ty].category;
				if (c == 0x10) {
					fcn_004e4730("Kampfszenario_RAEUBERLAGER.ed3");
					mode = 0xf;
				} else if (c == 0xc)
					fcn_004e4730("Kampfszenario_STEINBRUCH.ed3");
				else if (c == 0xb)
					fcn_004e4730("Kampfszenario_WALDSTUECK.ed3");
				else if (c == 0xd)
					fcn_004e4730("Kampfszenario_MINE.ed3");
			} else {
				base = (int) &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[ty];
				c = ((BUILDING_PROTOTYPE*)base)->category;
				if (c == 4) {
					c = ((BUILDING_PROTOTYPE*)base)->level;
					if (c == 1)
						fcn_004e4730("Kampfszenario_SCHMUGGLERLOCH.ed3");
					else if (c == 2)
						fcn_004e4730("Kampfszenario_UNTERSCHLUPF.ed3");
					else if (c == 3)
						fcn_004e4730("Kampfszenario_DIEBESGILDE.ed3");
				} else if (c == 0x13) {
					c = ((BUILDING_PROTOTYPE*)base)->level;
					if (c == 1)
						fcn_004e4730("Kampfszenario_STADTWACHE_KLEIN.ed3");
					else if (c == 2)
						fcn_004e4730("Kampfszenario_STADTWACHE_MITTEL.ed3");
					else if (c == 3)
						fcn_004e4730("Kampfszenario_STADTWACHE_GROSS.ed3");
				}
			}
		}
	}
	cur = *(int *) (*(int *) &g_67a370 + 0xb0);
	d3_UpdateSeasonTextures();
	if (*(int *) &g_6b8300 != 0) {
		*(int *) (*(int *) &d3_CurrentContextIndex * 0x3dc + 0x1043378) = *(int *) 0x1043378;
		g_6b89c0 = *(int *) 0x1043378;
		fcn_00536bb0();
		fcn_00459710(g_6b89c0, 1);
	}
	for (p = (int *) 0x9ba2e0, i = 0x20; i != 0; i--)
		*p++ = -1;
	for (p = (int *) 0x9b4904; p < (int *) 0x9b4a44; p += 5) {
		p[1] = -1;
		p[0] = 0;
		p[2] = 0;
	}
	for (p = (int *) 0x9b8e40, i = 0x400; i != 0; i--)
		*p++ = 0;
	for (p = (int *) &g_9ba1c0, i = 0x40; i != 0; i--)
		*p++ = 0;
	for (p = (int *) 0x9b9ec0, i = 0x80; i != 0; i--)
		*p++ = 0;
	for (p = (int *) 0x9b4a40, i = 0x10e0; i != 0; i--)
		*p++ = 0;
	for (sp = (short *) 0x9b4a40; sp < (short *) 0x9b8dc0; sp += 0x10e)
		*sp = -1;
	for (p = (int *) 0x9b4848; p < (int *) 0x9b4908; p += 8)
		*p = -1;
	*(int *) 0x772ebc = sb_LoadSampleBank("kampf.sbf", 1);
	*(int *) 0x772ec0 = sb_LoadSampleBank("kampf\\armbrust.sbf", 1);
	*(int *) &g_772ec4 = sb_LoadSampleBank("kampf\\bombeundtopf.sbf", 1);
	*(int *) 0x772ec8 = sb_LoadSampleBank("kampf\\dolche.sbf", 1);
	*(int *) 0x772ecc = sb_LoadSampleBank("kampf\\pistole.sbf", 1);
	*(int *) 0x772ed0 = sb_LoadSampleBank("kampf\\schwerter.sbf", 1);
	first = (int) gm_StartFilteredEntitySearch(1, 1, *(int *) (o + 0x10c));
	if (first != 0)
		*(int *) 0x772f00 = fcn_004d5450((void *) first);
	switch (*(int *) 0x772f00) {
	case 2:
		*(int *) 0x772ed4 = fcn_004c3100("ARBEITER_KOMMENTARE_KLICK_DIEBE.sbf", 0);
		*(int *) 0x772edc = fcn_004c3100("K_C2C_ANGRIFF_DIEBE.sbf", 0);
		*(int *) 0x772ee4 = fcn_004c3100("K_C2C_BEFEHL_ERHALTEN_DIEBE.sbf", 0);
		*(int *) 0x772eec = fcn_004c3100("K_C2C_HOHN_DIEBE.sbf", 0);
		*(int *) 0x772ef4 = fcn_004c3100("K_C2C_SCHMERZ_DIEBE.sbf", 0);
		break;
	case 1:
		*(int *) 0x772ed4 = fcn_004c3100("ARBEITER_KOMMENTARE_KLICK_RAEUBER.sbf", 0);
		*(int *) 0x772edc = fcn_004c3100("K_C2C_ANGRIFF_RAEUBER.sbf", 0);
		*(int *) 0x772ee4 = fcn_004c3100("K_C2C_BEFEHL_ERHALTEN_RAEUBER.sbf", 0);
		*(int *) 0x772eec = fcn_004c3100("K_C2C_HOHN_RAEUBER.sbf", 0);
		*(int *) 0x772ef4 = fcn_004c3100("K_C2C_SCHMERZ_RAEUBER.sbf", 0);
		break;
	case 0:
		*(int *) 0x772ed4 = fcn_004c3100("ARBEITER_KOMMENTARE_KLICK_SOELDNER.sbf", 0);
		*(int *) 0x772edc = fcn_004c3100("K_C2C_ANGRIFF_SOELDNER.sbf", 0);
		*(int *) 0x772ee4 = fcn_004c3100("K_C2C_BEFEHL_ERHALTEN_SOELDNER.sbf", 0);
		*(int *) 0x772eec = fcn_004c3100("K_C2C_HOHN_SOELDNER.sbf", 0);
		*(int *) 0x772ef4 = fcn_004c3100("K_C2C_SCHMERZ_SOELDNER.sbf", 0);
		break;
	default:
		break;
	}
	first = (int) gm_StartFilteredEntitySearch(1, 1, *(int *) (o + 0x14));
	if (first != 0)
		*(int *) 0x772f04 = fcn_004d5450((void *) first);
	if (*(int *) 0x772f04 == *(int *) 0x772f00) {
		*(int *) 0x772ed8 = *(int *) 0x772ed4;
		*(int *) 0x772ee0 = *(int *) 0x772edc;
		*(int *) 0x772ee8 = *(int *) 0x772ee4;
		*(int *) 0x772ef0 = *(int *) 0x772eec;
		*(int *) 0x772ef8 = *(int *) 0x772ef4;
	} else if (*(int *) 0x772f04 == 2) {
		*(int *) 0x772ed8 = fcn_004c3100("ARBEITER_KOMMENTARE_KLICK_DIEBE.sbf", 0);
		*(int *) 0x772ee0 = fcn_004c3100("K_C2C_ANGRIFF_DIEBE.sbf", 0);
		*(int *) 0x772ee8 = fcn_004c3100("K_C2C_BEFEHL_ERHALTEN_DIEBE.sbf", 0);
		*(int *) 0x772ef0 = fcn_004c3100("K_C2C_HOHN_DIEBE.sbf", 0);
		*(int *) 0x772ef8 = fcn_004c3100("K_C2C_SCHMERZ_DIEBE.sbf", 0);
	} else if (*(int *) 0x772f04 == 1) {
		*(int *) 0x772ed8 = fcn_004c3100("ARBEITER_KOMMENTARE_KLICK_RAEUBER.sbf", 0);
		*(int *) 0x772ee0 = fcn_004c3100("K_C2C_ANGRIFF_RAEUBER.sbf", 0);
		*(int *) 0x772ee8 = fcn_004c3100("K_C2C_BEFEHL_ERHALTEN_RAEUBER.sbf", 0);
		*(int *) 0x772ef0 = fcn_004c3100("K_C2C_HOHN_RAEUBER.sbf", 0);
		*(int *) 0x772ef8 = fcn_004c3100("K_C2C_SCHMERZ_RAEUBER.sbf", 0);
	} else if (*(int *) 0x772f04 == 0) {
		*(int *) 0x772ed8 = fcn_004c3100("ARBEITER_KOMMENTARE_KLICK_SOELDNER.sbf", 0);
		*(int *) 0x772ee0 = fcn_004c3100("K_C2C_ANGRIFF_SOELDNER.sbf", 0);
		*(int *) 0x772ee8 = fcn_004c3100("K_C2C_BEFEHL_ERHALTEN_SOELDNER.sbf", 0);
		*(int *) 0x772ef0 = fcn_004c3100("K_C2C_HOHN_SOELDNER.sbf", 0);
		*(int *) 0x772ef8 = fcn_004c3100("K_C2C_SCHMERZ_SOELDNER.sbf", 0);
	}
	*(int *) 0x772f0c = fcn_0044c310("ub_STIEFEL", "ub_STIEFEL");
	if (cur == 0) {
		cur = fcn_0045b700(*(int *) &g_6b8300, *(int *) (*(int *) &g_67a370 + 0xb4), 2);
		*(int *) (*(int *) &g_67a370 + 0xb0) = cur;
		cur = *(int *) (*(int *) &g_67a370 + 0xb0);
	}
	*(float *) 0x9ba2c0 = (float) (*(float *) (cur + 0x10) * g_664ef8);
	*(int *) 0x6a2570 = 0x3e19999a;
	g_6a2574[0] = 0;
	*(void **) 0x772eb4 = (void *) o;
	fcn_004d1cf0();
	*(int *) &g_772e9c = gm_LookupEntityRecordById(*(int *) (o + 0x34));
	*(int *) 0x772e98 = gm_LookupEntityRecordById(*(int *) (o + 0x38));
	if (*(int *) (*(unsigned short *) &g_774970 * 0x21c + (unsigned long)&g_7f4ca4) == g_68b79c && (o[0x7c] & 1) != 0) {
		cm_BeginCommandSync();
		for (p = (int *) (o + 0x100), i = 3; i != 0; i--, p++) {
			if (*p != -1)
				fcn_004c51f0(-2, -1, 0x154, 1, *(unsigned char *) &g_773d75, 0);
		}
		cm_EndCommandSync();
		while (fcn_004c44c0() == 0)
			fcn_00535960();
	}
	for (p = (int *) (o + 0xc0), i = 0x10; i != 0; i--, p++) {
		if (*p != -1) {
			e = fcn_004d1970(*p, "dummy_OFFENSE_ENTRY");
			*(int *) (e + 0x16c) = *(int *) &g_772e9c;
			if (*(int *) (e + 0x184) != 0) {
				t = *(int *) (*(int *) (e + 0x184) + 0x34);
				SelectTextureSet(t, *(int *) (t + 0x1cc), 5, 1);
			}
		}
	}
	for (p = (int *) (o + 0x80), i = 0x10; i != 0; i--, p++) {
		if (*p != -1) {
			e = fcn_004d1970(*p, "dummy_DEFENSE_ENTRY");
			*(int *) (e + 0x16c) = *(int *) 0x772e98;
			*(float *) (*(int *) (e + 0x184) + 0x1a0) =
				(float) (*(float *) (*(int *) (e + 0x184) + 0x1a0) * 1.2);
			if (*(int *) (e + 0x184) != 0) {
				t = *(int *) (*(int *) (e + 0x184) + 0x34);
				SelectTextureSet(t, *(int *) (t + 0x1cc), 4, 1);
			}
		}
	}
	d3_TraverseSceneObjects(*(int *) &g_67a370, 0, 0xc0, 0x4d1fd0);
	base = *(int *) &g_67a370;
	pp = (int **) &ch_ContextCharacters;
	for (i = 0x20; i != 0; i--)
		*pp++ = 0;
	pp = (int **) &ch_ContextCharacters;
	for (sp = (short *) 0x9b4a40; sp < (short *) 0x9b8dc0; sp += 0x10e) {
		if (*sp != -1 && *(int *) (sp + 0xc2) != 0
			&& *(int *) (*(int *) (sp + 0xc2) + 0x88) == base)
			*pp++ = (int *) sp;
	}
	for (i = 1; i < 9; i++) {
		fcn_0064d41a(buf, "WARE_0%i", i);
		h = fcn_00445600(0, 0x40, 0, buf);
		if (h != 0)
			fcn_00442c00(h, 0);
	}
	i = 0;
	p = (int *) (o + 0x100);
	for (;;) {
		slots[0] = 0;
		slots[1] = 0;
		slots[2] = 0;
		gm_GenerateShuffledByteIndices(9, ids);
		i++;
		fcn_0064d41a(buf, "dummy_KARREN_0%i", i);
		h = fcn_00445600(0, 0x100, 0, buf);
		if (h != 0) {
			if (*p == -1) {
				d3_SetSubtreeVisible(h, 0);
			} else {
				ent = (int) fcn_00502cd0(0, 2, 7, 1, *p);
				if (ent == 0) {
					gm_FindRecordById(*p);
					*p = -1;
				} else {
					containerId = *(int *) (ent + 0x14);
					v10 = fcn_00502cd0(containerId, 1, 0, 0x1dd);
					n = 0;
					m = fcn_00502cd0(*(int *) (v10 + 0x14), 1, 5, containerId);
					while (n < 3 && m != 0) {
						slots[n] = m;
						n++;
						m = gm_NextEntityQueryMatch();
					}
					d3_TransformPoint(h, (int) h + 0x4c, pathbuf);
					switch (*(short *) ent) {
					case 0x134:
						fcn_0064d41a(buf, "%s*ob_KARREN_KLEIN_KAMPF.ogr", g_7e1ae0);
						break;
					case 0x135:
						fcn_0064d41a(buf, "%s*ob_KARREN_MITTEL_KAMPF.ogr", g_7e1ae0);
						break;
					case 0x136:
						fcn_0064d41a(buf, "%s*ob_KARREN_GROSS_KAMPF.ogr", g_7e1ae0);
						break;
					default:
						break;
					}
					e = fcn_004488e0(buf, 0, 0);
					fcn_00438b40(e, pathbuf);
					*(int *) (e + 0x204) = ent;
					for (j = 0; j < 3; j++) {
						fcn_0064d41a(buf, "WARE_0%i", ids[j] + 1);
						h = fcn_00445600(0, 0xc0, 0, buf);
						if (h != 0) {
							if (n - 1 < j)
								fcn_00442c00(h, 0);
							else {
								*(int *) (h + 0x204) = slots[j];
								fcn_00442c00(h, 1);
								*(int *) (h + 0x224) = 1;
							}
						}
					}
				}
			}
		}
		p++;
		if (i >= 3) {
			fcn_0045b290(*(int *) (*(int *) &g_67a370 + 0xb0), *(int *) &g_6b8300);
			i = 0;
			if (mode > 0) {
				n = *(int *) (cur + 0x20);
				for (k = 0; k < mode; k++) {
					m = k;
					while (m < n) {
						*(int *) (*(int *) (cur + 0x24) + ((n - 1) * k + m) * 0x1c) = 0xd;
						*(int *) (*(int *) (cur + 0x24) + (((n - k) - 1) * n + m) * 0x1c) = 0xd;
						*(int *) (*(int *) (cur + 0x24) + (n * m + k) * 0x1c) = 0xd;
						m++;
						*(int *) (*(int *) (cur + 0x24) + ((n * m - k) - 1) * 0x1c) = 0xd;
						n = *(int *) (cur + 0x20);
					}
				}
			}
			if (first != 0) {
				*(float *) 0x68b798 = (float) gm_GetBuildingTechEffect(first, 6, 1) + 1.4f;
			} else {
				*(float *) 0x68b798 = 1.0f;
			}
		}
	}
}
