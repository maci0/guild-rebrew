#include <string.h>

void* __cdecl gm_SearchTable67(int id);
void __cdecl fcn_0051af00(char* buf, int id, void* a3, int a4);
char* __cdecl fcn_00508e40(int a1);
void __cdecl fcn_004e6240(int* a1, char* a2, char* text, char* extra);

extern unsigned char g_7747b0;
extern char* g_14a9a1c;
extern char* g_14a9a20;
extern char g_6b5c60[];

/* ADDRESS: GOLDTL 0x004e32c0 */
int __cdecl fcn_004e32c0(char* p)
{
	char buf[0x200];
	void* t;
	char* q;
	int i;

	t = gm_SearchTable67(*(int*) (p + 0x7c));
	if (t == 0) {
		return 0;
	}
	fcn_0051af00(buf, 0x3fd9, t, *(int*) (p + 0x80));
	strcat(buf, (g_7747b0 & 4) ? g_14a9a20 : g_14a9a1c);
	for (i = 0; i < *(unsigned char*) (p + 0x30); i++) {
		q = fcn_00508e40(*(int*) (p + 0x34 + i * 4));
		if (q != 0 && (*(unsigned char*) (q + 2) == 6 || *(unsigned char*) (q + 2) == 7)) {
			fcn_004e6240((int*) q, p, buf, g_6b5c60);
		}
	}
	return 1;
}
