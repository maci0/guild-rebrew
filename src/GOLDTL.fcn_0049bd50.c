int __cdecl fcn_004f4830(int idx, void* dst);
int __cdecl fcn_004a4680(void* o0, void* o1, int idx, char* s, void* p4);
int __cdecl fcn_004a4410(void* o0, void* o1, int idx, char* s, int a4, int a5, void* a6);

/* ADDRESS: GOLDTL 0x0049bd50 */
int __cdecl fcn_0049bd50(void* o0, void* o1, int idx, char* s, int a4, int a5, void* a6)
{
	char buf[0x24];

	*(int*) o0 = 0;
	*(int*) o1 = 0;
	if (*(int*) ((char*) a6 + 0x10) < 0x1c || *(int*) ((char*) a6 + 0x10) > 0x22)
		return 0;
	fcn_004f4830(0x12, buf);
	if (*(int*) (buf + 0x18) != 0)
		return fcn_004a4680(o0, o1, idx, s, buf);
	return fcn_004a4410(o0, o1, idx, s, a4, a5, a6);
}
