typedef struct {

extern unsigned short func_1001a0d0(unsigned int);
extern unsigned int __cdecl CreateEntityFromParents(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
extern int __cdecl get_priority_info(int, int*);
extern int DAT_100a8c30;
extern void __cdecl StartEntityQuery(int, int, int, ...);
extern unsigned int __cdecl FindAndMatchParents(int param);
extern void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);
extern unsigned char DAT_10035a04;
extern unsigned char DAT_10035a05;
extern unsigned char DAT_100358a0;

// STATUS: MATCHING
// BLOCKER: instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout, zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 535
// SYMBOL: _FindAndMatchParents
// FUNCTION: SERVER 0x100151e0
// FindAndMatchParents

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 469

unsigned int FindAndMatchParents(unsigned int param_1)
{
	unsigned short uVar1;
	unsigned short uVar2;
	unsigned int uVar3;
	int* piVar4;
	int iVar5;
	unsigned int uVar6;
	int iVar7;
	int iVar8;
	unsigned int uStack_20;
	int aiStack_18[6];

	iVar8 = 0;
	aiStack_18[0] = 0x60;
	aiStack_18[1] = 0x4b;
	aiStack_18[2] = 0x28;
	aiStack_18[3] = 0x17;
	aiStack_18[4] = 9;
	aiStack_18[5] = 0;
	uVar6 = 0x300;
	do {
		uVar1 = func_1001a0d0(uVar6);
		uVar3 = uVar1 * 0xf;
		iVar5 = uVar1 * 0x21c;
		if (*(int*) (iVar5 + 0x100358a0) == -1) {
			uVar3 = uVar6 * 3 + (uVar6 * 3 >> 0x1f & 3U) >> 2;
			uVar6 = uVar3;
		}
		else if (((5 < *(unsigned int*) (iVar5 + 0x100358a2)) ||
				  (uVar3 = 0, *(unsigned int*) (iVar5 + 0x100358aa) < *(unsigned int*) (iVar5 + 0x100358c0))) ||
				 (uVar3 = 0, *(char*) (iVar5 + 0x100358a8) == '\0')) {
			uVar1 = 0xffff;
		}
		else {
			piVar4 = (int*) (iVar5 + 0x10035908);
			iVar7 = 0;
			iVar5 = 5;
			do {
				if (*piVar4 != -1) {
					iVar7 = iVar7 + 1;
				}
				piVar4 = piVar4 + 1;
				iVar5 = iVar5 + -1;
			} while (iVar5 != 0);
			uVar3 = func_1001a0d0(0x100);
			uVar3 = (uVar3 & 0xffff) + 1;
			if (uVar3 < aiStack_18[iVar7]) {
				break;
			}
		}
		iVar8 = iVar8 + 1;
	} while (iVar8 < 0x10);
	if (uVar1 == 0xffff) {
		return uVar3 & 0xffff0000;
	}
	uStack_20 = 0;
	do {
		uVar2 = func_1001a0d0(uVar6);
		iVar8 = uVar2 * 0x21c;
		if (*(int*) (iVar8 + 0x100358a0) == -1) {
			uVar6 = uVar6 * 3 + (uVar6 * 3 >> 0x1f & 3U) >> 2;
		}
		else if (((5 < *(unsigned int*) (iVar8 + 0x100358a2)) ||
				  (*(unsigned int*) (iVar8 + 0x100358aa) < *(unsigned int*) (iVar8 + 0x100358c0))) ||
				 (*(char*) (iVar8 + 0x100358a8) == '\0')) {
			uVar2 = 0xffff;
		}
		else {
			piVar4 = (int*) (iVar8 + 0x10035908);
			iVar5 = 0;
			iVar8 = 5;
			do {
				if (*piVar4 != -1) {
					iVar5 = iVar5 + 1;
				}
				piVar4 = piVar4 + 1;
				iVar8 = iVar8 + -1;
			} while (iVar8 != 0);
			uVar3 = func_1001a0d0(0x100);
			uVar3 = (uVar3 & 0xffff) + 1;
			if (uVar3 < aiStack_18[iVar5]) {
				break;
			}
		}
		uVar3 = uStack_20 + 1;
		uStack_20 = uVar3;
	} while (uVar3 < 0x10);
	if (uVar2 != 0xffff) {
		uVar6 = CreateEntityFromParents(
			0,
			*(unsigned int*) (uVar1 * 0x21c + 0x100358a4),
			*(unsigned int*) (uVar2 * 0x21c + 0x100358a4),
			param_1,
			0,
			0,
			0,
			2
		);
		return uVar6;
	}
	return uVar3 & 0xffff0000;
}

// ORIGIN: GAME
// STATUS: RELOC
// SIZE: 83
// SYMBOL: _priority_update
// ANALYSIS: Updates priority tracking for dynamic entity dispatch/update lists. Limits simultaneous update weight using GetStatPair constraints.
// FUNCTION: SERVER 0x10015400
// priority_update

void __cdecl priority_update(char* ctx, char* entity)
{
	int info[2];
	unsigned char type;
	unsigned short prio;
	char* current;
	type = *(unsigned char*) entity;
	get_priority_info((int) type, info);
	prio = (unsigned char) *(entity + 0x65);
	if (prio >= (unsigned short) info[0]) {
		return;
	}
	current = *(char**) (ctx + 0x170);
	if (current) {
		if (*(unsigned char*) (current + 0x65) > 0) {
			*(unsigned char*) (current + 0x65) -= 1;
		}
	}
	*(char**) (ctx + 0x170) = entity;
	*(unsigned char*) (entity + 0x65) += 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 145
// SYMBOL: _StartEntityQueryByType
// FUNCTION: SERVER 0x10015460
// StartEntityQueryByType

void __cdecl StartEntityQueryByType(unsigned char* param_1)
{
	char cVar1;
	int owner;

	cVar1 = *(char*) (DAT_100a8c30 + (unsigned int) *param_1 * 0x24d);
	owner = *(int*) (param_1 + 0x5d);
	if (cVar1 == '\x01') {
		StartEntityQuery(owner, 1, 0, 0x12);
		return;
	}
	if (cVar1 == '\x02') {
		StartEntityQuery(owner, 1, 0, 0x13);
		return;
	}
	if (cVar1 == '\x1d') {
		StartEntityQuery(owner, 1, 0, 0xfd);
		return;
	}
	if (cVar1 == '\x16') {
		StartEntityQuery(owner, 1, 0, 0x120);
	}
	return;
}

// STATUS: RELOC
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), zero-extend pattern (xor vs mov)
// BLOCKER_DELTA: 138
// SIZE: 180
// SYMBOL: _sim_CreateCitizen
// FUNCTION: SERVER 0x10015500
// sim_CreateCitizen

void* __cdecl sim_CreateCitizen(
	unsigned char param_1,
	int param_2,
	int param_3,
	unsigned char param_4,
	unsigned char param_5
)
{
	unsigned int uVar1;

	if ((param_1 & 1) != 0) {
		uVar1 = FindAndMatchParents(param_3) & 0xffff;
		if (uVar1 == 0xffff) {
			goto error;
		}
		if ((param_1 & 2) != 0) {
			(&DAT_10035a05)[uVar1 * 0x21c] = param_5;
			(&DAT_10035a04)[uVar1 * 0x21c] = param_4;
		}
	}
	else {
		uVar1 =
			CreateEntityFromParents(param_2, -1, -1, param_3, 0, (unsigned int) param_4, (unsigned int) param_5, 2) &
			0xffff;
	}
	if (uVar1 == 0xffff) {
		goto error;
	}
	return &DAT_100358a0 + uVar1 * 0x21c;
error:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\sim.c",
		0x127d,
		"sim_CreateCitizen(): could not alloc spieler",
		1
	);
	return (void*) 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 197
// SYMBOL: _AdvanceGameClock
// BLOCKER_DELTA: 164
// FUNCTION: SERVER 0x100155c0
// AdvanceGameClock

#pragma pack(push, 1)
	int days;    /* 0x00 */
	short hours; /* 0x04 */
	int minutes; /* 0x06 */
	int seconds; /* 0x0a */
} TimeStruct;
#pragma pack(pop)

