#pragma pack(push, 1)
typedef struct {
	int a;
	int b;
	int c;
	unsigned short d;
} F00550770;
#pragma pack(pop)

/* ADDRESS: GOLDTL 0x00550770 */
void __cdecl fcn_00550770(char* object)
{
	*(F00550770*) (object + 0x52) = *(F00550770*) (object + 0x44);
}
