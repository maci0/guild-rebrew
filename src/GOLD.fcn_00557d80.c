#pragma pack(push, 1)
struct blk14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack(pop)

void __cdecl fcn_004fe140(int, int, int, int);

/* ADDRESS: GOLD 0x00557d80 */
void __cdecl fcn_00557d80(char* e)
{
	*(struct blk14*) (e + 0x52) = *(struct blk14*) (e + 0x44);
	fcn_004fe140(e + 0x52, 2, 0, 0);
}
