extern unsigned int cut_RandomSeed;
extern char g_68d6dc[];

int __cdecl fcn_0064d41a(char*, char*, ...);


/* ADDRESS: GOLDTL 0x004e6d20 */
float __cdecl fcn_004e6d20(void)
{
	char buf[0x40];

	cut_RandomSeed = cut_RandomSeed * 0x41c64e6d + 0x3039;
	fcn_0064d41a(buf, g_68d6dc, ((unsigned short*) &cut_RandomSeed)[1] % 0x7fffu * (1.0f / 32767.0f));
	return ((unsigned short*) &cut_RandomSeed)[1] % 0x7fffu * (1.0f / 32767.0f);
}
