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
extern int d3_ActiveScene;
extern int g_6798d4;
extern int vfs_RootDir;
extern int d3_ActiveCamera;
extern char* g_774a68;
extern unsigned short gm_LocalPlayerSlot;
extern char gm_EntitySlotTable[];
extern int d2_DialogCloseRequested;
extern char io_LastKeyScancode;
extern short io_ActiveCursorX;
extern short io_ActiveCursorY;
extern int g_14ce8cc;
extern int g_14ce8d8;
extern int io_RightButtonReleased;
extern int g_14ab2e0;
extern int g_14ab2e4;
extern int g_14ab2d0;
extern int d2_CurrentElementId;
extern int g_6a2590;
extern int g_6a2594;
extern char str_empty;

int __cdecl gm_RandomMod(int);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned short* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl d2_ShowModalMessageBox(char*, int);
char* __cdecl _strupr(char*);
int __cdecl lc_GetBauplatzPrefix(int, char*);
int __cdecl d3_CollectUnusedSceneObjects(char*, void**);
void* __cdecl d3_FindNearestSceneObject(float*, void**);
void __cdecl d3_ComputeObjectYawToTarget(float*, char*);
void __cdecl d3_SetObjectGroundPosition(char*, float*);
void __cdecl d3_TransformPoint(char*, float*, float*);
void* __cdecl d3_LoadObjectFile(char*, int, int);
int __cdecl vfs_ResolvePath(char*, int, int, char*);
char __cdecl d3_AlignObjectToTerrain(char*, int, int);
void __cdecl d3_SetNodePosition(char*, float*);
void __cdecl d3_SetObjectRotation(char*, float*);
void __cdecl d3_ComputeObjectWorldBounds(float*, float*, char*);
void __cdecl d3_BuildEulerRotationMatrix(float*, float*);
void __cdecl d3_ApplyObjectAnimation(char*, char*, int);
void __cdecl d3_ObjectNoopStub(char*);
char __cdecl d3_DestroyObject(char*);
void __cdecl d3_SetSubtreeColor(char*, unsigned char, unsigned char, unsigned char);
void __cdecl d3_ChangeObjectTransparency(char*, char*, Key4_5988b0);
void __cdecl d2_ShowStatusBanner(char*);
void __cdecl ReportClientMessage(char*);
void __cdecl io_ClearInputButtonFlags(char);
void __cdecl UpdateSceneLighting(unsigned char);
int __cdecl gm_CalcBuildingCost(int, int);
char __cdecl d3sm_RaycastScreenPoint(int, int, int, int*, int*);
char __cdecl d3_GridPointToWorld(char*, int, int, float*);
void __cdecl d3_AnimateCameraToObject(char*);
int __cdecl d3_UpdateCameraController(void);
void* __cdecl d2_RunCityScrollMapDialog(int, char*, int, void*, int);
int __cdecl main_RunFrameLoop(int, int);

