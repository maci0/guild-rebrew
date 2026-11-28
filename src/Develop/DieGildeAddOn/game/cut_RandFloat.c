extern unsigned int cut_RandomSeed;
extern char str_cut_rndfloat_f[];

int __cdecl fcn_0064d41a(char*, char*, ...);


/* ADDRESS: GOLDTL 0x004e6d20 */
/* ADDRESS: GOLDDE 0x004d3540 */
float __cdecl cut_RandFloat(void)
{
	char buf[0x40];

	cut_RandomSeed = cut_RandomSeed * 0x41c64e6d + 0x3039;
	fcn_0064d41a(buf, str_cut_rndfloat_f, ((unsigned short*) &cut_RandomSeed)[1] % 0x7fffu * (1.0f / 32767.0f));
	return ((unsigned short*) &cut_RandomSeed)[1] % 0x7fffu * (1.0f / 32767.0f);
}
