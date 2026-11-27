


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
} GV_SPAWN_ENTITIES_MSG;

#pragma pack(pop)
// SIZE 0x20

int __cdecl fcn_004c6c30(void*);

int __cdecl gv_SendSpawnEntities(int building, int count)
{
	GV_SPAWN_ENTITIES_MSG msg;

	if (building == 0) {
		return -1;
	}
	msg.f0 = 6;
	msg.f4 = -1;
	msg.f8 = *(int*) ((char*) building + 1);
	msg.fc = 0;
	msg.f10 = 0;
	msg.f11 = 0;
	msg.f13 = count;
	return fcn_004c6c30(&msg);
}
