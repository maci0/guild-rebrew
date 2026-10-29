extern unsigned char g_6a375c;
extern int g_14cbca0;
extern unsigned int g_14cbcb4;


/* ADDRESS: GOLDTL 0x0047dca0 */
int __cdecl fcn_0047dca0(char* e)
{
	if ((g_14cbca0 == -1 || e[2] == 6 || *(unsigned int*) (e + 4) % g_6a375c == g_14cbcb4) &&
	    (*(int*) (e + 0x1cc) & 0x3000) == 0)
		return 1;
	return 0;
}
