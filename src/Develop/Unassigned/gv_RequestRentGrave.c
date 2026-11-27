


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
} GV_RENT_GRAVE_MSG;

#pragma pack(pop)
// SIZE 0x20

int __cdecl gv_EnqueueSlotCommand(void*);

int __cdecl gv_RequestRentGrave(int entity, void* graveyard, int slotType, short duration, int price)
{
	GV_RENT_GRAVE_MSG msg;

	if (entity == 0 || graveyard == 0) {
		return -1;
	}
	msg.f0 = 1;
	msg.f4 = *(int*) ((char*) entity + 4);
	msg.f8 = *(int*) ((char*) graveyard + 1);
	msg.fc = slotType;
	msg.f10 = (char) 0xff;
	msg.f11 = duration;
	msg.f13 = price;
	return gv_EnqueueSlotCommand(&msg);
}
