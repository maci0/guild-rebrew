#pragma optimize("y", off)
#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
/* Client (GOLDTL) building allocator. Sibling of the server body in
 * Develop/DieGildeAddOn/game/spiel.c, which shares the field layout but not the
 * client's prototype-name selection. */

#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern pos14_7f4c00 gm_GameTime;

extern char* lpGebaeudePROT;
extern int gm_NextEntityId;
extern char g_14a6558[];
extern char* lpGebaeudeINST;
extern int lpObjektePROT;
extern char str_empty;
extern char s_699858[];
extern char s_69983c[];
extern char s_69982c[];
extern char s_699820[];

char* __cdecl gm_SearchStruct(void);
char* __cdecl gm_AllocObjekt(int, int, int);
char* __cdecl gm_AllocRaum(char*, int);
char* __cdecl gm_SetupEntityQuery(char*);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_CheckEntityType(char*);
void __cdecl gm_SetBuildingWorkerLimits(char*);
int __cdecl gm_GetBuildingTypeCategory(int);
void __cdecl gm_InitBuildingStartingGoods(char*);
char* __cdecl gv_AllocGraveyardField(char*);
void __cdecl gm_AssignBuildingResidents(char*, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl hp_AddProdSetting(char*);
char* __cdecl m_alloc(int, char*);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_0064d41a(char*, char*, ...);


#pragma pack(push, 1)
typedef struct {
	unsigned char unknown00[0x23];
	unsigned short components[0x40];
	unsigned char unknowna3[0x1aa];
} BuildingProto5043d0;

/* Building name table row: default name, then twelve instance names. */
typedef struct {
	char* name;
	char* unknown04;
	char* alias[12];
} BuildingNames5043d0;
/* SIZE 0x38 */

/* Plot record allocated for type 0x1e. */
typedef struct {
	unsigned char unknown00[0xd];
	unsigned char owner;
	unsigned char unknown0e[6];
	int value;
} PlotRecord5043d0;
/* SIZE 0x18 */
#pragma pack(pop)


/* Allocates a building entity for a prototype type and owner slot and fills in
 * its type defaults: name, the object ids of its prototype record, its room
 * layout, the owner's position block and the per-type fields. */
/* ADDRESS: GOLDTL 0x005043d0 */
char* __cdecl gm_AllocGebaeude(unsigned char geb_type, unsigned short owner)
{
	char tmp[0x100];
	char names[12][0x40];
	unsigned int type;
	BuildingProto5043d0* rec; BuildingProto5043d0* prototypes;
	char* geb;
	unsigned short comp;
	char* obj;
	OBJECT_PROTOTYPE* proto;
	unsigned char comp_type;
	char* q;
	int i;
	int n; int room_mode;
	char** alias;

	prototypes = (BuildingProto5043d0*) lpGebaeudePROT;
	if (prototypes == 0) {
		return 0;
	}
	room_mode = 0;
	geb = gm_SearchStruct();
	if (geb == 0) {
		return 0;
	}
	type = (unsigned char) geb_type;
	*geb = (char) geb_type;
	rec = &prototypes[type];
	{
	char buf[0x100];
	char msg[0x200];
	fcn_0064d41a(buf, s_699858, gm_NextEntityId, (int) type);
	*(int*) (geb + 1) = gm_NextEntityId;
	gm_NextEntityId = gm_NextEntityId + 1;
	*(unsigned short*) (geb + 0x25) = owner;
	*(unsigned short*) (geb + 0x27) = owner;
	*(unsigned short*) (geb + 0x29) = 0;
	*(int*) (geb + 0x2b) = 0;
	geb[0x2f] = 0;
	*(int*) (geb + 0x5d) = 0;
	*(int*) (geb + 0x61) = 0;
	*(int*) (geb + 0x30) = 0;
	*(int*) (geb + 0x39) = 0x7d00;
	*(int*) (geb + 0x3d) = 0x64;
	*(int*) (geb + 0x41) = 2;
	*(int*) (geb + 0x45) = 0x64;
	*(int*) (geb + 0x49) = 0x3f800000;
	geb[0x5c] = 0x64;
	*(int*) (geb + 0x95) = -1;
	if (owner != 0xffff) {
		if (((ENTITY_RECORD*) gm_EntitySlotTable)[owner].entity_state == 6) {
			hp_AddProdSetting(geb);
		}
	}
	memset(geb + 0x99, 0, 0x10);
	*(int*) (geb + 0xa5) = -1;
	*(int*) (geb + 0x99) |= 1;
	{
	char* fillStart;
	int fillBytes;

	fillBytes = 0x30; fillStart = geb + 0x65;
	__asm {
		mov edi, fillStart
		mov ebx, fillBytes
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short fill_end
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	fill_end:
		add ecx, ebx
		rep stosb
	}
	}
	n = 0;
	alias = ((BuildingNames5043d0*) g_14a6558)[type].alias;
	if (**alias != 0) {
		strcpy(geb + 5, ((BuildingNames5043d0*) g_14a6558)[type].name);
		i = 0;
	} else {
		geb[5] = str_empty;
		i = 0;
	}
	for (; i < 12; i++, alias++) {
		int j;

		if (**alias == 0) {
			continue;
		}
		strcpy(tmp, ((BuildingNames5043d0*) g_14a6558)[type].alias[i]);
		for (j = 0; j < 0x100; j++) {
			if (lpGebaeudeINST[j * 0xa9] != 0 && strcmp(lpGebaeudeINST + j * 0xa9 + 5, tmp) == 0) {
				break;
			}
		}
		if (j < 0x100) {
			continue;
		}
		if (strlen(tmp) < 0x20) {
			strcpy(names[n++], tmp);
		} else {
			fcn_0064d41a(msg, s_69983c, tmp);
		}
	}
	}
	if (n != 0) {
		strcpy(geb + 5, names[gm_RandomMod(n) & 0xffff]);
	}
	for (i = 0; i < 0x40; i++) {
		comp = rec->components[i];
		if (comp == 0) {
			break;
		}
		if (comp != 0xffff) {
			proto = &((OBJECT_PROTOTYPE *)lpObjektePROT)[comp & 0x7fff];
			comp_type = proto->kind;
			if (comp_type == 2 || comp_type == 6) {
				room_mode = 1;
			}
			if ((comp & 0x8000) != 0) {
				if (comp_type == 2 || comp_type == 6) {
					room_mode = 1;
					gm_AllocRaum(geb, comp & 0x7fff);
				} else if (room_mode == 0) {
					gm_AllocObjekt(*(int*) (geb + 1), comp & 0x7fff, 1);
				}
			}
		}
	}
	q = fcn_00502cd0(*(int*) (geb + 0x5d), 1, 4, 2);
	while (q != 0) {
		if (*(unsigned short*) q != 0xfd) {
			*(unsigned short*) (geb + 0x29) = *(unsigned short*) q;
			break;
		}
		q = gm_NextEntityQueryMatch();
	}
	q = gm_SetupEntityQuery(geb);
	if (q != 0) {
		*(unsigned short*) (geb + 0x29) = *(unsigned short*) q;
	}
	if (gm_CheckEntityType(geb) != 0) {
		*(int*) (geb + 0x30) = 0x1388;
	}
	switch (type) {
	case 4:
	case 5:
	case 6:
	case 7:
		*(pos14_7f4c00*) (geb + 0x69) = gm_GameTime;
		if (owner != 0xffff) {
			*(int*) (geb + 0x65) = ((ENTITY_RECORD*) gm_EntitySlotTable)[owner].entity_id;
		} else {
			*(int*) (geb + 0x65) = -1;
		}
		break;
	case 0x14:
	case 0x15:
	case 0x16:
		obj = gm_AllocObjekt(*(int*) (geb + 1), 0x1b5, 1);
		if (obj != 0) {
			obj[0x22] = 0;
			obj[0x1c] = (char) -1;
			obj[0x1d] = (char) -1;
			*(int*) (obj + 0x1e) = -1;
		}
		break;
	case 0x47:
		*(int*) (geb + 0x30) = 0x13880;
		break;
	case 0x1e:
		*(int*) (geb + 0x71) = (int) m_alloc(0x600, s_69982c);
		for (i = 0; i < 0x40; i++) {
			(*(PlotRecord5043d0**) (geb + 0x71))[i].owner = 0xff;
			(*(PlotRecord5043d0**) (geb + 0x71))[i].value = 0;
		}
	case 0x1f:
	case 0x20:
		*(int*) (geb + 0x30) = 0x64;
		*(int*) (geb + 0x49) = 0x3f4ccccd;
		break;
	case 0x35:
	case 0x36:
	case 0x37:
		*(int*) (geb + 0x65) = 0;
		*(unsigned short*) (geb + 0x69) = 0;
		*(unsigned short*) (geb + 0x6b) = 0;
		*(int*) (geb + 0x6d) = 0;
		break;
	case 0xb:
	case 0xc:
	case 0xd:
		*(int*) (geb + 0x65) = -1;
		break;
	case 0xe:
	case 0xf:
	case 0x10:
		*(int*) (geb + 0x65) = 0xa;
		*(int*) (geb + 0x69) = 3;
		*(int*) (geb + 0x6d) = 5;
		break;
	case 0x48:
	case 0x49:
	case 0x4a:
		*(int*) (geb + 0x65) = (int) gv_AllocGraveyardField(geb);
		gm_AssignBuildingResidents(geb, 3);
		break;
	case 0x4b:
	case 0x4c:
	case 0x4d:
		obj = m_alloc(0x3c, s_699820);
		*(int*) (geb + 0x65) = (int) obj;
		*(int*) obj = -1;
		break;
	default:
		break;
	}
	if (*geb == 0x26) {
		*(unsigned short*) (geb + 0x29) = 0x10e;
	}
	gm_SetBuildingWorkerLimits(geb);
	gm_GetBuildingTypeCategory((unsigned char) *geb);
	gm_InitBuildingStartingGoods(geb);
	return geb;
}
