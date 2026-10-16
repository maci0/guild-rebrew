#pragma pack(push, 1)
struct blk14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack(pop)

extern struct blk14 g_current_year;

/* ADDRESS: GOLD 0x0054c710 */
void __cdecl fcn_0054c710(char *p)
{
	int z;

	*(struct blk14 *)(p + 0x52) = g_current_year;
	z = 0;
	*(short *)(p + 0x56) = 10;
	*(int *)(p + 0x58) = z;
	*(int *)(p + 0x5c) = z;
	*(int *)(p + 0xac) = z;
	*(int *)(p + 0xb0) = z;
	*(int *)(p + 0xb4) = z;
}
