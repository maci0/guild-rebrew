#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#pragma pack(push, 1)
typedef struct {
	int day;
	unsigned short hour;
	int minute;
	unsigned short x;
} Clock;
/* SIZE 0xe */
#pragma pack(pop)

/* SIZE 0x21c */
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x164];
	char* home2;
	char* home;
	char pad174[0xa8];
} Player;

extern pos14_7f4c00 gm_GameTime;
extern Player g_7f4ca0[];
extern unsigned char* lpGebaeudePROT;
extern char g_6b5c60[];
extern float g_662cf8;
extern float g_665370;
extern float g_66430c;
extern float g_6628ac;
extern double g_662908;
extern double g_664f08;
extern float g_662a6c;

int __cdecl gm_RandomMod(unsigned short);
double __cdecl gm_RandomFloat01(void);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl gm_GetBuildingTechEffect(char*, int, int);
int __cdecl gm_ApplyRandomDisease(char*, int*, float*);
float __cdecl gm_GetEntityHealth(char*);
int __cdecl gm_HasActiveSpecialObject(char*, int);
int __cdecl he_IsEntityEligibleForIllness(unsigned short*);
void __cdecl he_ResolveAccidentOutcome(char*, char*, char*, char*, int, float);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
void __cdecl he_FreeAction(char*);

/* One step of the disease simulation: walks twelve towns in a pseudo-random
 * order and rolls an illness for each one. */
/* ADDRESS: GOLDTL 0x00556ed0 */
void __cdecl RunSimKrankheiten(char* s)
{
	float x;
	float y;
	int idx;
	int r;
	float g;
	float m;
	int count;
	float f;
	int steps[16];
	char buf[0x200];
	Player* p;
	char* home;
	char* home2;
	unsigned char* q;

	if (*(int*) (s + 0x70) == -2) {
		he_FreeAction(s);
		return;
	}
	io_FormatTextBuffer(buf, "-------> RunSimKrankheiten: calculating at <Day = %i Time = %i.2:%i.2>",
	    ((Clock*) &gm_GameTime)->day, ((Clock*) &gm_GameTime)->hour, ((Clock*) &gm_GameTime)->minute);
	if (*(int*) (s + 0xb0) == 0) {
		steps[0] = 1;
		steps[1] = 3;
		steps[2] = 5;
		steps[3] = 7;
		steps[4] = 11;
		steps[5] = 13;
		steps[6] = 17;
		steps[7] = 19;
		steps[8] = 0x2ed;
		steps[9] = 0x2ef;
		steps[10] = 0x2f3;
		steps[11] = 0x2f5;
		steps[12] = 0x2f9;
		steps[13] = 0x2fb;
		steps[14] = 0x2fd;
		steps[15] = 0x2ff;
		*(int*) (s + 0xb0) = steps[gm_RandomMod(16) & 0xffff];
		*(int*) (s + 0xac) = gm_RandomMod(0x300) & 0xffff;
	}
	if (*(int*) (s + 0x70) != 0) {
		return;
	}
	idx = *(int*) (s + 0xac);
	count = 12;
	do {
		p = &g_7f4ca0[idx];
		if (he_IsEntityEligibleForIllness((unsigned short*) p) != 0) {
			f = gm_RandomFloat01() * g_662cf8;
			home = g_7f4ca0[idx].home;
			y = 0.0f;
			x = 0.0f;
			if (home != 0) {
				if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) home].category == 2) {
					x = (float) gm_GetBuildingTechEffect(home, 8, 1) * g_665370 * g_66430c;
				} else {
					x = (float) gm_GetBuildingTechEffect(home, 8, 1) * 0.02f * g_66430c;
				}
			} else {
				y = g_664f08 - gm_RandomFloat01() * g_66430c * 0.5;
			}
			m = gm_HasActiveSpecialObject((char*) p, 0x2b3) != 0 ? y * 0.75f : y;
			if (f < m - x) {
				if (gm_ApplyRandomDisease((char*) p, &r, &g) != 0) {
					home2 = g_7f4ca0[idx].home2;
					if (home2 != 0 && *(unsigned short*) (home2 + 0x27) != 0xffff
					    && (q = (unsigned char*) &g_7f4ca0[*(unsigned short*) (home2 + 0x27)]) != 0) {
						he_ResolveAccidentOutcome(s, (char*) p, (char*) q, home2, r, g);
					} else {
						if (g < gm_GetEntityHealth((char*) p)
						    && (g_7f4ca0[idx].type == 6 || g_7f4ca0[idx].type == 7)) {
							io_FormatTextBuffer(buf, (char*) 0x163c, (char*) (r + 0x1632));
							he_PostEntityMessage(g_7f4ca0[idx].handle, -1, buf, 0, 0x5f7, g_6b5c60);
						}
					}
				}
			}
		}
		idx = (*(int*) (s + 0xb0) + idx) % 0x300;
		*(int*) (s + 0xb4) = *(int*) (s + 0xb4) + 1;
	} while (--count != 0);
	*(int*) (s + 0xac) = idx;
	if (*(int*) (s + 0xb4) >= 0x300) {
		*(unsigned short*) (s + 0x56) = 10;
		*(int*) (s + 0xac) = 0;
		*(int*) (s + 0xb0) = 0;
		*(int*) (s + 0xb4) = 0;
		*(int*) (s + 0x52) = *(int*) (s + 0x52) + 1;
		return;
	}
	gm_AddTime((pos14_7f4c00*) (s + 0x52), 0, 0x1e, 0);
	if (*(unsigned short*) (s + 0x56) >= 0x12) {
		*(int*) (s + 0x58) = 0;
		*(unsigned short*) (s + 0x56) = 10;
		*(int*) (s + 0x52) = *(int*) (s + 0x52) + 1;
	}
}
