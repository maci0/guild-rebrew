#pragma pack(push, 1)
typedef struct {
	int a;
	int b;
	int c;
	unsigned short d;
} HE_TIMESTAMP_14;
#pragma pack(pop)

/* ADDRESS: GOLDTL 0x00550770 */
void __cdecl he_StartMeisterpruefungPrompt(char* object)
{
	*(HE_TIMESTAMP_14*) (object + 0x52) = *(HE_TIMESTAMP_14*) (object + 0x44);
}
