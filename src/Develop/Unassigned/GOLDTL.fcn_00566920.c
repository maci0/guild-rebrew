

#pragma pack(push, 1)
typedef struct {
	int f0;
	int f4;
	int f8;
	unsigned short fc;
} HE_ACTION_TIMESTAMP;
#pragma pack(pop)
// SIZE 0xe

void __cdecl he_StartWorkerStealAction(char* obj)
{
	*(HE_ACTION_TIMESTAMP*) (obj + 0x52) = *(HE_ACTION_TIMESTAMP*) (obj + 0x44);
}
