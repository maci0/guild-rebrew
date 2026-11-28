#include "Develop/DieGildeAddOn/command/client_packet_builder.h"

void __cdecl gm_UpdateEntityAgingAndTraining(int);

// SIZE 0x21c
struct s_7f4ca0 {
	unsigned short id;
	char kind;
	char pad;
	int f4;
	char pad2[0x14];
	float f1c;
	char pad3[0x144];
	char b164;
	char b165;
	char pad4[0x4b];
	unsigned char b1b1;
	char pad5[0x6a];
};

extern char gm_EntitySlotTable[];




int __cdecl gm_CheckAndCollectEntityDebt(struct s_7f4ca0*, int);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short, int);

void __cdecl cm_AppendPacketFieldValue(int, int, int, char*);
void __cdecl cm_RequestChangeAttribute(void);

void __cdecl gm_ApplyHourlyEntityUpdates(void)
{
	int i;
	char* cursor;
	struct s_7f4ca0* rec;
	char flag_val;

	i = 0;
	for (cursor = &((struct s_7f4ca0*)gm_EntitySlotTable)[0].kind; (int) cursor < (int) &((struct s_7f4ca0*)gm_EntitySlotTable)[768].kind; cursor += sizeof(struct s_7f4ca0)) {
		rec = (struct s_7f4ca0*) (cursor - 2);
		if (rec->id != 0xffff) {
			if (rec->b164 != 0 || rec->b165 != 0) {
				gm_UpdateEntityAgingAndTraining(i);
			}
			if ((rec->kind == 2 || rec->kind == 5 || rec->kind == 4) && gm_CheckAndCollectEntityDebt(rec, 0) != 0) {
				gm_ApplyEntityHealthDelta(rec->id, (int) -(rec->f1c + 5.0f));
			}
			if (rec->b1b1 > 0) {
				flag_val = -1;
				cm_BeginPacketFieldDelta((char*) rec, rec->f4);
				cm_AppendPacketFieldValue(1, 1, cursor - cm_PacketDeltaBase + 0x1af, &flag_val);
				cm_RequestChangeAttribute();
			}
		}
		i++;
	}
}
