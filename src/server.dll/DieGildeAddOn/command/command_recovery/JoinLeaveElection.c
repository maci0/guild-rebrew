// FUNCTION: SERVER 0x1000fd50
// STATUS: STUB
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 445
// CFLAGS: /O2 /Gd
// SYMBOL: _JoinLeaveElection

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
// BLOCKER_DELTA: 400
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 445B
 *    CFlags: 
 *    Symbol: _JoinLeaveElection
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl JoinLeaveElection(int param_1,char *param_2)
 * 
 * {
 *   ushort uVar1;
 *   ushort *puVar2;
 *   int iVar3;
 *   ushort *puVar4;
 *   ushort *puVar5;
 *   
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x02';
 *     param_2[1] = '\0';
 *     param_2[6] = '\0';
 *     param_2[7] = '\0';
 *     param_2[8] = '\0';
 *     param_2[9] = '\0';
 *   }
 *   iVar3 = *(int *)(param_1 + 0x10);
 *   if (iVar3 == 0x6a6f696e) {
 *     puVar2 = StartFilteredEntitySearch(1,1,*(undefined4 *)(param_1 + 0x18));
 *     if ((puVar2 != (ushort *)0x0) &&
 *        (puVar2 = StartEntityQuery(*(int *)((int)puVar2 + 0x5d),2,6,0,0x12d), puVar2 != (ushort *)0x0
 *        )) {
 *       puVar5 = puVar2 + 0xe;
 *       iVar3 = 0;
 *       puVar4 = puVar5;
 *       do {
 *         if (*(int *)puVar4 == *(int *)(param_1 + 0x14)) {
 *           return 1;
 *         }
 *         iVar3 = iVar3 + 1;
 *         puVar4 = puVar4 + 2;
 *       } while (iVar3 < 4);
 *       iVar3 = 0;
 *       do {
 *         if (*(int *)puVar5 == -1) {
 *           if (3 < iVar3) {
 *             return 1;
 *           }
 *           if (param_2 != (char *)0x0) {
 *             *param_2 = '\x01';
 *           }
 */

extern void* __cdecl StartFilteredEntitySearch(int, int, int);
extern void* __cdecl StartEntityQuery(int, int, int, int, int);

extern int g_1003546c;
extern char g_100358a0[];

int __cdecl JoinLeaveElection(int param_1, char *param_2)
{
	void *entity;
	int i;
	int cmd;
	char *resident;
	unsigned short uVar1;

	if (param_2 != (char *)0) {
		*param_2 = '\x02';
		param_2[1] = '\0';
		*(int *)(param_2 + 6) = 0;
	}

	cmd = *(int *)(param_1 + 0x10);

	if (cmd == 0x6a6f696e) {
		entity = StartFilteredEntitySearch(1, 1, *(int *)(param_1 + 0x18));
		if (entity != (void *)0 &&
			(entity = StartEntityQuery(*(int *)((char *)entity + 0x5d), 2, 6, 0, 0x12d),
			 entity != (void *)0)) {
			i = 0;
			do {
				if (*(int *)((char *)entity + 0x1c + i * 4) == *(int *)(param_1 + 0x14)) {
					return 1;
				}
				i++;
			} while (i < 4);

			i = 0;
			do {
				if (*(int *)((char *)entity + 0x1c + i * 4) == -1) {
					if (i >= 4) {
						return 1;
					}
					if (param_2 != (char *)0) {
						*param_2 = '\x01';
					}
					*(int *)((char *)entity + i * 4 + 0x1c) = *(int *)(param_1 + 0x14);
					return 0;
				}
				i++;
			} while (i < 4);
		}
		return 1;
	}

	if (cmd == 0x6c656176) {
		entity = StartFilteredEntitySearch(1, 1, *(int *)(param_1 + 0x18));
		if (entity != (void *)0 &&
			(entity = StartEntityQuery(*(int *)((char *)entity + 0x5d), 2, 6, 0, 0x12d),
			 entity != (void *)0)) {
			i = 0;
			do {
				if (*(int *)((char *)entity + 0x1c + i * 4) == *(int *)(param_1 + 0x14)) {
					if (i >= 4) {
						return 1;
					}
					if (param_2 != (char *)0) {
						*param_2 = '\x01';
					}
					*(int *)((char *)entity + i * 4 + 0x1c) = -1;
					return 0;
				}
				i++;
			} while (i < 4);
		}
		return 1;
	}

	if (cmd == 0x636c6572) {
		entity = StartFilteredEntitySearch(1, 1, *(int *)(param_1 + 0x18));
		if (entity != (void *)0) {
			uVar1 = *(unsigned short *)((char *)entity + 0x27);
			if (uVar1 != 0xffff) {
				resident = (char *)(g_100358a0 + ((((unsigned int)uVar1 * 3) * 5) * 9) * 4);
				if (resident != (char *)0 && (int)resident != g_1003546c) {
					if (*(unsigned char *)(resident + 8) != 0 &&
						*(unsigned char *)(resident + 2) != 0x0f) {
						return 1;
					}
				}
			}

			entity = StartEntityQuery(*(int *)((char *)entity + 0x5d), 2, 6, 0, 0x12d);
			if (entity != (void *)0) {
				if (param_2 != (char *)0) {
					*param_2 = '\x01';
				}

				i = 4;
				entity = (char *)entity + 0x1c;
				do {
					if (*(int *)entity == *(int *)(param_1 + 0x14)) {
						*(int *)entity = -1;
					}
					entity = (char *)entity + 4;
					i--;
				} while (i != 0);
				return 0;
			}
		}
	}

	return 1;
}
