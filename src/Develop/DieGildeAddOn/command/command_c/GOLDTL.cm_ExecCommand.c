extern char* g_aed324;
extern char* g_aed200;
extern int g_14cbcb0;
extern int g_774954;

int __cdecl sprintf(char*, const char*, ...);
void __cdecl fcn_004c4aa0(char*);
int __cdecl fcn_004c41c0(char*);
void __cdecl fcn_004c4250(char*);
int __cdecl ahm_ProcessEntityChain(char*);
void __cdecl fcn_005356b0(int);

/* ADDRESS: GOLDTL 0x004c4b00 */
unsigned int __cdecl cm_ExecCommand(void)
{
	char* prev;
	char* node;
	char* next;
	char* slot;
	char* cell;
	int pass;
	int seq;
	char buf1[256];
	char buf2[256];
	char buf3[256];

	node = g_aed324;
	if (g_14cbcb0) {
		while (node) {
			g_aed324 = node;
			if (*(int*) (node + 4) != -1) {
				cell = (char*) ((*(int*) (node + 4) & 0x7fff) * 10 + 0xfb5760);
				cell[0] = 2;
				cell[1] = 0;
				*(int*) (cell + 6) = 0;
			}
			fcn_004c4aa0(node);
			node = g_aed324;
		}
		cell = (char*) 0xfb5760;
		do {
			*cell = 2;
			cell += 10;
		} while ((int) cell < 0x1005760);
		if (!g_774954) {
			g_774954 = 1;
			fcn_005356b0(0x5438c0);
			node = g_aed324;
		}
	}
	prev = 0;
	if (!node)
		return 0;
	do {
		next = *(char**) (node + 0x95);
		slot = node + 0x95;
		pass = 1;
		if (prev) {
			if (*node != 6) {
				pass = 0;
			} else {
				if (ahm_ProcessEntityChain(prev) == 0)
					pass = 0;
				slot = prev + 0x95;
				next = *(char**) (prev + 0x95);
				node = prev;
				prev = 0;
			}
		} else {
			if (*node == 5) {
				prev = node;
				pass = 0;
			}
		}
		if (*node != 7 && fcn_004c41c0(node) && pass) {
			if (node != g_aed324) {
				*(char**) (*(char**) (node + 0x91) + 0x95) = *(char**) slot;
				if (*(char**) slot)
					*(char**) (*(char**) slot + 0x91) = *(char**) (node + 0x91);
			} else {
				g_aed324 = next;
			}
			*(int*) (node + 0x91) = 0;
			*(char**) slot = g_aed200;
			g_aed200 = node;
			fcn_004c4250(node);
			if ((unsigned char) *node < 0x6a) {
				if (*(int*) (node + 4) != -1) {
					cell = (char*) ((*(int*) (node + 4) & 0x7fff) * 10 + 0xfb5760);
					cell[0] = 2;
					cell[1] = 0;
					*(int*) (cell + 6) = 0;
					seq = *(int*) (node + 8);
					if (seq != *(int*) 0xaed31c + 1) {
						if (seq != *(int*) 0xaecde0) {
							if (*node != 0x20 || node[0x10] != 0xe) {
								sprintf(buf3,
									"cm_ExecCommand(): Lost a Command, cmd->Count is %li, cm_LastRequCount is %li",
									seq, *(int*) 0xaed31c);
								seq = *(int*) (node + 8);
								goto label_cf9;
							}
							sprintf(buf2,
								"cm_ExecCommand(): Received Sync, cmd->Count is %li, LastRequCnt is %li",
								seq, *(int*) 0xaed31c);
						} else {
							sprintf(buf1,
								"cm_ExecCommand(): Received a Command with Count == cm_LastSyncCount, cmd->Count is %li, LastRequCnt is %li",
								seq, *(int*) 0xaed31c);
						}
					} else {
label_cf9:
						*(int*) 0xaed31c = seq;
					}
				} else {
					cell = 0;
				}
				(*(void (__cdecl**) (int, char*)) ((int) (unsigned char) *node * 4 + 0x68a9e0))(node, cell);
			}
		}
		node = next;
	} while (node);
	return 0;
}
