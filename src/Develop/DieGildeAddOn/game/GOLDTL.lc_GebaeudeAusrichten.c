#include <stdio.h>
#include <string.h>
#include <math.h>

#pragma intrinsic(sqrt)

/* Key4 view: fcn_0043a3f0 takes the 4-byte colour key by value. */
typedef struct {
	unsigned char b0 : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char b3 : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} Bits8_5988b0;

typedef struct {
	unsigned char id;
	unsigned char b;
	Bits8_5988b0 f;
	unsigned char d;
} Key4_5988b0;

/* Frame view: native slots from the disassembly (frame 0x4110). */
typedef struct {
	int iRot;
	float fPruef;
	Key4_5988b0 key;
	char* pPrev;
	int iAnzahl;
	float fAbstand;
	int iKennung;
	float fPos[3];
	float fUnbenutzt;
	int iTypOffset;
	int iTreffer;
	int iErgebnis;
	float fObjektPos[3];
	int iFlag44;
	int iFlag48;
	char* pKontext;
	float fVec[3];
	int iKennung2;
	float fAusrichtung[3];
	float fMin[4];
	float fMax[4];
	char cName[0x100];
	char cOgrName[0x40];
	char cPfad[0x100];
	float fMatrix[16];
	char cBafPfad[0x104];
	char* pObjekte[256];
	char* pListe[256];
	char cTmp[0x100];
	char cText[0x400];
	char cGruppen[128][0x60];
} LC_GEBAEUDE_FRAME;

extern unsigned char* lpGebaeudePROT;
extern int g_67a370;
extern int g_6798d4;
extern int g_6b7fdc;
extern int g_6b8014;
extern int g_774a68;
extern short g_774970;
extern int g_774654;
extern char g_14cf950;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_14ce8cc;
extern int g_14ce8d8;
extern int g_14ce8e0;
extern int g_14ab2e0;
extern int g_14ab2e4;
extern int g_14ab2d0;
extern int g_67d370;
extern int g_6a2590;
extern int g_6a2594;
extern char g_6b5c60;

int __cdecl gm_RandomMod(int);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned short* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
char* __cdecl _strupr(char*);
int __cdecl fcn_00597ff0(int, char*);
int __cdecl fcn_00598150(char*, void**);
void* __cdecl fcn_005987c0(float*, void**);
void __cdecl fcn_00598740(float*, char*);
void __cdecl fcn_00598860(char*, float*);
void __cdecl fcn_00455350(char*, float*, float*);
void* __cdecl fcn_004488e0(char*, int, int);
int __cdecl fcn_0042f690(char*, int, int, char*);
char __cdecl fcn_004143b0(char*, int, int);
void __cdecl fcn_00438b40(char*, float*);
void __cdecl fcn_00438cb0(char*, float*);
void __cdecl fcn_00414960(float*, float*, char*);
void __cdecl fcn_00451900(float*, float*);
void __cdecl fcn_00412f10(char*, char*, int);
void __cdecl fcn_00415300(char*);
char __cdecl d3_DestroyObject(char*);
void __cdecl fcn_00414c90(char*, unsigned char, unsigned char, unsigned char);
void __cdecl fcn_0043a3f0(char*, char*, Key4_5988b0);
void __cdecl fcn_00533a40(char*);
void __cdecl ReportClientMessage(char*);
void __cdecl fcn_00412830(char);
void __cdecl UpdateSceneLighting(unsigned char);
int __cdecl fcn_0050d200(int, int);
char __cdecl fcn_0045bad0(int, int, int, int*, int*);
char __cdecl fcn_0045b920(char*, int, int, float*);
void __cdecl fcn_0052d4c0(char*);
int __cdecl fcn_0052c9b0(void);
void* __cdecl fcn_005bdc30(int, char*, int, void*, int);
int __cdecl fcn_005373e0(int, int);

