#include "client_types.h"

extern char* g_aed324;
extern char* g_aed200;
extern int g_14cbcb0;
extern int g_774954;
extern int g_aecde0;
extern cell10_fb5760 g_fb5760[0x8000];

int __cdecl sprintf(char*, const char*, ...);
void __cdecl fcn_004c4aa0(char*);
int __cdecl fcn_004c41c0(char*);
void __cdecl fcn_004c4250(char*);
int __cdecl ahm_ProcessEntityChain(char*);
void __cdecl fcn_005356b0(int);

/* ADDRESS: GOLDTL 0x004c4b00 */
int __cdecl cm_ExecCommand(void)
{
	char* node;
	char* prev;
	char* next;
	char* slot;
	cell10_fb5760* cell;
	char* p;
	int pass;
	int seq;
	int lastreq;
	char buf1[256];
	char buf2[256];
	char buf3[256];

	node = g_aed324;
	if (g_14cbcb0) {
		while (node) {
			if (*(int*) (node + 4) != -1) {
				cell = &g_fb5760[*(int*) (node + 4) & 0x7fff];
				cell->f0 = 2;
				cell->f1 = 0;
				cell->f6 = 0;
			}
			fcn_004c4aa0(node);
			node = g_aed324;
		}
		p = (char*) 0xfb5760;
		do {
			*p = 2;
			p += 10;
		} while ((int) p < 0x1005760);
		if (!g_774954) {
			g_774954 = 1;
			fcn_005356b0(0x5438c0);
			node = g_aed324;
		}
	}
	prev = 0;
	if (node) {
		do {
			slot = node + 0x95;
			next = *(char**) slot;
			pass = 1;
			if (!prev) {
				if (*node == 5)
					prev = node;
			} else if (*node == 6) {
				if (!ahm_ProcessEntityChain(prev))
					pass = 0;
				slot = prev + 0x95;
				next = *(char**) slot;
				node = prev;
				prev = 0;
			}
			if (prev)
				pass = 0;
			if (*node != 7 && fcn_004c41c0(node) && pass) {
				if (node == g_aed324) {
					g_aed324 = next;
				} else {
					*(char**) (*(char**) (node + 0x91) + 0x95) = *(char**) slot;
					if (*(char**) slot)
						*(char**) (*(char**) slot + 0x91) = *(char**) (node + 0x91);
				}
				*(int*) (node + 0x91) = 0;
				*(char**) slot = g_aed200;
				g_aed200 = node;
				fcn_004c4250(node);
				if ((unsigned char) *node < 0x6a) {
					if (*(int*) (node + 4) == -1) {
						cell = 0;
					} else {
						lastreq = *(int*) 0xaed31c;
						cell = &g_fb5760[*(int*) (node + 4) & 0x7fff];
						cell->f0 = 2;
						cell->f1 = 0;
						cell->f6 = 0;
						seq = *(int*) (node + 8);
						if (seq == lastreq + 1) {
							*(int*) 0xaed31c = seq;
						} else if (seq == g_aecde0) {
							sprintf(buf1,
								"cm_ExecCommand(): Received a Command with Count == cm_LastSyncCount, cmd->Count is %li, LastRequCnt is %li",
								seq, lastreq);
						} else if (*node == 0x20 && node[0x10] == 0xe) {
							sprintf(buf2,
								"cm_ExecCommand(): Received Sync, cmd->Count is %li, LastRequCnt is %li",
								seq, lastreq);
						} else {
							sprintf(buf3,
								"cm_ExecCommand(): Lost a Command, cmd->Count is %li, cm_LastRequCount is %li",
								seq, lastreq);
							*(int*) 0xaed31c = *(int*) (node + 8);
						}
					}
					(*(void (__cdecl**) (char*, char*)) ((int) (unsigned char) *node * 4 + 0x68a9e0))(node, (char*) cell);
				}
			}
			node = next;
		} while (node);
	}
	return 0;
}
