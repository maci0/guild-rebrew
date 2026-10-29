#pragma pack(2)
typedef struct {
	int a;
	int b;
	int c;
	short d;
} pos14;
#pragma pack()

extern pos14 g_7f4c00;
void __cdecl fcn_00500bb0(char*, int, int, int);

/* ADDRESS: GOLDTL 0x005530d0 */
void __cdecl fcn_005530d0(char* a0)
{
	pos14* p;

	p = (pos14*) (a0 + 0x52);
	*p = g_7f4c00;
	fcn_00500bb0((char*) p, 0, 2, 0);
}
