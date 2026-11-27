


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
} GV_OFFICE_POOL_MSG;

#pragma pack(pop)
// SIZE 0x20

int __cdecl gv_EnqueueSlotCommand(void*);

int __cdecl gv_RequestAddCandidateToOfficePool(int candidate, int building, int slot_type, int slot_index)
{
	GV_OFFICE_POOL_MSG msg;

	if (candidate == 0 || building == 0 || slot_index == -1) {
		return -1;
	}
	msg.f0 = 0;
	msg.f4 = *(int*) ((char*) candidate + 4);
	msg.f8 = *(int*) ((char*) building + 1);
	msg.fc = slot_type;
	msg.f10 = (char) slot_index;
	msg.f11 = 0;
	msg.f13 = 0;
	return gv_EnqueueSlotCommand(&msg);
}
