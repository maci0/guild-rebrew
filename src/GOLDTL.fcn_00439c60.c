/* ADDRESS: GOLDTL 0x006b8014 */
extern char* g_6b8014;
/* ADDRESS: GOLD 0x00fc2dec */
extern char* g_6b8014;



void __cdecl fcn_00438af0(int);

void __cdecl fcn_00439c60(int a1)
{
	if (a1 == *(int*) ((char*)&g_6b8014)) {
		return;
	}
	if (*(int*) (a1 + 0x218) != 3) {
		return;
	}
	*(int*) ((char*)&g_6b8014) = a1;
	fcn_00438af0(0);
}
