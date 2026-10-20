#include <string.h>

extern unsigned char g_773d75;

int __cdecl fcn_004f0c90(int);
void __cdecl fcn_004f4f60(int, int, int, int, int);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_005100f0(int, int);
int __cdecl fcn_004c6de0(void*);

/* ADDRESS: GOLDTL 0x004f0a30 */
int __cdecl fcn_004f0a30(char* a0, char* a1, unsigned int* a2,
	unsigned int* a3, unsigned int* a4, unsigned int a5, int a6, unsigned int a7)
{
	unsigned int pkt[32];
	char* rec;
	unsigned int first;
	unsigned int need_start;
	unsigned int prio;
	int ret;
	int ok;

	first = a5;
	prio = a5;
	ok = 1;
	ret = -1;
	need_start = 0;
	if (a0 == 0) {
		return -1;
	}
	rec = (char*) fcn_004f0c90(*(int*) (a0 + 1));
	if (rec == 0) {
		return -1;
	}
	if (*(unsigned char*) (rec + 4) & 2) {
		return -1;
	}
	if (a4 != 0) {
		need_start = 2;
	} else if (a3 != 0) {
		need_start = 1;
	}
	memset(pkt, 0, sizeof(pkt));
	if (a2 != 0) {
		fcn_004f4f60(8, 1, *(int*) (a1 + 4), -1, -1);
		fcn_005100f0(*(int*) (a1 + 4), -a6);
		fcn_004c51a0(-1, *(int*) (a1 + 4), (char) g_773d75, a7);
		pkt[0] = *(unsigned int*) (a0 + 1);
		pkt[2] = need_start;
		pkt[1] = first;
		memcpy(&pkt[3], a2, 0x1a * 4);
		ok = 0;
		prio = 0;
		ret = fcn_004c6de0(pkt);
	}
	if (a3 != 0) {
		if (ok != 0) {
			fcn_005100f0(*(int*) (a1 + 4), -a6);
			fcn_004c51a0(-1, *(int*) (a1 + 4), (char) g_773d75, a7);
			ok = 0;
		}
		pkt[0] = *(unsigned int*) (a0 + 1);
		pkt[2] = need_start;
		pkt[1] = prio;
		memcpy(&pkt[3], a3, 0x1a * 4);
		prio = 0;
		ret = fcn_004c6de0(pkt);
	}
	if (a4 != 0) {
		if (ok != 0) {
			fcn_005100f0(*(int*) (a1 + 4), -a6);
			fcn_004c51a0(-1, *(int*) (a1 + 4), (char) g_773d75, a7);
		}
		pkt[0] = *(unsigned int*) (a0 + 1);
		pkt[1] = prio;
		pkt[2] = need_start;
		memcpy(&pkt[3], a4, 0x1a * 4);
		ret = fcn_004c6de0(pkt);
	}
	return ret;
}