int __cdecl AdvanceGameClock(int* param_1, int param_2, int param_3, int param_4)
{
	int iVar1;
	unsigned int uVar2;
	unsigned int uVar3;

	param_4 = param_4 + *(int*) ((int) param_1 + 10);
	*(int*) ((int) param_1 + 6) = *(int*) ((int) param_1 + 6) + param_4 / 0x3c;
	*(int*) ((int) param_1 + 10) = param_4 % 0x3c;
	param_3 = *(int*) ((int) param_1 + 6) + param_3;
	*(short*) (param_1 + 1) = *(short*) (param_1 + 1) + (short) (param_3 / 0x3c);
	iVar1 = param_3 / 0x3c;
	*(int*) ((int) param_1 + 6) = param_3 % 0x3c;
	uVar3 = (unsigned int) *(unsigned short*) (param_1 + 1) + param_2;
	if (0x17 < (int) uVar3) {
		uVar2 = uVar3 / 0x18;
		uVar3 = uVar3 % 0x18;
		do {
			iVar1 = *param_1 + 1;
			uVar2 = uVar2 - 1;
			*param_1 = iVar1;
		} while (uVar2 != 0);
	}
	if ((int) uVar3 < 0) {
		uVar2 = (0x17 - uVar3) / 0x18;
		iVar1 = uVar3 + uVar2 * 0x18;
		do {
			uVar2 = uVar2 - 1;
			*param_1 = *param_1 + -1;
		} while (uVar2 != 0);
		*(short*) (param_1 + 1) = (short) iVar1;
		return iVar1;
	}
	*(short*) (param_1 + 1) = (short) uVar3;
	return iVar1;
}

// ORIGIN: GAME
// STATUS: EXACT
// SIZE: 41
// SYMBOL: _SetSyncParams
// FUNCTION: SERVER 0x10015690
// SetSyncParams

void __cdecl SetSyncParams(int param_1, unsigned char param_2, unsigned int param_3, unsigned int param_4)
{
	*(unsigned int*) (param_1 + 10) = param_4 & 0xff;
	*(unsigned short*) (param_1 + 4) = (unsigned short) param_2;
	*(unsigned int*) (param_1 + 6) = param_3 & 0xff;
}
