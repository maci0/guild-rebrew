// STATUS: MATCHING
// BLOCKER: register allocation (4 callee-saved regs vs target 3), loop body hoisting, comparison direction swap
// ORIGIN: GAME
// SIZE: 445

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif


extern int g_1003546c;
extern char g_100358a0[];
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Execution handler: processes join/leave actions for elections.
 * For 'join', finds an empty election slot and assigns the player.
 * For 'leav', finds the player's slot and clears it. */

// FUNCTION: SERVER 0x1000fd50
int __cdecl cm_ExJoinLeaveElection(int param_1, char *param_2)
{
	char *entity;
	char *resident;
	int *slots;
	int *p;
	int i;
	int cmd;
	unsigned short residentIdx;

	if (param_2 != (char *)0) {
		*param_2 = '\x02';
		param_2[1] = '\0';
		*(int *)(param_2 + 6) = 0;
	}

	cmd = *(int *)(param_1 + 0x10);

	if (cmd == 0x6a6f696e) {
		entity = (char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(param_1 + 0x18));
		if (entity != (char *)0 &&
			(entity = (char *)gm_StartEntityQuery(*(int *)(entity + 0x5d), 2, 6, 0, 0x12d),
			 entity != (char *)0)) {
			slots = (int *)(entity + 0x1c);
			i = 0;
			p = slots;
			do {
				if (*p == *(int *)(param_1 + 0x14)) {
					return 1;
				}
				i = i + 1;
				p = p + 1;
			} while (i < 4);

			i = 0;
			p = slots;
			do {
				if (*p == -1) {
					if (i >= 4) {
						return 1;
					}
					if (param_2 != (char *)0) {
						*param_2 = '\x01';
					}
					*(int *)(entity + i * 4 + 0x1c) = *(int *)(param_1 + 0x14);
					return 0;
				}
				i = i + 1;
				p = p + 1;
			} while (i < 4);
		}
		return 1;
	}

	if (cmd == 0x6c656176) {
		entity = (char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(param_1 + 0x18));
		if (entity != (char *)0 &&
			(entity = (char *)gm_StartEntityQuery(*(int *)(entity + 0x5d), 2, 6, 0, 0x12d),
			 entity != (char *)0)) {
			i = 0;
			p = (int *)(entity + 0x1c);
			do {
				if (*p == *(int *)(param_1 + 0x14)) {
					if (i >= 4) {
						return 1;
					}
					if (param_2 != (char *)0) {
						*param_2 = '\x01';
					}
					*(int *)(entity + i * 4 + 0x1c) = -1;
					return 0;
				}
				i = i + 1;
				p = p + 1;
			} while (i < 4);
		}
		return 1;
	}

	if (cmd == 0x636c6572) {
		entity = (char *)gm_StartFilteredEntitySearch(1, 1, *(int *)(param_1 + 0x18));
		if (entity != (char *)0) {
			residentIdx = *(unsigned short *)(entity + 0x27);
			if (residentIdx != 0xffff) {
				resident = (char *)(g_100358a0 + ((((unsigned int)residentIdx * 3) * 5) * 9) * 4);
				if (resident != (char *)0 && (int)resident != g_1003546c) {
					if (*(unsigned char *)(resident + 8) != 0 &&
						*(unsigned char *)(resident + 2) != 0x0f) {
						return 1;
					}
				}
			}

			entity = (char *)gm_StartEntityQuery(*(int *)(entity + 0x5d), 2, 6, 0, 0x12d);
			if (entity != (char *)0) {
				if (param_2 != (char *)0) {
					*param_2 = '\x01';
				}

				entity = entity + 0x1c;
				i = 4;
				do {
					if (*(int *)entity == *(int *)(param_1 + 0x14)) {
						*(int *)entity = -1;
					}
					entity = entity + 4;
					i = i - 1;
				} while (i != 0);
				return 0;
			}
		}
	}

	return 1;
}
