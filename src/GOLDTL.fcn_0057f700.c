// FUNCTION: GOLDTL 0x0057f700
// SIZE: 99

extern char* g_868050;
extern short g_774970;

int __cdecl fcn_0057ed10(int* m);

int __cdecl fcn_0057f700(int* m)
{
	if (m[0] == 0x2b && m[1] != 0 && g_868050[*(unsigned char*) m[1] * 589] == 0x12 &&
	    *(short*) (m[1] + 0x27) == g_774970 && (m[3] == 0x79 || m[3] == 0x7a || m[3] == 0x78)) {
		return 1;
	}
	return fcn_0057ed10(m);
}
