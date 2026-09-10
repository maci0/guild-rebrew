extern unsigned short* g_entity_table_end; /* 0x1003546c */
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Execution handler: processes join/leave actions for elections.
 * For 'join', finds an empty election slot and assigns the player.
 * For 'leav', finds the player's slot and clears it. */

// FUNCTION: SERVER 0x1000fd50
// cm_ExJoinLeaveElection

int __cdecl cm_ExJoinLeaveElection(int cmd, char* result)
{
	int action;
	char* q;
	int player;
	int i;
	unsigned short w;
	char* rec;

	if (result) {
		result[0] = 2;
		result[1] = 0;
		*(int *) (result + 6) = 0;
	}
	action = *(int *) (cmd + 0x10);
	if (action == 0x6a6f696e) {
		q = (char *) gm_StartFilteredEntitySearch(1, 1, *(int *) (cmd + 0x18));
		if (q == 0) return 1;
		q = (char *) gm_StartEntityQuery(*(int *) (q + 0x5d), 2, 6, 0, 0x12d);
		if (q == 0) return 1;
		player = *(int *) (cmd + 0x14);
		for (i = 0; i < 4; i++) {
			if (*(int *) (q + 0x1c + i * 4) == player) return 1;
		}
		for (i = 0; i < 4; i++) {
			if (*(int *) (q + 0x1c + i * 4) == -1) break;
		}
		if (i >= 4) return 1;
		if (result) result[0] = 1;
		*(int *) (q + 0x1c + i * 4) = *(int *) (cmd + 0x14);
		return 0;
	}
	if (action == 0x6c656176) {
		q = (char *) gm_StartFilteredEntitySearch(1, 1, *(int *) (cmd + 0x18));
		if (q == 0) return 1;
		q = (char *) gm_StartEntityQuery(*(int *) (q + 0x5d), 2, 6, 0, 0x12d);
		if (q == 0) return 1;
		player = *(int *) (cmd + 0x14);
		for (i = 0; i < 4; i++) {
			if (*(int *) (q + 0x1c + i * 4) == player) break;
		}
		if (i >= 4) return 1;
		if (result) result[0] = 1;
		*(int *) (q + 0x1c + i * 4) = -1;
		return 0;
	}
	if (action == 0x636c6572) {
		q = (char *) gm_StartFilteredEntitySearch(1, 1, *(int *) (cmd + 0x18));
		if (q == 0) return 1;
		w = *(unsigned short *) (q + 0x27);
		if (w != 0xffff) {
			rec = (char *) (0x100358a0 + w * 0x21c);
			if (rec == 0) goto cler_query;
			if (rec == (char *) g_entity_table_end) goto cler_query;
			if (*(unsigned char *) (rec + 8) == 0) goto cler_query;
			if (*(unsigned char *) (rec + 2) != 0xf) return 1;
		}
		goto cler_query;
	}
	return 1;
cler_query:
	q = (char *) gm_StartEntityQuery(*(int *) (q + 0x5d), 2, 6, 0, 0x12d);
	if (q == 0) return 1;
	if (result) result[0] = 1;
	for (i = 0; i < 4; i++) {
		if (*(int *) (q + 0x1c + i * 4) == *(int *) (cmd + 0x14)) {
			*(int *) (q + 0x1c + i * 4) = -1;
		}
	}
	return 0;
}
