


#pragma pack(push, 1)

typedef struct
{
	int f0;
	int f4;
	int f8;
	int fc;
	char f10;
	short f11;
	int f13;
	char pad[9];
} GV_EXTEND_SLOT_MSG;

#pragma pack(pop)
// SIZE 0x20

int __cdecl gv_EnqueueSlotCommand(void*);

int __cdecl gv_SendExtendProductionTime(int slot, int building, int worktype, int slotIndex, short duration, int cost)
{
	GV_EXTEND_SLOT_MSG msg;

	if (slot == 0 || building == 0 || slotIndex == -1) {
		return -1;
	}
	msg.f0 = 2;
	msg.f4 = *(int*) ((char*) slot + 4);
	msg.f8 = *(int*) ((char*) building + 1);
	msg.fc = worktype;
	msg.f10 = (char) slotIndex;
	msg.f11 = duration;
	msg.f13 = cost;
	return gv_EnqueueSlotCommand(&msg);
}
