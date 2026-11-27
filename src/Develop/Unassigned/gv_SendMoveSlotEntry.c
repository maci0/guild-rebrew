


#pragma pack(push, 1)

typedef struct
{
	int f0;
	int f4;
	int f8;
	char fc;
	int fd;
	int f11;
	char pad[7];
} GV_MOVE_SLOT_MSG;
// SIZE 0x1c

#pragma pack(pop)

void __cdecl cm_RequestMoveSlot(void*);

void __cdecl gv_SendMoveSlotEntry(int payer, int dstWorktype, int building, int srcWorktype, char srcSlotIndex, int cost)
{
	GV_MOVE_SLOT_MSG message;

	message.f0 = *(int*) ((char*) payer + 4);
	message.f4 = *(int*) ((char*) building + 1);
	message.f8 = srcWorktype;
	message.fc = srcSlotIndex;
	message.fd = dstWorktype;
	message.f11 = cost;
	cm_RequestMoveSlot(&message);
}
