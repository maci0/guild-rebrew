int __cdecl amt_ExecGebaeudeBauen(char*, char*, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c6470(int, int);
void __cdecl fcn_005100f0(int, int);


/* ADDRESS: GOLDTL 0x0049f230 */
int __cdecl fcn_0049f230(char* a, char* b, int c)
{
	if (amt_ExecGebaeudeBauen(a, b, c) != 0) {
		fcn_004c5420(*(int*) (a + 4), 0x1c8, 4, 0x1000000, 0);
		fcn_004c6470(*(int*) (a + 4), *(int*) (b + 0x10));
		fcn_005100f0(*(int*) (a + 4), 8);
		return 0x34;
	}
	return 0;
}
