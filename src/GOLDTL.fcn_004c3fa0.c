char* __cdecl fcn_004c49a0(int, int);
void __cdecl fcn_004ce100(int, int);
void __cdecl fcn_004c4aa0(char*);

/* ADDRESS: GOLD 0x004c3630 */
/* ADDRESS: GOLDTL 0x004c3fa0 */

int __cdecl fcn_004c3fa0(void)
{
	char* p;

	p = fcn_004c49a0(3, 0x165);
	if (p == 0)
		return 1;
	if (*(unsigned int*) (p + 0x10) != 0xa03ef57c)
		return 1;
	fcn_004ce100(*(int*) (p + 0x14), *(int*) (p + 0x18));
	fcn_004c4aa0(p);
	return 0;
}
