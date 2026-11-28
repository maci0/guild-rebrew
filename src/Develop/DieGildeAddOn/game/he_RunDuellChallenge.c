#include "Develop/client_types.h"
#pragma pack(push, 2)
// SIZE 0xe






#pragma pack(pop)

// SIZE 0x8
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3;
	int id;
} Entity_54f0c0;

// SIZE 0xb8
typedef struct {
	char pad0[0x52];
	pos14_7f4c00 stamp;
	char pad60[0x10];
	int state;
	char pad74[4];
	unsigned char flags;
	char pad79[0xb];
	int event;
	char pad88[0x24];
	int actor;
	int target;
	int mode;
} Order_54f0c0;


extern pos14_7f4c00 gm_GameTime;

Entity_54f0c0* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl cm_SendSetHE(int, Order_54f0c0*);
void __cdecl he_FreeAction(Order_54f0c0*);


/* ADDRESS: GOLDTL 0x0054f0c0 */
void __cdecl he_RunDuellChallenge(Order_54f0c0* o)
{
	char buf[0x100];
	Entity_54f0c0* a;
	Entity_54f0c0* b;

	switch (o->state) {
	case -2:
	case -1:
		if (o->flags & 2) {
			a = gm_LookupEntityRecordById(o->actor);
			if (a != 0) {
				cm_RequestChangeBits(a->id, 0x1c8, 4, 0, 0x100);
			}
			b = gm_LookupEntityRecordById(o->target);
			if (b != 0) {
				cm_RequestChangeBits(b->id, 0x1c8, 4, 0, 0x200);
			}
		}
		he_FreeAction(o);
		break;
	case 2:
		if (o->flags & 2) {
			a = gm_LookupEntityRecordById(o->actor);
			if (a != 0) {
				cm_RequestChangeBits(a->id, 0x1c8, 4, 0, 0x100);
			}
			b = gm_LookupEntityRecordById(o->target);
			if (b != 0) {
				cm_RequestChangeBits(b->id, 0x1c8, 4, 0, 0x200);
			}
			if (a != 0 && b != 0) {
				if (o->mode == 1) {
					if (b->type == 6 || b->type == 7) {
						io_FormatTextBuffer(buf, 0x1e19, a->slot);
						he_PostEntityMessage(b->id, -1, buf, 0, 0x5fb, 0);
					}
				} else if (o->mode == 2) {
					if (b->type == 6 || b->type == 7) {
						io_FormatTextBuffer(buf, 0x1e20, a->slot);
						he_PostEntityMessage(b->id, -1, buf, 0, 0x5fb, 0);
					}
				} else {
					cm_RequestCopyEntityData(a->id, b->id, -0x68, 1);
					if (b->type == 6 || b->type == 7) {
						io_FormatTextBuffer(buf, 0x1d5d, a->slot);
						he_PostEntityMessage(b->id, b->id, buf, 0, 0x5fb, 0);
					}
					if (a->type == 6 || a->type == 7) {
						io_FormatTextBuffer(buf, 0x1d5c, b->slot);
						he_PostEntityMessage(b->id, b->id, buf, 0, 0x5fb, 0);
					}
				}
			}
			o->stamp = (*(pos14_7f4c00*)&gm_GameTime);
			gm_AddTime(&o->stamp, 0, 2, 0);
			o->event = cm_SendSetHE(-1, o);
		}
		break;
	}
}
