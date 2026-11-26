#include <string.h>

/* Message object handed to fcn_004c5530. Field offsets and the 0xf8 extent
 * come from the reference stores and its `rep stosd` clear. */
typedef struct GOLDTL_Msg549 {
	int f0;                     /* 0x00 */
	unsigned char f4;           /* 0x04, 0x71 */
	char pad5[3];
	int f8;                     /* 0x08 */
	int fc;                     /* 0x0c, -1 */
	char pad10[0x18];
	int f28;                    /* 0x28 */
	int f2c;                    /* 0x2c */
	int f30;                    /* 0x30 */
	unsigned short f34;         /* 0x34 */
	unsigned char f36;          /* 0x36, 2 */
	char pad37[0x21];
	int f58;                    /* 0x58 */
	char pad5c[0x9c];
} GOLDTL_Msg549;

extern float g_6628a8;
extern float g_6628cc;
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern int g_7f4ca4[];
extern char s_6a5930[];
extern char s_6a594c[];
extern char s_6a5960[];
extern char s_6a5968[];
extern char s_6a597c[];

void __cdecl fcn_00529160(int a, int b, int id, int c);
int __cdecl evt_FindScriptById(int a);
void __cdecl evt_RequestScriptExit(int a);
int __cdecl cm_SendCopyEntityData(GOLDTL_Msg549* msg);
void __cdecl cm_RequestChangeBits(int a, int b, int c, int d, int e);
int __cdecl ch_StartMovement(int a, int b, int c, int d, int e, char* text);
float __cdecl gm_GetEntityMaxHealth(unsigned short* e);
int __cdecl fcn_00567170(unsigned short* e, int* a, int* b, int c);
void __cdecl io_FormatTextBuffer(char* buf, int fmt, ...);
int __cdecl he_MessageBoxQuickjump(int a, int b, char* text, int c, int d,
                                   int e, int f, int g, void* h);

/* ADDRESS: GOLDTL 0x00549580 */
void __cdecl fcn_00549580(int a0, char* subject, char* a2, char* a3,
                          float a4, int a5)
{
	char* p;
	int v9;
	int v8;
	GOLDTL_Msg549 msg;
	char buf[0x800];
	int t;

	p = subject;
	if (a4 <= 0.0f) {
		fcn_00529160(0, 0, *(unsigned short*) p, 0);
		t = *(int*) (p + 0x184);
		if (t != 0) {
			t = *(int*) (t + 0x28);
			if (t != -1) {
				evt_RequestScriptExit(evt_FindScriptById(t));
			}
		}
		memset(&msg, 0, 0xf8);
		msg.f4 = 0x71;
		if (a0) {
			msg.f8 = g_7f4ca4[*(unsigned short*) (a0 + 8) * 0x87];
		} else {
			msg.f8 = *(int*) (a2 + 4);
		}
		msg.f28 = gm_GameTime;
		msg.f2c = g_7f4c04;
		msg.f30 = g_7f4c08;
		msg.fc = -1;
		msg.f34 = (unsigned short) g_7f4c0c;
		msg.f36 = 2;
		msg.f58 = *(int*) (p + 4);
		cm_SendCopyEntityData(&msg);
		if (a2[2] != 6 && a2[2] != 7) {
			return;
		}
		if (a5) {
			return;
		}
		if (p[2] == 0x14) {
			io_FormatTextBuffer(buf, 0x414a, *(unsigned short*) p, a3);
			he_MessageBoxQuickjump(*(int*) (a2 + 4), *(int*) (a3 + 1), buf, 0, 0x60a,
				*(int*) (a3 + 1), -1, 0, s_6a597c);
		} else {
			io_FormatTextBuffer(buf, 0x1bb0, *(unsigned short*) p, a3);
			he_MessageBoxQuickjump(*(int*) (a2 + 4), *(int*) (a3 + 1), buf, 0, 0x60a,
				*(int*) (a3 + 1), -1, 0, s_6a5968);
		}
		return;
	}
	if (gm_GetEntityMaxHealth((unsigned short*) p) * g_6628cc > a4) {
		if (fcn_00567170((unsigned short*) p, &v9, &v8, 0)) {
			if (*(int*) (p + 0x184) != 0) {
				fcn_00529160(0, 0, *(unsigned short*) p, 0);
				t = *(int*) (*(int*) (p + 0x184) + 0x28);
				if (t != -1) {
					evt_RequestScriptExit(evt_FindScriptById(t));
				}
				cm_RequestChangeBits(*(int*) (p + 4), 0x1c8, 4, 0x800, 0);
				if (v8 == -1) {
					ch_StartMovement(*(int*) (p + 4), v9, v8, 0, 1,
									  s_6a5960);
				} else {
					ch_StartMovement(*(int*) (p + 4), v9, v8, 0, 0,
									  s_6a5960);
				}
				if (a2[2] != 6 && a2[2] != 7) {
					return;
				}
				io_FormatTextBuffer(buf, 0x1baf, *(unsigned short*) p, a3);
				he_MessageBoxQuickjump(*(int*) (a2 + 4), *(int*) (a3 + 1), buf, 0, 0x60a,
					*(int*) (a3 + 1), -1, 0, s_6a594c);
				return;
			}
		}
	}
	if (a2[2] != 6 && a2[2] != 7) {
		return;
	}
	if (p[2] == 0x14) {
		io_FormatTextBuffer(buf, 0x4149, *(unsigned short*) p, a3);
		he_MessageBoxQuickjump(*(int*) (a2 + 4), *(int*) (a3 + 1), buf, 0, 0x60a,
			*(int*) (a3 + 1), -1, 0, s_6a5930);
	} else {
		io_FormatTextBuffer(buf, 0x1bae, *(unsigned short*) p, a3);
		he_MessageBoxQuickjump(*(int*) (a2 + 4), *(int*) (a3 + 1), buf, 0, 0x60a,
			*(int*) (a3 + 1), -1, 0, s_6a594c);
	}
}
