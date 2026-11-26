#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c06;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern char g_7f4ca2[];
extern char g_7f4ca4[];
extern unsigned char g_773d75;
extern char* lpGebaeudePROT;
extern unsigned short* lpObjekteINST;
extern char* lpObjektePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
typedef struct BuildingRow489250 { unsigned char kind; char fields[0x246]; unsigned char capacity; char tail[5]; } BuildingRow489250;

int __cdecl gm_RandomMod(unsigned short);
int __cdecl gm_ResolveEntityById(void**, void**, int, int);
float __cdecl eval_ObjektPreis2Credits(int, int);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
void __cdecl cm_SendSellObjekt(int, int, int, int, char, int);
void __cdecl cm_SendCopyEntityData(void*);
int __cdecl sprintf(char*, char*, ...);

/* Master AI: counts the transports the master already runs, then reports a
   free transporter (job 0x135/0x136) to the server. */
/* ADDRESS: GOLDTL 0x00489250 */
void __cdecl ai_MeisterCollectTrans(char* e)
{
	void* found;
	int n136;
	char* slot;
	int count;
	int iter;
	void* out2;
	unsigned char pkt[0xf8];
	char buf[0x400];
	BUILDING_PROTOTYPE *row;
	char* u;
	int type;
	int id;
	int t;
	unsigned short v3;
	int flags;

	if (((unsigned short) g_7f4c04 % 2) != 0) {
		flags = *(int*) (e + 0x1b4);
		if (flags & 0x80) {
			return;
		}
		*(int*) (e + 0x1b4) = flags | 0x80;
		sprintf(buf, (char*) 0x67e488, *(unsigned short*) &g_7f4c04,
		        g_7f4c06);
		count = 0;
		n136 = 0;
		slot = (char*) lpObjekteINST;
		iter = 0x5008;
		do {
			v3 = *(unsigned short*) slot;
			if (v3 != 0 && *(char*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[(unsigned int) v3])) == 0x1d
			    && *(int*) (slot + 0x1c) == *(int*) (*(char**) (e + 0x16c) + 1)) {
				count++;
				if (v3 == 0x136) {
					n136++;
				}
				u = he_StartHandlungSearch(2, 0, 0xb, 3, *(int*) (*(char**) (e + 0x16c) + 1));
				while (u != 0) {
					if (*(int*) (u + 0xac) == *(int*) (slot + 2)) {
						goto next;
					}
					u = he_fn_Handlung();
				}
				u = he_StartHandlungSearch(2, 0, 0xf, 2,
				                 *(unsigned short*) (*(char**) (e + 0x16c) + 0x27));
				while (u != 0) {
					if (*(int*) (u + 0xac) == *(int*) (slot + 2)) {
						goto next;
					}
					u = he_fn_Handlung();
				}
				id = *(int*) (slot + 6);
				found = 0;
				while (found == 0 && id != -1) {
					if (!gm_ResolveEntityById(&found, &out2, 0, id)) {
						id = -1;
					} else if (out2 != 0) {
						id = *(int*) ((char*) out2 + 6);
					}
				}
				if (found != 0) {
					if (found != *(char**) (e + 0x16c)) {
						memset(pkt, 0, 0xf8);
						pkt[4] = 0xf;
						type = *(int*) (g_7f4ca4 +
						                *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c);
						pkt[0x36] = 2;
						*(int*) (pkt + 0x28) = gm_GameTime;
						*(int*) (pkt + 0x2c) = g_7f4c04;
						*(int*) (pkt + 0x30) = g_7f4c08;
						*(unsigned short*) (pkt + 0x34) = g_7f4c0c;
						*(int*) (pkt + 0x08) = type;
						*(int*) (pkt + 0x0c) = -1;
						*(int*) (pkt + 0x58) = *(int*) (slot + 2);
						*(int*) (pkt + 0x5c) = *(int*) ((char*) found + 1);
						*(int*) (pkt + 0x60) = *(int*) (*(char**) (e + 0x16c) + 1);
						*(int*) (pkt + 0xa0) = -1;
						cm_SendCopyEntityData(pkt);
						sprintf(buf, (char*) 0x67e438, (char*) found + 5, *(char**) (e + 0x16c) + 5);
					}
				}
			}
next:
			slot += 0x43;
			iter--;
		} while (iter != 0);
		type = **(unsigned char**) (e + 0x16c);
		row = &((BUILDING_PROTOTYPE *) lpGebaeudePROT)[type];
		if (row->category == 9) {
			if (count - n136 == 0) {
				t = (int) eval_ObjektPreis2Credits(0x134, 100);
				cm_RequestMoveCredits(-1, *(int*) (g_7f4ca4 +
				                         *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c),
				             (char) g_773d75, t);
				cm_SendSellObjekt(*(int*) (*(char**) (e + 0x16c) + 1), -1, 0x134, 1, (char) g_773d75, 0);
				sprintf(buf, (char*) 0x67e3fc, *(char**) (e + 0x16c) + 5);
				return;
			}
			if (n136 == 0) {
				if (*(int*) (e + 0x1c8) & 8) {
					return;
				}
				if (count >= row->level) {
					return;
				}
				if ((unsigned short) gm_RandomMod(0x2ee) >= 2) {
					return;
				}
				t = (int) eval_ObjektPreis2Credits(0x136, 100);
				if (*(int*) (e + 0x1b8) <= t * 2) {
					return;
				}
				t = (int) eval_ObjektPreis2Credits(0x136, 100);
				cm_RequestMoveCredits(-1, *(int*) (g_7f4ca4 +
				                         *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c),
				             (char) g_773d75, t);
				cm_SendSellObjekt(*(int*) (*(char**) (e + 0x16c) + 1), -1, 0x136, 1, (char) g_773d75, 0);
				sprintf(buf, (char*) 0x67e3a8, *(unsigned short*) &g_7f4c04,
				        g_7f4c06, *(char**) (e + 0x16c) + 5);
				*(int*) (e + 0x1c8) |= 8;
				return;
			} else {
				if (*(int*) (e + 0x1c8) & 8) {
					return;
				}
				if (count >= row->level) {
					return;
				}
				if ((unsigned short) gm_RandomMod(0x2ee) >= 2) {
					return;
				}
				id = ((unsigned short) gm_RandomMod(8) < 4) ? 0x135 : 0x136;
				t = (int) eval_ObjektPreis2Credits(id, 100);
				if (*(int*) (e + 0x1b8) <= t * 2) {
					return;
				}
				t = (int) eval_ObjektPreis2Credits(id, 100);
				cm_RequestMoveCredits(-1, *(int*) (g_7f4ca4 +
				                         *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c),
				             (char) g_773d75, t);
				cm_SendSellObjekt(*(int*) (*(char**) (e + 0x16c) + 1), -1, id, 1, (char) g_773d75, 0);
				sprintf(buf, (char*) 0x67e3a8, *(unsigned short*) &g_7f4c04,
				        g_7f4c06, *(char**) (e + 0x16c) + 5);
				*(int*) (e + 0x1c8) |= 8;
				return;
			}
		}
		if (count == 0) {
			if (*(char*) (g_7f4ca2 + *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c) == 6
			    || *(char*) (g_7f4ca2 + *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c) == 7) {
				if (!(*(int*) (e + 0x1b4) & 4)) {
					return;
				}
			}
			t = (int) eval_ObjektPreis2Credits(0x134, 100);
			cm_RequestMoveCredits(-1, *(int*) (g_7f4ca4 +
			                         *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c),
			             (char) g_773d75, t);
			cm_SendSellObjekt(*(int*) (*(char**) (e + 0x16c) + 1), -1, 0x134, 1, (char) g_773d75, 0);
			sprintf(buf, (char*) 0x67e3fc, *(char**) (e + 0x16c) + 5);
			return;
		}
		if (*(char*) (g_7f4ca2 + *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c) == 6
		    || *(char*) (g_7f4ca2 + *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c) == 7) {
			if (!(*(int*) (e + 0x1b4) & 4)) {
				return;
			}
		}
		if (*(int*) (e + 0x1c8) & 8) {
			return;
		}
		if (count >= row->level) {
			return;
		}
		if ((unsigned short) gm_RandomMod(0x2ee) >= 2) {
			return;
		}
		t = (int) eval_ObjektPreis2Credits(0x135, 100);
		if (*(int*) (e + 0x1b8) <= t * 2) {
			return;
		}
		t = (int) eval_ObjektPreis2Credits(0x135, 100);
		cm_RequestMoveCredits(-1, *(int*) (g_7f4ca4 + *(unsigned short*) (*(char**) (e + 0x16c) + 0x27) * 0x21c),
		             (char) g_773d75, t);
		cm_SendSellObjekt(*(int*) (*(char**) (e + 0x16c) + 1), -1, 0x135, 1, (char) g_773d75, 0);
		sprintf(buf, (char*) 0x67e3a8, *(unsigned short*) &g_7f4c04,
		        g_7f4c06, *(char**) (e + 0x16c) + 5);
		*(int*) (e + 0x1c8) |= 8;
	} else {
		*(int*) (e + 0x1b4) &= ~0x80;
	}
}
