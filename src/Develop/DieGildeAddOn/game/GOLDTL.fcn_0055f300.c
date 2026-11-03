#include "client_types.h"

int __cdecl gm_ResolveEntityById();
int __cdecl fcn_00500d20(void*, void*);
void __cdecl gm_ChangeObjektZustand(int, int);
void __cdecl fcn_00500bb0(void*, int, int, int);
void* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_SearchTable67(int);
int __cdecl fcn_005049a0(unsigned char*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(unsigned char, unsigned char, unsigned short, char*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00546190(char*);
extern pos14_7f4c00 g_7f4c00;

/* One stage of the message-box tick; state lives at +0x70 of the caller's record. */
/* ADDRESS: GOLDTL 0x0055f300 */
void __cdecl fcn_0055f300(char* e)
{
	void* item;
	char ch;
	char buf[128];
	int* msg;
	int* p;
	int i;

	item = 0;
	switch (*(int*) (e + 0x70)) {
	case 0:
		msg = (int*) (e + 0x60);
		i = fcn_00500d20(msg, (void*) 0x7f4c00);
		item = fcn_00502cd0(0, 2, 7, 1, *(int*) (e + 0xac));
		if (item == 0) {
			item = fcn_00502cd0(0, 2, 7, 1, *(int*) (e + 0xac));
			fcn_00546190(e);
			return;
		}
		if ((int) *((unsigned char*) item + 0x12) < *(int*) (e + 0xb4)) {
			gm_ChangeObjektZustand(*(int*) (e + 0xac), i / *(int*) (e + 0xb8));
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((void*) (e + 0x52), 0, *(int*) (e + 0xb8) * 2, 0);
		} else {
			*(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
		}
		msg[0] = *(int*) 0x7f4c00;
		msg[1] = *(int*) 0x7f4c04;
		msg[2] = *(int*) 0x7f4c08;
		*(unsigned short*) (msg + 3) = *(unsigned short*) 0x7f4c0c;
		return;
	case 1:
		gm_ResolveEntityById(0, &item, 0, *(int*) (e + 0xac));
		if (*(int*) (e + 0xd8) != 0) {
			io_FormatTextBuffer(buf, 0x1c49, (*(unsigned short*) item) * 2 + 0x9a8);
			p = (int*) fcn_005049a0((unsigned char*) gm_SearchTable67(*(int*) (e + 0x10)));
			if (p != 0) {
				he_MessageBoxQuickjump(*(int*) ((*(unsigned short*) (e + 8)) * 0x21c + 0x7f4ca4), -1, buf, 0, 0x5ec, *(int*) (e + 0x10), *(int*) ((char*) p + 2), 0, "_NACHRICHTEN_HS_55");
			} else {
				he_MessageBoxQuickjump(*(int*) ((*(unsigned short*) (e + 8)) * 0x21c + 0x7f4ca4), -1, buf, 0, 0x5ec, *(int*) (e + 0x10), -1, 0, "_NACHRICHTEN_HS_55");
			}
		}
		fcn_004c5420(*(int*) ((char*) item + 2), 0x13, 1, 0, 0x20);
		ch = *(char*) (e + 0xb4);
		fcn_004c4510((char*) item, *(int*) ((char*) item + 2));
		fcn_004c4570(1, 1, 0x12, &ch);
		fcn_004c5360();
		fcn_00546190(e);
		return;
	case -2:
	case -1:
		gm_ResolveEntityById(0, &item, 0, *(int*) (e + 0xac));
		if (item != 0) {
			fcn_004c5420(*(int*) ((char*) item + 2), 0x13, 1, 0, 0x20);
		}
		fcn_00546190(e);
		return;
	default:
		return;
	}
}
