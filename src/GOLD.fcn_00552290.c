#pragma pack(push, 1)
struct blk14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack(pop)

extern struct blk14 g_current_year;

void __cdecl fcn_004fe140(int, int, int, int);

/* ADDRESS: GOLD 0x00552290 */
void __cdecl fcn_00552290(char* e)
{
	*(struct blk14*) (e + 0x52) = g_current_year;
	fcn_004fe140(e + 0x52, 2, 0, 0);
	*(int*) (e + 0x70) = 0;
}
