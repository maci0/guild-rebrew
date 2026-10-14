/* ADDRESS: GOLDTL 0x006a9b9c */
extern int g_6a9b9c;
/* ADDRESS: GOLD 0x0062aa88 */
extern int g_6a9b9c;
/* ADDRESS: GOLD 0x006ed938 */
extern int g_772514;



void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);

void __cdecl fcn_005931a0(void)
{
	int a;
	int b;
	int c;
	int s;

	if (g_6a9b9c != -1) {
		fcn_004727a0(g_6a9b9c, 5);
		s = g_772514;
		fcn_004727a0(g_6a9b9c, 6);
		fcn_00533f40(0, 0, g_772514, s, 0x35, &c, &b, &a);
	}
}
