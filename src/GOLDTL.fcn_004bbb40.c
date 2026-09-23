// FUNCTION: GOLDTL 0x4bbb40
// SIZE: 131

void* __cdecl fcn_00508e40(int);
void __cdecl fcn_0051af00(void*, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

int __cdecl fcn_004bbb40(void* a1)
{
	char buf[0x200];
	void* p;
	unsigned len;

	p = fcn_00508e40(*(int*) a1);
	if (p == 0) {
		return 1;
	}
	fcn_0051af00(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7);
	len = (unsigned) strlen(buf);
	fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    len > 0x100, 0x603, 0);
	return 0;
}
