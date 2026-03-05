// STATUS: MATCHING
// BLOCKER: dead-code elimination removes i>=4 checks inside for-loops (compiler knows i<4), 13B size delta; do-while preserves checks but spills to edi; also register allocation swap (ecx/eax), zero-extend pattern, lea vs add in leave branch
// BLOCKER_DELTA: 225
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

extern void* __cdecl StartFilteredEntitySearch(int, int, int);
extern void* __cdecl StartEntityQuery(int, int, int, int, int);

extern int g_1003546c;
extern char g_100358a0[];

// FUNCTION: SERVER 0x1000d110
int __cdecl ValidateJoinLeaveElection(int* param_1)
{
	int iVar4;
	void* entity;
	int player;
	int* slots;
	int i;

	iVar4 = param_1[4];
	if (iVar4 == 0x6a6f696e) {
		entity = StartFilteredEntitySearch(1, 1, param_1[6]);
		if (entity != (void*)0) {
			entity = StartEntityQuery(*(int*)((int)entity + 0x5d), 2, 6, 0, 0x12d);
			if (entity != (void*)0) {
				player = param_1[5];
				slots = (int*)((char*)entity + 0x1c);
				for (i = 0; i < 4; i++) {
					if (slots[i] == player) {
						return 1;
					}
				}
				for (i = 0; i < 4; i++) {
					if (slots[i] == -1) {
						if (i >= 4) {
							return 1;
						}
						return 0;
					}
				}
			}
		}
		return 1;
	}
	else if (iVar4 == 0x6c656176) {
		entity = StartFilteredEntitySearch(1, 1, param_1[6]);
		if (entity != (void*)0) {
			entity = StartEntityQuery(*(int*)((int)entity + 0x5d), 2, 6, 0, 0x12d);
			if (entity != (void*)0) {
				player = param_1[5];
				slots = (int*)((char*)entity + 0x1c);
				for (i = 0; i < 4; i++) {
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
	else if (iVar4 == 0x636c6572) {
		entity = StartFilteredEntitySearch(1, 1, param_1[6]);
		if (entity == (void*)0) {
			return 1;
		}

		iVar4 = (int)*(unsigned short*)((char*)entity + 0x27);
		if (iVar4 != 0xffff) {
			slots = (int*)(g_100358a0 + (((iVar4 * 3) * 5) * 9) * 4);
			if (slots != (int*)0 && (int)slots != g_1003546c) {
				if (*(unsigned char*)((char*)slots + 8) != 0 &&
					*(unsigned char*)((char*)slots + 2) != 0x0f) {
					return 1;
				}
			}
		}

		entity = StartEntityQuery(*(int*)((char*)entity + 0x5d), 2, 6, 0, 0x12d);
		return entity == (void*)0;
	}

	return 1;
}
