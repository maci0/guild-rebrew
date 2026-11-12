#include "client_dialog_helpers.h"

/* Tooltip text builder for the currently hovered object. Picks the target
 * from the cursor selection, formats a message string from the object's
 * action code and finally dispatches it to the tooltip channel. */

#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_7746b4;
extern int g_7746a4;
extern int g_7746c4;
extern int g_7746c8;
extern short* g_7746cc;
extern int g_7746ac;
extern int g_14ce8cc;
extern int g_67fcb4;
extern char* g_14a5310[];
extern char g_6b5c60[];
extern double g_664e78;
extern double g_662930;

int __cdecl fcn_0042e410(int a);
int __cdecl fcn_005463a0(int n, ...);
int __cdecl fcn_00506380(int a, int b, int c, int d);
int __cdecl fcn_00403300(int a, ...);
int __cdecl fcn_00507c30(int a);
int __cdecl gm_MapEntityStatRange(int a);
int __cdecl gm_SearchTable67(int a);
int __cdecl gm_LookupEntityRecordById(int a);
int __cdecl fcn_00531c40(int a, int b, void* c);
float __cdecl fcn_004fc460(char* p);
float __cdecl fcn_004fbd40(void);

struct Building_531d20 { unsigned char class_id; char pad1[0x24c]; };
/* ADDRESS: GOLDTL 0x00531d20 */
void __cdecl fcn_00531d20(void)
{
	int id;
	int idx;
	float f[10];
	char text[0x200];
	unsigned char* sel;
	struct Building_531d20* kind;
	unsigned char* ent;
	unsigned short* idp;
	char** names;
	int rec;
	int obj;
	int i;
	int n;
	char mode;
	int action;

	if (g_7746b4 == 0) {
		if (g_7746a4 == 0)
			return;
		if (*(int*) (g_7746a4 + 0x220) != 2)
			return;
		if (g_7746ac != 0)
			return;
	}
	if (g_14ce8cc == 0)
		return;
	sel = 0;
	kind = 0;
	i = g_7746c4;
	if (i == 0)
		i = g_7746c8;
	sel = (unsigned char*) i;
	if (sel != 0)
		kind = &((struct Building_531d20*) lpGebaeudePROT)[*sel];
	if (g_7746b4 == 0
	    || (fcn_00506380(g_774970, 0, 0, g_7746b4), g_7746b4 == 0))
		rec = g_7746a4 != 0 ? fcn_00403300(g_7746a4) : 0;
	else
		rec = *(int*) (g_7746b4 + 0x184);
	if (rec != 0 && (*(unsigned char*) (rec + 4) & 1) == 0)
		return;
	if (sel != 0) {
		if (kind->class_id == 0x16) {
			if (*g_7746cc != 0x120) {
				if (kind->class_id != 0x0f)
					return;
			}
		} else {
			if (kind->class_id != 0x0f)
				return;
		}
	}
	fcn_0042e410(4);
	text[0] = g_6b5c60[0];
	for (i = 1; i < 0x200; i++)
		text[i] = 0;
	obj = -1;
	id = -1;
	if (g_7746b4 != 0) {
		mode = 1;
		i = 0;
		if (*(unsigned char*) (g_7746b4 + 0x164) != 0)
			i = gm_MapEntityStatRange(*(unsigned char*) (g_7746b4 + 0x164));
		else if (*(unsigned char*) (g_7746b4 + 0x165) != 0)
			i = fcn_00507c30(*(unsigned char*) (g_7746b4 + 0x165));
		if (i == 0x0b || i == 0x0c) {
			mode = 0;
			idx = (unsigned short) fcn_0042e410(4) + 1;
			if (idx == 3)
				idx = 4;
		} else {
			idx = (unsigned short) fcn_0042e410(4) + 1;
		}
		rec = *(int*) (g_7746b4 + 0x17c);
		if (rec != 0) {
			idx = -1;
			action = *(unsigned char*) (g_7746b4 + 0x180);
			switch (action) {
			case 0x49:
				ent = (unsigned char*) gm_SearchTable67(*(int*) (rec + 0xac));
				if (ent != 0)
					io_FormatTextBuffer((char*) text,
					    0x124a + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *(unsigned short*) (ent + 0x27), ent);
				break;
			case 0x44:
				ent = (unsigned char*) gm_SearchTable67(*(int*) (rec + 0xac));
				if (ent != 0)
					io_FormatTextBuffer((char*) text,
					    0x1259 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *(unsigned short*) (ent + 0x27), ent);
				break;
			case 0x28:
				io_FormatTextBuffer((char*) text,
				    0x124d + (fcn_0042e410(3) & 0xffff));
				break;
			case 0x3c:
				idp = (unsigned short*) gm_LookupEntityRecordById(*(int*) (rec + 0xac));
				if (idp != 0)
					io_FormatTextBuffer((char*) text,
					    0x1253 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *idp);
				break;
			case 0x14:
				if (*(int*) (g_7746b4 + 0x16c) != 0) {
					ent = *(unsigned char**) (g_7746b4 + 0x16c);
					if (((struct Building_531d20*) lpGebaeudePROT)[*ent].class_id == 0x20)
						io_FormatTextBuffer((char*) text,
						    0x1286 + (fcn_0042e410(3) & 0xffff));
					else
						io_FormatTextBuffer((char*) text,
						    0x1256 + (fcn_0042e410(3) & 0xffff));
				}
				break;
			case 0x19:
				ent = (unsigned char*) gm_SearchTable67(*(int*) (rec + 0xac));
				if (ent != 0)
					io_FormatTextBuffer((char*) text,
					    0x125c + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *(unsigned short*) (ent + 0x27), ent);
				break;
			case 0x62:
				io_FormatTextBuffer((char*) text,
				    0x125f + (fcn_0042e410(3) & 0xffff));
				break;
			case 0x18:
				idp = (unsigned short*) gm_LookupEntityRecordById(*(int*) (rec + 0xc4));
				if (idp != 0)
					io_FormatTextBuffer((char*) text,
					    0x1262 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *idp);
				break;
			case 0x40:
				ent = (unsigned char*) gm_SearchTable67(*(int*) (rec + 0xac));
				if (ent != 0 && *(unsigned short*) (ent + 0x27) != 0xffff)
					io_FormatTextBuffer((char*) text,
					    0x1265 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *(unsigned short*) (ent + 0x27), ent);
				break;
			case 0x43:
				io_FormatTextBuffer((char*) text,
				    0x1268 + (fcn_0042e410(3) & 0xffff));
				break;
			case 0x61:
				io_FormatTextBuffer((char*) text,
				    0x126b + (fcn_0042e410(3) & 0xffff));
				break;
			case 0x48:
				io_FormatTextBuffer((char*) text,
				    0x126e + (fcn_0042e410(3) & 0xffff));
				break;
			case 0x64:
				ent = (unsigned char*) gm_SearchTable67(*(int*) (rec + 0xb0));
				if (ent != 0)
					io_FormatTextBuffer((char*) text,
					    0x1271 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *(unsigned short*) (ent + 0x27), ent);
				break;
			case 0x65:
				io_FormatTextBuffer((char*) text,
				    0x1274 + (fcn_0042e410(3) & 0xffff));
				break;
			case 0x1a:
				idp = (unsigned short*) gm_LookupEntityRecordById(*(int*) (rec + 0xb4));
				if (idp != 0)
					io_FormatTextBuffer((char*) text,
					    0x1277 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *idp);
				break;
			case 0x3f:
			case 0x75:
				ent = (unsigned char*) gm_SearchTable67(*(int*) (rec + 0xac));
				if (ent != 0)
					io_FormatTextBuffer((char*) text,
					    0x1250 + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *(unsigned short*) (ent + 0x27), ent);
				break;
			case 0x89:
				idp = (unsigned short*) gm_LookupEntityRecordById(*(int*) (rec + 0xb0));
				if (idp != 0)
					io_FormatTextBuffer((char*) text,
					    0x127a + (fcn_0042e410(3) & 0xffff),
					    (void*) (unsigned) *idp);
				break;
			case 0x8e:
				io_FormatTextBuffer((char*) text,
				    0x127d + (fcn_0042e410(3) & 0xffff));
				break;
			case 0xa1:
				io_FormatTextBuffer((char*) text,
				    0x1280 + (fcn_0042e410(3) & 0xffff));
				break;
			case 0x8c:
				if (*(int*) (g_7746b4 + 0x16c) != 0) {
					ent = *(unsigned char**) (g_7746b4 + 0x16c);
					if (((struct Building_531d20*) lpGebaeudePROT)[*ent].class_id == 0x1d)
						io_FormatTextBuffer((char*) text,
						    0x1283 + (fcn_0042e410(3) & 0xffff));
					else if (((struct Building_531d20*) lpGebaeudePROT)[*ent].class_id == 0x1f)
						io_FormatTextBuffer((char*) text,
						    0x1289 + (fcn_0042e410(3) & 0xffff));
				}
				break;
			default:
				idx = (unsigned short) fcn_0042e410(4) + 1;
				if (mode == 0 && idx == 3)
					idx = 4;
				break;
			}
		}
	} else {
		idx = (unsigned short) fcn_0042e410(4) + 1;
	}
	if (idx >= 0 && idx <= 4) {
		obj = idx * 0xf + 0x11e9;
		id = obj;
	}
	if ((short) fcn_0042e410(2) == 0) {
		if (fcn_005463a0(1, 0, 0x52) != 0)
			idx = 5;
	}
	fcn_004fc460((char*) f);
	switch (idx) {
	case 1:
		obj = (int) (f[1] * g_664e78 * g_662930 + id);
		obj += fcn_0042e410(3) & 0xffff;
		break;
	case 2:
		obj = (int) (fcn_004fbd40() * g_664e78 * g_662930 + id);
		obj += fcn_0042e410(3) & 0xffff;
		break;
	case 3:
		obj = (int) (f[2] * g_664e78 * g_662930 + id);
		obj += fcn_0042e410(3) & 0xffff;
		break;
	case 4:
		obj = (int) (f[0] * g_664e78 * g_662930 + id);
		obj += fcn_0042e410(3) & 0xffff;
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
			obj = ((fcn_0042e410(n - 1) & 0xffff) - 5) + g_67fcb4;
		}
		break;
	}
	if (g_7746b4 != 0) {
		if (obj != -1) {
			fcn_00531c40(*(int*) (g_7746b4 + 0x184), obj, 0);
			return;
		}
		if (text[0] != 0)
			fcn_00531c40(*(int*) (g_7746b4 + 0x184), 0, text);
		return;
	}
	if (g_7746a4 != 0)
		fcn_00531c40(fcn_00403300(g_7746a4), obj, 0);
}
