int __cdecl aip_ExecAnschwaerzen(char*, int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);


/* ADDRESS: GOLDTL 0x0049ce90 */
/* ADDRESS: GOLDDE 0x0048b8d0 */
int __cdecl ai_RunAnschwaerzen(char* a, int b, int c)
{
	if (aip_ExecAnschwaerzen(a, b, c) != 0) {
		cm_RequestChangeBits(*(int*) (a + 4), 0x1e8, 4, 0x200, 0);
		return 0x2a;
	}
	return 0;
}
