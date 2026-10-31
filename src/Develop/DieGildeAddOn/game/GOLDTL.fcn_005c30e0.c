#include <string.h>

#include "client_types.h"
#include "client_placement.h"

/* Message object handed to fcn_004c5530: 0xf8 bytes, same field layout the
 * other packet builders in this unit store into. */
typedef struct GOLDTL_Msg5c30 {
	int f0;                     /* 0x00 */
	unsigned char f4;           /* 0x04 */
	char pad5[3];
	int f8;                     /* 0x08 */
	int fc;                     /* 0x0c */
	char pad10[0x18];
	int f28;                    /* 0x28 */
	int f2c;                    /* 0x2c */
	int f30;                    /* 0x30 */
	unsigned short f34;         /* 0x34 */
	unsigned char f36;          /* 0x36 */
	char pad37[0x21];
	int f58;                    /* 0x58 */
	char pad5c[0x9c];
} GOLDTL_Msg5c30;               /* SIZE 0xf8 */

/* Entity type record, stride 0x24d. */
typedef struct GOLDTL_EntType5c30 {
	char pad[0x247];
	unsigned char f247;
	unsigned char f248;
	char pad249[4];
} GOLDTL_EntType5c30;

/* One player/house slot, stride 0x21c. */
typedef struct GOLDTL_House5c30 {
	int f0;
	int f4;
	char pad8[0x214];
} GOLDTL_House5c30;

extern unsigned char* lpGebaeudePROT;
extern unsigned char g_773d75;
extern unsigned short g_774970;
extern int g_774800;
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern double g_664e60;
extern char g_67e968[];

int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl fcn_00504f30(int, int);
int __cdecl fcn_0050d170(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00526120(void*, int);
int __cdecl fcn_00526010(void*, int, char);
int __cdecl gm_SearchTable67(int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void* __cdecl fcn_0050e4a0(int);
int __cdecl fcn_00507a10(unsigned char*);
int __cdecl fcn_00526070(int, int, int, char);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c5530(char*);
void __cdecl fcn_004c4ef0(char*);
int __cdecl fcn_0064d470(char*, char*);
int __cdecl fcn_0065f220(const char*, const char*);

/* ADDRESS: GOLDTL 0x005c30e0 */
void __cdecl fcn_005c30e0(unsigned char* a1)
{
	int v;
	GOLDTL_Msg5c30 msg;
	LC_GEBAEUDE_BAUPLATZ bp;
	char buf[0x200];
	char text[0x400];
	GOLDTL_EntType5c30* rec;
	int kind;
	int m;
	int id;

	rec = &((GOLDTL_EntType5c30*) lpGebaeudePROT)[*(unsigned char*) a1];
	id = *(int*) (a1 + 1);
	if (rec->f247 >= rec->f248) {
		io_FormatTextBuffer(buf, 0x17d7);
		fcn_00526120(buf, 0);
		return;
	}
	kind = gm_GetBuildingTypeCategory(*(unsigned char*) a1);
	if (g_774800 == 0) {
		if (kind == 1 || kind == 4 || kind == 8) {
			if (fcn_00504f30(*(unsigned char*) a1 + 1, g_774970) != 1) {
				io_FormatTextBuffer(buf, 0x17d6);
				fcn_00526120(buf, 0);
				return;
			}
		} else {
			if (fcn_00504f30(*(unsigned char*) a1 + 1, g_774970) != 1) {
				io_FormatTextBuffer(buf, 0x17d9);
				fcn_00526120(buf, 0);
				return;
			}
		}
	}
	lc_GetGebaeudeBauplatz(&bp, a1);
	if (bp.node == 0) {
		fcn_00597ff0(*(unsigned char*) a1 + 1, (char*) &msg);
		if (fcn_0065f220((char*) &msg, bp.name) != 0) {
			io_FormatTextBuffer(buf, 0x17d8, *(unsigned char*) a1 * 14 + 0x49c);
			fcn_00526120(buf, 0);
			return;
		}
	} else {
		fcn_00597ff0(*(unsigned char*) a1 + 1, (char*) &msg);
		if (fcn_0064d470((char*) &msg, bp.node) == 0) {
			io_FormatTextBuffer(buf, 0x17d8, *(unsigned char*) a1 * 14 + 0x49c);
			fcn_00526120(buf, 0);
			return;
		}
	}
	v = (int) (fcn_0050d170(*(unsigned char*) a1 + 1) * g_664e60);
	io_FormatTextBuffer(buf, 0x17d5, v, a1, *(unsigned char*) a1 * 14 + 0x49c);
	switch (kind) {
	default:
		if (fcn_00526120(buf, 0x11) == 0) {
			return;
		}
		if (fcn_00526010(&((GOLDTL_House5c30*) g_7f4ca0)[g_774970], v,
		                 (char) g_773d75) == 0) {
			return;
		}
		m = gm_SearchTable67(id);
		if (a1[0x5b] & 4) {
			return;
		}
		if (m == 0) {
			return;
		}
		memset(&msg, 0, sizeof msg);
		msg.f4 = 0x1e;
		msg.f8 = ((GOLDTL_House5c30*) g_7f4ca0)[g_774970].f4;
		msg.fc = id;
		msg.f36 = 1;
		msg.f28 = g_7f4c00.a;
		msg.f2c = g_7f4c00.b;
		msg.f30 = g_7f4c00.c;
		msg.f34 = g_7f4c00.d;
		msg.f58 = id;
		fcn_004c4eb0(g_67e968);
		fcn_004c5150(-1, ((GOLDTL_House5c30*) g_7f4ca0)[g_774970].f4,
		             (char) g_773d75, v);
		fcn_004c5530((char*) &msg);
		fcn_004c4ef0(g_67e968);
		io_FormatTextBuffer(text, 0x17da, *(unsigned char*) a1 * 14 + 0x49c);
		fcn_00526120(text, 4);
		return;
	case 3:
		m = fcn_00502cd0(*(int*) ((char*) fcn_0050e4a0(1) + 0x5d), 2, 6, 0, 0x115);
		if (fcn_00526120(buf, 0x11) == 0) {
			return;
		}
		break;
	case 5:
		m = fcn_00507a10(a1);
		if (fcn_00526120(buf, 0x11) == 0) {
			return;
		}
		if (m == 0) {
			return;
		}
		break;
	}
	if (fcn_00526070(m, *(int*) (m + 0x14), v, (char) g_773d75) == 0) {
		return;
	}
	memset(&msg, 0, sizeof msg);
	msg.f4 = 0x1e;
	msg.f58 = *(int*) (a1 + 1);
	msg.f34 = g_7f4c00.d;
	msg.f36 = 1;
	msg.fc = *(int*) (a1 + 1);
	msg.f8 = ((GOLDTL_House5c30*) g_7f4ca0)[g_774970].f4;
	msg.f30 = g_7f4c00.c;
	msg.f2c = g_7f4c00.b;
	msg.f28 = g_7f4c00.a;
	fcn_004c4eb0(g_67e968);
	fcn_004c5150(-1, *(int*) (m + 2), (char) g_773d75, v);
	fcn_004c5530((char*) &msg);
	fcn_004c4ef0(g_67e968);
}
