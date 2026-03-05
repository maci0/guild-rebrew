// FUNCTION: SERVER 0x1000d110
// STATUS: STUB
// BLOCKER: comparison direction swap
// ORIGIN: GAME
// SIZE: 333
// CFLAGS: /O2 /Gd
// SYMBOL: _ValidateJoinLeaveElection

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
// BLOCKER_DELTA: 317
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 333B
 *    CFlags: 
 *    Symbol: _ValidateJoinLeaveElection
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ValidateJoinLeaveElection(int *param_1)
 * 
 * {
 *   ushort uVar1;
 *   ushort *puVar2;
 *   ushort *puVar3;
 *   int iVar4;
 *   
 *   iVar4 = param_1[4];
 *   if (iVar4 == 0x6a6f696e) {
 *     puVar2 = StartFilteredEntitySearch(1,1,param_1[6]);
 *     if ((puVar2 != (ushort *)0x0) &&
 *        (puVar2 = StartEntityQuery(*(int *)((int)puVar2 + 0x5d),2,6,0,0x12d), puVar2 != (ushort *)0x0
 *        )) {
 *       puVar2 = puVar2 + 0xe;
 *       iVar4 = 0;
 *       puVar3 = puVar2;
 *       do {
 *         if (*(int *)puVar3 == param_1[5]) {
 *           return 1;
 *         }
 *         iVar4 = iVar4 + 1;
 *         puVar3 = puVar3 + 2;
 *       } while (iVar4 < 4);
 *       iVar4 = 0;
 *       do {
 *         if (*(int *)puVar2 == -1) {
 *           if (3 < iVar4) {
 *             return 1;
 *           }
 *           return 0;
 *         }
 *         iVar4 = iVar4 + 1;
 *         puVar2 = puVar2 + 2;
 *       } while (iVar4 < 4);
 *     }
 *   }
 *   else if (iVar4 == 0x6c656176) {
 *     puVar2 = StartFilteredEntitySearch(1,1,param_1[6]);
 *     if ((puVar2 != (ushort *)0x0) &&
 *        (puVar2 = StartEntityQuery(*(int *)((int)puVar2 + 0x5d),2,6,0,0x12d), puVar2 != (ushort *)0x0
 *        )) {
 */

extern void* __cdecl StartFilteredEntitySearch(int, int, int);
extern void* __cdecl StartEntityQuery(int, int, int, int, int);

extern int g_1003546c;
extern char g_100358a0[];

int __cdecl ValidateJoinLeaveElection(int* param_1)
{
	void* entity;
	void* resident;
	int* slots;
	int i;
	int player;

	player = param_1[5];

	if (param_1[4] == 0x6a6f696e) {
		entity = StartFilteredEntitySearch(1, 1, param_1[6]);
		if (entity != (void*) 0x0) {
			entity = StartEntityQuery(*(int*) ((char*) entity + 0x5d), 2, 6, 0, 0x12d);
			if (entity != (void*) 0x0) {
				slots = (int*) ((char*) entity + 0x1c);

				for (i = 0; i < 4; i = i + 1) {
					if (slots[i] == player) {
						return 1;
					}
				}

				for (i = 0; i < 4; i = i + 1) {
					if (slots[i] == -1) {
						if (i > 3) {
							return 1;
						}
						return 0;
					}
				}
			}
		}
		return 1;
	}

	if (param_1[4] == 0x6c656176) {
		entity = StartFilteredEntitySearch(1, 1, param_1[6]);
		if (entity != (void*) 0x0) {
			entity = StartEntityQuery(*(int*) ((char*) entity + 0x5d), 2, 6, 0, 0x12d);
			if (entity != (void*) 0x0) {
				slots = (int*) ((char*) entity + 0x1c);
				for (i = 0; i < 4; i = i + 1) {
					if (slots[i] == player) {
						if (i >= 4) {
							return 1;
						}
						return 0;
					}
				}
				return 1;
			}
		}
		return 1;
	}

	if (param_1[4] == 0x636c6572) {
		entity = StartFilteredEntitySearch(1, 1, param_1[6]);
		if (entity == (void*) 0x0) {
			return 1;
		}

		i = *(unsigned short*) ((char*) entity + 0x27);
		if (i != 0xffff) {
			resident = (void*) (g_100358a0 + (((i * 3) * 5) * 9) * 4);
			if ((resident != (void*) 0x0) && ((int) resident != g_1003546c)) {
				if ((*(unsigned char*) ((char*) resident + 8) != 0) &&
					(*(unsigned char*) ((char*) resident + 2) != 0x0f)) {
					return 1;
				}
			}
		}

		entity = StartEntityQuery(*(int*) ((char*) entity + 0x5d), 2, 6, 0, 0x12d);
		return entity == (void*) 0x0;
	}

	return 1;
}
