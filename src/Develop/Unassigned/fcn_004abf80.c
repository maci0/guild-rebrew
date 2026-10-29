extern int __cdecl fcn_00508e40(int id);
extern void __cdecl fcn_004c5420(int, int, int, int, int);
extern void __cdecl fcn_005100f0(int, int);
extern void __cdecl fcn_004c54c0(int, int, int, int);

/* ADDRESS: GOLDTL 0x004abf80 */
int __cdecl fcn_004abf80(char* a1, char* a2)
{
	unsigned short* p;

	p = (unsigned short*) fcn_00508e40(*(int*) (a2 + 4));
	if (p == 0)
		return 0;
	fcn_004c5420(*(int*) (a1 + 4), 0x1cc, 4, 0x20, 0);
	fcn_005100f0(*(int*) (a1 + 4), -*(int*) (a2 + 0x10));
	fcn_004c54c0(*(unsigned short*) a1, *p, *(int*) (a2 + 0x10) * 5, 1);
	return 0x47;
}
