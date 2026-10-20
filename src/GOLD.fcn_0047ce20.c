
#pragma pack(push, 1)
typedef struct {
	int f0;
	int f4;
	int f8;
	int fc;
	char f10;
} rec17;
#pragma pack(pop)
/* SIZE 0x11 */

/* ADDRESS: GOLD 0x0047ce20 */
void __cdecl fcn_0047ce20(int a)
{
	rec17* p;

	p = &((rec17*)0xf8a520)[a];
	p->f0 = 0;
	p->f4 = 0;
	p->f8 = 0;
	p->fc = 0;
	p->f10 = 0;
}
