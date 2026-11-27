int __cdecl aip_ExecPamphlet(char*, int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);


/* ADDRESS: GOLDTL 0x0049ccb0 */
int __cdecl ai_RunPamphlete(char* a, int b, int c)
{
	if (aip_ExecPamphlet(a, b, c) != 0) {
		cm_RequestChangeBits(*(int*) (a + 4), 0x1e8, 4, 0x100, 0);
		return 0x29;
	}
	return 0;
}
