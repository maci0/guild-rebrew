#include <stdio.h>
#include "Units/Error/error.h"
#include "game_structs.h"
#include "DieGildeAddOn/loadsave/loadsave.h"

#if !defined(REBREW_SERVER)
#include <string.h>
#include <stdlib.h>
#include "client_types.h"
#include "client_data.h"
#include "DieGildeAddOn/game/aemter.h"
#include "DieGildeAddOn/game/building_prototype.h"
#include "DieGildeAddOn/game/entity_record.h"
#include "DieGildeAddOn/game/spiel.h"
#include "DieGildeAddOn/game/game_data.h"
#endif

#if defined(REBREW_GOLD)
#include "gold_rec.h"
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
#include "GOLDTL.fcn_004e99e0_gconf.h"
#endif

extern char g_office_slots[0x3f0];
extern unsigned short g_current_hour;
void* __cdecl gm_LookupEntityRecordById(int entityId);
int __cdecl sprintf(char* buffer, const char* format, ...);
extern void __cdecl srv_InitBuildingTypeTable(void);

typedef struct {
	int type;
	float score;
	unsigned char rank;
	char pad9[3];
} OFFICE_PICK;
// SIZE 0xc

typedef struct {
	short lo;
	short hi;
	int cost_lo;
	int cost_hi;
	int a;
	int b;
	int c;
	int d;
} OFFICE_RANK_LIMITS;

int __cdecl amt_GetRoleTemplate(int role, OFFICE_ROLE_TEMPLATE* out);
int __cdecl amt_GetRankLimits(int role, OFFICE_RANK_LIMITS* out);

#if defined(REBREW_SERVER)
extern void __cdecl LogMessageInternal(const char* module, int line, const char* text, int type);
extern char* g_entity_type_table;
unsigned char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int kind);
int __cdecl amt_GetSlotByRole(int role, OFFICE_SLOT* out);
int __cdecl amt_ListSlotsOfGroup(int group, int max, OFFICE_SLOT* out);
int __cdecl amt_IsNextRoleStep(unsigned char* entity, int role);
#endif

#if !defined(REBREW_SERVER)
extern Rec18_68da68 g_68da68[];
extern char g_68de84[];
extern char g_6b5c60[];
extern float g_6628a8;
extern char* gm_CityEntity;

typedef struct {
	unsigned char c0;
	char pad1[3];
	int id;
	unsigned char kind;
	char pad9[7];
	unsigned char f10;
	char pad11[3];
	int f14;
} rec18_4e8240;

typedef struct {
	unsigned char id;
	char pad1[3];
	int holder;
	unsigned char type;
	char pad9[3];
	int count;
	unsigned char state;
	char pad11[7];
} Slot_4e8d10;

typedef struct {
	int x0;
	int x4;
	unsigned char rank;
	char pad9[15];
} Tmpl_4e8d10;

struct job_4e8810 {
	unsigned char key;
	char pad1[3];
	int id;
	unsigned char slot;
	char pad9[15];
};

typedef struct {
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
} fcn_004e90d0_E;

typedef struct {
	unsigned char a;
	int b;
	char c;
	int d;
	char e;
	int f;
} Rec_4ea9a0;

typedef struct {
	char a;
	int b;
	char c;
	int d;
	char e;
	int f;
} Rec_4ec520;

