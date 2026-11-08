#include <string.h>
#pragma intrinsic(memset)

/* Entity action dialog for one entity record. Opens the panel, rebuilds its
 * controls while the record or the hovered slot changes, dispatches the
 * dialog message ids, then runs the close/cleanup sequence.
 * ent is the entity record: kind byte at +0, action id at +1, short at
 * +0x25 and +0x27, flags at +0x5a/+0x5b, side byte at +0x5c, byte at
 * +0x65, int at +0x69. */

typedef struct {
	int len;
	int other;
	int h18;
	int h1c;
	int h20;
	int mode;
	int h28;
	char* rec;
	int h30;
	int h34;
	int h38;
	int h3c;
	int ptr;
	int h44;
	int h48;
	int h4c;
	int hover;
	int h54;
	int h58;
	int h5c;
	int prev;
	int id;
} Vars;

/* Dialog message packet, SIZE 0xf8. */
typedef struct {
	char f0[4];
	char f04;
	char f05[3];
	int f08;
	int f0c;
	char f10[0x18];
	int f28;
	int f2c;
	int f30;
	unsigned short f34;
	char f36;
	char f37[0x21];
	int f58;
	char f5c[0x9c];
} Msg;

extern unsigned char* lpGebaeudePROT;
extern char g_7f4ca0[];
extern unsigned short g_774970;
extern int g_774654;
extern int g_67d370;
extern signed char g_7747b0;
extern unsigned char g_773d75;
extern int g_14ab294;
extern int g_774800;
extern int g_14ce8e0;
extern int g_100f1dc;
extern int g_7725d0;
extern int g_773da8;
extern int g_aed32c;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern float g_662a3c;
extern float g_665c0c;
extern double g_662908;

int __cdecl fcn_0057ec20(int a);
void __cdecl fcn_0057e880(int a, int b, int c, int d);
int __cdecl fcn_00504bd0(int a);
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00471b60(int a);
void __cdecl fcn_00473a90(int a, int b);
int __cdecl fcn_0050cf50(char* ent, int kind);
int __cdecl fcn_00504f30(int a, int b);
int __cdecl fcn_005463a0(int a, int b, int c);
int __cdecl fcn_005462a0(void);
void* __cdecl gm_SearchTable67(int a);
int __cdecl fcn_00508da0(char* ent);
void __cdecl fcn_004727a0(int a, int b);
int __cdecl fcn_00519190(int id, ...);
void __cdecl io_FormatTextBuffer(char* out, int id, ...);
int __cdecl fcn_00526120(char* text, int mode);
int __cdecl fcn_00472250(int dlg, int a, int b);
void __cdecl fcn_00472640(int a, int b);
void __cdecl d2_SetBildArgument(int a, int b);
void __cdecl fcn_00471af0(int a, int b);
void __cdecl fcn_00471e30(int a);
int __cdecl fcn_00471f80(int a);
void __cdecl fcn_004c4510(char* ent, int id);
void __cdecl fcn_004c4700(int a, int b, int c, void* d);
void __cdecl fcn_004c5150(int a, int b, int c, int d);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c53a0(void);
void __cdecl fcn_004c5530(void* msg);
void __cdecl fcn_004c5f60(int a, int b, int c);
void __cdecl fcn_004c6000(int a, int b);
void __cdecl fcn_00505e20(int a, int b, int c, int d, int e);
int __cdecl fcn_0050d2a0(char* a);
void __cdecl fcn_0059aa10(int a, int b);
void __cdecl fcn_005c23b0(int a);
void __cdecl fcn_005c2580(int a);
void __cdecl fcn_005c2910(int a);
void __cdecl fcn_005c2a40(int a);
void __cdecl fcn_005c30e0(int a);
void __cdecl fcn_005c35d0(int a);
void __cdecl fcn_005c3820(int a);
void __cdecl fcn_005c3cc0(int a);
int __cdecl fcn_005373e0(void* fn, int message);

