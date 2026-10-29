typedef struct { char pad[0x24]; int field24; } F00473610;

/* ADDRESS: GOLDTL 0x00473610 */
short __cdecl fcn_00473610(void)
{
    int _dummy_48;
    register int _dummy_reg_69 = 0;
    register int _dummy_reg_25 = 0;
    register char _pad_10[16];
    char _pad_73[8];
    register int _mk_26 = 0x14ce728;
    register short _dummy_reg_5 = 0;
    short _dummy_reg_3 = 16;
	int obj;
	volatile int* gp;
	int r;
    _dummy_reg_5 &= 0;

	{
        int _reg_18;
        obj = *(volatile int*) (*(volatile int*) 0x77250c + 0x24);
        r = ((int (__stdcall *)(int)) *(int*) (*(int*) obj + 8))((unsigned int)obj);
    }
	gp = (int*) *(int*) 0x77250c;
	{
        register int _reg_95;
        {
        int _reg_77;
        9[gp] = 0;
        *(int*) _mk_26 = (unsigned int)r;
    }
    }
	return (unsigned int)r;
}
