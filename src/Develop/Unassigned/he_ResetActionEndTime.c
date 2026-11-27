

#pragma pack(push, 1)
typedef struct {
	int f0;
	int f4;
	int f8;
	unsigned short fc;
} HE_END_TIME_REC;
#pragma pack(pop)
// SIZE 0xe

void __cdecl he_ResetActionEndTime(char* a1)
{
	*(HE_END_TIME_REC*) (a1 + 0x52) = *(HE_END_TIME_REC*) (a1 + 0x44);
}
