
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

extern int g_1003546c;
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Validation handler: checks preconditions for joining or
 * leaving an election. For 'join', verifies player isn't already
 * in the election slots and an empty slot exists. For 'leav',
 * verifies the player is actually in a slot. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000d110
// cm_ChkJoinLeaveElection

int __cdecl cm_ChkJoinLeaveElection(int* cmd)
{
	int action;
	char* q;
	int player;
	int i;
	unsigned short w;
	char* rec;

	action = *(int *) ((char *) cmd + 0x10);
	if (action == 0x6a6f696e) {
		q = (char *) gm_StartFilteredEntitySearch(1, 1, *(int *) ((char *) cmd + 0x18));
		if (q == 0) return 1;
		q = (char *) gm_StartEntityQuery(*(int *) (q + 0x5d), 2, 6, 0, 0x12d);
		if (q == 0) return 1;
		player = *(int *) ((char *) cmd + 0x14);
		for (i = 0; i < 4; i++) {
			if (*(int *) (q + 0x1c + i * 4) == player) return 1;
		}
		i = 0;
		while (i < 4 && *(int *) (q + 0x1c + i * 4) != -1) {
			i++;
		}
		if (i >= 4) return 1;
		return 0;
	}
	if (action == 0x6c656176) {
		q = (char *) gm_StartFilteredEntitySearch(1, 1, *(int *) ((char *) cmd + 0x18));
		if (q == 0) return 1;
		q = (char *) gm_StartEntityQuery(*(int *) (q + 0x5d), 2, 6, 0, 0x12d);
		if (q == 0) return 1;
		player = *(int *) ((char *) cmd + 0x14);
		for (i = 0; i < 4; i++) {
			if (*(int *) (q + 0x1c + i * 4) == player) break;
		}
		if (i >= 4) return 1;
		return 0;
	}
	if (action == 0x636c6572) {
		q = (char *) gm_StartFilteredEntitySearch(1, 1, *(int *) ((char *) cmd + 0x18));
		if (q == 0) return 1;
		w = *(unsigned short *) (q + 0x27);
		if (w != 0xffff) {
			rec = (char *) (0x100358a0 + w * 0x21c);
			if (rec == 0) goto cler_query;
			if (rec == (char *) g_1003546c) goto cler_query;
			if (*(unsigned char *) (rec + 8) == 0) goto cler_query;
			if (*(unsigned char *) (rec + 2) != 0xf) return 1;
		}
		goto cler_query;
	}
	return 1;
cler_query:
	return gm_StartEntityQuery(*(int *) (q + 0x5d), 2, 6, 0, 0x12d) == 0;
}