/* ADDRESS: GOLDTL 0x005c3f10 */
void __cdecl fcn_005c3f10(char* ent)
{
	Vars v;
	Msg st;
	char name[0x80];
	char text1[0x200];
	char text2[0x200];
	char text3[0x400];
	char* s;
	char* d;
	char c;
	int changed;
	int dlg;
	int h;
	int n2;

	v.prev = -1;
	v.h34 = -1;
	v.h3c = -1;
	v.h1c = -1;
	v.h30 = -1;
	v.h54 = -1;
	v.h44 = -1;
	v.h20 = -1;
	v.h4c = -1;
	v.h28 = -1;
	v.h18 = -1;
	v.h38 = -1;
	v.h5c = -1;
	v.h48 = -1;
	v.h58 = -1;
	v.rec = (char*) lpGebaeudePROT + (unsigned char) ent[0] * 0x24d;
	v.id = *(int*) (ent + 1);
	changed = 1;
	v.other = 0;
	v.hover = 0;
	if ((*(unsigned char*) (ent + 0x5b) & 4) != 0)
		return;
	if (*(unsigned short*) (ent + 0x25) == g_774970) {
		if (fcn_0057ec20(0x100) == 0)
			return;
		if (*(unsigned short*) (ent + 0x25) == g_774970)
			fcn_0057e880(0x10, (int) ent, 0, 0);
	} else {
		if (fcn_0057ec20(0x4000) == 0)
			return;
	}
	v.mode = fcn_00504bd0((unsigned char) ent[0]);
	dlg = fcn_00470820(0, 0, (char*) 0x6ac690);
	fcn_00471b60(dlg);
	fcn_00473a90(0, 0);
	v.ptr = fcn_0050cf50(ent, ent[0x5c]);
	fcn_00504f30((unsigned char) ent[0], g_774970);
	if ((*(unsigned char*) (ent + 0x5a) & 2) != 0
	    && *(unsigned short*) (ent + 0x25) != g_774970) {
		v.other = fcn_005463a0(1, 0, 0x1b);
		while (v.other != 0
		    && *(int*) (v.other + 0xac) != *(int*) (ent + 1))
			v.other = fcn_005462a0();
	}
	do {
		if ((*(unsigned char*) (ent + 0x5b) & 4) != 0
		    || gm_SearchTable67(v.id) == 0)
			g_774654 = 1;
		if (*(unsigned short*) (ent + 0x5a) != v.prev)
			changed = 1;
		if (*(unsigned short*) (ent + 0x27) == g_774970) {
			h = fcn_005463a0(1, 0, 0x4f);
			while (h != 0
			    && *(int*) (h + 0xac) != *(int*) (ent + 1))
				h = fcn_005462a0();
			if (h != v.hover) {
				changed = 1;
				v.hover = h;
			}
		}
		v.prev = *(unsigned short*) (ent + 0x5a);
		if (changed) {
			v.h34 = -1;
			v.h3c = -1;
			v.h1c = -1;
			v.h30 = -1;
			v.h54 = -1;
			v.h44 = -1;
			v.h20 = -1;
			v.h4c = -1;
			v.h28 = -1;
			v.h18 = -1;
			v.h38 = -1;
			v.h48 = -1;
			v.h58 = -1;
			fcn_004727a0(dlg, 1);
			v.len = fcn_00508da0(ent);
			if (*(unsigned short*) (ent + 0x27) == g_774970) {
				if (*(unsigned short*) (ent + 0x25) == g_774970)
					goto build_other;
				if (*(unsigned short*) (ent + 0x27) != g_774970)
					goto after_build;
			} else if (*(unsigned short*) (ent + 0x25)
			    == g_774970) {
				goto build_other;
			}
			n2 = (int) ((double) v.len * g_662a3c
			    - g_665c0c + g_662908);
			fcn_00519190(
			    (v.rec[0] == 0x21) ? 0x17fb : 0x17a0,
			    (unsigned short) *(unsigned short*) (ent + 0x25),
			    (int) ent, n2 + 0x17b1, n2 + 0x17bb, v.ptr);
			if (v.rec[0] == 1)
				fcn_00519190(0x17a2,
				    (unsigned char) ent[0x65]);
			if (v.mode != 3 && v.mode != 5 && v.rec[0] != 1) {
				if (v.other != 0)
					v.h54 = fcn_00472250(dlg, 1,
					    fcn_00519190(0x17aa));
				else if (v.mode != 2 || v.rec[0] == 0x10)
					v.h20 = fcn_00472250(dlg, 1,
					    fcn_00519190(0x17ad));
				if ((*(unsigned char*) (ent + 0x5b) & 2) != 0)
					fcn_00472640(v.h20, 0);
			}
			goto after_build;
build_other:
			n2 = (int) ((double) v.len * g_662a3c
			    - g_665c0c + g_662908);
			fcn_00519190(
			    (v.rec[0] == 0x21) ? 0x17f9 : 0x179e,
			    (int) ent, n2 + 0x17b1, n2 + 0x17bb, v.ptr);
			if (*(unsigned short*) (ent + 0x25) == g_774970) {
				if (v.rec[0] == 0x21)
					v.h38 = fcn_00472250(dlg, 1,
					    fcn_00519190(0x17fc, ent + 5));
				else
					v.h38 = fcn_00472250(dlg, 1,
					    fcn_00519190(0x17a1, ent + 5));
				d2_SetBildArgument(v.h38, 0x10);
			}
			if (v.rec[0] == 1)
				fcn_00519190(0x17a2,
				    (unsigned char) ent[0x65]);
			if (v.mode != 2) {
				if ((*(unsigned char*) (ent + 0x5a) & 2)
				    != 0)
					v.h44 = fcn_00472250(dlg, 1,
					    fcn_00519190(0x17a7));
				else
					v.h1c = fcn_00472250(dlg, 1,
					    fcn_00519190(0x17a4));
			} else {
				v.h48 = fcn_00472250(dlg, 1,
				    fcn_00519190(0x17af));
			}
			v.h3c = fcn_00472250(dlg, 1,
			    fcn_00519190(0x17a5));
			if ((*(unsigned char*) (ent + 0x5a) & 0x18) == 0
			    && v.mode != 2 && v.rec[0] != 0x10)
				v.h30 = fcn_00472250(dlg, 1,
				    fcn_00519190(0x17a6));
			if (v.rec[0] != 3 && v.rec[0] != 0x21)
				v.h34 = fcn_00472250(dlg, 1,
				    fcn_00519190(0x17ac));
			if ((unsigned char) v.rec[0x21] > 1)
				v.h28 = fcn_00472250(dlg, 1,
				    fcn_00519190(0x17a8));
			else
				v.h28 = -1;
			if (v.mode != 2)
				v.h18 = fcn_00472250(dlg, 1,
				    fcn_00519190(0x17ab));
			if (v.hover != 0)
				v.h58 = fcn_00472250(dlg, 1,
				    fcn_00519190(0x17b0));
			if (*(unsigned short*) (ent + 0x27) == g_774970) {
				fcn_004727a0(dlg, 1);
				if (v.rec[0] == 2
				    && *(int*) ((char*) g_7f4ca0
					+ (unsigned int) g_774970 * 0x21c
					+ 0x170) != (int) ent)
					v.h4c = fcn_00472250(dlg, 1,
					    fcn_00519190(0x17a9));
			}
after_build:
			if (*(int*) 0x774800 != 0)
				v.h5c = fcn_00472250(dlg, 1,
				    fcn_00519190(0x1ba7));
			changed = 0;
		}
		if ((*(unsigned char*) (ent + 0x5a) & 4) != 0) {
			fcn_00472640(v.h34, 0);
			fcn_00472640(v.h3c, 0);
			fcn_00472640(v.h30, 0);
			fcn_00472640(v.h1c, 0);
		}
		if (v.h18 != -1) {
			if ((*(unsigned char*) (ent + 0x5a) & 0x40) != 0)
				fcn_00472640(v.h18, 0);
			else
				fcn_00472640(v.h18, 1);
		}
		if (g_14ce8e0 != 0 && g_7725d0 == 0)
			g_774654 = 1;
		if (*(int*) 0x100f1dc == -1)
			goto loop_test;
		if (g_67d370 == v.h34) {
			fcn_00471af0(dlg, 0);
			fcn_0059aa10((int) ent, 0xfd);
			fcn_00471af0(dlg, 1);
			goto loop_test;
		}
		if (g_67d370 == v.h1c && g_7747b0 >= 0) {
			fcn_00471af0(dlg, 0);
			fcn_005c23b0((int) ent);
			goto tail_on;
		}
		if (g_67d370 == v.h3c && g_7747b0 >= 0) {
			fcn_00471af0(dlg, 0);
			fcn_005c2580((int) ent);
			goto tail_on;
		}
		if (g_67d370 == v.h20 && g_7747b0 >= 0) {
			fcn_00471af0(dlg, 0);
			fcn_005c35d0((int) ent);
			goto tail_on;
		}
		if (g_67d370 == v.h44 && g_7747b0 >= 0) {
			fcn_00471af0(dlg, 0);
			fcn_005c2910((int) ent);
			goto tail_on;
		}
		if (g_67d370 == v.h28 && g_7747b0 >= 0) {
			fcn_00471af0(dlg, 0);
			fcn_005c2a40((int) ent);
			goto tail_on;
		}
		if (g_67d370 == v.h4c) {
			fcn_00471af0(dlg, 0);
			fcn_004c6000(
			    *(int*) ((char*) g_7f4ca0
				+ (unsigned int) g_774970 * 0x21c + 4),
			    *(int*) (ent + 1));
			fcn_00471af0(dlg, 1);
			goto tail_changed;
		}
		if (g_67d370 == v.h18 && g_7747b0 >= 0) {
			fcn_00471af0(dlg, 0);
			fcn_005c30e0((int) ent);
			goto tail_on;
		}
		if (g_67d370 == v.h30 && g_7747b0 >= 0) {
			io_FormatTextBuffer(text1, 0x17c7, (int) ent);
			fcn_00471af0(dlg, 0);
			if (fcn_00526120(text1, 1) != 0) {
				memset(&st, 0, sizeof(st));
				st.f04 = 0x20;
				st.f08 = *(int*) ((char*) g_7f4ca0
					+ (unsigned int) g_774970 * 0x21c + 4);
				st.f0c = *(int*) (ent + 1);
				st.f28 = g_7f4c00;
				st.f2c = g_7f4c04;
				st.f30 = g_7f4c08;
				st.f34 = g_7f4c0c;
				st.f36 = 1;
				st.f58 = *(int*) (ent + 1);
				fcn_004c5530(&st);
				g_774654 = 1;
			}
			fcn_00471af0(dlg, 1);
			goto tail_changed;
		}
		if (g_67d370 == v.h54 && g_7747b0 >= 0) {
			if (fcn_00504f30((unsigned char) ent[0],
				g_774970) != 1) {
				fcn_00526120((char*) g_14ab294, 0);
				goto loop_test;
			}
			fcn_00471af0(dlg, 0);
			if (fcn_0050d2a0((char*) g_7f4ca0
				+ (unsigned int) g_774970 * 0x21c)
			    > *(int*) (v.other + 0xb0)) {
				io_FormatTextBuffer(text2, 0x17db,
				    (unsigned short) *(unsigned short*)
					(ent + 0x25), (int) ent,
				    *(int*) (v.other + 0xb0));
				if (fcn_00526120(text2, 1) != 0) {
					fcn_00505e20(*(int*) (ent + 1),
					    *(int*) ((char*) g_7f4ca0
						+ (unsigned int) g_774970
						* 0x21c + 4),
					    *(int*) (v.other + 0xb0),
					    v.other, 0);
				}
			}
			fcn_00471af0(dlg, 1);
			goto tail_changed;
		}
		if (g_67d370 == -1) {
			fcn_00471af0(dlg, 0);
			fcn_005c3820((int) ent);
			goto tail_on;
		}
		if (g_67d370 == v.h5c) {
			fcn_004c5f60(*(int*) (ent + 1),
			    *(int*) ((char*) g_7f4ca0
				+ (unsigned int) g_774970 * 0x21c + 4),
			    *(int*) ((char*) g_7f4ca0
				+ (unsigned int) g_774970 * 0x21c + 4));
			goto tail_changed;
		}
		if (g_67d370 == v.h48) {
			v.len = *(int*) (ent + 0x69)
			    + *(int*) (ent + 0x65);
			fcn_00471af0(dlg, 0);
			v.len = (int) ((double) v.len * g_662908);
			io_FormatTextBuffer(text3, 0x17e3, (int) ent,
			    (int) ent, v.len);
			if (fcn_00526120(text3, 1) != 0) {
				fcn_004c5150(*(int*) ((char*) g_7f4ca0
					+ (unsigned int) g_774970 * 0x21c
					+ 4), -1, g_773d75, v.len);
				fcn_004c5f60(*(int*) (ent + 1),
				    *(int*) (g_773da8 + 4),
				    *(int*) (g_773da8 + 4));
				fcn_004c4510(ent, *(int*) (ent + 1));
				fcn_004c4700(4, 1,
				    (int) ent - g_aed32c + 0x65, &v.len);
				fcn_004c5360();
				g_774654 = 1;
			}
			fcn_00471af0(dlg, 1);
			goto tail_changed;
		}
		if (g_67d370 == v.h58) {
			fcn_00471af0(dlg, 0);
			fcn_005c3cc0((int) ent);
			goto tail_on;
		}
		goto loop_test;
tail_on:
		fcn_00471af0(dlg, 1);
tail_changed:
		changed = 1;
loop_test:
		;
	} while (fcn_005373e0((void*) 0x5c3f10, 0x657c7) != 0);

	if (v.h38 != -1) {
		s = (char*) fcn_00471f80(v.h38);
		d = name;
		do {
			c = *s++;
			*d++ = c;
		} while (c != 0);
		fcn_004c4510(ent, *(int*) (ent + 1));
		fcn_004c4700(1, 0x20, 5, name);
		fcn_004c53a0();
	}
	fcn_00471e30(dlg);
	if (*(unsigned short*) (ent + 0x25) == g_774970)
		fcn_0057e880(0x10, (int) ent, 1, 0);
}