/* ADDRESS: GOLDTL 0x005988b0 */
int __cdecl lc_GebaeudeAusrichten(int gebaeudetyp, char* name_aus)
{
	LC_GEBAEUDE_FRAME f;
	float dx;
	float dy;
	float dz;
	float fDistanz;
	char* pAktuell;
	char* pNaechster;
	char* pTemp;
	unsigned char* pSuch;
	int i;

	f.iFlag48 = 1;
	f.iFlag44 = 1;
	f.pKontext = *(char**) (g_67a370 + 0xb0);
	f.iRot = 0;
	f.iAnzahl = 0;
	f.pPrev = 0;
	f.iErgebnis = 0;
	f.fAbstand = 1.0e9f;
	f.iTypOffset = gebaeudetyp * 0x24d;
	if (lpGebaeudePROT[f.iTypOffset] == 2) {
		pSuch = (unsigned char*) gm_StartFilteredEntitySearch(2, 4, g_774970, 5, 2);
		while (pSuch != 0) {
			if (*pSuch == gebaeudetyp) {
				io_FormatTextBuffer(f.cTmp, 0x17f2, gebaeudetyp * 14 + 0x48e);
				if (fcn_00526120(f.cTmp, 1) == 0) {
					return 0;
				}
				break;
			}
			pSuch = (unsigned char*) gm_FindNextFilteredEntity();
		}
	}
	memset(f.pListe, 0, sizeof(f.pListe));
	memset(f.pObjekte, 0, sizeof(f.pObjekte));
	*(int*) f.cName = g_6798d4;
	strcat(f.cName, (char*) (lpGebaeudePROT + f.iTypOffset + 1));
	_strupr(f.cName + 2);
	pTemp = (char*) f.cGruppen;
	for (f.fPruef = 0.0f; f.fPruef < 128.0f; f.fPruef += 1.0f) {
		if (f.fPruef == 0.0f) {
			sprintf(f.cPfad, (char*) 0x67f0ac, (char*) 0x7e1ae0, f.cName);
		}
		else {
			sprintf(f.cPfad, (char*) 0x67f0c0, (char*) 0x7e1ae0, f.cName,
				(char) (f.fPruef + 65.0f - 1.0f));
		}
		if (fcn_0042f690(f.cPfad, g_6b7fdc, g_6b7fdc, f.cTmp) != 0) {
			strcpy(pTemp, f.cPfad);
			pTemp += 0x60;
			f.iAnzahl++;
		}
		else {
			if (f.fPruef != 0.0f) {
				break;
			}
		}
	}
	if (f.iAnzahl == 0) {
		sprintf(f.cName, (char*) 0x6aa240, f.cPfad);
		ReportClientMessage(f.cName);
		return 0;
	}
	f.iKennung = (unsigned short) gm_RandomMod(f.iAnzahl);
	if (lpGebaeudePROT[f.iTypOffset] == 0x21) {
		f.iKennung = (*(unsigned char*) (0x7f4ca9 + g_774970 * 0x21c) != 1);
	}
	if (fcn_00597ff0(gebaeudetyp, f.cOgrName) == 0) {
		return 0;
	}
	f.iTreffer = fcn_00598150(f.cOgrName, (void**) f.pListe);
	g_774a68 = (int) f.pListe;
	f.fObjektPos[0] = 0.0f;
	f.fObjektPos[1] = 0.0f;
	f.fObjektPos[2] = 0.0f;
	if (f.iTreffer <= 0) {
		fcn_00526120((char*) g_14ab2e0, 0);
		return 0;
	}
	for (i = 0; i < f.iTreffer; i++) {
		pAktuell = f.pListe[i];
		if (pAktuell == 0) {
			continue;
		}
		fcn_00455350(pAktuell, (float*) (pAktuell + 0x4c), f.fPos);
		sprintf(f.cBafPfad, (char*) 0x6aa228, (char*) 0x7e1ae0);
		pTemp = (char*) fcn_004488e0(f.cBafPfad, 0, 0);
		f.pObjekte[i] = pTemp;
		fcn_00415300(pTemp);
		fcn_00438b40(pTemp, f.fPos);
		*(unsigned char*) (pTemp + 0x214) &= 0x7f;
		memset(&f.key, 0, sizeof(f.key));
		f.key.f.b0 = 1;
		f.key.id = 0x80;
		fcn_0043a3f0(pTemp, *(char**) (pTemp + 0x1cc), f.key);
		fcn_00414c90(pTemp, 0xc0, 0xa0, 0x80);
		dx = f.fPos[0] - *(float*) (g_6b8014 + 0x4c);
		dy = f.fPos[1] - *(float*) (g_6b8014 + 0x50);
		dz = f.fPos[2] - *(float*) (g_6b8014 + 0x54);
		fDistanz = (float) sqrt(dx * dx + dy * dy + dz * dz);
		if (fDistanz < f.fAbstand) {
			f.fAbstand = fDistanz;
			f.pPrev = pTemp;
		}
		fcn_00412f10(pTemp, (char*) 0x6a2eb8, 1);
	}
	if (f.pPrev == 0) {
		fcn_00526120((char*) g_14ab2e0, 0);
		return 0;
	}
	UpdateSceneLighting(1);
	fcn_00412830(2);
	g_14cf950 = 0x32;
	pAktuell = 0;
	for (;;) {
		if (f.iFlag48 != 0) {
			f.fPruef = 0.0f;
			if (pAktuell != 0) {
				f.fPos[0] = *(float*) (pAktuell + 0x4c);
				f.fPos[1] = *(float*) (pAktuell + 0x50);
				f.fPos[2] = *(float*) (pAktuell + 0x54);
				f.fObjektPos[0] = *(float*) (pAktuell + 0x84);
				f.fObjektPos[1] = *(float*) (pAktuell + 0x88);
				f.fObjektPos[2] = *(float*) (pAktuell + 0x8c);
				d3_DestroyObject(pAktuell);
			}
			f.iKennung2 = (unsigned short) gm_RandomMod(f.iAnzahl);
			strcpy(f.cPfad, f.cGruppen[f.iKennung2]);
			pAktuell = (char*) fcn_004488e0(f.cPfad, 0, 0);
			if (pAktuell == 0) {
				goto laden_fehlgeschlagen;
			}
			*(unsigned char*) (pAktuell + 0x214) &= 0x7f;
			fcn_00438b40(pAktuell, f.fPos);
			fcn_004143b0(pAktuell, f.iRot, 0);
			pNaechster = (char*) fcn_005987c0(f.fPos, (void**) f.pListe);
			f.pPrev = pNaechster;
			if (pNaechster != 0) {
				fcn_00598740(f.fObjektPos, pNaechster);
				fcn_00438cb0(pAktuell, f.fObjektPos);
				fcn_004143b0(pAktuell, f.iRot, 0);
				fcn_00533a40((char*) 0x677c94);
				if (f.iRot != 1) {
					fcn_00414c90(pAktuell, 0x40, 0xc0, 0x40);
					f.iRot = 1;
				}
			}
			else {
				fcn_00533a40((char*) g_14ab2e4);
				if (f.iRot != 2) {
					fcn_00414c90(pAktuell, 0x40, 0x40, 0xc0);
					f.iRot = 2;
				}
			}
			*(int*) (pAktuell + 0x84) = 0;
			*(int*) (pAktuell + 0x88) = 0;
			*(int*) (pAktuell + 0x8c) = 0;
			*(int*) (pAktuell + 0x4c) = 0;
			*(int*) (pAktuell + 0x50) = 0;
			*(int*) (pAktuell + 0x54) = 0;
			fcn_00414960(f.fMin, f.fMax, pAktuell);
			*(float*) (pAktuell + 0x4c) = f.fPos[0];
			*(float*) (pAktuell + 0x50) = f.fPos[1];
			*(float*) (pAktuell + 0x54) = f.fPos[2];
			*(float*) (pAktuell + 0x84) = f.fObjektPos[0];
			*(float*) (pAktuell + 0x88) = f.fObjektPos[1];
			*(float*) (pAktuell + 0x8c) = f.fObjektPos[2];
			f.iFlag48 = 0;
		}
		if (g_14cf950 != 0x32) {
			if (g_14ce8d8 == 0) {
				goto platzieren;
			}
			if (g_67d370 != g_6a2590 && g_67d370 != g_6a2594) {
				goto platzieren;
			}
		}
		pTemp = (char*) fcn_005bdc30(8, 0, g_14ab2d0, 0, 0);
		if (pTemp != 0) {
			fcn_0052d4c0(pTemp);
			fcn_00455350(pTemp, (float*) (pTemp + 0x4c), f.fPos);
			fcn_00598860(pAktuell, f.fPos);
		}
		else {
			if (f.iFlag44 != 0) {
				g_774654 = 1;
			}
		}
		f.iFlag44 = 0;
platzieren:
		pNaechster = (char*) fcn_005987c0((float*) (pAktuell + 0x4c), (void**) f.pListe);
		if (pNaechster == 0) {
			f.pPrev = 0;
			fcn_00533a40((char*) g_14ab2e4);
			if (f.iRot != 2) {
				fcn_00414c90(pAktuell, 0x40, 0x40, 0xc0);
				f.iRot = 2;
			}
		}
		else if (pNaechster == f.pPrev) {
			fcn_00533a40((char*) 0x677c94);
			if (f.iRot != 1) {
				fcn_00414c90(pAktuell, 0x40, 0xc0, 0x40);
				f.iRot = 1;
			}
		}
		else {
			fcn_00455350(pNaechster, (float*) (pNaechster + 0x4c), f.fPos);
			f.pPrev = pNaechster;
			fcn_00438b40(pAktuell, f.fPos);
			fcn_00598740(f.fAusrichtung, pNaechster);
			fcn_00438cb0(pAktuell, f.fAusrichtung);
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (pAktuell != 0) {
			if (f.fPruef < 90.0f) {
				*(unsigned char*) (pAktuell + 0x215) &= 0x7f;
				memset(&f.key, 0, sizeof(f.key));
				f.key.f.b0 = 1;
				f.key.id = 0xdd;
				fcn_0043a3f0(pAktuell, *(char**) (pAktuell + 0x1cc), f.key);
				*(unsigned char*) (pAktuell + 0x215) |= 0x80;
				if (pNaechster == 0) {
					if (f.iRot != 2) {
						fcn_00414c90(pAktuell, 0x40, 0x40, 0xc0);
						f.iRot = 2;
					}
				}
				else {
					if (f.iRot != 1) {
						fcn_00414c90(pAktuell, 0x40, 0xc0, 0x40);
						f.iRot = 1;
					}
				}
				f.fPruef = 90.0f;
			}
		}
		if (fcn_0052c9b0() == 0) {
			fcn_0045bad0((int) f.pKontext, g_14ce8c0, g_14ce8c2, (int*) &f.fAbstand, &f.iKennung2);
			if (fcn_0045b920(f.pKontext, f.iKennung2, *(int*) &f.fAbstand, f.fPos) != 0) {
				fcn_00438b40(pAktuell, f.fPos);
				fcn_004143b0(pAktuell, 1, 0);
			}
			f.fVec[0] = *(float*) (pAktuell + 0x84);
			f.fVec[1] = *(float*) (pAktuell + 0x88);
			f.fVec[2] = *(float*) (pAktuell + 0x8c);
			f.fVec[1] = f.fVec[1] + 3.1415927f;
			fcn_00451900(f.fVec, f.fMatrix);
		}
		if (g_14ce8cc != 0 && pNaechster != 0) {
			i = fcn_0050d200((int) (0x7f4ca0 + g_774970 * 0x21c), gebaeudetyp);
			io_FormatTextBuffer(f.cText, 0x17ef, i, gebaeudetyp * 14 + 0x48e,
				*(int*) (lpGebaeudePROT + f.iTypOffset + 0x243));
			if (fcn_00526120(f.cText, 1) != 0) {
				f.iErgebnis = (int) f.pPrev;
			}
			else {
				f.iErgebnis = 0;
			}
			g_774654 = 1;
		}
		if (fcn_005373e0((int) 0x5988b0, 0x657c7) == 0) {
			break;
		}
		pNaechster = 0;
		f.iRot = 1;
	}
	if (f.iErgebnis != 0) {
		strcpy(name_aus, f.cGruppen[f.iKennung]);
	}
	else {
		d3_DestroyObject(pAktuell);
		*name_aus = g_6b5c60;
		pAktuell = 0;
	}
	for (i = 0; i < f.iTreffer; i++) {
		if (f.pObjekte[i] != 0) {
			d3_DestroyObject(f.pObjekte[i]);
		}
	}
	if (pAktuell != 0) {
		d3_DestroyObject(pAktuell);
	}
	return f.iErgebnis;

laden_fehlgeschlagen:
	sprintf(f.cName, (char*) 0x6aa1e8, f.cPfad);
	ReportClientMessage(f.cName);
	for (i = 0; i < f.iTreffer; i++) {
		if (f.pObjekte[i] != 0) {
			d3_DestroyObject(f.pObjekte[i]);
		}
	}
	return 0;
}
