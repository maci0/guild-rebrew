#include "client_dialog_helpers.h"

/* Tooltip text builder for the currently hovered object. Picks the target
 * from the cursor selection, formats a message string from the object's
 * action code and finally dispatches it to the tooltip channel. */

extern short g_774970;
extern int g_7746b4;
extern int g_7746a4;
extern int g_7746c4;
extern int g_7746c8;
extern short g_7746cc;
extern int g_67fcb4;
extern char** g_14a5310;
extern int g_6b5c60;

int __cdecl fcn_0042e410(int a);
int __cdecl fcn_005463a0(int a);
int __cdecl fcn_00506380(int a, int b, int c, int d);
int __cdecl fcn_00403300(int a, ...);
int __cdecl fcn_00507c30(int a);
int __cdecl gm_MapEntityStatRange(int a);
int __cdecl gm_SearchTable67(int a);
int __cdecl fcn_00531c40(int a, int b, void* c);
void __cdecl fcn_004fc460(void* a);
void __cdecl fcn_004fbd40(void);

/* ADDRESS: GOLDTL 0x00531d20 */
void __cdecl fcn_00531d20(void)
{
	unsigned char text[0x200];
	unsigned char* ent;
	unsigned char* sel;
	char* kind;
	int target;
	int action;
	int obj;
	int sel2;
	int idx;
	int pick;
	int i;
	int n;
	char** names;
	short* idp;

	sel = 0;
	obj = 0;
	if (g_7746c4 != 0 || g_7746c8 != 0) {
		sel = (unsigned char*) g_7746c4;
		if (sel == 0)
			sel = (unsigned char*) g_7746c8;
		if (sel != 0)
			kind = (char*) (lpGebaeudePROT + (unsigned) *sel * 0x24d);
	}
	target = 0;
	if (g_7746b4 == 0
	    || (fcn_00506380(g_774970, 0, 0, g_7746b4), g_7746b4 == 0)) {
		if (g_7746a4 != 0) {
			obj = fcn_00403300(g_7746a4, 0, 0);
		} else {
			return;
		}
	} else {
		obj = *(int*) (g_7746b4 + 0x184);
		if (obj != 0 && (*(unsigned char*) (obj + 4) & 1) == 0)
			return;
	}
	if (sel != 0 && ((*kind != 0x16 || g_7746cc != 0x120)
	    && *kind != 0x0f))
		return;
	fcn_0042e410(4);
	for (i = 0; i < 0x200; i++)
		text[i] = 0;
	text[0] = (unsigned char) g_6b5c60;
	idx = -1;
	action = 0;
	if (g_7746b4 != 0) {
		int mode = 1;
		if (*(unsigned char*) (g_7746b4 + 0x164) == 0) {
			if (*(char*) (g_7746b4 + 0x165) != 0) {
				i = fcn_00507c30(*(char*) (g_7746b4 + 0x165));
			} else {
				i = 0;
			}
		} else {
			i = gm_MapEntityStatRange(*(unsigned char*) (g_7746b4 + 0x164));
			if (i == 0x0b || i == 0x0c) {
				mode = 0;
				pick = fcn_0042e410(4) + 1;
				if (pick == 3)
					pick = 4;
				idx = pick;
			}
		}
		obj = *(int*) (g_7746b4 + 0x17c);
		if (obj != 0) {
			action = *(unsigned char*) (g_7746b4 + 0x180);
			switch (action) {
			case 0x14:
				if (*(int*) (g_7746b4 + 0x16c) != 0) {
					ent = *(unsigned char**) (g_7746b4 + 0x16c);
					n = (lpGebaeudePROT[(unsigned) *ent * 0x24d] == 0x20)
					    ? 0x1286 : 0x1256;
					io_FormatTextBuffer((char*) text, n,
					    (void*) 3);
				}
				break;
			case 0x18:
				idp = (short*) gm_LookupEntityRecordById(*(int*) (obj + 0xc4));
				if (idp != 0)
					io_FormatTextBuffer((char*) text,
					    0x1262 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *idp);
				break;
			case 0x19:
				ent = (unsigned char*) gm_SearchTable67(
				    *(int*) (obj + 0xac));
				if (ent != 0)
					io_FormatTextBuffer((char*) text,
					    0x125c + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned)
					    *(unsigned short*) (ent + 0x27));
				break;
			case 0x1a:
				idp = (short*) gm_LookupEntityRecordById(*(int*) (obj + 0xb4));
				if (idp != 0)
					io_FormatTextBuffer((char*) text,
					    0x1277 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *idp);
				break;
			case 0x28:
				io_FormatTextBuffer((char*) text,
				    0x124d + (fcn_0042e410(3) & 0xffff),
				    (void*) 3);
				break;
			case 0x3c:
				idp = (short*) gm_LookupEntityRecordById(*(int*) (obj + 0xac));
				if (idp != 0)
					io_FormatTextBuffer((char*) text,
					    0x1253 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *idp);
				break;
			case 0x3f:
			case 0x75:
				ent = (unsigned char*) gm_SearchTable67(
				    *(int*) (obj + 0xac));
				if (ent != 0)
					io_FormatTextBuffer((char*) text,
					    0x1250 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned)
					    *(unsigned short*) (ent + 0x27));
				break;
			case 0x40:
				ent = (unsigned char*) gm_SearchTable67(
				    *(int*) (obj + 0xac));
				if (ent != 0 && *(unsigned short*) (ent + 0x27)
				    != 0xffff)
					io_FormatTextBuffer((char*) text,
					    0x1265 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned)
					    *(unsigned short*) (ent + 0x27));
				break;
			case 0x43:
				io_FormatTextBuffer((char*) text,
				    0x1268 + (fcn_0042e410(3) & 0xffff),
				    (void*) 3);
				break;
			case 0x44:
				ent = (unsigned char*) gm_SearchTable67(
				    *(int*) (obj + 0xac));
				if (ent != 0)
					io_FormatTextBuffer((char*) text,
					    0x1259 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned)
					    *(unsigned short*) (ent + 0x27));
				break;
			case 0x48:
				io_FormatTextBuffer((char*) text,
				    0x126e + (fcn_0042e410(3) & 0xffff),
				    (void*) 3);
				break;
			case 0x49:
				ent = (unsigned char*) gm_SearchTable67(
				    *(int*) (obj + 0xac));
				if (ent != 0)
					io_FormatTextBuffer((char*) text,
					    0x124a + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned)
					    *(unsigned short*) (ent + 0x27));
				break;
			case 0x61:
				io_FormatTextBuffer((char*) text,
				    0x126b + (fcn_0042e410(3) & 0xffff),
				    (void*) 3);
				break;
			case 0x62:
				io_FormatTextBuffer((char*) text,
				    0x125f + (fcn_0042e410(3) & 0xffff),
				    (void*) 3);
				break;
			case 100:
				ent = (unsigned char*) gm_SearchTable67(
				    *(int*) (obj + 0xb0));
				if (ent != 0)
					io_FormatTextBuffer((char*) text,
					    0x1271 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned)
					    *(unsigned short*) (ent + 0x27));
				break;
			case 0x65:
				io_FormatTextBuffer((char*) text,
				    0x1274 + (fcn_0042e410(3) & 0xffff),
				    (void*) 3);
				break;
			case 0x89:
				idp = (short*) gm_LookupEntityRecordById(*(int*) (obj + 0xb0));
				if (idp != 0)
					io_FormatTextBuffer((char*) text,
					    0x127a + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *idp);
				break;
			case 0x8c:
				if (*(int*) (g_7746b4 + 0x16c) != 0) {
					ent = *(unsigned char**) (g_7746b4
					    + 0x16c);
					i = lpGebaeudePROT[(unsigned) *ent * 0x24d];
					if (i == 0x1d)
						io_FormatTextBuffer((char*) text,
						    0x1283
						    + (fcn_0042e410(3)
						    & 0xffff), (void*) 3);
					else if (i == 0x1f)
						io_FormatTextBuffer((char*) text,
						    0x1289
						    + (fcn_0042e410(3)
						    & 0xffff), (void*) 3);
				}
				break;
			case 0x8e:
				io_FormatTextBuffer((char*) text,
				    0x127d + (fcn_0042e410(3) & 0xffff),
				    (void*) 3);
				break;
			case 0xa1:
				io_FormatTextBuffer((char*) text,
				    0x1280 + (fcn_0042e410(3) & 0xffff),
				    (void*) 3);
				break;
			default:
				break;
			}
		}
	}
	fcn_0042e410(2);
	if (idx == -1 && fcn_005463a0(1) != 0)
		idx = 5;
	fcn_004fc460(text);
	switch (idx) {
	case 2:
		fcn_004fbd40();
		break;
	case 5:
		if (g_67fcb4 != -1) {
			n = 1;
			names = (char**) (g_67fcb4 * 4 + (int) g_14a5310);
			do {
				if (**names == 0)
					break;
				n++;
				names++;
			} while (n < 5);
			pick = fcn_0042e410(n - 1);
			obj += ((pick & 0xffff) - 5) + g_67fcb4;
		}
		break;
	}
	if (g_7746b4 == 0) {
		if (g_7746a4 != 0) {
			target = fcn_00403300(g_7746a4, obj, 0);
			fcn_00531c40(target, 0, 0);
		}
		return;
	}
	if (obj != -1) {
		fcn_00531c40(*(int*) (g_7746b4 + 0x184), obj, 0);
		return;
	}
	if ((char) text[0] != 0)
		fcn_00531c40(*(int*) (g_7746b4 + 0x184), 0, text);
}
