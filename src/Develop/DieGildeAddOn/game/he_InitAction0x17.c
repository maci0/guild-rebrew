


#pragma pack(push, 1)
typedef struct {
	int f0;
	int f4;
	int f8;
	unsigned short fc;
} ACTION_TIME_REC;
#pragma pack(pop)
// SIZE 0xe

/* ADDRESS: GOLDDE 0x00547420 */
void __cdecl he_InitAction0x17(char* object)
{
	*(ACTION_TIME_REC*) (object + 0x52) = *(ACTION_TIME_REC*) (object + 0xb4);
}