/* ADDRESS: GOLDTL 0x005988b0 */
/* ADDRESS: GOLDDE 0x0057e060 */
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
	f.pKontext = *(char**) (d3_ActiveScene + 0xb0);
	f.iErgebnis = 0;
	f.iRot = 0;
	f.iAnzahl = 0;
	f.pPrev = 0;
	f.fAbstand = 1.0e9f;
	f.iTypOffset = gebaeudetyp * 0x24d;
	if (lpGebaeudePROT[f.iTypOffset] == 2) {
		pSuch = (unsigned char*) gm_StartFilteredEntitySearch(2, 4, gm_LocalPlayerSlot, 5, 2);
		while (pSuch != 0) {
			if (*pSuch == gebaeudetyp) {
				io_FormatTextBuffer((char*) f.pObjekte, 0x17f2, gebaeudetyp * 14 + 0x48e);
				if (d2_ShowModalMessageBox((char*) f.pObjekte, 1) == 0) {
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
		if (f.fPruef != 0.0f) {
			sprintf(f.cPfad, (char*) 0x67f0c0, (char*) 0x7e1ae0, f.cName,
				(char) (f.fPruef + 65.0f - 1.0f));
		} else {
			sprintf(f.cPfad, (char*) 0x67f0ac, (char*) 0x7e1ae0, f.cName);
		}
		if (vfs_ResolvePath(f.cPfad, vfs_RootDir, vfs_RootDir, f.cTmp) != 0) {
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
		f.iKennung = (*(unsigned char*) (gm_EntitySlotTable + 9 + gm_LocalPlayerSlot * 0x21c) != 1);
	}
	if (lc_GetBauplatzPrefix(gebaeudetyp, f.cOgrName) == 0) {
		return 0;
	}
	f.iTreffer = d3_CollectUnusedSceneObjects(f.cOgrName, (void**) f.pListe);
	g_774a68 = (char*) f.pListe;
	f.fObjektPos[0] = 0.0f;
	f.fObjektPos[1] = 0.0f;
	f.fObjektPos[2] = 0.0f;
	if (f.iTreffer <= 0) {
		d2_ShowModalMessageBox((char*) g_14ab2e0, 0);
		return 0;
	}
	for (i = 0; i < f.iTreffer; i++) {
		pAktuell = f.pListe[i];
		if (pAktuell == 0) {
			continue;
		}
		d3_TransformPoint(pAktuell, (float*) (pAktuell + 0x4c), f.fPos);
		sprintf(f.cBafPfad, (char*) 0x6aa228, (char*) 0x7e1ae0);
		pTemp = (char*) d3_LoadObjectFile(f.cBafPfad, 0, 0);
		f.pObjekte[i] = pTemp;
		d3_ObjectNoopStub(pTemp);
		d3_SetNodePosition(pTemp, f.fPos);
		*(unsigned char*) (pTemp + 0x214) &= 0x7f;
		memset(&f.key, 0, sizeof(f.key));
		f.key.f.b0 = 1;
		f.key.id = 0x80;
		d3_ChangeObjectTransparency(pTemp, *(char**) (pTemp + 0x1cc), f.key);
		d3_SetSubtreeColor(pTemp, 0xc0, 0xa0, 0x80);
		dx = f.fPos[0] - *(float*) (d3_ActiveCamera + 0x4c);
		dy = f.fPos[1] - *(float*) (d3_ActiveCamera + 0x50);
		dz = f.fPos[2] - *(float*) (d3_ActiveCamera + 0x54);
		fDistanz = (float) sqrt(dx * dx + dy * dy + dz * dz);
		if (fDistanz < f.fAbstand) {
			f.fAbstand = fDistanz;
			f.pPrev = pTemp;
		}
		d3_ApplyObjectAnimation(pTemp, (char*) 0x6a2eb8, 1);
	}
	if (f.pPrev == 0) {
		d2_ShowModalMessageBox((char*) g_14ab2e0, 0);
		return 0;
	}
	UpdateSceneLighting(1);
	io_ClearInputButtonFlags(2);
	io_LastKeyScancode = 0x32;
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
			pAktuell = (char*) d3_LoadObjectFile(f.cPfad, 0, 0);
			if (pAktuell == 0) {
				goto laden_fehlgeschlagen;
			}
			*(unsigned char*) (pAktuell + 0x214) &= 0x7f;
			d3_SetNodePosition(pAktuell, f.fPos);
			d3_AlignObjectToTerrain(pAktuell, f.iRot, 0);
			pNaechster = (char*) d3_FindNearestSceneObject(f.fPos, (void**) f.pListe);
			f.pPrev = pNaechster;
			if (pNaechster != 0) {
				d3_ComputeObjectYawToTarget(f.fObjektPos, pNaechster);
				d3_SetObjectRotation(pAktuell, f.fObjektPos);
				d3_AlignObjectToTerrain(pAktuell, f.iRot, 0);
				d2_ShowStatusBanner((char*) 0x677c94);
				if (f.iRot != 1) {
					d3_SetSubtreeColor(pAktuell, 0x40, 0xc0, 0x40);
					f.iRot = 1;
				}
			}
			else {
				d2_ShowStatusBanner((char*) g_14ab2e4);
				if (f.iRot != 2) {
					d3_SetSubtreeColor(pAktuell, 0x40, 0x40, 0xc0);
					f.iRot = 2;
				}
			}
			*(int*) (pAktuell + 0x84) = 0;
			*(int*) (pAktuell + 0x88) = 0;
			*(int*) (pAktuell + 0x8c) = 0;
			*(int*) (pAktuell + 0x4c) = 0;
			*(int*) (pAktuell + 0x50) = 0;
			*(int*) (pAktuell + 0x54) = 0;
			d3_ComputeObjectWorldBounds(f.fMin, f.fMax, pAktuell);
			*(float*) (pAktuell + 0x4c) = f.fPos[0];
			*(float*) (pAktuell + 0x50) = f.fPos[1];
			*(float*) (pAktuell + 0x54) = f.fPos[2];
			*(float*) (pAktuell + 0x84) = f.fObjektPos[0];
			*(float*) (pAktuell + 0x88) = f.fObjektPos[1];
			*(float*) (pAktuell + 0x8c) = f.fObjektPos[2];
			f.iFlag48 = 0;
		}
		if (io_LastKeyScancode != 0x32) {
			if (g_14ce8d8 == 0) {
				goto platzieren;
			}
			if (d2_CurrentElementId != g_6a2590 && d2_CurrentElementId != g_6a2594) {
				goto platzieren;
			}
		}
		pTemp = (char*) d2_RunCityScrollMapDialog(8, 0, g_14ab2d0, 0, 0);
		if (pTemp != 0) {
			d3_AnimateCameraToObject(pTemp);
			d3_TransformPoint(pTemp, (float*) (pTemp + 0x4c), f.fPos);
			d3_SetObjectGroundPosition(pAktuell, f.fPos);
		}
		else {
			if (f.iFlag44 != 0) {
				d2_DialogCloseRequested = 1;
			}
		}
		f.iFlag44 = 0;
platzieren:
		pNaechster = (char*) d3_FindNearestSceneObject((float*) (pAktuell + 0x4c), (void**) f.pListe);
		if (pNaechster == 0) {
			f.pPrev = 0;
			d2_ShowStatusBanner((char*) g_14ab2e4);
			if (f.iRot != 2) {
				d3_SetSubtreeColor(pAktuell, 0x40, 0x40, 0xc0);
				f.iRot = 2;
			}
		}
		else if (pNaechster == f.pPrev) {
			d2_ShowStatusBanner((char*) 0x677c94);
			if (f.iRot != 1) {
				d3_SetSubtreeColor(pAktuell, 0x40, 0xc0, 0x40);
				f.iRot = 1;
			}
		}
		else {
			d3_TransformPoint(pNaechster, (float*) (pNaechster + 0x4c), f.fPos);
			f.pPrev = pNaechster;
			d3_SetNodePosition(pAktuell, f.fPos);
			d3_ComputeObjectYawToTarget(f.fAusrichtung, pNaechster);
			d3_SetObjectRotation(pAktuell, f.fAusrichtung);
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (pAktuell != 0) {
			if (f.fPruef < 90.0f) {
				*(unsigned char*) (pAktuell + 0x215) &= 0x7f;
				memset(&f.key, 0, sizeof(f.key));
				f.key.f.b0 = 1;
				f.key.id = 0xdd;
				d3_ChangeObjectTransparency(pAktuell, *(char**) (pAktuell + 0x1cc), f.key);
				*(unsigned char*) (pAktuell + 0x215) |= 0x80;
				if (pNaechster != 0) {
					if (f.iRot != 1) {
						d3_SetSubtreeColor(pAktuell, 0x40, 0xc0, 0x40);
						f.iRot = 1;
					}
				} else {
					if (f.iRot != 2) {
						d3_SetSubtreeColor(pAktuell, 0x40, 0x40, 0xc0);
						f.iRot = 2;
					}
				}
				f.fPruef = 90.0f;
			}
		}
		if (d3_UpdateCameraController() == 0) {
			d3sm_RaycastScreenPoint((int) f.pKontext, io_ActiveCursorX, io_ActiveCursorY, (int*) &f.fAbstand, &f.iKennung2);
			if (d3_GridPointToWorld(f.pKontext, f.iKennung2, *(int*) &f.fAbstand, f.fPos) != 0) {
				d3_SetNodePosition(pAktuell, f.fPos);
				d3_AlignObjectToTerrain(pAktuell, 1, 0);
			}
			f.fVec[0] = *(float*) (pAktuell + 0x84);
			f.fVec[1] = *(float*) (pAktuell + 0x88);
			f.fVec[2] = *(float*) (pAktuell + 0x8c);
			f.fVec[1] = f.fVec[1] + 3.1415927f;
			d3_BuildEulerRotationMatrix(f.fVec, f.fMatrix);
		}
		if (g_14ce8cc != 0 && pNaechster != 0) {
			i = gm_CalcBuildingCost((int) (gm_EntitySlotTable + gm_LocalPlayerSlot * 0x21c), gebaeudetyp);
			io_FormatTextBuffer(f.cText, 0x17ef, i, gebaeudetyp * 14 + 0x48e,
				*(int*) (lpGebaeudePROT + f.iTypOffset + 0x243));
			if (d2_ShowModalMessageBox(f.cText, 1) != 0) {
				f.iErgebnis = (int) f.pPrev;
			}
			else {
				f.iErgebnis = 0;
			}
			d2_DialogCloseRequested = 1;
		}
		if (main_RunFrameLoop((int) 0x5988b0, 0x657c7) == 0) {
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
		*name_aus = str_empty;
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