int __cdecl cm_SendExecuteOffice(char*);
int __cdecl cm_SendSwapOfficeOccupants(char*);
void __cdecl amt_NotifyOfficeSwap(char*, char*, char*);
int __cdecl amt_FindOfficeSlotByType(int type, Rec18_68da68* out);
int __cdecl amt_FindOfficeSlotByKey(unsigned char key, void* dst);
int __cdecl amt_CollectOfficeSlotsByGroup(int group, int max, OFFICE_SLOT* out);
int __cdecl amt_GetRoleLevel(int office_id);
void __cdecl amt_NotifyOfficeAppointed(void*, int);
void __cdecl amt_NotifyOfficeLost(void*, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
void __cdecl cm_RequestCopyEntityData(int a, int b, int value, int flag);
void __cdecl cm_RequestTransferCurrencyNoKill(int a1, int a2, char a3, int a4);
void __cdecl cm_BeginPacketFieldDelta(char* a1, int a2);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_RequestChangeBits(int handle, int a, int b, int c, int d);
void __cdecl gm_ModifyHealth(int id, int amount);
void* __cdecl gm_StartFilteredEntitySearch(int a1, int a2, int a3);
void* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl he_PostEntityMessage(int a1, int a2, void* p, int a4, int a5, void* p6);
unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
char* __cdecl gm_AddObjekt(void);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
#undef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
int __cdecl amt_IsNextOfficeStep(void* rec, int role);
typedef struct {
	unsigned char c0;
	char pad1[3];
	int id;
	unsigned char kind;
	char pad9[3];
	int fc;
	int f10;
	int f14;
} Rec18_4e93d0;
#endif

#if defined(REBREW_GOLD)
typedef struct {
	unsigned char id;
	char pad1[3];
	int owner;
	unsigned char kind;
	char pad9[3];
	int count;
	unsigned char state;
	char pad11[3];
	int holder;
} OFFICESLOT;
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
extern int g_9a9620[10];
extern Rec18_68da68 g_9a9228[];
extern int g_6b7fdc;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_67f0ac[];
extern char g_68de2c[];

typedef struct OFFICE_SLOT_VIEW {
	unsigned char type;
	char pad_001[3];
	int id;
	unsigned char tag;
	char pad_009[3];
	int count;
	unsigned char state;
	char pad_011[7];
} OFFICE_SLOT_VIEW;

typedef struct OFFICE_ROLE_VIEW {
	int f0;
	int f1;
	int f2;
	int f3;
	int f4;
	int f5;
} OFFICE_ROLE_VIEW;

typedef struct {
	unsigned char f00;
	char pad01[3];
	int f04;
	unsigned char f08;
	char pad09[3];
	int f0c;
	unsigned char f10;
	char pad11[3];
	int f14;
} OFFICE_ASSIGN_SLOT;

typedef struct {
	int x0;
	int x1;
	int x2;
	int x3;
	int x4;
	int x5;
} OFFICE_SLOT_EXPAND;

typedef struct {
	int f0;
	int id;
	unsigned char c8;
	int n;
	unsigned char type;
	int ref;
} EVT_ARG;

typedef struct Rec_4eafe0 {
	unsigned char id;
	char pad1[3];
	int x4;
	unsigned char type;
	char pad9[3];
	int xc;
	unsigned char x10;
	char pad11[7];
} Rec_4eafe0;

typedef struct {
	unsigned short id;
	char pad2[0xe];
	int f10;
	int f14;
	int f18;
	int f1c;
	float f20;
	float f24;
	float f28;
	float f2c;
	int f30;
	int f34;
	float f38;
	char pad3c[0x44];
} slot80;

void __cdecl he_NotifyOfficeAction(void* a1, void* a2);
int __cdecl amt_VacateOfficeSlot(unsigned char id);
int __cdecl amt_CollectOfficeGroup7(int all, int max, Rec18_68da68* out);
int __cdecl amt_CollectOfficeGroup7_4eafe0(int all, int max, Rec_4eafe0* out);
int __cdecl gm_GetRangeStatId(int, int);
int __cdecl cm_RequestAllocSpieler(char, int, int, short, int, char, char, char);
int __cdecl amt_ApplyForOffice(char* a0, int a1);
int __cdecl ai_CompareOfficeCandidates(unsigned short*, unsigned short*, unsigned short*, int*);
int __cdecl ai_SelectOfficeCandidate(unsigned char, unsigned short*, int*, int*);
void __cdecl amt_ResolveOfficeApplications(int, int, OFFICE_SLOT*);
void __cdecl amt_FillOffice0x1c0x1dFromRichest(void);
void __cdecl amt_FillOffice0x22FromRichest(void);
int __cdecl he_StartHandlungSearch(int, int, int);
void __cdecl amt_calc_zuenfte(unsigned int);
int __cdecl vfs_ResolvePath(char* a, int b, int c, char* out);
int __cdecl gm_CalcBuildingCost(int a, int b);
void __cdecl d3_GetObjectWorldPosition(char* a, int b);
void __cdecl d3_ComputeObjectYawToTarget(float* out, int obj);
void __cdecl cm_SendCopyEntityData(int a1);
int __cdecl d3_SelectSceneContext(int, int);
int __cdecl d3_TransformPoint(char*, char*, int*);
void __cdecl lc_GetBauplatzPrefix(int, char*);
int __cdecl d3_CollectUnusedSceneObjects(char*, int*);
char* __cdecl strupr(char*);
void __cdecl ReportClientMessage(const char*);
int __cdecl fcn_00507080(int k);
void __cdecl gm_GenerateShuffledIndices(int a1, int* a2);
slot80* __cdecl gm_FindSlotById(int a1, int a2);
float __cdecl gm_CalcMarketSlotPriceByObjektId(int a1, int a2);
int __cdecl cm_SendMarktSlotDelta(slot80* e, unsigned char kind);
int __cdecl fcn_00526120(char* text, int arg);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
#endif


float g_office_float_table[7][7] = {
	{ 1.0f, -2.5f, -2.5f, -2.5f, -5.0f, -5.0f, -10.0f },
	{ 1.0f, 0.0f, -2.5f, -5.0f, -2.5f, -7.0f, -10.0f },
	{ 1.0f, -2.5f, 0.0f, -2.5f, -5.0f, -5.0f, -10.0f },
	{ 1.0f, -5.0f, -2.5f, 0.0f, -7.5f, -2.5f, -10.0f },
	{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -5.0f, -10.0f },
	{ 1.0f, 1.0f, 1.0f, 1.0f, -5.0f, 0.0f, -10.0f },
	{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f },
};

OFFICE_ROLE_TEMPLATE g_office_role_templates[40] = {
	{ 0, 0, 0, 0, 0, 0x40a00000 },
	{ 1, 1, 1, 0x1f4, 1, 0x40a00000 },
	{ 2, 1, 2, 0x2bc, 0, 0x40a00000 },
	{ 3, 1, 3, 0x3e8, 0, 0x40a00000 },
	{ 4, 2, 1, 0x1f4, 1, 0x40a00000 },
	{ 5, 2, 2, 0x2bc, 0, 0x40a00000 },
	{ 6, 2, 3, 0x3e8, 0, 0x40a00000 },
	{ 7, 3, 1, 0x1f4, 1, 0x40a00000 },
	{ 8, 3, 2, 0x2bc, 0, 0x40a00000 },
	{ 9, 3, 3, 0x3e8, 0, 0x40a00000 },
	{ 0xa, 4, 4, 0x7d0, 0, 0x40a00000 },
	{ 0xb, 4, 4, 0x7d0, 0, 0x40a00000 },
	{ 0xc, 4, 4, 0x7d0, 0, 0x40a00000 },
	{ 0xd, 4, 5, 0x9c4, 0, 0x40a00000 },
	{ 0xe, 4, 5, 0x9c4, 0, 0x40a00000 },
	{ 0xf, 4, 6, 0xbb8, 0, 0x40a00000 },
	{ 0x10, 5, 4, 0x7d0, 0, 0x40c00000 },
	{ 0x11, 5, 4, 0x7d0, 0, 0x40c00000 },
	{ 0x12, 5, 4, 0x7d0, 0, 0x40c00000 },
	{ 0x13, 5, 5, 0x9c4, 0, 0x40c00000 },
	{ 0x14, 5, 5, 0x9c4, 0, 0x41000000 },
	{ 0x15, 5, 6, 0xbb8, 0, 0x41000000 },
	{ 0x16, 6, 7, 0x1388, 0, 0x40e00000 },
	{ 0x17, 6, 7, 0x1388, 0, 0x40e00000 },
	{ 0x18, 6, 7, 0x1388, 0, 0x41200000 },
	{ 0x19, 6, 8, 0x1b58, 0, 0x40e00000 },
	{ 0x1a, 6, 8, 0x1b58, 0, 0x41400000 },
	{ 0x1b, 6, 9, 0x2710, 0, 0x40e00000 },
	{ 0x1c, 7, 4, 0xbb8, 0, 0x40a00000 },
	{ 0x1d, 7, 4, 0xbb8, 0, 0x40a00000 },
	{ 0x1e, 7, 4, 0xbb8, 0, 0x40a00000 },
	{ 0x1f, 7, 4, 0xbb8, 0, 0x40a00000 },
	{ 0x20, 7, 4, 0xbb8, 0, 0x40a00000 },
	{ 0x21, 7, 4, 0xbb8, 0, 0x40a00000 },
	{ 0x22, 7, 4, 0xbb8, 0, 0x41000000 },
	{ 0x23, 8, 0xa, 0x4e20, 0, 0x40a00000 },
	{ 0x24, 8, 0xa, 0x4e20, 0, 0x40a00000 },
	{ 0x25, 8, 0xb, 0x7530, 0, 0x40a00000 },
	{ 0x26, 8, 0xc, 0xc350, 0, 0x40a00000 },
	{ 0x27, 8, 0xc, 0xc350, 0, 0x40a00000 },
};

/* ADDRESS: SERVER 0x1000b1c0 */
/* ADDRESS: GOLD 0x004e6360 */
/* ADDRESS: GOLDTL 0x004e7f20 */
int __cdecl amt_ValidateOfficeCandidate(int* arg1)
{
	unsigned char* rec;
	unsigned char holder;
	OFFICE_SLOT* p;
	int i;

	rec = gm_LookupEntityRecordById(arg1[0]);
	if (rec == 0 || rec[0x168] != 0)
		return 0;

	i = 0;
	for (; i < 30; i++) {
		if (((OFFICE_SLOT*) g_office_slots)[i].id == ((unsigned char*) arg1)[4])
			break;
	}
	if (i >= 30)
		return 0;

	if (((OFFICE_SLOT*) g_office_slots)[i].mplayerid != -1 ||
	    ((OFFICE_SLOT*) g_office_slots)[i].status != 3 ||
	    ((OFFICE_SLOT*) g_office_slots)[i].pcount >= 4)
		return 0;
	holder = ((OFFICE_SLOT*) g_office_slots)[i].mamt;
	if (((unsigned char*) arg1)[6] != holder)
		return 0;

	if (((unsigned char*) arg1)[5] != 0xff) {
		i = 0;
		for (; i < 30; i++) {
			if (((OFFICE_SLOT*) g_office_slots)[i].id == ((unsigned char*) arg1)[5])
				break;
		}
		if (i >= 30)
			return 0;

		if (holder != ((OFFICE_SLOT*) g_office_slots)[i].mamt ||
		    ((OFFICE_SLOT*) g_office_slots)[i].mplayerid != -1 ||
		    ((OFFICE_SLOT*) g_office_slots)[i].status != 3 ||
		    ((OFFICE_SLOT*) g_office_slots)[i].pcount >= 4)
			return 0;
	}
	return 1;
}

#if defined(REBREW_SERVER)
/* ADDRESS: SERVER 0x1000b290 */
unsigned int __cdecl amt_ValidateAndAssignOffice(unsigned int* arg1)
{
	unsigned char* cmd;
	unsigned int* arg1_alias;
	unsigned char* rec;
	unsigned char x5;
	unsigned int arg1_value;
	int f0v;
	OFFICE_ROLE_TEMPLATE copy;
	int i;
	int j;
	cmd = (unsigned char*) arg1;
	rec = gm_LookupEntityRecordById(*(int*) cmd);
	if (rec == 0)
		return 0;
	if (*(unsigned short*) rec == 0xffff)
		return 0;
	if (rec[0x168] != 0)
		return 0;
	i = 0;
	for (; i < 30; i++) {
		if (((OFFICE_SLOT*) g_office_slots)[i].id == cmd[4])
			break;
	}
	if (i >= 30)
		return 0;
	*(unsigned char*) &arg1 = cmd[6];
	if (*(unsigned char*) &arg1 != ((OFFICE_SLOT*) g_office_slots)[i].mamt)
		return 0;
	x5 = cmd[5];
	if (x5 != 0xff) {
		for (j = 0; j < 30; j++) {
			if (((OFFICE_SLOT*) g_office_slots)[j].id == x5)
				break;
		}
		if (j >= 30)
			return 0;
		if (((OFFICE_SLOT*) g_office_slots)[i].mamt != ((OFFICE_SLOT*) g_office_slots)[j].mamt)
			return 0;
		copy = g_office_role_templates[((OFFICE_SLOT*) g_office_slots)[i].mamt];
		arg1_alias = (unsigned int*) &arg1;
		arg1_value = *arg1_alias;
		f0v = copy.f0;
		if (f0v != (int) (arg1_value & 0xff) || copy.f10 == 0)
			return 0;
		{
			int type_i;
			int type_j;
			type_i = ((OFFICE_SLOT*) g_office_slots)[i].mplayerid;
			type_j = ((OFFICE_SLOT*) g_office_slots)[j].mplayerid;
			if (type_i != -1 ||
			    ((OFFICE_SLOT*) g_office_slots)[i].status != 3 ||
			    ((OFFICE_SLOT*) g_office_slots)[i].pcount >= 4 ||
			    type_j != -1 ||
			    ((OFFICE_SLOT*) g_office_slots)[j].pcount >= 4)
				return 0;
			rec[0x168] = (unsigned char) arg1_value;
			((OFFICE_SLOT*) g_office_slots)[i].pcount++;
			((OFFICE_SLOT*) g_office_slots)[j].pcount++;
			return 1;
		}
	}
	{
		int type_i;
		type_i = ((OFFICE_SLOT*) g_office_slots)[i].mplayerid;
		if (type_i != -1 ||
		    ((OFFICE_SLOT*) g_office_slots)[i].status != 3 ||
		    ((OFFICE_SLOT*) g_office_slots)[i].pcount >= 4)
			return 0;
		rec[0x168] = *(unsigned char*) &arg1;
		((OFFICE_SLOT*) g_office_slots)[i].pcount++;
		return 1;
	}
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004e7ff0 */
int __cdecl amt_ValidateOfficeApplication(unsigned char* arg)
{
	unsigned char* owner;
	OFFICE_SLOT_VIEW* slot;
	OFFICE_SLOT_VIEW* other;
	OFFICE_ROLE_VIEW rec;
	unsigned char c;
	unsigned char want;
	int i;
	int j;

	owner = (unsigned char*) gm_LookupEntityRecordById(*(int*) arg);
	if (owner == 0) {
		goto fail;
	}
	if (*(unsigned short*) owner == 0xffff) {
		goto fail;
	}
	if (*(unsigned char*) (owner + 0x168) != 0) {
		goto fail;
	}
	want = arg[4];
	slot = (OFFICE_SLOT_VIEW*) amt_OfficeSlots;
	for (i = 0; (int) slot < (int) amt_OfficeSlots + 0x2d0; slot++, i++) {
		if (slot->type == want) {
			goto found;
		}
	}
fail:
	return 0;
found:
	if (i >= 0x1e) {
		goto fail;
	}
	c = arg[6];
	if (c != ((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[i].tag) {
		goto fail;
	}
	if (arg[5] == 0xff) {
		if (((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[i].id != -1) {
			goto fail;
		}
		if (((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[i].state != 3) {
			goto fail;
		}
		if (((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[i].count >= 4) {
			goto fail;
		}
		*(unsigned char*) (owner + 0x168) = c;
		((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[i].count++;
		return 1;
	}
	want = arg[5];
	other = (OFFICE_SLOT_VIEW*) amt_OfficeSlots;
	for (j = 0; (int) other < (int) amt_OfficeSlots + 0x2d0; other++, j++) {
		if (((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[j].type == want) {
			goto found2;
		}
	}
	return 0;
found2:
	if (j >= 0x1e) {
		goto fail;
	}
	if (((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[i].tag != ((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[j].tag) {
		goto fail;
	}
	rec = ((OFFICE_ROLE_VIEW*) g_68da68)[((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[i].tag];
	if (rec.f0 != c) {
		goto fail;
	}
	if (rec.f4 == 0) {
		goto fail;
	}
	if (((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[i].id != -1) {
		goto fail;
	}
	if (((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[i].state != 3) {
		goto fail;
	}
	if (((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[i].count >= 4) {
		goto fail;
	}
	if (((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[j].id != -1) {
		goto fail;
	}
	if (((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[j].count >= 4) {
		goto fail;
	}
	*(unsigned char*) (owner + 0x168) = c;
	((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[i].count++;
	((OFFICE_SLOT_VIEW*) amt_OfficeSlots)[j].count++;
	return 1;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e65e0 */
/* ADDRESS: GOLDTL 0x004e81a0 */
int __cdecl amt_VacateOfficeSlot(unsigned char id)
{
	return amt_SendOfficeCommand(id, 0, 0, 3, 0xff);
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e6600 */
/* ADDRESS: GOLDTL 0x004e81c0 */
int __cdecl amt_AssignEntityOfficeDefault(unsigned char* entity, unsigned char* other_entity)
{
	int l0[6];
	int l1[6];

	if (srv_GetEntityOfficeSlot(entity, l1, l0) == 0) {
		return -1;
	}
	if (other_entity == 0) {
		return -1;
	}
	return amt_SendOfficeCommand(l0[0], entity, other_entity, 2, 1);
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e6650 */
/* ADDRESS: GOLDTL 0x004e8210 */
int __cdecl amt_AssignOfficeHolder(int office_id, unsigned char* payload, int mode)
{
	if (payload == 0) {
		return -1;
	}
	return amt_SendOfficeCommand(office_id, payload, 0, 1, mode);
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e6680 */
/* ADDRESS: GOLDTL 0x004e8240 */
int __cdecl amt_SendOfficeCommand(unsigned char id, unsigned char* ea, unsigned char* eb, int x1, int x2)
{
	char m[0x10];
	int a;
	int b;
	int i;

	a = -1;
	b = -1;
	if (ea != 0)
		a = *(int*) (ea + 4);
	if (eb != 0)
		b = *(int*) (eb + 4);
	for (i = 0; i < 42; i++) {
		if (((rec18_4e8240*)amt_OfficeSlots)[i].c0 == id)
			break;
	}
	if (i >= 42)
		return -1;
	m[0] = id;
	*(int*) (m + 1) = a;
	m[5] = x1;
	m[6] = x2;
	*(int*) (m + 7) = b;
	return cm_SendExecuteOffice(m);
}
#endif

#if defined(REBREW_SERVER)
/* ADDRESS: SERVER 0x1000b440 */
int __cdecl amt_ValidateCommand(char* arg1)
{
	int i;

	if (((unsigned char*) arg1)[6] == 0xff)
		return 1;

	i = 0;
	for (; i < 42; i++) {
		if (((OFFICE_SLOT*) g_office_slots)[i].id == ((unsigned char*) arg1)[0])
			break;
	}
	if (i >= 42)
		return 0;

	if (((OFFICE_SLOT*) g_office_slots)[i].status != 1)
		return 0;
	if (((OFFICE_SLOT*) g_office_slots)[i].msetter != -1)
		return 0;
	if (*(int*) (arg1 + 7) != -1) {
		if (gm_LookupEntityRecordById(*(int*) (arg1 + 7)) == 0)
			return 0;
	}
	if (*(int*) (arg1 + 1) != -1) {
		if (gm_LookupEntityRecordById(*(int*) (arg1 + 1)) == 0)
			return 0;
	}
	return 1;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e6710 */
/* ADDRESS: GOLDTL 0x004e82d0 */
int __cdecl amt_ValidateOfficeRequest(unsigned char* m)
{
	int i;

	if (m[6] == 0xff)
		return 1;
	for (i = 0; i < 42; i++) {
		if (((rec18_4e8240*)amt_OfficeSlots)[i].c0 == m[0])
			break;
	}
	if (i >= 42)
		return 0;
	if (((rec18_4e8240*)amt_OfficeSlots)[i].f10 != 1)
		return 0;
	if (((rec18_4e8240*)amt_OfficeSlots)[i].f14 != -1)
		return 0;
	if (*(int*) (m + 7) != -1 && gm_LookupEntityRecordById(*(int*) (m + 7)) == 0)
		return 0;
	if (*(int*) (m + 1) != -1 && gm_LookupEntityRecordById(*(int*) (m + 1)) == 0)
		return 0;
	return 1;
}
#endif

#if defined(REBREW_SERVER)
/* ADDRESS: SERVER 0x1000b4d0 */
int __cdecl amt_ExecuteOfficeAssignment(char* cmd_payload)
{
	int iStack;
	int ent;
	int record_index;
	int old_owner;
	int record_off;

	iStack = -1;

	/* Validate associated entity if present */
	if (*(int*) (cmd_payload + 7) != -1) {
		if (gm_LookupEntityRecordById(*(int*) (cmd_payload + 7)) == 0) {
			return 0;
		}
	}

	/* Get owner entity */
	ent = 0;
	if (*(int*) (cmd_payload + 1) != -1) {
		ent = (int)gm_LookupEntityRecordById(*(int*) (cmd_payload + 1));
		if (ent == 0) {
			return 0;
		}
		iStack = *(int*) (ent + 4);
	}

	/* Search table for matching type byte */
	record_index = 0;
	for (; record_index < 0x2a; record_index++) {
		if ((char) ((OFFICE_SLOT*) g_office_slots)[record_index].id == *cmd_payload)
			break;
	}
	if (record_index >= 0x2a) {
		return 0;
	}

	record_off = record_index * 0x18;

	/* Lookup existing owner and clear old role references */
	old_owner = (int)gm_LookupEntityRecordById(((OFFICE_SLOT*) g_office_slots)[record_index].mplayerid);
	if (old_owner != 0 && *(int*) (old_owner + 4) != *(int*) (cmd_payload + 1)) {
		char role;
		role = ((OFFICE_SLOT*) g_office_slots)[record_index].mamt;

		if (*(char*) (old_owner + 0x166) == role) {
			*(char*) (old_owner + 0x166) = 0;
		}
		else if (*(char*) (old_owner + 0x169) == role) {
			*(char*) (old_owner + 0x169) = 0;
		}
		else {
			int flags;
			if (role == 0x23) {
				flags = *(int*) (old_owner + 0x1cc);
				flags &= 0xfffffdff;
			}
			else if (role == 0x24) {
				flags = *(int*) (old_owner + 0x1cc);
				flags &= 0xfffffbff;
			}
			else if (role == 0x25) {
				flags = *(int*) (old_owner + 0x1cc);
				flags &= 0xfffff7ff;
			}
			else {
				goto after_old_clear;
			}
			*(int*) (old_owner + 0x1cc) = flags;
		}
	}

after_old_clear:
	if (ent == 0) {
		goto final_store;
	}

	{
		int k;

		if ((unsigned char) ((OFFICE_SLOT*) g_office_slots)[record_index].mamt <= 0x1b) {
			/* Small role path */
			if (*(char*) (ent + 0x166) != 0) {
				/* Search for existing assignment with same owner */
				int j;
				for (j = 0; j < 30; j++) {
					if (((OFFICE_SLOT*) g_office_slots)[j].mplayerid == iStack) {
						((OFFICE_SLOT*) g_office_slots)[j].mplayerid = -1;
						((OFFICE_SLOT*) g_office_slots)[j].msetter = -1;
						((OFFICE_SLOT*) g_office_slots)[j].status = 4;
						((OFFICE_SLOT*) g_office_slots)[j].pcount = 0;
						break;
					}
				}
			}

			/* Compare role priorities */
			if (*(unsigned char*) ((unsigned char) ((OFFICE_SLOT*) g_office_slots)[record_index].mamt * 0x18 + (unsigned int) ((char*) &g_office_role_templates + 0x8)) >=
			    *(unsigned char*) (*(unsigned char*) (ent + 0x166) * 0x18 + (unsigned int) ((char*) &g_office_role_templates + 0x8))) {
				*(char*) (ent + 0x167) = ((OFFICE_SLOT*) g_office_slots)[record_index].mamt;
			}

			{
				char new_role;
				new_role = ((OFFICE_SLOT*) g_office_slots)[record_index].mamt;
				*(char*) (ent + 0x166) = new_role;
				if (*(char*) (ent + 0x168) == new_role) {
					*(char*) (ent + 0x168) = 0;
				}
			}

			/* Set flags based on role */
			{
				unsigned char role_val;
				role_val = (unsigned char) ((OFFICE_SLOT*) g_office_slots)[record_index].mamt;

				if (role_val == 0x0f) {
					*(int*) (ent + 0x1cc) = *(int*) (ent + 0x1cc) | 0x40;
				}
				else if (role_val == 0x15) {
					*(int*) (ent + 0x1cc) = *(int*) (ent + 0x1cc) | 0x80;
				}
				else if (role_val == 0x1b) {
					*(int*) (ent + 0x1cc) = *(int*) (ent + 0x1cc) | 0x100;
				}
			}

			/* Check role's count property */
			if (*(int*) ((unsigned int) (unsigned char) ((OFFICE_SLOT*) g_office_slots)[record_index].mamt * 0x18 + (unsigned int) ((char*) &g_office_role_templates + 0x10)) != 0) {
				unsigned char* scan;
				k = 0;
				scan = (unsigned char*) ((char*) &g_office_slots + 0x8);

				while ((int) scan < (int) ((char*) &g_office_slots + 0x2d8)) {
					if (*scan == (unsigned char) ((OFFICE_SLOT*) g_office_slots)[record_index].mamt && k != record_index) {
						goto dec_count;
					}
					scan += 0x18;
					k++;
				}
			}

		final_store:
			((OFFICE_SLOT*) g_office_slots)[record_index].mplayerid = iStack;
			((OFFICE_SLOT*) g_office_slots)[record_index].msetter = *(int*) (cmd_payload + 7);
			((OFFICE_SLOT*) g_office_slots)[record_index].status = cmd_payload[5];
			if (cmd_payload[5] == 3) {
				((OFFICE_SLOT*) g_office_slots)[record_index].pcount = 0;
			}
			return 1;

		dec_count:
			if (((OFFICE_SLOT*) g_office_slots)[k].status == 3) {
				int cnt;
				cnt = ((OFFICE_SLOT*) g_office_slots)[k].pcount;
				if (cnt != 0) {
					((OFFICE_SLOT*) g_office_slots)[k].pcount = cnt - 1;
					if (cnt - 1 == 0) {
						((OFFICE_SLOT*) g_office_slots)[k].status = 4;
					}
				}
			}
			goto final_store;
		}

		if ((unsigned char) ((OFFICE_SLOT*) g_office_slots)[record_index].mamt >= 0x1c &&
		    (unsigned char) ((OFFICE_SLOT*) g_office_slots)[record_index].mamt <= 0x22) {
			/* Medium role path (0x1c-0x22) */
			if (*(char*) (ent + 0x169) != 0) {
				int* scan;
				scan = (int*) ((char*) &g_office_slots + 0x2d4);
				do {
					if (*(char*) ((char*) scan + 4) == *(char*) (ent + 0x169) && *scan == *(int*) (ent + 4)) {
						*scan = -1;
					}
					scan = (int*) ((char*) scan + 0x18);
				} while ((int) scan < (int) ((char*) &g_office_slots + 0x37c));
			}

			*(char*) (ent + 0x169) = ((OFFICE_SLOT*) g_office_slots)[record_index].mamt;
			goto final_store;
		}

		/* High role path (> 0x22) */
		{
			unsigned char role_ch;
			int flags;
			int mask;

			flags = *(int*) (ent + 0x1cc);
			flags &= 0xfffff1ff;
			*(int*) (ent + 0x1cc) = flags;

			role_ch = ((OFFICE_SLOT*) g_office_slots)[record_index].mamt;
			mask = 0;
			if (role_ch == 0x23) {
				*(int*) (ent + 0x1cc) = flags | 0x200;
				mask = 0x4000;
			}
			else if (role_ch == 0x24) {
				*(int*) (ent + 0x1cc) = flags | 0x400;
				mask = 0x8000;
			}
			else if (role_ch == 0x25) {
				*(int*) (ent + 0x1cc) = flags | 0x800;
				mask = 0x10000;
			}

			{
				int row; extern unsigned char g_slot_table[];
				row = 0;
				do {
					*(int*) ((int) g_slot_table + 0x1cc + row * 0x21c) =
						*(int*) ((int) g_slot_table + 0x1cc + row * 0x21c) & ~mask;
					row++;
				} while (row < 768);
			}
		}
		goto final_store;
	}
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004e8360 */
int __cdecl amt_ApplyOfficeAssignment(char* requestData)
{
	char* ent;
	char* setter;
	char* x;
	unsigned char* p;
	unsigned char bit;
	unsigned int flags;
	int other;
	int i;
	int k;
	int* ip;

	other = -1;
	setter = 0;
	if (*(int*) (requestData + 7) != -1) {
		setter = gm_LookupEntityRecordById(*(int*) (requestData + 7));
		if (setter == 0)
			return 0;
	}
	ent = 0;
	if (*(int*) (requestData + 1) != -1) {
		ent = gm_LookupEntityRecordById(*(int*) (requestData + 1));
		if (ent == 0)
			return 0;
		other = *(int*) (ent + 4);
	}
	for (i = 0; i < 0x2a; i++) {
		if (((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f00 == *(unsigned char*) requestData)
			break;
	}
	if (i >= 0x2a)
		return 0;
	x = gm_LookupEntityRecordById(((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f04);
	if (x != 0 && *(int*) (x + 4) != *(int*) (requestData + 1)) {
		bit = ((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08;
		if (*(unsigned char*) (x + 0x166) == bit) {
			*(unsigned char*) (x + 0x166) = 0;
		} else if (*(unsigned char*) (x + 0x169) == bit) {
			*(unsigned char*) (x + 0x169) = 0;
		} else if (bit == '#') {
			*(int*) (x + 0x1cc) &= 0xfffffdff;
		} else if (bit == '$') {
			*(int*) (x + 0x1cc) &= 0xfffffbff;
		} else if (bit == '%') {
			*(int*) (x + 0x1cc) &= 0xfffff7ff;
		}
	}
	if (ent != 0) {
		if (((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08 <= 0x1b) {
			if (*(unsigned char*) (ent + 0x166) != 0) {
				k = 0;
				ip = (int*) 0x9a9224;
				do {
					if (*ip == other) {
						((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[k].f04 = -1;
						((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[k].f14 = -1;
						((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[k].f10 = 4;
						((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[k].f0c = 0;
						break;
					}
					ip = (int*) ((char*) ip + 0x18);
					k++;
				} while ((int) ip < (int) 0x9a94f4);
			}
			if (*(unsigned char*) ((char*)g_68da68 + ((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08 * 0x18 + 8) >=
			    *(unsigned char*) ((char*)g_68da68 + *(unsigned char*) (ent + 0x166) * 0x18 + 8))
				*(unsigned char*) (ent + 0x167) = ((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08;
			bit = ((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08;
			*(unsigned char*) (ent + 0x166) = bit;
			if (*(unsigned char*) (ent + 0x168) == bit)
				*(unsigned char*) (ent + 0x168) = 0;
			if (((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08 == 0x0f) {
				*(int*) (ent + 0x1cc) |= 0x40;
			} else if (((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08 == 0x15) {
				*(int*) (ent + 0x1cc) |= 0x80;
			} else if (((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08 == 0x1b) {
				*(int*) (ent + 0x1cc) |= 0x100;
			}
			if (*(int*) ((char*)g_68da68 + ((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08 * 0x18 + 0x10) != 0) {
				k = 0;
				p = (unsigned char*) 0x9a9228;
				do {
					if (*(unsigned char*) p == ((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08 && k != i) {
						if (((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[k].f10 == 3 &&
						    ((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[k].f0c != 0) {
							((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[k].f0c =
								((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[k].f0c - 1;
							if (((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[k].f0c == 0)
								((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[k].f10 = 4;
						}
						break;
					}
					p += 0x18;
					k++;
				} while ((int) p < (int) 0x9a94f8);
			}
		} else if (((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08 >= 0x1c && ((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08 <= 0x22) {
			if (*(unsigned char*) (ent + 0x169) != 0) {
				p = (unsigned char*) 0x9a94f4;
				do {
					if (*(unsigned char*) (p + 4) == *(unsigned char*) (ent + 0x169) &&
					    *(int*) p == *(int*) (ent + 4))
						*(int*) p = -1;
					p += 0x18;
				} while ((int) p < (int) 0x9a959c);
			}
			*(unsigned char*) (ent + 0x169) = ((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08;
		} else {
			flags = *(int*) (ent + 0x1cc) & 0xfffff1ff;
			*(int*) (ent + 0x1cc) = flags;
			k = 0;
			if (((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08 == '#') {
				*(int*) (ent + 0x1cc) = flags | 0x200;
				k = 0x4000;
			} else if (((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08 == '$') {
				*(int*) (ent + 0x1cc) = flags | 0x400;
				k = 0x8000;
			} else if (((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f08 == '%') {
				*(int*) (ent + 0x1cc) = flags | 0x800;
				k = 0x10000;
			}
			for (ip = (int*) 0x7f4e6c; (int) ip < (int) 0x85a26c; ip = (int*) ((char*) ip + 0x21c))
				*ip &= ~k;
		}
	}
	((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f04 = other;
	((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f14 = *(int*) (requestData + 7);
	((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f10 = *(unsigned char*) (requestData + 5);
	if (*(unsigned char*) (requestData + 5) == 3)
		((OFFICE_ASSIGN_SLOT*) amt_OfficeSlots)[i].f0c = 0;
	if (setter != 0 && ent != 0 &&
	    *(int*) ((unsigned long)&g_7f4ca4 + *(unsigned short*) &g_774970 * 0x21c) == *(int*) (ent + 4))
		he_NotifyOfficeAction(setter, ent);
	return 1;
}
#endif

#if defined(REBREW_SERVER)
/* ADDRESS: SERVER 0x1000b820 */
void __cdecl amt_FindEntity26(int val)
{
	unsigned int i;
	for (i = 0x29; i != 0; i--) {
		/* asm checks byte at slot+8 (role); stores dword at slot+4 (entityId) */
		if (((OFFICE_SLOT*) g_office_slots)[i].mamt == 0x26) {
			((OFFICE_SLOT*) g_office_slots)[i].mplayerid = val;
			return;
		}
	}
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e6b40 */
/* ADDRESS: GOLDTL 0x004e8700 */
void __cdecl amt_SetType26OfficeHolder(int holder)
{
	int i;

	for (i = 41; i != 0; i--) {
		if (amt_OfficeSlots[i].type == 0x26) {
			amt_OfficeSlots[i].x4 = holder;
			return;
		}
	}
}
#endif

#if defined(REBREW_SERVER)
/* ADDRESS: SERVER 0x1000b850 */
void __cdecl amt_FindEntity27(int val)
{
	unsigned int i;
	for (i = 0x29; i != 0; i--) {
		if (((OFFICE_SLOT*) g_office_slots)[i].mamt == 0x27) {
			((OFFICE_SLOT*) g_office_slots)[i].mplayerid = val;
			return;
		}
	}
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e6b70 */
/* ADDRESS: GOLDTL 0x004e8730 */
void __cdecl amt_SetOfficeType0x27Handle(int v)
{
	int i;

	for (i = 41; i != 0; i--) {
		if (amt_OfficeSlots[i].type == 0x27) {
			amt_OfficeSlots[i].x4 = v;
			return;
		}
	}
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e6ba0 */
/* ADDRESS: GOLDTL 0x004e8760 */
int __cdecl amt_SendSameOfficeCommand(char* x, unsigned char* firstEntity, unsigned char* secondEntity)
{
	char message[0xc];
	rec18_4e8240 a1;
	rec18_4e8240 b1;
	rec18_4e8240 a2;
	rec18_4e8240 b2;

	if (x == 0 || firstEntity == 0 || secondEntity == 0)
		return -1;
	if (srv_GetEntityOfficeSlot(firstEntity, &a1, &a2) == 0)
		return -1;
	if (srv_GetEntityOfficeSlot(secondEntity, &b1, &b2) == 0)
		return -1;
	if (a1.kind != b1.kind || a1.id != b1.id)
		return -1;
	*(int*) message = *(int*) (x + 4);
	message[4] = a2.c0;
	message[5] = b2.c0;
	*(int*) (message + 6) = 6;
	return cm_SendSwapOfficeOccupants(message);
}
#endif

#if defined(REBREW_SERVER)
/* ADDRESS: SERVER 0x1000b880 */
int __cdecl amt_SwapOfficeHolders(int* arg1)
{
	OFFICE_SLOT* slot_a;
	OFFICE_SLOT* slot_b;
	char* ent_a;
	char* ent_b;
	char* ent_c;
	int i;

	ent_a = (char*) gm_LookupEntityRecordById(arg1[0]);
	if (ent_a == 0)
		return 0;
	if (*(int*) (ent_a + 0x194) < *(int*) ((char*) arg1 + 6))
		return 0;

	/* find office slot A by type byte */
	i = 0;
	while (1) {
		if ((char) ((OFFICE_SLOT*) g_office_slots)[i].id == *((char*) arg1 + 4)) {
			break;
		}
		i++;
		if (i >= 0x1e) {
			return 0;
		}
	}
	slot_a = &((OFFICE_SLOT*) g_office_slots)[i];
	if (slot_a == 0) {
		return 0;
	}
	ent_b = (char*) gm_LookupEntityRecordById(slot_a->mplayerid);
	if (ent_b == 0) {
		return 0;
	}

	/* find office slot B by type byte */
	i = 0;
	while (1) {
		if ((char) ((OFFICE_SLOT*) g_office_slots)[i].id == *((char*) arg1 + 5)) {
			break;
		}
		i++;
		if (i >= 0x1e) {
			return 0;
		}
	}
	slot_b = &((OFFICE_SLOT*) g_office_slots)[i];
	if (slot_b == 0) {
		return 0;
	}
	ent_c = (char*) gm_LookupEntityRecordById(slot_b->mplayerid);
	if (ent_c == 0) {
		return 0;
	}
	*(char*) (ent_b + 0x166) = slot_b->mamt;
	*(char*) (ent_c + 0x166) = slot_a->mamt;
	i = slot_a->mplayerid;
	slot_a->mplayerid = slot_b->mplayerid;
	slot_b->mplayerid = i;
	*(int*) (ent_a + 0x194) -= *(int*) ((char*) arg1 + 6);
	return 1;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e6c50 */
/* ADDRESS: GOLDTL 0x004e8810 */
int __cdecl amt_SwapOfficeOccupants(unsigned char* request)
{
	char* e;
	char* w1;
	char* w2;
	struct job_4e8810* p1;
	struct job_4e8810* p2;
	int i;
	int savedId;

	e = gm_LookupEntityRecordById(*(int*) request);
	if (e == 0)
		return 0;
	if (*(int*) (e + 0x194) < *(int*) (request + 6))
		return 0;
	p1 = 0;
	for (i = 0; i < 30; i++) {
		if (((struct job_4e8810*)amt_OfficeSlots)[i].key == request[4]) {
			p1 = &((struct job_4e8810*)amt_OfficeSlots)[i];
			break;
		}
	}
	if (p1 == 0)
		return 0;
	w1 = gm_LookupEntityRecordById(p1->id);
	if (w1 == 0)
		return 0;
	p2 = 0;
	for (i = 0; i < 30; i++) {
		if (((struct job_4e8810*)amt_OfficeSlots)[i].key == request[5]) {
			p2 = &((struct job_4e8810*)amt_OfficeSlots)[i];
			break;
		}
	}
	if (p2 == 0)
		return 0;
	w2 = gm_LookupEntityRecordById(p2->id);
	if (w2 == 0)
		return 0;
	amt_NotifyOfficeSwap(e, w1, w2);
	w1[0x166] = p2->slot;
	w2[0x166] = p1->slot;
	savedId = p1->id;
	p1->id = p2->id;
	p2->id = savedId;
	*(int*) (e + 0x194) -= *(int*) (request + 6);
	return 1;
}
#endif

#if defined(REBREW_SERVER)
/* ADDRESS: SERVER 0x1000b990 */
int __cdecl amt_ClearEntityLinks(char* entity)
{
	OFFICE_SLOT* slot;
	unsigned short default_val;
	int i;
	int result;
	int state_tmp;

	default_val = (unsigned short) g_current_hour;
	result = 0;
	slot = (OFFICE_SLOT*) g_office_slots;
	for (i = 0; i < 0x2a; i++) {
		if (slot[i].mplayerid == *(int*) (entity + 4)) {
			slot[i].mplayerid = -1;
			slot[i].msetter = -1;
			state_tmp = (default_val > 0xb) ? 4 : 3;
			slot[i].status = (char) state_tmp;
			slot[i].pcount = 0;
			result |= 1;
		}
		else if (slot[i].msetter == *(int*) (entity + 4)) {
			slot[i].msetter = -1;
			slot[i].status = 1;
		}
	}
	if (*(char*) (entity + 0x168) != 0) {
		for (i = 0; i < 0x2a; i++) {
			if ((char) slot[i].mamt == *(char*) (entity + 0x168)) {
				if (slot[i].pcount > 0) {
					slot[i].pcount--;
					result |= 1;
				}
			}
		}
	}
	*(char*) (entity + 0x166) = 0;
	*(char*) (entity + 0x169) = 0;
	*(char*) (entity + 0x168) = 0;
	return result;
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004e8940 */
int __cdecl amt_ClearEntityOffices(char* obj)
{
	int a;
	int v;
	int ret;
	unsigned short w;

	w = g_7f4c04;
	ret = 0;
	a = 0x9a9234;
	do {
		v = *(int*) (obj + 4);
		if (*(int*) (a - 0x10) == v) {
			*(int*) (a - 0x10) = -1;
			*(int*) (a - 8) = 0;
			*(unsigned char*) (a - 4) = (unsigned char) ((w > 0xb) + 3);
			ret |= 1;
		} else if (*(int*) a == v) {
			*(unsigned char*) (a - 4) = 1;
		} else {
			a += 0x18;
			continue;
		}
		*(int*) a = -1;
		a += 0x18;
	} while (a < 0x9a9624);
	if (*(unsigned char*) (obj + 0x168) != 0) {
		a = 0x9a922c;
		do {
			if (*(unsigned char*) (a - 4) == *(unsigned char*) (obj + 0x168)) {
				v = *(int*) a;
				if (v > 0) {
					*(int*) a = v - 1;
					ret |= 1;
				}
			}
			a += 0x18;
		} while (a < 0x9a961c);
	}
	*(unsigned char*) (obj + 0x166) = 0;
	*(unsigned char*) (obj + 0x169) = 0;
	*(unsigned char*) (obj + 0x168) = 0;
	return ret;
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
#define BASE_A 0x9a9234
#define END_A  0x9a9624
#define BASE_B 0x9a922c
#define END_B  0x9a961c
/* ADDRESS: GOLDTL 0x004e89e0 */
void __cdecl amt_ReleaseEntityOffices(char* obj, int flag)
{
	int a;
	int v;
	unsigned short w;

	w = g_7f4c04;
	a = BASE_A;
	do {
		v = *(int*) (obj + 4);
		if (*(int*) (a - 0x10) == v && flag != 0) {
			*(int*) (a - 0x10) = -1;
			*(int*) (a - 8) = 0;
			*(unsigned char*) (a - 4) = (unsigned char) ((w > 0xb) + 3);
		} else if (*(int*) a == v) {
			*(unsigned char*) (a - 4) = 1;
		} else {
			a += 0x18;
			continue;
		}
		*(int*) a = -1;
		a += 0x18;
	} while (a < END_A);
	if (*(unsigned char*) (obj + 0x168) != 0) {
		a = BASE_B;
		do {
			if (*(unsigned char*) (a - 4) == *(unsigned char*) (obj + 0x168) && *(int*) a > 0) {
				*(int*) a = *(int*) a - 1;
			}
			a += 0x18;
		} while (a < END_B);
	}
	*(unsigned char*) (obj + 0x168) = 0;
	if (flag != 0) {
		*(unsigned char*) (obj + 0x166) = 0;
		*(unsigned char*) (obj + 0x169) = 0;
	}
}
#undef BASE_A
#undef END_A
#undef BASE_B
#undef END_B
#endif

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004e6e20 */
void __cdecl ClearUserRecords(GOLDUser *p, int who)
{
	unsigned short lim = GOLD_limit;
	int i;

	for (i = 0; i < 42; i++) {
		if (((OFFICESLOT *)g_office_slots)[i].owner == p->f04 && who) {
			((OFFICESLOT *)g_office_slots)[i].owner = -1;
			((OFFICESLOT *)g_office_slots)[i].count = 0;
			((OFFICESLOT *)g_office_slots)[i].state = (lim > 11) ? 4 : 3;
		} else if (((OFFICESLOT *)g_office_slots)[i].holder == p->f04) {
			((OFFICESLOT *)g_office_slots)[i].state = 1;
		} else {
			continue;
		}
		((OFFICESLOT *)g_office_slots)[i].holder = -1;
	}

	if (p->b168) {
		for (i = 0; i < 42; i++) {
			if (((OFFICESLOT *)g_office_slots)[i].kind == (unsigned char)p->b168) {
				if (((OFFICESLOT *)g_office_slots)[i].count > 0) {
					((OFFICESLOT *)g_office_slots)[i].count--;
				}
			}
		}
	}

	p->b168 = 0;
	if (who) {
		p->b166 = 0;
		p->b169 = 0;
	}
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_GetSlotByRole(int role, OFFICE_SLOT* out)
{
	int i;

	for (i = 0; i < 0x2a; i++) {
		if ((char) ((OFFICE_SLOT*) g_office_slots)[i].mamt == role) {
			break;
		}
	}
	if (i >= 0x2a) {
		return 0;
	}
	*out = ((OFFICE_SLOT*) g_office_slots)[i];
	return 1;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e6ec0 */
/* ADDRESS: GOLDTL 0x004e8a80 */
int __cdecl amt_FindOfficeSlotByType(int type, Rec18_68da68* out)
{
	int i;

	for (i = 0; i < 42; i++) {
		if (amt_OfficeSlots[i].type == type) {
			break;
		}
	}
	if (i >= 42) {
		return 0;
	}
	*out = amt_OfficeSlots[i];
	return 1;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_GetRoleGroup(int role)
{
	if (role >= 0x28) {
		return 0;
	}
	return g_office_role_templates[role].f4;
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004e8ad0 */
int __cdecl amt_GetOfficeGroup(int role)
{
	if (role >= 0x28) {
		return 0;
	}
	return *(int*) (0x68da6c + role * 0x18);
}
#endif

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004e6f10 */
int __cdecl amt_GetOfficeGroup(int index)
{
    if (index >= 0x28) {
        return 0;
    }
    return ((int (*)[6]) g_68da68)[index][1];
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_GetSlotByType(unsigned char type, OFFICE_SLOT* out)
{
	int i;

	for (i = 0; i < 0x2a; i++) {
		if ((unsigned char) ((OFFICE_SLOT*) g_office_slots)[i].id == type) {
			break;
		}
	}
	if (i >= 0x2a) {
		return 0;
	}
	*out = ((OFFICE_SLOT*) g_office_slots)[i];
	return 1;
}
#endif

#if !defined(REBREW_SERVER)
#pragma intrinsic(memcpy, memset)
/* ADDRESS: GOLD 0x004e6f30 */
/* ADDRESS: GOLDTL 0x004e8af0 */
int __cdecl amt_FindOfficeSlotByKey(unsigned char key, void* dst)
{
	int i;
	int a;

	i = 0;
	a = (int) amt_OfficeSlots;
	for (;;) {
		if (a >= (int) amt_OfficeSlots + 0x3f0) {
			return 0;
		}
		if (*(unsigned char*) a == key) {
			break;
		}
		a += 0x18;
		i++;
	}
	if (i >= 0x2a) {
		return 0;
	}
	memcpy(dst, (void*) ((int) amt_OfficeSlots + i * 24), 24);
	return 1;
}
#endif

/* ADDRESS: GOLD 0x004e6f80 */
/* ADDRESS: GOLDTL 0x004e8b40 */
int __cdecl amt_GetRoleTemplate(int role, OFFICE_ROLE_TEMPLATE* out)
{
	if (role >= 0x28) {
		*out = g_office_role_templates[0];
		return 0;
	}
	*out = g_office_role_templates[role];
	return 1;
}

#if defined(REBREW_SERVER)
int __cdecl amt_ListSlotsOfGroup(int group, int max, OFFICE_SLOT* out)
{
	int n;
	int i;
	int start;

	if (group == 0) {
		return 0;
	}
	if (group <= 6) {
		start = 30;
	}
	else if (group == 8) {
		start = 0x2a;
	}
	else {
		return 0;
	}
	n = 0;
	for (i = start - 1; i >= 0 && n < max; i--) {
		if (g_office_role_templates[(unsigned char) ((OFFICE_SLOT*) g_office_slots)[i].mamt].f4 == group) {
			out[n++] = ((OFFICE_SLOT*) g_office_slots)[i];
		}
	}
	return n;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e6fc0 */
/* ADDRESS: GOLDTL 0x004e8b80 */
int __cdecl amt_FindOfficeSlotsByKind(int kind, int max, OFFICE_SLOT* out)
{
	int n;
	int i;
	int start;

	if (kind == 0)
		return 0;
	if (kind <= 6)
		start = 30;
	else if (kind == 8)
		start = 42;
	else
		return 0;
	n = 0;
	for (i = start - 1; i >= 0 && n < max; i--) {
		if (((OFFICE_ROLE_TEMPLATE*)g_68da68)[((OFFICE_SLOT*)amt_OfficeSlots)[i].mamt].f4 == kind)
			out[n++] = ((OFFICE_SLOT*)amt_OfficeSlots)[i];
	}
	return n;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_ListHeldSlotsOfGroup(int group, int max, OFFICE_SLOT* out)
{
	int n;
	int i;
	int start;

	if (group == 0) {
		return 0;
	}
	if (group <= 6) {
		start = 30;
	}
	else if (group == 5) {
		start = 0x2a;
	}
	else {
		return 0;
	}
	n = 0;
	for (i = start - 1; i >= 0 && n < max; i--) {
		if (g_office_role_templates[(unsigned char) ((OFFICE_SLOT*) g_office_slots)[i].mamt].f4 == group &&
		    gm_LookupEntityRecordById(((OFFICE_SLOT*) g_office_slots)[i].mplayerid) != 0) {
			out[n++] = ((OFFICE_SLOT*) g_office_slots)[i];
		}
	}
	return n;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e7040 */
/* ADDRESS: GOLDTL 0x004e8c00 */
int __cdecl amt_CollectOfficeSlotsByGroup(int group, int max, OFFICE_SLOT* out)
{
	int n;
	int i;
	int start;

	if (group == 0)
		return 0;
	if (group <= 6)
		start = 30;
	else if (group == 5)
		start = 42;
	else
		return 0;
	n = 0;
	for (i = start - 1; i >= 0 && n < max; i--) {
		if (((OFFICE_ROLE_TEMPLATE*)g_68da68)[((OFFICE_SLOT*)amt_OfficeSlots)[i].mamt].f4 == group &&
		    gm_LookupEntityRecordById(((OFFICE_SLOT*)amt_OfficeSlots)[i].mplayerid) != 0)
			out[n++] = ((OFFICE_SLOT*)amt_OfficeSlots)[i];
	}
	return n;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_ListCouncilSlots(int all, int max, OFFICE_SLOT* out)
{
	int n;
	int i;

	n = 0;
	for (i = 30; i < 37; i++) {
		if (n >= max) {
			break;
		}
		if (g_office_role_templates[(unsigned char) ((OFFICE_SLOT*) g_office_slots)[i].mamt].f4 == 7 &&
		    (all != 0 || ((OFFICE_SLOT*) g_office_slots)[i].mplayerid != -1)) {
			*out = ((OFFICE_SLOT*) g_office_slots)[i];
			n++;
			out++;
		}
	}
	return n;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e70f0 */
/* ADDRESS: GOLDTL 0x004e8cb0 */
int __cdecl amt_CollectOfficeGroup7(int all, int max, Rec18_68da68* out)
{
	int n;
	int i;

	n = 0;
	for (i = 30; i < 37; i++) {
		if (n >= max) {
			break;
		}
		if (g_68da68[amt_OfficeSlots[i].type].x4 == 7 && (all != 0 || amt_OfficeSlots[i].x4 != -1)) {
			*out = amt_OfficeSlots[i];
			n++;
			out++;
		}
	}
	return n;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_RankOpenOffices(unsigned char* who, int n, OFFICE_PICK* picks)
{
	int __cdecl amt_GetOfficeAffinity(unsigned char* entity, int role, float* out);
	float score;
	int count;
	int i;
	int j;
	int k;
	int t;
	int found;

	count = 0;
	if (n <= 0) {
		return 0;
	}
	for (j = n - 1; j >= 0; j--) {
		picks[j].score = -100.0f;
		picks[j].type = 0;
		picks[j].rank = 0;
	}
	for (i = 0; i < 30; i++) {
		if (((OFFICE_SLOT*) g_office_slots)[i].status != 3 || ((OFFICE_SLOT*) g_office_slots)[i].pcount >= 4) {
			continue;
		}
		t = (unsigned char) ((OFFICE_SLOT*) g_office_slots)[i].mamt;
		if (amt_GetOfficeAffinity(who, t, &score) == 0) {
			continue;
		}
		found = 0;
		for (j = n - 1; j >= 0 && !found; j--) {
			if (picks[j].type == t) {
				found = 1;
			}
		}
		if (found) {
			continue;
		}
		found = 0;
		for (j = n - 1; j >= 0; j--) {
			if (picks[j].rank < (unsigned char) g_office_role_templates[t].f8) {
				continue;
			}
			if (picks[j].rank != (unsigned char) g_office_role_templates[t].f8 || !(picks[j].score <= score)) {
				found = 1;
				break;
			}
		}
		if (j == -1) {
			j = 0;
			if (picks[0].rank < (unsigned char) g_office_role_templates[t].f8 ||
			    (picks[0].rank == (unsigned char) g_office_role_templates[t].f8 && picks[0].score <= score)) {
				found = 1;
			}
		}
		if (found) {
			count++;
			for (k = n - 1; k > j; k--) {
				picks[k] = picks[k - 1];
			}
			picks[j].rank = (unsigned char) g_office_role_templates[t].f8;
			picks[j].score = score;
			picks[j].type = t;
		}
	}
	return count < n ? count : n;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e7150 */
/* ADDRESS: GOLDTL 0x004e8d10 */
int __cdecl amt_SelectOfficeCandidates(char* who, int n, OFFICE_PICK* picks)
{
	float score;
	int count;
	int len;
	int i;
	int j;
	int k;
	int t;
	int better;

	count = 0;
	if (n <= 0)
		return 0;
	len = n * 4;
	__asm {
		mov edi, picks
		mov ebx, len
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	for (j = n - 1; j >= 0; j--) {
		picks[j].score = -100.0f;
		picks[j].type = 0;
		picks[j].rank = 0;
	}
	for (i = 0; i < 30; i++) {
		if (((Slot_4e8d10*)amt_OfficeSlots)[i].state != 3 || ((Slot_4e8d10*)amt_OfficeSlots)[i].count >= 4)
			continue;
		t = ((Slot_4e8d10*)amt_OfficeSlots)[i].type;
		if (amt_GetOfficeAffinity((unsigned char*) who, t, &score) == 0)
			continue;
		better = 0;
		for (j = n - 1; j >= 0; j--) {
			if (better)
				break;
			if (picks[j].type == t)
				better = 1;
		}
		if (better)
			continue;
		better = 0;
		for (j = n - 1; j >= 0; j--) {
			if (picks[j].rank < ((Tmpl_4e8d10*)g_68da68)[t].rank)
				continue;
			if (picks[j].rank != ((Tmpl_4e8d10*)g_68da68)[t].rank || !(picks[j].score <= score)) {
				better = 1;
				break;
			}
		}
		if (j == -1) {
			j = 0;
			if (picks[0].rank < ((Tmpl_4e8d10*)g_68da68)[t].rank ||
			    (picks[0].rank == ((Tmpl_4e8d10*)g_68da68)[t].rank && picks[0].score <= score))
				better = 1;
		}
		if (better) {
			count++;
			for (k = n - 1; k > j; k--) {
				picks[k].rank = picks[k - 1].rank;
				picks[k].score = picks[k - 1].score;
				picks[k].type = picks[k - 1].type;
			}
			picks[j].rank = ((Tmpl_4e8d10*)g_68da68)[((Slot_4e8d10*)amt_OfficeSlots)[i].type].rank;
			picks[j].score = score;
			picks[j].type = ((Slot_4e8d10*)amt_OfficeSlots)[i].type;
		}
	}
	if (count < n)
		return count;
	return n;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_RankAllOffices(unsigned char* who, int n, OFFICE_PICK* picks, int* full_out)
{
	int __cdecl amt_GetOfficeAffinity(unsigned char* entity, int role, float* out);
	float score;
	int count;
	int i;
	int j;
	int k;
	int t;
	int found;
	int full;

	count = 0;
	full = 0;
	if (n <= 0) {
		return 0;
	}
	for (j = n - 1; j >= 0; j--) {
		picks[j].score = -100.0f;
		picks[j].type = 0;
		picks[j].rank = 0;
	}
	for (i = 0; i < 30; i++) {
		if (((OFFICE_SLOT*) g_office_slots)[i].status != 3) {
			continue;
		}
		t = (unsigned char) ((OFFICE_SLOT*) g_office_slots)[i].mamt;
		if (amt_GetOfficeAffinity(who, t, &score) == 0) {
			continue;
		}
		if (((OFFICE_SLOT*) g_office_slots)[i].pcount >= 4) {
			full = 1;
			continue;
		}
		found = 0;
		for (j = n - 1; j >= 0 && !found; j--) {
			if (picks[j].type == t) {
				found = 1;
			}
		}
		if (found) {
			continue;
		}
		found = 0;
		for (j = n - 1; j >= 0; j--) {
			if (picks[j].rank < (unsigned char) g_office_role_templates[t].f8) {
				continue;
			}
			if (picks[j].rank != (unsigned char) g_office_role_templates[t].f8 || !(picks[j].score <= score)) {
				found = 1;
				break;
			}
		}
		if (j == -1) {
			j = 0;
			if (picks[0].rank < (unsigned char) g_office_role_templates[t].f8 ||
			    (picks[0].rank == (unsigned char) g_office_role_templates[t].f8 && picks[0].score <= score)) {
				found = 1;
			}
		}
		if (found) {
			count++;
			for (k = n - 1; k > j; k--) {
				picks[k] = picks[k - 1];
			}
			picks[j].rank = (unsigned char) g_office_role_templates[t].f8;
			picks[j].score = score;
			picks[j].type = t;
		}
	}
	if (full_out != 0) {
		*full_out = full;
	}
	return count < n ? count : n;
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004e8ee0 */
int __cdecl amt_RankAvailableOffices(char* who, int n, OFFICE_PICK* picks, int* full_out)
{
	int count;
	int len;
	int i;
	int j;
	int k;
	int t;
	int better;
	int full;

	count = 0;
	full = 0;
	if (n <= 0)
		return 0;
	len = n * 4;
	__asm {
		mov edi, picks
		mov ebx, len
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	for (j = n - 1; j >= 0; j--) {
		picks[j].score = -100.0f;
		picks[j].type = 0;
		picks[j].rank = 0;
	}
	for (i = 0; i < 30; i++) {
		float score;

		if (((Slot_4e8d10*)amt_OfficeSlots)[i].state != 3)
			continue;
		t = ((Slot_4e8d10*)amt_OfficeSlots)[i].type;
		if (amt_GetOfficeAffinity((unsigned char*) who, t, &score) == 0)
			continue;
		if (((Slot_4e8d10*)amt_OfficeSlots)[i].count >= 4) {
			full = 1;
			continue;
		}
		better = 0;
		for (j = n - 1; j >= 0; j--) {
			if (better)
				break;
			if (picks[j].type == t)
				better = 1;
		}
		if (better)
			continue;
		better = 0;
		for (j = n - 1; j >= 0; j--) {
			if (picks[j].rank < ((Tmpl_4e8d10*)g_68da68)[t].rank)
				continue;
			if (picks[j].rank != ((Tmpl_4e8d10*)g_68da68)[t].rank || !(picks[j].score <= score)) {
				better = 1;
				break;
			}
		}
		if (j == -1) {
			j = 0;
			if (picks[0].rank < ((Tmpl_4e8d10*)g_68da68)[t].rank ||
			    (picks[0].rank == ((Tmpl_4e8d10*)g_68da68)[t].rank && picks[0].score <= score))
				better = 1;
		}
		if (better) {
			count++;
			for (k = n - 1; k > j; k--) {
				picks[k].rank = picks[k - 1].rank;
				picks[k].score = picks[k - 1].score;
				picks[k].type = picks[k - 1].type;
			}
			picks[j].rank = ((Tmpl_4e8d10*)g_68da68)[((Slot_4e8d10*)amt_OfficeSlots)[i].type].rank;
			picks[j].score = score;
			picks[j].type = ((Slot_4e8d10*)amt_OfficeSlots)[i].type;
		}
	}
	if (full_out != 0)
		*full_out = full;
	if (count < n)
		return count;
	return n;
}
#endif

#if defined(REBREW_SERVER)
void* __cdecl amt_GetRoleHolder(int role)
{
	int i;

	for (i = 0; i < 0x2a; i++) {
		if ((char) ((OFFICE_SLOT*) g_office_slots)[i].mamt == role) {
			return gm_LookupEntityRecordById(((OFFICE_SLOT*) g_office_slots)[i].mplayerid);
		}
	}
	return 0;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e7510 */
/* ADDRESS: GOLDTL 0x004e90d0 */
char* __cdecl amt_FindOfficeHolderByType(int value)
{
	int index;
	int cursor;

	for (index = 0, cursor = (int) amt_OfficeSlots + 8; cursor < (int) amt_OfficeSlots + 0x3f8; cursor += 0x18, index++) {
		if (*(unsigned char*) cursor == value) {
			return gm_LookupEntityRecordById(((fcn_004e90d0_E*) ((int) amt_OfficeSlots + 4))[index].a);
		}
	}
	return 0;
}
#endif

#if defined(REBREW_SERVER)
void* __cdecl amt_GetSuperiorHolder(int role)
{
	OFFICE_SLOT slot;

	if (role == 0x24) {
		if (amt_GetSlotByRole(0x27, &slot) != 0) {
			return gm_LookupEntityRecordById(slot.mplayerid);
		}
	}
	else if (role == 0x25 || role == 0x23) {
		if (amt_GetSlotByRole(0x26, &slot) != 0) {
			return gm_LookupEntityRecordById(slot.mplayerid);
		}
	}
	return 0;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e7550 */
/* ADDRESS: GOLDTL 0x004e9110 */
char* __cdecl amt_GetOfficeHolderRecord(int kind)
{
	Rec18_68da68 r;

	if (kind == 0x24) {
		if (amt_FindOfficeSlotByType(0x27, &r) != 0)
			return gm_LookupEntityRecordById(r.x4);
	}
	else if (kind == 0x25 || kind == 0x23) {
		if (amt_FindOfficeSlotByType(0x26, &r) != 0)
			return gm_LookupEntityRecordById(r.x4);
	}
	return 0;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_IsNextRoleStep(unsigned char* entity, int role)
{
	OFFICE_ROLE_TEMPLATE want;
	OFFICE_ROLE_TEMPLATE held;
	int a;
	int b;

	if (role == 0 || role > 0x1b) {
		return 0;
	}
	if (amt_GetRoleTemplate(role, &want) == 0) {
		return 0;
	}
	if (amt_GetRoleTemplate(entity[0x166], &held) == 0) {
		return 0;
	}
	if (want.f4 != held.f4) {
		return 0;
	}
	a = (want.f8 & 0xff) % 3;
	b = (held.f8 & 0xff) % 3;
	if (a == 0 && b != 0) {
		return 1;
	}
	if (a == 2 && b == 0) {
		return 1;
	}
	if (a == 1 && b == 2) {
		return 1;
	}
	return 0;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e75c0 */
/* ADDRESS: GOLDTL 0x004e9180 */
int __cdecl amt_IsNextOfficeStep(void* rec, int role)
{
	Rec18_68da68 r[2];

	if (role == 0 || role > 0x1b) {
		return 0;
	}
	if (!amt_GetRoleTemplate(role, &r[0])) {
		return 0;
	}
	if (!amt_GetRoleTemplate(*(unsigned char*) ((char*) rec + 0x166), &r[1])) {
		return 0;
	}
	if (r[0].x4 != r[1].x4) {
		return 0;
	}
	if (r[0].type % 3 == 0 && r[1].type % 3 != 0) {
		return 1;
	}
	if (r[0].type % 3 == 2 && r[1].type % 3 == 0) {
		return 1;
	}
	if (r[0].type % 3 == 1 && r[1].type % 3 == 2) {
		return 1;
	}
	return 0;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_HasIdleSuperior(int role)
{
	OFFICE_ROLE_TEMPLATE tmpl;
	OFFICE_SLOT list[6];
	int n;
	int i;
	unsigned char* e;

	if (amt_GetRoleTemplate(role, &tmpl) == 0) {
		return 0;
	}
	n = amt_ListSlotsOfGroup(tmpl.f4, 6, list);
	if (n == 0) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		e = gm_LookupEntityRecordById(list[i].mplayerid);
		if (e != 0 && amt_IsNextRoleStep(e, role) != 0 && e[0x1b1] == 0) {
			return 1;
		}
	}
	return 0;
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004e9270 */
int __cdecl amt_HasIdleSuperior(int k)
{
	Rec18_68da68 a;
	OFFICE_SLOT list[6];
	int n;
	int i;
	unsigned char* e;

	if (amt_GetRoleTemplate(k, (OFFICE_ROLE_TEMPLATE*) &a) == 0)
		return 0;
	n = amt_FindOfficeSlotsByKind(a.x4, 6, list);
	if (n == 0)
		return 0;
	for (i = 0; i < n; i++) {
		e = gm_LookupEntityRecordById(list[i].mplayerid);
		if (e != 0 && amt_IsNextOfficeStep(e, k) != 0 && e[0x1b1] == 0)
			return 1;
	}
	return 0;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_ListSuperiors(int role, int max, unsigned char** out)
{
	OFFICE_ROLE_TEMPLATE tmpl;
	OFFICE_SLOT list[6];
	int n;
	int i;
	int cnt;
	unsigned char* e;

	if (amt_GetRoleTemplate(role, &tmpl) == 0) {
		return 0;
	}
	n = amt_ListSlotsOfGroup(tmpl.f4, max < 6 ? max : 6, list);
	if (n == 0) {
		return 0;
	}
	n = n < max ? n : max;
	cnt = 0;
	for (i = 0; i < n; i++) {
		e = gm_LookupEntityRecordById(list[i].mplayerid);
		if (e != 0 && amt_IsNextRoleStep(e, role) != 0) {
			out[cnt++] = e;
		}
	}
	return cnt;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e76b0 */
/* ADDRESS: GOLDTL 0x004e9310 */
int __cdecl amt_CollectOfficeCandidates(int k, int max, unsigned char** out)
{
	Rec18_68da68 a;
	OFFICE_SLOT list[6];
	int n;
	int i;
	int cnt;
	unsigned char* e;

	if (amt_GetRoleTemplate(k, (OFFICE_ROLE_TEMPLATE*) &a) == 0)
		return 0;
	n = amt_FindOfficeSlotsByKind(a.x4, MIN(max, 6), list);
	if (n == 0)
		return 0;
	n = MIN(n, max);
	cnt = 0;
	for (i = 0; i < n; i++) {
		e = gm_LookupEntityRecordById(list[i].mplayerid);
		if (e != 0 && amt_IsNextOfficeStep(e, k) != 0)
			out[cnt++] = e;
	}
	return cnt;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_ListPromotionRoles(unsigned char* entity, int max, int* out)
{
	OFFICE_ROLE_TEMPLATE tmpl;
	OFFICE_SLOT list[6];
	int want;
	int n;
	int i;
	int cnt;
	int role;
	int level;

	if (entity[0x166] == 0) {
		return 0;
	}
	if (amt_GetRoleTemplate(entity[0x166], &tmpl) == 0) {
		return 0;
	}
	n = amt_ListSlotsOfGroup(tmpl.f4, 6, list);
	if (n == 0) {
		return 0;
	}
	want = (tmpl.f8 & 0xff) % 3 == 1 ? 0 : (tmpl.f8 & 0xff) - 1;
	cnt = 0;
	for (i = 0; i < n && cnt < max; i++) {
		if (list[i].status == 3) {
			role = (unsigned char) list[i].mamt;
			amt_GetRoleTemplate(role, &tmpl);
			level = tmpl.f8 & 0xff;
			if (level % 3 == 0) {
				out[cnt++] = role;
			}
			else if (want == level) {
				out[cnt++] = role;
				if (tmpl.f10 != 0) {
					break;
				}
			}
		}
	}
	return cnt;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e7770 */
/* ADDRESS: GOLDTL 0x004e93d0 */
int __cdecl amt_ListPromotionOffices(unsigned char* entity, int max, int* out)
{
	int want;
	int i;
	int n;
	Rec18_4e93d0 r;
	OFFICE_SLOT arr[6];
	int cnt;
	int id;
	int v;

	if (entity[0x166] == 0)
		return 0;
	if (amt_GetRoleTemplate(entity[0x166], (OFFICE_ROLE_TEMPLATE*) &r) == 0)
		return 0;
	n = amt_FindOfficeSlotsByKind(r.id, 6, arr);
	if (n == 0)
		return 0;
	if (r.kind % 3 == 1)
		want = 0;
	else
		want = r.kind - 1;
	cnt = 0;
	for (i = 0; i < n; i++) {
		if (cnt >= max)
			break;
		if (arr[i].status == 3) {
			id = arr[i].mamt;
			amt_GetRoleTemplate(id, (OFFICE_ROLE_TEMPLATE*) &r);
			v = r.kind;
			if (v % 3 == 0) {
				out[cnt++] = id;
			} else if (want == v) {
				out[cnt++] = id;
				if (r.f10 != 0)
					break;
			}
		}
	}
	return cnt;
}
#endif

#if defined(REBREW_SERVER)
void __cdecl amt_ExpandSlots(int count, OFFICE_SLOT* p)
{
	int i;

	for (i = 0; i < count; i++) {
		p[i] = ((OFFICE_SLOT*) g_office_slots)[(unsigned char) p[i].id];
	}
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004e9500 */
void __cdecl amt_LoadOfficeSlots(int count, OFFICE_SLOT_EXPAND* p)
{
	int i;

	if (count <= 0) {
		return;
	}
	for (i = 0; i < count; i++) {
		p[i] = ((OFFICE_SLOT_EXPAND*) 0x9a9220)[*(unsigned char*) &p[i]];
	}
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_FindVacantRoleBelow(int role)
{
	OFFICE_SLOT slot;

	if (role == 0) {
		return 0;
	}
	if (role >= 0x1b) {
		role = 0x1b;
	}
	while (role > 0) {
		if (amt_GetSlotByRole(role, &slot) != 0 && slot.status == 3 && slot.pcount <= 1) {
			break;
		}
		role--;
	}
	return role;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e78a0 */
/* ADDRESS: GOLDTL 0x004e9530 */
int __cdecl amt_FindHighestOccupiedOffice(int n)
{
	Rec18_68da68 r;

	if (n == 0) {
		return 0;
	}
	if (n >= 0x1b) {
		n = 0x1b;
	}
	while (n > 0) {
		if (amt_FindOfficeSlotByType(n, &r) != 0 && r.x10 == 3 && r.xc <= 1) {
			break;
		}
		n--;
	}
	return n;
}
#endif

/* ADDRESS: GOLD 0x004e78f0 */
/* ADDRESS: GOLDTL 0x004e9580 */
int __cdecl amt_GetRankLimits(int role, OFFICE_RANK_LIMITS* out)
{
	OFFICE_ROLE_TEMPLATE tmpl;

	if (amt_GetRoleTemplate(role, &tmpl) == 0) {
		return 0;
	}
	switch ((unsigned char) tmpl.f8) {
	case 1:
	case 2:
		out->lo = 0x10;
		out->hi = 0x14;
		out->cost_lo = 0x9c400;
		out->cost_hi = 0x138800;
		out->a = 3;
		out->b = 4;
		out->c = 2;
		out->d = 3;
		return 1;
	case 3:
	case 4:
		out->lo = 0x14;
		out->hi = 0x18;
		out->cost_lo = 0x138800;
		out->cost_hi = 0x1d4c00;
		out->a = 4;
		out->b = 5;
		out->c = 3;
		out->d = 4;
		return 1;
	case 5:
		out->lo = 0x18;
		out->hi = 0x1c;
		out->cost_lo = 0x1d4c00;
		out->cost_hi = 0x271000;
		out->a = 5;
		out->b = 6;
		out->c = 3;
		out->d = 4;
		return 1;
	case 6:
		out->lo = 0x18;
		out->hi = 0x1c;
		out->cost_lo = 0x222e00;
		out->cost_hi = 0x30d400;
		out->a = 6;
		out->b = 7;
		out->c = 3;
		out->d = 5;
		return 1;
	case 7:
	case 8:
	case 9:
		out->lo = 0x1c;
		out->hi = 0x20;
		out->cost_lo = 0x30d400;
		out->cost_hi = 0x493e00;
		out->a = 7;
		out->b = 8;
		out->c = 5;
		out->d = 6;
		return 1;
	}
	return 0;
}

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004e9730 */
unsigned int __cdecl amt_SpawnOfficeCandidate(unsigned int role)
{
	OFFICE_RANK_LIMITS t;
	int v;
	int r;
	int x;


	if (amt_GetRankLimits((int) role, &t) == 0) {
		return 0xffffffff;
	}
	if (*(int*) 0x68de28 == 2) {
		*(int*) 0x68de28 = gm_RandomMod(2) & 0xffff;
	}
	x = t.c;
	r = (gm_RandomMod(t.d - x + 1) & 0xffff) + x;
	v = gm_GetRangeStatId((gm_RandomMod(0xc) & 0xffff) + 1, r);
	x = t.lo;
	v = cm_RequestAllocSpieler(0x13, -1, -1, (short) (gm_RandomMod(t.hi - x + 1) + x), -1, (char) v, 0, *(char*) 0x68de28);

	*(int*) 0x68de28 = 1 - *(int*) 0x68de28;
	return v;
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004e97f0 */
int __cdecl amt_PurchaseOfficeApplication(unsigned char* entity, int office_id)
{
	int mode;
	OFFICE_RANK_LIMITS info;
	unsigned short rnd;
	int lo;

	mode = 3;
	if (entity[2] != 0x13) {
		return 0;
	}
	if (amt_GetRankLimits(office_id, &info) == 0) {
		return 0;
	}
	lo = info.cost_lo;
	cm_RequestTransferCurrencyNoKill(*(int*) (entity + 4), -1, g_773d75,
	    (unsigned short) gm_RandomMod((unsigned short) (info.cost_hi - lo + 1)) + lo);
	rnd = (unsigned short) gm_RandomMod((unsigned short) (info.b - info.a + 1)) + info.a;
	cm_BeginPacketFieldDelta(entity, *(int*) (entity + 4));
	cm_AppendPacketFieldDelta(1, 1, 0xd, (char*) &rnd);
	cm_AppendPacketFieldDelta(1, 1, 2, (char*) &mode);
	cm_AppendPacketFieldDelta(1, 1, 0x167, (char*) &office_id);
	cm_RequestChangeAttribute();
	amt_ApplyForOffice(entity, office_id);
	return 1;
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004e98d0 */
int* __cdecl amt_CountRolesByLevel(void)
{
	Rec18_68da68 tmpl;
	int p;
	unsigned char state;

	memset(g_9a9620, 0, sizeof(g_9a9620));
	for (p = (int) (g_7f4ca0 + 0x167); p < (int) (g_7f4ca0 + 0x167 + 0x65400); p += 0x21c) {
		state = *(unsigned char*) (p - 0x165);
		if (state >= 2 && state <= 7) {
			if (*(unsigned char*) p == 0) {
				g_9a9620[0]++;
			} else {
				amt_GetRoleTemplate(*(unsigned char*) p, (OFFICE_ROLE_TEMPLATE*) &tmpl);
				g_9a9620[tmpl.type]++;
			}
		}
	}
	return g_9a9620;
}
#endif

/* ADDRESS: GOLDTL 0x004e9950 */
int __cdecl amt_ListRolesOfLevel(int level, int max, int* out)
{
	OFFICE_ROLE_TEMPLATE tmpl;
	int i;
	int n;
	int role;

	if (max < 1) {
		return 0;
	}
	n = 0;
	for (i = 0; i < 0x1c && n < max; i++) {
		role = (unsigned char) ((OFFICE_SLOT*) g_office_slots)[i].mamt;
		amt_GetRoleTemplate(role, &tmpl);
		if ((unsigned char) tmpl.f8 == level) {
			out[n++] = role;
		}
	}
	return n;
}

/* ADDRESS: GOLD 0x004e7c40 */
/* ADDRESS: GOLDTL 0x004e99c0 */
int __cdecl amt_GetRoleLevel(int role)
{
	OFFICE_ROLE_TEMPLATE tmpl;

	amt_GetRoleTemplate(role, &tmpl);
	return tmpl.f8 & 0xff;
}

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004e99e0 */
void __cdecl amt_ResolveOfficeApplications(int office, int count, OFFICE_SLOT* list)
{
	int remain;
	int i;
	int k;
	int n;
	int b;
	struct { int relation; unsigned int vote[4]; OFFICE_SLOT* recs[4]; int ids[4]; unsigned int score[6]; } work;

	char* self;
	char* other;
	char* ent;
	OFFICE_SLOT* p;


	int version;
	int held;
	int id;
	int j;
	int best;
	int pick;
	int tie;
	char* h;

	remain = 0;
	for (i = count, p = list; i > 0; i--, p++) {
		if (p->status == 2) {
			remain++;
		}
	}
	for (i = 0, p = list; i < count && remain != 0; i++, p++) {
		work.vote[0] = 0;
		work.vote[1] = 0;
		work.vote[2] = 0;
		if (p->status != 2) {
			continue;
		}
		remain--;
		self = gm_LookupEntityRecordById(p->mplayerid);
		other = gm_LookupEntityRecordById(p->msetter);
		if (self == 0 || other == 0) {
			continue;
		}
		for (k = 0; count > k; k++) {
			work.score[k] = 3;
			ent = gm_LookupEntityRecordById(list[k].mplayerid);
			if (ent != 0 && *(char*) (ent + 0x166) != 0
			    && *(char*) (ent + 0x1b1) == 0) {
				held = ai_CompareOfficeCandidates((unsigned short*) ent,
				    (unsigned short*) self, (unsigned short*) other,
				    &work.relation);
				work.score[k] = held;
				work.vote[held]++;
			}
		}
		if (work.vote[0] > work.vote[1]) {
			for (k = 0; k < count; k++) {
				id = list[k].mplayerid;
				if (id != *(int*) (self + 4) && id != -1
				    && work.score[k] <= 2) {
					if (work.score[k] == 0) {
						cm_RequestCopyEntityData(id, *(int*) (self + 4), -10, 1);
					}
					if (work.score[k] == 1) {
						cm_RequestCopyEntityData(id, *(int*) (self + 4), 10, 1);
					} else {
						cm_RequestCopyEntityData(id, *(int*) (self + 4), -4, 1);
					}
				}
			}
			version = amt_SendOfficeCommand(p->id, 0, 0, 3, 0xff);
			if (version != -1) {
				do {
					if (cm_GetCommandStatus(version) != 0) {
						break;
					}
					cm_StepCommandQueue();
				} while (1);
			}
		} else {
			for (k = 0; k < count; k++) {
				id = list[k].mplayerid;
				if (id != *(int*) (self + 4) && id != -1
				    && work.score[k] <= 2) {
					if (work.score[k] == 0) {
						cm_RequestCopyEntityData(id, *(int*) (self + 4), -20, 1);
					} else if (work.score[k] == 1) {
						cm_RequestCopyEntityData(id, *(int*) (self + 4), 0x14, 1);
					} else {
						cm_RequestCopyEntityData(id, *(int*) (self + 4), 4, 1);
					}
				}
			}
			version = amt_SendOfficeCommand(p->id, (unsigned char*) self, 0, 1, 0xff);
			if (version != -1) {
				do {
					if (cm_GetCommandStatus(version) != 0) {
						break;
					}
					cm_StepCommandQueue();
				} while (1);
			}
		}
	}
	remain = 0;
	for (i = count, p = list; i > 0; i--, p++) {
		if (p->status == 3) {
			remain++;
		}
	}
	for (i = 0, p = list; i < count && remain != 0; i++, p++) {
		work.vote[0] = 0;
		work.vote[1] = 0;
		work.vote[2] = 0;
		work.vote[3] = 0;
		work.score[0] = (unsigned int) -1;
		work.score[1] = (unsigned int) -1;
		work.score[2] = (unsigned int) -1;
		work.score[3] = (unsigned int) -1;
		work.score[4] = (unsigned int) -1;
		work.score[5] = (unsigned int) -1;

		if (p->status != 3 || p->pcount == 0) {
			continue;
		}
		remain--;
		n = 0;
		{
			for (h = (char*) g_slot_table; (int) h < (int) (g_slot_table + 0x65400);
			    h += 0x21c) {
				if (n >= p->pcount || 4 <= n) {
					break;
				}
				if (*(unsigned char*) (h + 0x168) == p->mamt) {
					work.recs[n] = (OFFICE_SLOT*) h;
					work.ids[n] = *(int*) (h + 4);
					n++;
				}
			}
		}
		if (n == 0) {
			continue;
		}
		if (n == 1) {
			version = amt_SendOfficeCommand(p->id, (unsigned char*) work.recs[0], 0, 1, 0xff);
			if (version != -1) {
				do {
					if (cm_GetCommandStatus(version) != 0) {
						break;
					}
					cm_StepCommandQueue();
				} while (1);
			}
		} else {
			if (n < 4) {
				for (k = n; k < 4; k++) {
					work.ids[k] = -1;
				}
				for (k = n; k < 4; k++) {
					work.recs[k] = 0;
				}
			}
			for (k = 0; k < count; k++) {
				work.score[k] = -1;
				ent = gm_LookupEntityRecordById(list[k].mplayerid);
				if (ent != 0 && amt_IsNextOfficeStep(ent, p->mamt) != 0
				    && *(unsigned char*) (ent + 0x1b1) <= 0) {
					work.score[k] = ai_SelectOfficeCandidate(p->id,
					    (unsigned short*) ent, work.ids, &work.relation);
				}
			}
			for (k = 0; k < count; k++) {
				if (work.score[k] == -1) {
					continue;
				}
				for (j = 0; j < n; j++) {
					if (*(int*) ((char*) work.recs[j] + 4) == work.score[k]) {
						work.vote[j]++;
					}
				}
			}
			best = -1;
			pick = -1;
			tie = 1;
			for (j = 0; j < n; j++) {
				if ((int) work.vote[j] > best) {
					tie = 0;
					best = work.vote[j];
					pick = j;
				} else if ((int) work.vote[j] == best) {
					tie = 1;
				}
			}
			if (!tie) {
				version = amt_SendOfficeCommand(p->id,
				    (unsigned char*) work.recs[pick], 0, 1, 0xff);
				if (version != -1) {
					do {
						if (cm_GetCommandStatus(version) != 0) {
							break;
						}
						cm_StepCommandQueue();
					} while (1);
				}
			} else {
				k = (unsigned short) gm_RandomMod(n);
				for (j = n; j != 0; j--) {
					if (work.vote[k] == best) {
						pick = k;
						break;
					}
					k = (k + 1) % n;
				}
				version = amt_SendOfficeCommand(p->id,
				    (unsigned char*) work.recs[pick], 0, 1, 0xff);
				if (version != -1) {
					do {
						if (cm_GetCommandStatus(version) != 0) {
							break;
						}
						cm_StepCommandQueue();
					} while (1);
				}
			}
		}
	}
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004e9ee0 */
int __cdecl amt_ProcessOfficeElections(void)
{
	int flags[6] = {0, 0, 0, 0, 0, 0};
	int order[6] = {6, 5, 4, 3, 2, 1};
	OFFICE_SLOT recs[6];
	char* e1;
	char* e2;
	char* h;
	unsigned char m;
	int n;
	int result;
	int i;
	int j;
	int v;

	result = 0;
	for (i = 0; i < 6; i++) {
		n = amt_FindOfficeSlotsByKind(order[i], 6, recs);
		if (n > 0) {
			for (j = 0; j < n; j++) {
				if (recs[j].status == 2) {
					e1 = gm_LookupEntityRecordById(recs[j].msetter);
					e2 = gm_LookupEntityRecordById(recs[j].mplayerid);
					if (e1 != 0 && *(unsigned char*) (e1 + 8) > 0
						&& e2 != 0 && *(unsigned char*) (e2 + 8) > 0) {
						flags[i] |= 1;
					} else if (e1 != 0 && *(unsigned char*) (e1 + 8)) {
						v = amt_SendOfficeCommand(recs[j].id, 0, 0, 4, 0xff);
						while (v != -1 && !cm_GetCommandStatus(v)) {
							cm_StepCommandQueue();
						}
					} else {
						v = amt_SendOfficeCommand(recs[j].id, (unsigned char*) e2, 0, 1, 0xff);
						while (v != -1 && !cm_GetCommandStatus(v)) {
							cm_StepCommandQueue();
						}
					}
				} else if (recs[j].status == 3 && recs[j].pcount > 0) {
					m = recs[j].mamt;
					for (h = (char*) g_7f4ca2;
						(int) h < (int) (g_7f4ca2 + 768);
						h += 0x21c) {
						if (*(unsigned char*) (h + 0x166) == m) {
							flags[i] |= 1;
							if ((*h == 6 || *h == 7) && h[0x1af] == 0) {
								flags[i] |= 2;
								break;
							}
						}
					}
				}
			}
		}
		if (flags[i] & 1) {
			for (j = 0; j < n; j++) {
				e1 = gm_LookupEntityRecordById(recs[j].mplayerid);
				if (e1 != 0 && (e1[2] == 6 || e1[2] == 7) && e1[0x1b1] == 0) {
					flags[i] |= 2;
					break;
				}
			}
		}
		if (flags[i] & 2) {
			result = 1;
		} else if ((flags[i] & 1) && result == 0) {
			amt_ResolveOfficeApplications(order[i], n, recs);
		}
	}
	return result;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_GetGroupVacancyFlags(int group)
{
	extern char g_entity_state_base[2];
	extern char g_dynamic_entities[];
	OFFICE_SLOT list[6];
	unsigned char* holder;
	unsigned char* setter;
	unsigned char* e;
	int flags;
	int n;
	int i;
	int j;

	flags = 0;
	n = amt_ListSlotsOfGroup(group, 6, list);
	for (i = 0; i < n; i++) {
		if (list[i].status == 2) {
			holder = gm_LookupEntityRecordById(list[i].msetter);
			setter = gm_LookupEntityRecordById(list[i].mplayerid);
			if (holder == 0 || holder[8] == 0 || holder[0x1b1] != 0 || setter == 0 || setter[8] == 0) {
				continue;
			}
			for (j = 0; j < n; j++) {
				if (list[j].mplayerid == list[i].msetter) {
					flags |= 1;
					break;
				}
			}
		}
		else if (list[i].status == 3 && list[i].pcount > 0) {
			for (e = (unsigned char*) g_entity_state_base; e < (unsigned char*) g_dynamic_entities; e += 0x21c) {
				if (e[0x166] == (unsigned char) list[i].mamt) {
					flags |= 1;
					if ((e[0] == 6 || e[0] == 7) && e[0x1af] == 0) {
						flags |= 2;
						break;
					}
				}
			}
		}
	}
	if (flags & 1) {
		for (i = 0; i < n; i++) {
			e = gm_LookupEntityRecordById(list[i].mplayerid);
			if (e != 0 && (e[2] == 6 || e[2] == 7) && e[0x1b1] == 0) {
				flags |= 2;
				break;
			}
		}
	}
	return (flags & 2) >> 1;
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004ea130 */
unsigned int __cdecl amt_GetOfficeGroupHumanFlags(unsigned int officeKind)
{
	EVT_ARG args[6];
	int flag;
	int n;
	int i;
	int j;
	int id;
	char* obj;
	char* obj2;
	char* p;

	flag = 0;
	n = amt_FindOfficeSlotsByKind(officeKind, 6, (OFFICE_SLOT*) args);
	if (n <= 0) {
		goto done;
	}
	for (i = 0; i < n; i++) {
		if ((char) args[i].type == 2) {
			id = args[i].ref;
			obj = gm_LookupEntityRecordById(id);
			obj2 = gm_LookupEntityRecordById(args[i].id);
			if (obj == 0 || (unsigned char) obj[8] <= 0 || obj[0x1b1] != 0 || obj2 == 0 || (unsigned char) obj2[8] <= 0) {
				continue;
			}
			for (j = 0; j < n; j++) {
				if (args[j].id == id) {
					flag = flag | 1;
					break;
				}
			}
		} else if ((char) args[i].type == 3) {
			if (args[i].n <= 0) {
				continue;
			}
			p = (char*) 0x7f4ca2;
			while ((int) p < 0x85a0a2) {
				if ((char) p[0x166] == (char) args[i].c8) {
					flag = flag | 1;
					if ((*p == 6 || *p == 7) && p[0x1af] == 0) {
						flag = flag | 2;
						break;
					}
				}
				p += 0x21c;
			}
		}
	}
done:
	if ((flag & 1) != 0) {
		for (i = 0; i < n; i++) {
			obj = gm_LookupEntityRecordById(args[i].id);
			if (obj == 0) {
				continue;
			}
			if ((*(unsigned char*) (obj + 2) != 6 && *(unsigned char*) (obj + 2) != 7) ||
			    *(unsigned char*) (obj + 0x1b1) != 0) {
				continue;
			}
			flag = flag | 2;
			break;
		}
	}
	return (flag & 2) >> 1;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_IsPendingAssignment(int group, char* slot)
{
	OFFICE_SLOT list[6];
	int n;
	int i;
	unsigned char* a;
	unsigned char* b;

	if (slot[0x10] != 2) {
		return 0;
	}
	n = amt_ListSlotsOfGroup(group, 6, list);
	a = gm_LookupEntityRecordById(*(int*) (slot + 0x14));
	b = gm_LookupEntityRecordById(*(int*) (slot + 4));
	if (a == 0 || a[8] == 0 || a[0x1b1] != 0 || b == 0 || b[8] == 0) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		if (list[i].mplayerid == *(int*) (slot + 0x14)) {
			return 1;
		}
	}
	return 0;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e8530 */
/* ADDRESS: GOLDTL 0x004ea2b0 */
int __cdecl amt_IsCandidateInOffice(int kind, char* x)
{
	OFFICE_SLOT list[6];
	int n;
	int i;
	unsigned char* a;
	unsigned char* b;

	if (x[0x10] != 2)
		return 0;
	n = amt_FindOfficeSlotsByKind(kind, 6, list);
	a = gm_LookupEntityRecordById(*(int*) (x + 0x14));
	b = gm_LookupEntityRecordById(*(int*) (x + 4));
	if (a == 0 || a[8] <= 0 || a[0x1b1] != 0 || b == 0 || b[8] <= 0)
		return 0;
	for (i = 0; i < n; i++) {
		if (list[i].mplayerid == *(int*) (x + 0x14))
			return 1;
	}
	return 0;
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004ea350 */
void __cdecl amt_SyncAllOfficeSlots(void)
{
	unsigned char* r;
	char* p;
	char* e;
	int res;



	for (r = &amt_OfficeSlots[0].x10; (int) r < (int) &amt_OfficeSlots[30].x10; r += 0x18) {
		e = gm_LookupEntityRecordById(*(int*) (r - 0xc));
		res = -1;
		if (e != 0 && *(unsigned char*) (e + 8) != 0) {
			if (*r != 1) {
				res = amt_SendOfficeCommand(*(unsigned char*) (r - 0x10), e, 0, 1, 0xff);
			}
		} else {
			if (*r != 3) {
				res = amt_VacateOfficeSlot(*(unsigned char*) (r - 0x10));
			}
			if (e != 0 && *(unsigned char*) (e + 0x166) != 0) {
				int n = *(int*) (e + 4);
				int v;
				v = 0;
				cm_BeginPacketFieldDelta(e, n);
				cm_AppendPacketFieldDelta(1, 1, 0x166, &v);
				cm_RequestChangeAttribute();
			}
		}
		if (res != -1) {
			while (1) {
				if (cm_GetCommandStatus(res) != 0) {
					break;
				}
				cm_StepCommandQueue();
			}
		}
	}
	for (p = g_7f4ca0 + 0x168; (int) p < (int) (g_7f4ca0 + 0x168 + 0x65400); p += 0x21c) {
		if (*(unsigned char*) p != 0) {
			int v = 0;
			cm_BeginPacketFieldDelta(p - 0x168, *(int*) (p - 0x164));
			cm_AppendPacketFieldDelta(1, 1, 0x168, &v);
			cm_RequestChangeAttribute();
		}
	}
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_HasCouncilHolder(void)
{
	int left;
	int i;

	left = 7;
	for (i = 36; i != 0 && left != 0; i--) {
		if (g_office_role_templates[(unsigned char) ((OFFICE_SLOT*) g_office_slots)[i].mamt].f4 == 7) {
			if (((OFFICE_SLOT*) g_office_slots)[i].mplayerid != -1) {
				if (gm_LookupEntityRecordById(((OFFICE_SLOT*) g_office_slots)[i].mplayerid) != 0) {
					return 1;
				}
			}
			else {
				left--;
			}
		}
	}
	return 0;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e86e0 */
/* ADDRESS: GOLDTL 0x004ea460 */
int __cdecl amt_HasOccupiedOfficeType7(void)
{
	int n;
	int i;

	n = 7;
	for (i = 36; i != 0; i--) {
		if (n == 0) {
			break;
		}
		if (g_68da68[amt_OfficeSlots[i].type].x4 == 7) {
			if (amt_OfficeSlots[i].x4 != -1) {
				if (gm_LookupEntityRecordById(amt_OfficeSlots[i].x4) != 0) {
					return 1;
				}
			} else {
				n--;
			}
		}
	}
	return 0;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e8730 */
/* ADDRESS: GOLDTL 0x004ea4b0 */
void __cdecl amt_NotifyOfficeAppointed(unsigned char* e, int k)
{
	char buf[0x200];
	int i;

	if (e[2] != 6 && e[2] != 7 && e[2] != 5)
		return;
	io_FormatTextBuffer(buf, 0x1c19, *(unsigned short*) e, 0x1c1b, (e[9] != 0 ? 0x27b : 0x253) + k);
	for (i = 0; i < 0x300; i++) {
		if (g_7f4ca4[i * 0x21c - 2] == 6)
			he_PostEntityMessage(*(int*) (g_7f4ca4 + i * 0x21c), -1, buf, 0, 0x5fd, g_6b5c60);
		else if (g_7f4ca4[i * 0x21c - 2] == 7)
			he_PostEntityMessage(*(int*) (g_7f4ca4 + i * 0x21c), -1, buf, 0, 0x5fe, g_6b5c60);
	}
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e87e0 */
/* ADDRESS: GOLDTL 0x004ea560 */
void __cdecl amt_NotifyOfficeLost(void* entity, char* role)
{
	char buf[0x200];
	char kind;
	char* slot;

	if (entity == 0) {
		return;
	}
	kind = *(char*) ((char*) entity + 2);
	if (kind == 6 || kind == 7 || kind == 5) {
		io_FormatTextBuffer(buf, 0x1c21, *(unsigned short*) entity,
		    role + (*(char*) ((char*) entity + 9) ? 0x27b : 0x253));
		slot = g_7f4ca4;
		do {
			if (*(char*) (slot - 2) == 6) {
				he_PostEntityMessage(*(int*) slot, -1, buf, 0, 0x5fd, g_6b5c60);
			} else if (*(char*) (slot - 2) == 7) {
				he_PostEntityMessage(*(int*) slot, -1, buf, 0, 0x5fe, g_6b5c60);
			}
			slot += 0x21c;
		} while ((int) slot < (int) (g_7f4ca4 + 0x65400));
	}
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004ea620 */
void __cdecl amt_FillOffice0x1c0x1dFromRichest(void)
{
	int a[6];
	int b[6];
	unsigned int cand[16];
	char* ent;
	char* rec;
	char* existing;
	char* best;
	int value;
	int n;
	int i;
	int count;
	int found;
	int kind;
	unsigned short owner_id;
	unsigned char t;
	int best_i;
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(cand, 0, sizeof(cand));
	a[1] = -1;
	b[1] = -1;
	count = 0;
	value = 0;
	found = 0;
	ent = gm_StartFilteredEntitySearch(1, 5, 4);
	if (ent != 0) {
		do {
			if (count >= 0x10) {
				break;
			}
			owner_id = *(unsigned short*) (ent + 0x27);
			if (owner_id != 0xffff && owner_id != *(unsigned short*) gm_CityEntity && (*(unsigned char*) (ent + 0x5a) & 1) == 0) {
				found++;
				rec = (char*) (((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[owner_id]));
				t = *(unsigned char*) (rec + 0x164);
				if (t >= 1 && t <= 6) {
					for (i = 0; i < 0x10; i++) {
						if (cand[i] == (unsigned int) rec) {
							break;
						}
					}
					if (i == 0x10) {
						cand[count] = (unsigned int) rec;
						count++;
					}
				}
			}
			ent = gm_FindNextFilteredEntity();
		} while (ent != 0);
	}
	ent = gm_StartFilteredEntitySearch(1, 5, 0x10);
	if (ent != 0) {
		do {
			if (count >= 0x10) {
				break;
			}
			owner_id = *(unsigned short*) (ent + 0x27);
			if (owner_id != 0xffff && owner_id != *(unsigned short*) gm_CityEntity && (*(unsigned char*) (ent + 0x5a) & 1) == 0) {
				found++;
				rec = (char*) (((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[owner_id]));
				t = *(unsigned char*) (rec + 0x164);
				if (t >= 0x28 && t <= 0x2d) {
					for (i = 0; i < 0x10; i++) {
						if (cand[i] == (unsigned int) rec) {
							break;
						}
					}
					if (i == 0x10) {
						cand[count] = (unsigned int) rec;
						count++;
					}
				}
			}
			ent = gm_FindNextFilteredEntity();
		} while (ent != 0);
	}
	if (found < 3) {
		return;
	}
	if (count == 0) {
		return;
	}
	n = 2;
	rec = (char*) 0x9a9580;
	do {
		if (n == 0) {
			break;
		}
		t = (unsigned char) rec[8];
		if (t == 0x1d) {
			memcpy(a, rec, 0x18);
			n--;
		} else if (t == 0x1c) {
			memcpy(b, rec, 0x18);
			n--;
		}
		rec -= 0x18;
	} while ((int) rec >= 0x9a9220);
	existing = 0;
	if (b[1] != -1 || a[1] != -1) {
		existing = gm_LookupEntityRecordById(b[1] != -1 ? b[1] : a[1]);
	}
	if (existing != 0) {
		value = gm_WalkEntityChain(*(unsigned short*) existing);
	} else {
		value = 0;
	}
	best = 0;
	for (best_i = 0; best_i < count; best_i++) {
		rec = (char*) cand[best_i];
		n = gm_WalkEntityChain(*(unsigned short*) rec);
		if (n > value) {
			best = rec;
			value = n;
		}
	}
	if (best == 0 || best == existing) {
		return;
	}
	if (existing != 0) {
		t = *(unsigned char*) (best + 0x164);
		if (abs(*(unsigned char*) (existing + 0x164) - t) < 6) {
			amt_NotifyOfficeLost(existing, *(unsigned char*) (existing + 0x169));
			amt_NotifyOfficeAppointed(best, *(unsigned char*) (existing + 0x169));
			t = *(unsigned char*) (best + 0x164);
			if (t >= 1 && t <= 6) {
				amt_SendOfficeCommand((unsigned char) b[0], best, 0, 1, 0xff);
			} else {
				amt_SendOfficeCommand((unsigned char) a[0], best, 0, 1, 0xff);
			}
			return;
		}
		if (t >= 1 && t <= 6) {
			amt_SendOfficeCommand((unsigned char) b[0], best, 0, 1, 0xff);
			amt_SendOfficeCommand((unsigned char) a[0], 0, 0, 1, 0xff);
			kind = 0x1c;
		} else {
			amt_SendOfficeCommand((unsigned char) b[0], 0, 0, 1, 0xff);
			amt_SendOfficeCommand((unsigned char) a[0], best, 0, 1, 0xff);
			kind = 0x1d;
		}
		amt_NotifyOfficeLost(existing, *(unsigned char*) (existing + 0x169));
		amt_NotifyOfficeAppointed(best, kind);
		return;
	}
	t = *(unsigned char*) (best + 0x164);
	if (t >= 1 && t <= 6) {
		amt_SendOfficeCommand((unsigned char) b[0], best, 0, 1, 0xff);
		kind = 0x1c;
	} else {
		amt_SendOfficeCommand((unsigned char) a[0], best, 0, 1, 0xff);
		kind = 0x1d;
	}
	amt_NotifyOfficeAppointed(best, kind);
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e8c20 */
/* ADDRESS: GOLDTL 0x004ea9a0 */
void __cdecl amt_FillOffice0x22FromRichest(void)
{
	int k;
	ENTITY_RECORD* cur;
	Rec_4ea9a0 rec;
	ENTITY_RECORD* list[16];
	char* e;
	ENTITY_RECORD* o;
	ENTITY_RECORD* best;
	int total;
	int found;
	int best_v;
	int v;
	int i;
	int j;

	memset(&rec, 0, sizeof(rec));
	memset(list, 0, sizeof(list));
	rec.b = -1;
	k = 0;
	total = 0;
	for (e = gm_StartFilteredEntitySearch(1, 5, 7); e != 0 && k < 16; e = gm_FindNextFilteredEntity()) {
		if (*(unsigned short*) (e + 0x27) != 0xffff && !(e[0x5a] & 1)) {
			total++;
			o = &((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (e + 0x27)];
			if (o->unk_164 >= 0xd && o->unk_164 <= 0x12) {
				for (j = 0; j < 16; j++) {
					if (list[j] == o) {
						break;
					}
				}
				if (j == 16) {
					list[k++] = o;
				}
			}
		}
	}
	if (total < 3 || k == 0) {
		return;
	}
	found = 1;
	for (i = 36; i >= 0 && found != 0; i--) {
		if (((Rec_4ea9a0*)amt_OfficeSlots)[i].c == 0x22) {
			rec = ((Rec_4ea9a0*)amt_OfficeSlots)[i];
			found--;
		}
	}
	cur = 0;
	if (rec.b != -1 && (cur = gm_LookupEntityRecordById(rec.b)) != 0) {
		best_v = gm_WalkEntityChain(cur->entity_index);
	} else {
		best_v = 0;
	}
	best = 0;
	for (j = 0; j < k; j++) {
		v = gm_WalkEntityChain(list[j]->entity_index);
		if (v > best_v) {
			best = list[j];
			best_v = v;
		}
	}
	if (best != 0 && best != cur) {
		if (cur != 0) {
			amt_SendOfficeCommand(rec.a, (unsigned char*) best, 0, 1, 0xff);
			amt_NotifyOfficeLost(cur, 0x22);
			amt_NotifyOfficeAppointed(best, 0x22);
		} else {
			amt_SendOfficeCommand(rec.a, (unsigned char*) best, 0, 1, 0xff);
			amt_NotifyOfficeAppointed(best, 0x22);
		}
	}
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004eab40 */
void __cdecl amt_calc_zuenfte(unsigned int kind)
{
	union {
		int office[6];
		float position[3];
	} info;
	unsigned int cand[16];
	char names[128];
	int ids[64];
	char path[128];
	char buf[128];
	unsigned char req[0xf8];
	char* t;
	char* rec;
	char* rowbase;
	char* best;
	char* existing;
	unsigned int found;
	int pass;
	int sel;
	int row;
	int min;
	int count;
	int max;
	int total;
	int i;
	int n;
	int value;
	float rotation[3];

	memset(info.office, 0, sizeof(info.office));
	info.office[1] = -1;
	if (kind == 0x1e) {
		pass = 0xe;
		sel = 0x17;
		min = 0x22;
		max = 0x27;
		row = 0x38;
	}
	else if (kind == 0x1f) {
		pass = 0x12;
		sel = 0x18;
		min = 0x2e;
		max = 0x33;
		row = 0x3b;
	}
	else if (kind == 0x20) {
		pass = 0x14;
		sel = 0x19;
		min = 0x3a;
		max = 0x3f;
		row = 0x3e;
	}
	else if (kind == 0x21) {
		pass = 0x15;
		sel = 0x1a;
		min = 0x40;
		max = 0x45;
		row = 0x41;
	}
	else {
		return;
	}
	memset(cand, 0, sizeof(cand));
	count = 0;
	total = 0;
	t = gm_StartFilteredEntitySearch(1, 5, pass);
	if (t != 0) {
		do {
			if (count >= 0x10) {
				break;
			}
			if (*(unsigned short*) (t + 0x27) != 0xffff &&
			    (t[0x5a] & 1) == 0) {
				total++;
				i = *(unsigned short*) (t + 0x27);
				rec = (char*) (0x7f4ca0 + i * 0x21c);
				n = *(unsigned char*) (rec + 0x164);
				if (n >= min && n <= max) {
					for (i = 0; i < 0x10; i++) {
						if (cand[i] == (unsigned int) rec) {
							break;
						}
					}
					if (i == 0x10) {
						cand[count] = (unsigned int) rec;
						count++;
					}
				}
			}
			t = gm_FindNextFilteredEntity();
		} while (t != 0);
		if (total >= 3 && count != 0) {
			t = gm_StartFilteredEntitySearch(1, 5, sel);
			if (t == 0) {
				found = (unsigned int) d3_CurrentContextIndex;
				d3_SelectSceneContext(0, 1);
				rowbase = (char*) &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[row];
				lc_GetBauplatzPrefix(row, names);
				n = d3_CollectUnusedSceneObjects(names, ids);
				rec = (char*) ids[gm_RandomMod(n) & 0xffff];
				i = 0;
				if (rec == 0) {
					do {
						if (i >= n) {
							break;
						}
						if (ids[i] != 0) {
							rec = (char*) ids[i];
						}
						i++;
					} while (rec == 0);
					if (rec == 0) {
						ReportClientMessage(g_68de2c);
						return;
					}
				}
				d3_TransformPoint(rec, (float*) (rec + 0x4c), info.position);
				d3_ComputeObjectYawToTarget(rotation, (int) rec);
				d3_SelectSceneContext((int) found, 1);
				cand[0] = (unsigned int) g_6798d4;
				strcat((char*) cand, rowbase + 1);
				strupr((char*) cand + 2);
				sprintf(buf, g_67f0ac, g_7e1ae0, (char*) cand);
				req[4] = 0xd;
				*(int*) (req + 0x08) = *(int*) (gm_CityEntity + 4);
				*(int*) (req + 0x0c) = -1;
				*(int*) (req + 0x28) = gm_GameTime.a;
				*(int*) (req + 0x2c) = (*(int*) &g_7f4c04);
				*(int*) (req + 0x30) = g_7f4c08;
				*(unsigned short*) (req + 0x34) = g_7f4c0c;
				req[0x36] = 2;
				*(int*) (req + 0x58) = *(int*) (gm_CityEntity + 4);
				*(int*) (req + 0x5c) = row;
				*(int*) (req + 0x60) = 0;
				memcpy(req + 0x80, info.position, sizeof(info.position));
				memcpy(req + 0x90, rotation, sizeof(rotation));




				strcpy((char*) (req + 0x9c), buf);
				cm_SendCopyEntityData(req);
				return;
			}
			if ((t[0x5a] & 1) == 0) {
				/* re-read the office type entry from the table */
				n = 1;
				rec = (char*) 0x9a9580;
				do {
					if (n == 0) {
						break;
					}
					if ((unsigned char) rec[8] == kind) {
						n--;
						memcpy(info.office, rec, 0x18);
					}
					rec -= 0x18;
				} while ((int) rec >= 0x9a9220);
				existing = 0;
				value = 0;
				if (info.office[1] != -1 &&
				    (existing = gm_LookupEntityRecordById(info.office[1])) != 0) {
					value = gm_WalkEntityChain(*(unsigned short*) existing);
				}
				best = 0;
				for (i = 0; i < count; i++) {
					rec = (char*) cand[i];
					n = gm_WalkEntityChain(*(unsigned short*) rec);
					if (n > value) {
						best = rec;
						value = n;
					}
				}
				if (best != 0 && best != existing) {
					if (existing != 0) {
						amt_SendOfficeCommand((unsigned char) info.office[0], best, 0, 1, 0xff);
						amt_NotifyOfficeLost(existing, kind);
						amt_NotifyOfficeAppointed(best, kind);
						return;
					}
					amt_SendOfficeCommand((unsigned char) info.office[0], best, 0, 1, 0xff);
					amt_NotifyOfficeAppointed(best, kind);
				}
			}
		}
	}
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004eafe0 */
void __cdecl amt_UpdateAllOffices(void)
{
	Rec_4eafe0 out[7];
	unsigned char* q;
	unsigned char t;
	int n;
	int i;
	int k;
	int lo;
	int hi;
	int v;
	int x;
	int tt;

	n = amt_CollectOfficeGroup7(1, 7, out);
	if (n > 0) {
		for (i = 0; i < n; i++) {
			x = out[i].x4;
			if (x == -1) {
				continue;
			}
			t = out[i].type;
			tt = out[i].type;
			switch (tt) {
			case 0x1c:
				lo = 1;
				hi = 6;
				break;
			case 0x1d:
				lo = 0x28;
				hi = 0x2d;
				break;
			case 0x1e:
				lo = 0x22;
				hi = 0x27;
				break;
			case 0x1f:
				lo = 0x2e;
				hi = 0x33;
				break;
			case 0x20:
				lo = 0x3a;
				hi = 0x3f;
				break;
			case 0x21:
				lo = 0x40;
				hi = 0x45;
				break;
			case 0x22:
				lo = 0xd;
				hi = 0x12;
				break;
			default:
				continue;
			}
			q = gm_LookupEntityRecordById(x);
			if (q == 0)
				goto body;
			if (q[8] == 0)
				goto body;
			if (q[0x169] == t) {
				k = q[0x164];
				if (k >= lo && k <= hi)
					goto skip;
			}
		body:
			amt_NotifyOfficeLost((Rec_4eafe0*) q, tt);
			v = amt_SendOfficeCommand(out[i].id, 0, 0, 4, 0xff);
			while (v != -1 && cm_GetCommandStatus(v) == 0) {
				cm_StepCommandQueue();
			}
		skip:
			;
		}
	}
	if (he_StartHandlungSearch(1, 0, 0x80) == 0) {
		amt_calc_zuenfte(0x1e);
		amt_calc_zuenfte(0x1f);
		amt_calc_zuenfte(0x20);
		amt_calc_zuenfte(0x21);
	}
	amt_FillOffice0x1c0x1dFromRichest();
	amt_FillOffice0x22FromRichest();
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004eb180 */
int __cdecl amt_CheckZunftTaxLaw(int rankRange)
{
	int officeType;
	void* officeRec;

	if (he_StartHandlungSearch(1, 0, 0x80) != 0) {
		amt_calc_zuenfte(0x1e);
		amt_calc_zuenfte(0x1f);
		amt_calc_zuenfte(0x20);
		amt_calc_zuenfte(0x21);
		return 0;
	}
	switch (rankRange) {
	case 1:
		officeType = 0x18;
		break;
	case 2:
		officeType = 0x19;
		break;
	case 3:
		officeType = 0x1a;
		break;
	case 4:
		officeType = 0x17;
		break;
	case 5:
		return 0;
	default:
		goto ret0;
	}
	officeRec = gm_StartFilteredEntitySearch(1, 5, officeType);
	if (officeRec == 0 || (((unsigned char*) officeRec)[0x5a] & 1))
		return 0;
	return 1;
ret0:
	return 0;
}
#endif

#if defined(REBREW_SERVER)
/* ADDRESS: SERVER 0x1000ba30 */
void __cdecl amt_UpdateEntityLinks(char* entity, int arg2)
{
	OFFICE_SLOT* slot;
	unsigned short default_val;
	int i;
	int result;

	default_val = (unsigned short) g_current_hour;
	result = 0;
	slot = (OFFICE_SLOT*) g_office_slots;
	for (i = 0; i < 0x2a; i++) {
		if (slot[i].mplayerid == *(int*) (entity + 4) && arg2 != 0) {
			slot[i].mplayerid = -1;
			slot[i].msetter = -1;
			slot[i].status = (default_val > 0xb) ? 4 : 3;
			slot[i].pcount = 0;
			result |= 1;
		}
		else if (slot[i].msetter == *(int*) (entity + 4)) {
			slot[i].msetter = -1;
			slot[i].status = 1;
		}
	}
	if (*(char*) (entity + 0x168) != 0) {
		for (i = 0; i < 0x2a; i++) {
			if ((char) slot[i].mamt == *(char*) (entity + 0x168)) {
				if (slot[i].pcount > 0) {
					slot[i].pcount--;
					result |= 1;
				}
			}
		}
	}
	if (arg2 != 0) {
		*(char*) (entity + 0x166) = 0;
		*(char*) (entity + 0x169) = 0;
	}
	*(char*) (entity + 0x168) = 0;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_CanUpgradeBuildingTier1(char* building)
{
	unsigned char kind;

	kind = *(unsigned char*) (building + 0x169);
	if (kind < 0x1e || kind > 0x21) {
		return 0;
	}
	if ((*(int*) (building + 0x1c8) & 0x4000000) != 0) {
		return -1;
	}
	if (*(int*) (building + 0x194) < 3) {
		return -2;
	}
	return 1;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e94a0 */
/* ADDRESS: GOLDTL 0x004eb220 */
int __cdecl gm_CheckZunftPreismanipulation(char* entity)
{
	unsigned char kind;
	int level;

	kind = *(unsigned char*) (entity + 0x169);
	if (kind < 0x1e || kind > 0x21) {
		return 0;
	}
	if ((*(int*) (entity + 0x1c8) & 0x4000000) != 0) {
		return -1;
	}
	level = *(int*) (entity + 0x194);
	if (level < 3) {
		return -2;
	}
	return 1;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_CanUpgradeBuildingTier2(unsigned char* building)
{


	unsigned char* hit;
	int kind;

	if (building[0x169] < 0x1e || building[0x169] > 0x21) {
		return 0;
	}
	switch (building[0x169]) {
	case 0x1f:
		kind = 0x18;
		break;
	case 0x20:
		kind = 0x19;
		break;
	case 0x21:
		kind = 0x1a;
		break;
	case 0x1e:
		kind = 0x17;
		break;
	default:
		return 0;
	}
	hit = gm_StartFilteredEntitySearch(1, 5, kind);
	if (hit == 0 || (hit[0x5a] & 1) != 0) {
		return 0;
	}
	if ((unsigned char) g_entity_type_table[*hit * 0x24d + 0x247] < 2) {
		return 0;
	}
	if (*(unsigned int*) (building + 0x1c8) & 0x8000000) {
		return -1;
	}
	return *(int*) (building + 0x194) < 5 ? -2 : 1;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e94e0 */
/* ADDRESS: GOLDTL 0x004eb260 */
int __cdecl amt_CanUpgradeBuildingTier2(unsigned char* obj)
{
	unsigned char* building;
	int kind;

	if (obj[0x169] < 0x1e || obj[0x169] > 0x21) {
		return 0;
	}
	switch (obj[0x169]) {
	case 0x1f:
		kind = 0x18;
		break;
	case 0x20:
		kind = 0x19;
		break;
	case 0x21:
		kind = 0x1a;
		break;
	case 0x1e:
		kind = 0x17;
		break;
	default:
		return 0;
	}
	building = gm_StartFilteredEntitySearch(1, 5, kind);
	if (building == 0 || (building[0x5a] & 1) != 0) {
		return 0;
	}
	if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*building].level < 2) {
		return 0;
	}
	if (*(unsigned int*) (obj + 0x1c8) & 0x8000000) {
		return -1;
	}
	return *(int*) (obj + 0x194) < 5 ? -2 : 1;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_CanUpgradeBuildingTier3(unsigned char* building)
{


	unsigned char* hit;
	int kind;

	if (building[0x169] < 0x1e || building[0x169] > 0x21) {
		return 0;
	}
	switch (building[0x169]) {
	case 0x1f:
		kind = 0x18;
		break;
	case 0x20:
		kind = 0x19;
		break;
	case 0x21:
		kind = 0x1a;
		break;
	case 0x1e:
		kind = 0x17;
		break;
	default:
		return 0;
	}
	hit = gm_StartFilteredEntitySearch(1, 5, kind);
	if (hit == 0 || (hit[0x5a] & 1) != 0) {
		return 0;
	}
	if ((unsigned char) g_entity_type_table[*hit * 0x24d + 0x247] < 3) {
		return 0;
	}
	if (*(unsigned int*) (building + 0x1c8) & 0x10000000) {
		return -1;
	}
	return *(int*) (building + 0x194) < 8 ? -2 : 1;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004e95a0 */
/* ADDRESS: GOLDTL 0x004eb320 */
int __cdecl amt_CheckHighOfficeEligibility(unsigned char* obj)
{
	unsigned char* r;
	int kind;

	if (obj[0x169] < 0x1e || obj[0x169] > 0x21) {
		return 0;
	}
	switch (obj[0x169]) {
	case 0x1f:
		kind = 0x18;
		break;
	case 0x20:
		kind = 0x19;
		break;
	case 0x21:
		kind = 0x1a;
		break;
	case 0x1e:
		kind = 0x17;
		break;
	default:
		return 0;
	}
	r = gm_StartFilteredEntitySearch(1, 5, kind);
	if (r == 0 || (r[0x5a] & 1) != 0) {
		return 0;
	}
	if (((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*r].level < 3) {
		return 0;
	}
	if (*(unsigned int*) (obj + 0x1c8) & 0x10000000) {
		return -1;
	}
	return *(int*) (obj + 0x194) < 8 ? -2 : 1;
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004eb3e0 */
unsigned int __cdecl gm_ExecZunftPreismanipulation(char* self, int* packet)
{
	slot80 ent;
	char buf1[512];
	char buf2[2048];
	int ids[10];
	int pick[10];
	slot80* e;
	unsigned char* q;
	BUILDING_PROTOTYPE * b;
	float t;
	float scale;
	unsigned int v20;
	unsigned int secondId;
	int found;
	int best;
	int k;
	int n;
	int i;


	best = 0;
	v20 = 0;
	secondId = 0;
	packet[3] = 0;
	packet[4] = 0;
	if (packet[0] != 3)
		return 0;
	if (packet[2] != 1 && packet[2] != -1)
		return 0;
	if ((unsigned int) packet[1] < 1 || (unsigned int) packet[1] > 7)
		return 0;
	found = fcn_00507080(packet[1]);
	if (found == 0)
		return 0;
	e = (slot80*) gm_StartFilteredEntitySearch(1, 5, found);
	if (e == 0)
		return 0;
	do {
		b = &((BUILDING_PROTOTYPE *) lpGebaeudePROT)[*(unsigned char*) e];
		if ((int) b->level > best) {
			best = (int) b->level;
			v20 = *(unsigned char*) e;
		}
		e = (slot80*) gm_FindNextFilteredEntity();
	} while (e != 0);
	if (v20 == 0)
		return 0;
	k = 0;
	q = (unsigned char*) 0x699058;
	do {
		if (*q == v20)
			goto found;
		q += 0x15;
		k++;
	} while ((int) q < 0x699361);
	return 0;
found:
	if (k >= 0x25)
		return 0;
	n = 0;
	q = (unsigned char*) (0x699058 + k * 0x15 + 1);
	for (i = 0; i < 10; i++) {
		if (*(unsigned short*) q != 0) {
			ids[n] = *(unsigned short*) q;
			n++;
		}
		q += 2;
	}
	if (n == 0)
		return 0;
	gm_GenerateShuffledIndices(n, pick);
	if (n == 1) {
		v20 = (unsigned int) ids[pick[0]];
	} else {
		v20 = (unsigned int) ids[pick[0]];
		secondId = (unsigned int) ids[pick[1]];
	}
	t = gm_GetEntitySkill(self, 2);
	if (packet[2] == 1) {
		scale = (float) (gm_RandomFloat01() + g_6628a0) * t * 0.4f + *(float*) 0x664198;
	} else {
		scale = *(double*) 0x6629c8 -
			((float) (gm_RandomFloat01() + g_6628a0) * t * 0.3f + *(double*) 0x6628f0);
	}

	e = gm_FindSlotById(g_773d75, v20);
	if (e != 0) {
		ent = *e;
		ent.f24 = ent.f20 * scale;
		ent.f38 = gm_CalcMarketSlotPriceByObjektId(g_773d75, v20);
		cm_SendMarktSlotDelta(&ent, g_773d75);
		packet[3] = v20;
		e = gm_FindSlotById(g_773d75, secondId);
		if (e != 0) {
			ent = *e;
			ent.f24 = ent.f20 * scale;
			ent.f38 = gm_CalcMarketSlotPriceByObjektId(g_773d75, secondId);
			cm_SendMarktSlotDelta(&ent, g_773d75);
			packet[4] = secondId;
		}
		cm_RequestChangeBits(*(int*) (self + 4), 0x1c8, 4, 0x4000000, 0);
		gm_ModifyHealth(*(int*) (self + 4), -3);
		found = gm_RandomMod(3);
		if (packet[2] == 1) {
			io_FormatTextBuffer(buf1, (found & 0xffff) + 0x1656, packet[1] + 0x1648);
			io_FormatTextBuffer(buf2, 0x1655, buf1, v20 * 2 + 0x9a8, secondId * 2 + 0x9a8);
		} else {
			io_FormatTextBuffer(buf1, (found & 0xffff) + 0x165a, packet[1] + 0x1648);
			io_FormatTextBuffer(buf2, 0x1659, buf1, v20 * 2 + 0x9a8, secondId * 2 + 0x9a8);
		}
		for (q = (unsigned char*) 0x7f4ca4; (int) q < (int) 0x85a0a4; q += 0x21c) {
			if ((*(unsigned char*) (q - 2) == 7 || *(unsigned char*) (q - 2) == 6) &&
			    *(int*) (self + 4) != *(int*) q)
				he_PostEntityMessage(*(int*) q, -1, buf2, 1, 0x5ec, (void*) 0x6b5c60);
		}
		if (*(unsigned char*) (self + 2) == 6)
			fcn_00526120(buf2, 0x10);
	}
	return 0;
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004eb780 */
int __cdecl gm_ExecZunftAufruhr(char* e, int* msg)
{
	char* h;
	int cnt;
	char buf[0x400];
	float f;
	int amount;
	int i;

	if (msg[0] != 2) {
		return 0;
	}
	gm_ResolveEntityById((void**) (&h), 0, 0, msg[1]);
	if (h == 0) {
		return 0;
	}
	if (*(unsigned short*) (h + 0x27) == *(unsigned short*) e || *(unsigned short*) (h + 0x27) == 0xffff) {
		return 0;
	}
	f = gm_GetEntitySkill(e, 4);
	amount = (int) (((gm_RandomFloat01() + 1.0f) * f * 15.0f + 5.0) * 2.55f);
	cm_RequestTransferCurrencyNoKill(-1, *(int*) (e + 4), (*(char*)&g_773d75), msg[2]);
	for (i = 0, cnt = 0; i < 0x300; i++) {
		if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_index != 0xffff && (*(char**)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].ptr_16c) == h && *(unsigned short*) (h + 0x27) != i) {
			cm_RequestCopyEntityData(((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].entity_id, ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id, -amount, 1);
			cnt++;
		}
	}
	if (cnt != 0) {
		amount = (int) ((float) msg[2] / cnt) + 0x20;
		for (i = 0; i < 0x300; i++) {
			if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_index != 0xffff && (*(char**)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].ptr_16c) == h && *(unsigned short*) (h + 0x27) != i) {
				cm_RequestTransferCurrencyNoKill(((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id, -1, (*(char*)&g_773d75), amount);
			}
		}
	}
	gm_ModifyHealth(*(int*) (e + 4), -5);
	cm_RequestChangeBits(*(int*) (e + 4), 0x1c8, 4, 0x8000000, 0);
	if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].entity_type == 7 || ((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].entity_type == 6) {
		io_FormatTextBuffer(buf, 0x1663, h);
		he_MessageBoxQuickjump(((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].entity_id, -1, buf, 0, 0x5fb, *(int*) (h + 1), -1, 0, "");
	}
	io_FormatTextBuffer(buf, 0x1662, *(unsigned short*) (h + 0x27), h);
	for (i = 0; i < 0x300; i++) {
		if ((((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 7 || ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 6) && *(int*) (e + 4) != ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id
		    && ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id != ((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].entity_id) {
			he_PostEntityMessage(((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id, -1, buf, 0, 0x5fd, "");
		}
	}
	if (e[2] == 6) {
		io_FormatTextBuffer(buf, 0x1661, *(unsigned short*) (h + 0x27), h);
		fcn_00526120(buf, 0);
	}
	return 1;
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004eba60 */
unsigned int __cdecl amt_HandleOfficeAction(char* e, unsigned int* target)
{
	float f;
	int sign;
	int value;
	int n;
	int i;
	int k;
	int fmt;
	char* p;
	char* out;
	char* h;
	int id1;
	int id2;
	int slot[6];
	OFFICE_SLOT arr[6];
	int role[6];
	char buf[0x400];
	char buf2[0x400];

	f = gm_RandomFloat01();
	sign = (f > 0.3f) ? 1 : -1;

	if (e[0x169] == 0x1e) {
		if (target[0] != 1)
			return 0;
		h = gm_LookupEntityRecordById(target[1]);
		if (h == 0)
			return 0;
		if (h[0x166] == 0)
			return 0;
		if (h == e)
			return 0;
		if (srv_GetEntityOfficeSlot(h, role, slot) == 0)
			return 0;
		if (f > 0.3f)
			amt_SendOfficeCommand(slot[0], 0, 0, 4, 0xff);
		gm_ModifyHealth(*(int*) (e + 4), -8);
		cm_RequestChangeBits(*(int*) (e + 4), 0x1c8, 4, 0x10000000, 0);
		if (f > 0.3f) {
			if (7 == h[2] || 6 == h[2]) {
				io_FormatTextBuffer(buf, 0x1684);
				he_PostEntityMessage(*(int*) (h + 4), -1, buf, 0, 0x5fb, g_6b5c60);
			}
			io_FormatTextBuffer(buf, 0x1682, *(unsigned short*) h, *(unsigned short*) h);
			p = g_7f4ca4;
			do {
				if ((7 == p[-2] || 6 == p[-2]) && *(int*) p != *(int*) (h + 4) && *(int*) p != *(int*) (e + 4))
					he_PostEntityMessage(*(int*) p, -1, buf, 0, 0x5fe, g_6b5c60);
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				io_FormatTextBuffer(buf, 0x1680, *(unsigned short*) h, *(unsigned short*) h);
				fcn_00526120(buf, 0);
			}
		} else {
			if (7 == h[2] || 6 == h[2]) {
				io_FormatTextBuffer(buf, 0x1685);
				he_PostEntityMessage(*(int*) (h + 4), -1, buf, 0, 0x5fb, g_6b5c60);
			}
			io_FormatTextBuffer(buf, 0x1683, *(unsigned short*) h, *(unsigned short*) h);
			p = g_7f4ca4;
			do {
				if ((7 == p[-2] || 6 == p[-2]) && *(int*) p != *(int*) (h + 4) && *(int*) p != *(int*) (e + 4))
					he_PostEntityMessage(*(int*) p, -1, buf, 0, 0x5fe, g_6b5c60);
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				io_FormatTextBuffer(buf, 0x1681, *(unsigned short*) h, *(unsigned short*) h);
				fcn_00526120(buf, 0);
			}
		}
		return sign;
	}

	if (e[0x169] != 0x1f && e[0x169] != 0x21) {
		if (e[0x169] != 0x20)
			return 0;
		if (target[0] != 4)
			return 0;
		if (target[1] < 1 || target[1] > 6)
			return 0;
		if (f > 0.3f) {
			float g;
			n = amt_FindOfficeSlotsByKind(target[1], 6, arr);
			g = gm_GetEntitySkill(e, 4);
			value = (int) (((gm_RandomFloat01() + 1.0f) * g * 15.0f + 5.0) * 2.55f);
			for (k = 0; k < n; k++) {
				id1 = arr[k].mplayerid;
				if (id1 != *(int*) (e + 4) && id1 != -1)
					cm_RequestCopyEntityData(*(int*) (e + 4), id1, value, 1);
			}
		}
		gm_ModifyHealth(*(int*) (e + 4), -8);
		cm_RequestChangeBits(*(int*) (e + 4), 0x1c8, 4, 0x10000000, 0);
		if (f > 0.3f) {
			io_FormatTextBuffer(buf, 0x167a, target[1] + 0x1663);
			p = g_7f4ca4;
			do {
				if ((7 == p[-2] || 6 == p[-2]) && *(int*) p != *(int*) (e + 4))
					he_PostEntityMessage(*(int*) p, -1, buf, 0, 0x5fd, g_6b5c60);
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				io_FormatTextBuffer(buf, 0x1678, target[1] + 0x1663);
				fcn_00526120(buf, 0);
			}
		} else {
			io_FormatTextBuffer(buf, 0x167b, target[1] + 0x1663);
			p = g_7f4ca4;
			do {
				if ((7 == p[-2] || 6 == p[-2]) && *(int*) p != *(int*) (e + 4))
					he_PostEntityMessage(*(int*) p, -1, buf, 0, 0x5fe, g_6b5c60);
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				io_FormatTextBuffer(buf, 0x1679, target[1] + 0x1663);
				fcn_00526120(buf, 0);
			}
		}
	} else {
		if (target[0] != 4)
			return 0;
		if (target[1] < 1 || target[1] > 6)
			return 0;
		if (f > 0.3f) {
			float g;
			n = amt_FindOfficeSlotsByKind(target[1], 6, arr);
			g = gm_GetEntitySkill(e, 4);
			value = (int) (((gm_RandomFloat01() + 1.0f) * g * 15.0f + 5.0) * 2.55f);
			for (i = 0; i < n - 1; i++) {
				id1 = arr[i].mplayerid;
				if (id1 == *(int*) (e + 4) || id1 == -1)
					continue;
				for (k = i + 1; k < n; k++) {
					id2 = arr[k].mplayerid;
					if (id2 == *(int*) (e + 4) || id2 == -1)
						continue;
					cm_RequestCopyEntityData(id2, id1, -value, 1);
					cm_RequestCopyEntityData(id1, id2, -value, 1);
				}
			}
		} else {
			n = amt_FindOfficeSlotsByKind(target[1], 6, arr);
		}
		gm_ModifyHealth(*(int*) (e + 4), -8);
		cm_RequestChangeBits(*(int*) (e + 4), 0x1c8, 4, 0x10000000, 0);
		if (f > 0.3f) {
			io_FormatTextBuffer(buf, 0x1672, target[1] + 0x1663);
			io_FormatTextBuffer(buf2, 0x1670, target[1] + 0x1663);
			p = g_7f4ca4;
			do {
				if ((7 == p[-2] || 6 == p[-2]) && *(int*) p != *(int*) (e + 4)) {
					for (k = 0; k < n; k++) {
						if (arr[k].mplayerid == *(int*) p) {
							he_PostEntityMessage(*(int*) p, -1, buf, 0, 0x5fb, g_6b5c60);
							goto next_p1;
						}
					}
					he_PostEntityMessage(*(int*) p, -1, buf2, 0, 0x5fe, g_6b5c60);
				}
			next_p1:
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				io_FormatTextBuffer(buf, 0x166e, target[1] + 0x1663);
				fcn_00526120(buf, 0);
				return sign;
			}
		} else {
			io_FormatTextBuffer(buf, 0x1673, target[1] + 0x1663);
			io_FormatTextBuffer(buf2, 0x1671, target[1] + 0x1663);
			p = g_7f4ca4;
			do {
				if ((7 == p[-2] || 6 == p[-2]) && *(int*) p != *(int*) (e + 4)) {
					for (k = 0; k < n; k++) {
						if (arr[k].mplayerid == *(int*) p) {
							he_PostEntityMessage(*(int*) p, -1, buf, 0, 0x5fb, g_6b5c60);
							goto next_p2;
						}
					}
					he_PostEntityMessage(*(int*) p, -1, buf2, 0, 0x5fe, g_6b5c60);
				}
			next_p2:
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				io_FormatTextBuffer(buf, 0x166f, target[1] + 0x1663);
				fcn_00526120(buf, 0);
			}
		}
	}
	return sign;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004ea550 */
/* ADDRESS: GOLDTL 0x004ec2d0 */
void __cdecl amt_AdjustOfficeHoldersFavor(char* p, int kind, int arg)
{
	OFFICE_SLOT recs[6];
	int n;
	int i;

	if (kind < 1 || kind > 7) {
		return;
	}
	n = amt_FindOfficeSlotsByKind(kind, 6, recs);
	for (i = 0; i < n; i++) {
		if (recs[i].mplayerid != *(int*) (p + 4) && recs[i].mplayerid != -1) {
			cm_RequestCopyEntityData(*(int*) (p + 4), recs[i].mplayerid, arg, 1);
		}
	}
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004ea5c0 */
/* ADDRESS: GOLDTL 0x004ec340 */
float __cdecl amt_GetOfficeAffinityScore(unsigned short* p, int kind)
{
	OFFICE_SLOT recs[6];
	float sum;
	int count;
	int n;
	int i;
	unsigned short* q;

	sum = 0;
	if (kind < 1 || kind > 7) {
		return g_6628a8;
	}
	n = amt_FindOfficeSlotsByKind(kind, 6, recs);
	count = 0;
	for (i = 0; i < n; i++) {
		if (recs[i].mplayerid != *(int*) (p + 2) && recs[i].mplayerid != -1) {
			q = gm_LookupEntityRecordById(recs[i].mplayerid);
			if (q != 0) {
				sum += gm_CalcEntityFavor(*p, *q, 1) * 0.01f;
				count++;
			}
		}
	}
	if (count != 0) {
		sum = sum / count;
	}
	return sum;
}
#endif

/* ADDRESS: GOLD 0x004ea690 */
/* ADDRESS: GOLDTL 0x004ec410 */
int __cdecl amt_fio_SaveAemter(void* file)
{
	extern unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
	int count;
	char msg[0x100];
	int i;

	count = 0x2a;
	if (file == 0) {
		return 0;
	}
	if (!vfs_fwrite(&count, 4, 1, file)) {
		return 0;
	}
	sprintf(msg, "amt_fio_SaveAemter(): count is %i", count);
	for (i = 0; i < 0x2a; i++) {
		if (!vfs_fwrite(&((OFFICE_SLOT*) g_office_slots)[i].id, 1, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((OFFICE_SLOT*) g_office_slots)[i].mplayerid, 4, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((OFFICE_SLOT*) g_office_slots)[i].mamt, 1, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((OFFICE_SLOT*) g_office_slots)[i].pcount, 4, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((OFFICE_SLOT*) g_office_slots)[i].status, 1, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((OFFICE_SLOT*) g_office_slots)[i].msetter, 4, 1, file)) {
			return 0;
		}
	}
	return 1;
}

#if defined(REBREW_SERVER)
/* ADDRESS: SERVER 0x1000baf0 */
int __cdecl amt_fio_LoadAemter(void* streamCtx, int version)
{
	int value;
	char msg[0x100];
	unsigned int count;
	unsigned int i;

	count = (version >= 0x10051) ? 0x2a : 0x25;

	srv_InitBuildingTypeTable();

	if (streamCtx == 0)
		return 0;

	if (!ls_ReadVfsDataChecked(&value, 4, 1, streamCtx)) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe73,
		                   "amt_fio_LoadAemter(): Can't load count", 1);
		return 0;
	}
	if (value != (int) count) {
		sprintf(msg, "amt_fio_LoadAemter(): count read is %i, expected %i",
		        value, 0x2a);
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe7c,
		                   msg, 1);
		return 0;
	}
	for (i = 0; i < count; i++) {
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].id, 1, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe82,
			                   "amt_fio_LoadAemter(): Can't load id", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].mplayerid, 4, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe83,
			                   "amt_fio_LoadAemter(): Can't load mplayerid", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].mamt, 1, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe84,
			                   "amt_fio_LoadAemter(): Can't load mamt", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].pcount, 4, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe85,
			                   "amt_fio_LoadAemter(): Can't load pcount", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].status, 1, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe86,
			                   "amt_fio_LoadAemter(): Can't load status", 1);
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((OFFICE_SLOT*) g_office_slots)[i].msetter, 4, 1, streamCtx)) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe87,
			                   "amt_fio_LoadAemter(): Can't load msetter", 1);
			return 0;
		}
	}
	return 1;
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004ea7a0 */
/* ADDRESS: GOLDTL 0x004ec520 */
int __cdecl amt_fio_LoadAemter(void* file, int version)
{
	int cnt;
	char buf[256];
	unsigned int n;
	unsigned int i;

	n = version >= 0x10051 ? 0x2a : 0x25;
	srv_InitBuildingTypeTable();
	if (file == 0) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&cnt, 4, 1, file)) {
		return 0;
	}
	if ((unsigned int)cnt != n) {
		sprintf(buf, g_68de84, cnt, 0x2a);
		return 0;
	}
	for (i = 0; i < n; i++) {
		if (!ls_ReadVfsDataChecked(&((Rec_4ec520*)amt_OfficeSlots)[i].a, 1, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec_4ec520*)amt_OfficeSlots)[i].b, 4, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec_4ec520*)amt_OfficeSlots)[i].c, 1, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec_4ec520*)amt_OfficeSlots)[i].d, 4, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec_4ec520*)amt_OfficeSlots)[i].e, 1, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec_4ec520*)amt_OfficeSlots)[i].f, 4, 1, file)) {
			return 0;
		}
	}
	return 1;
}
#endif

#if defined(REBREW_SERVER)
void* __cdecl amt_GetTownHallHolder(unsigned char* building)
{

	int* office;

	if (g_entity_type_table[building[0] * 0x24d] == 0x1e) {
		office = *(int**) (building + 0x65);
		if (office != 0) {
			return gm_LookupEntityRecordById(*office);
		}
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", __LINE__, "amt_GetTownHallHolder(): no town hall office", 1);
	return 0;
}
#endif

#if defined(REBREW_SERVER)
int __cdecl amt_CountTownHallSeats(char* entity)
{
	int __cdecl ahm_CheckFlag(void* entity);
	char* seats;
	int i;
	int n;

	if (ahm_CheckFlag(entity) == 0) {
		return 0;
	}
	n = 0;
	seats = *(char**) (*(char**) (entity + 0x16c) + 0x65);
	for (i = 0; i < 6; i++) {
		if (*(int*) (seats + 0xc + i * 8) != 0) {
			n++;
		}
	}
	return n;
}
#endif

#if !defined(REBREW_SERVER)
unsigned char _dpad_68da64[4] = {
    0x00, 0x00, 0x00, 0x00
};

unsigned char _dpad_68de28[4] = {
    0x02, 0x00, 0x00, 0x00
};
unsigned char _dpad_68de2d[51] = {
    0x6d, 0x74, 0x5f, 0x63, 0x61, 0x6c, 0x63, 0x5f, 0x7a, 0x75, 0x65, 0x6e, 0x66, 0x74, 0x65, 0x28,
    0x29, 0x3a, 0x20, 0x63, 0x6f, 0x75, 0x6c, 0x64, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x66, 0x69, 0x6e,
    0x64, 0x20, 0x61, 0x20, 0x66, 0x72, 0x65, 0x65, 0x20, 0x70, 0x6c, 0x61, 0x63, 0x65, 0x2e, 0x2e,
    0x2e, 0x00, 0x00
};
unsigned char _dpad_68de61[35] = {
    0x6d, 0x74, 0x5f, 0x66, 0x69, 0x6f, 0x5f, 0x53, 0x61, 0x76, 0x65, 0x41, 0x65, 0x6d, 0x74, 0x65,
    0x72, 0x28, 0x29, 0x3a, 0x20, 0x63, 0x6f, 0x75, 0x6e, 0x74, 0x20, 0x69, 0x73, 0x20, 0x25, 0x69,
    0x00, 0x00, 0x00
};
unsigned char _dpad_68de86[50] = {
    0x74, 0x5f, 0x66, 0x69, 0x6f, 0x5f, 0x4c, 0x6f, 0x61, 0x64, 0x41, 0x65, 0x6d, 0x74, 0x65, 0x72,
    0x28, 0x29, 0x3a, 0x20, 0x63, 0x6f, 0x75, 0x6e, 0x74, 0x20, 0x72, 0x65, 0x61, 0x64, 0x20, 0x69,
    0x73, 0x20, 0x25, 0x69, 0x2c, 0x20, 0x65, 0x78, 0x70, 0x65, 0x63, 0x74, 0x65, 0x64, 0x20, 0x25,
    0x69, 0x00
};

#endif

#if defined(REBREW_SERVER)
unsigned char _dpad_10029bb8[960];
unsigned char _dpad_101de5a0[1008];
#endif
