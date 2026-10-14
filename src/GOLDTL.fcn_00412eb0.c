/* ADDRESS: GOLD 0x006310ec */
extern int g_6b5cc4;
extern int g_67a370;



void __cdecl fcn_004379a0(int, int, int, void*, int);
void __cdecl fcn_00412e80(void);

int __cdecl fcn_00412eb0(int a1, int a2)
{
	g_6b5cc4 = 0;
	if (a2 & 2) {
		fcn_004379a0(g_67a370, 0, 0x1e0, fcn_00412e80, a1);
		return g_6b5cc4;
	}
	fcn_004379a0(g_67a370, 0, 0x60, fcn_00412e80, a1);
	return g_6b5cc4;
}
