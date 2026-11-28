


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
} GV_PROGRESS_MSG;

#pragma pack(pop)
// SIZE 0x20

int __cdecl gv_EnqueueSlotCommand(void*);

/* ADDRESS: GOLDDE 0x004dedf0 */
int __cdecl gv_RequestUpdateProductionProgress(int building, int slot_type, int slot_index, int delta)
{
	GV_PROGRESS_MSG msg;

	if (building == 0 || slot_index == -1) {
		return -1;
	}
	msg.f0 = 5;
	msg.f4 = -1;
	msg.f8 = *(int*) ((char*) building + 1);
	msg.fc = slot_type;
	msg.f10 = (char) slot_index;
	msg.f11 = 0;
	msg.f13 = delta;
	return gv_EnqueueSlotCommand(&msg);
}
