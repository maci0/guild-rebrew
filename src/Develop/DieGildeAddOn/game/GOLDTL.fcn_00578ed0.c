extern char* __cdecl gm_LookupEntityRecordById(int);
extern void __cdecl fcn_00529160(int, int, int, int);
extern char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
extern int __cdecl fcn_004a57a0(char*, int, int, char*, int, int, unsigned int*);
extern int __cdecl fcn_004f45b0(char*);
extern int __cdecl gm_WalkEntityChain(int);
extern int __cdecl fcn_0050b710(int, unsigned char);
extern int __cdecl gm_RandomMod(int);
extern void __cdecl fcn_00579390(char*, char*);
extern void __cdecl fcn_00579410(char*, char*);
extern void __cdecl fcn_004c5530(char*);
extern void __cdecl he_FreeAction(char*);
extern void __cdecl fcn_00500bb0(char*, int, int, int);

typedef struct Req578 {
	int a;
	int b;
	int c;
	int d;
} Req578;
#include "client_data.h"
typedef struct Msg578 {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int f08;
	int f0c;
	int f10;
	int f14;
	char pad18[0x10];
	int f28;
	int f2c;
	int f30;
	unsigned short f34;
	unsigned char f36;
	char pad37[0x21];
	int f58;
	int f5c;
	int f60;
	int f64;
	char pad68[0xf8 - 0x68];
} Msg578;
/* SIZE 0xf8 */
#include "Develop/DieGildeAddOn/game/game_data.h"
/* Death-pact action state machine; resolves the target entity and reports the
 * chosen announcement to the message queue. */
/* ADDRESS: GOLDTL 0x00578ed0 */
void __cdecl fcn_00578ed0(char* event)
{
	Msg578 msg;
	Req578 req;
	char* ent;
	char* e;
	unsigned int found;
	int state;
	int k;
	int ref;
	int idx;

	ent = gm_LookupEntityRecordById(*(int*) (event + 0xac));
	state = *(int*) (event + 0x70);
	if (state != -1 && state != -2) {
		if (ent == 0) {
			he_FreeAction(event);
			return;
		}
		if (*(unsigned char*) (ent + 8) != 0) {
			switch (state) {
			case 0:
				fcn_00529160(0, 0, *(unsigned short*) ent, (int) event);
				*(int*) (event + 0x84) = -1;
				*(int*) (event + 0x70) += 1;
				return;
			case 1:
				e = gm_StartFilteredEntitySearch(1, 1, *(int*) (event + 0xb4 + *(int*) (event + 0xb0) * 4));
				if (e == 0) {
					*(int*) (event + 0x70) = -1;
					return;
				}
				fcn_004c5da0(*(int*) (event + 0xac), *(int*) (e + 1), -1, 0, 1, (char*) 0x6a7f08);
				*(int*) (event + 0x70) += 1;
				return;
			case 2:
				e = gm_LookupEntityRecordById(*(int*) (event + 0xac));
				if (e == 0) {
					*(int*) (event + 0x70) = -1;
					return;
				}
				if (*(int*) (*(int*) (e + 0x184) + 0x128) != 0) {
					*(pos14_7f4c00*) (event + 0x52) = gm_GameTime;



					fcn_00500bb0(event + 0x52, 0, 10, 0);
					return;
				}
				if (fcn_004a57a0((char*) ((*(unsigned short*) (event + 8)) * 0x21c + (unsigned long)&g_7f4ca0),
						0x700408, 4, event + 0xc8, 0, 0x42c80000, &found) != 0) {
					goto found_one;
				}
				*(int*) (event + 0x70) = -1;
				return;
found_one:
				ref = fcn_004f45b0((char*) ((found & 0xffff) * 0x21c + (unsigned long)&g_7f4ca0));
				k = fcn_0050b710(gm_WalkEntityChain(found), g_773d75);
				*(unsigned short*) (event + 0xc8 + *(int*) (event + 0xb0) * 2) = (unsigned short) found;
				if (k > ref &&
				    (*(unsigned char*) ((found & 0xffff) * 0x21c + 0x7f4e6c) & 1) == 0) {
					if (*(unsigned char*) ((found & 0xffff) * 0x21c + (unsigned long)&g_7f4ca2) == 6 ||
					    *(unsigned char*) ((found & 0xffff) * 0x21c + (unsigned long)&g_7f4ca2) == 7) {
						msg.f08 = *(int*) ((found & 0xffff) * 0x21c + (unsigned long)&g_7f4ca4);
						msg.f0c = msg.f08;
						msg.f60 = msg.f08;
						msg.kind = 0x8b;
						*(pos14_7f4c00*) &msg.f28 = gm_GameTime;



						msg.f36 = 9;
						msg.f10 = 0;
						msg.f14 = 0;
						msg.f58 = *(int*) (event + 0xc);
						msg.f5c = *(int*) (event + 0xac);
						msg.f64 = ref;
						fcn_004c5530((char*) &msg);
					} else {
						req.a = *(int*) (event + 0xc);
						req.b = *(int*) (event + 0xac);
						req.c = *(int*) ((found & 0xffff) * 0x21c + (unsigned long)&g_7f4ca4);
						req.d = ref;
						if ((unsigned short) gm_RandomMod(2) != 0)
							fcn_00579390((char*) &req, (char*) ((found & 0xffff) * 0x21c + (unsigned long)&g_7f4ca0));
						else
							fcn_00579410((char*) &req, (char*) ((found & 0xffff) * 0x21c + (unsigned long)&g_7f4ca0));
					}
				}
				idx = ++*(int*) (event + 0xb0);
				if (idx < 5 && *(int*) (event + 0xb4 + idx * 4) != 0) {
					*(int*) (event + 0x70) -= 1;
					return;
				}
				*(int*) (event + 0x70) += 1;
				return;
			case 3:
				e = gm_LookupEntityRecordById(*(int*) (event + 0xac));
				if (e == 0 || *(int*) (e + 0x16c) == 0) {
					*(int*) (event + 0x70) = -1;
					return;
				}
				fcn_004c5da0(*(int*) (event + 0xac), *(int*) (*(int*) (e + 0x16c) + 1), -1, 0, 0,
					(char*) 0x6a7f08);
				*(int*) (event + 0x70) += 1;
				return;
			case 4:
				e = gm_LookupEntityRecordById(*(int*) (event + 0xac));
				if (e == 0 || *(int*) (e + 0x16c) == 0 ||
				    *(int*) (*(int*) (e + 0x184) + 0x128) == 0) {
					*(int*) (event + 0x70) = -1;
					return;
				}
				*(pos14_7f4c00*) (event + 0x52) = gm_GameTime;



				fcn_00500bb0(event + 0x52, 0, 4, 0);
				return;
			default:
				return;
			}
		}
	}
	if (ent != 0)
		fcn_00529160(0, 0, *(unsigned short*) ent, 0);
	he_FreeAction(event);
}
