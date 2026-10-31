


void* __cdecl fcn_0050dc90(void*);
void  __cdecl io_FormatTextBuffer(void*, int, ...);
int   __cdecl fcn_00526120(void*, int);

int __cdecl fcn_00525fb0(void* a1)
{
	char buf[0x100];
	void* p;

	p = fcn_0050dc90(a1);
	if (p != 0 && (*(unsigned char*) ((char*) p + 0x1b4) & 1)) {
		io_FormatTextBuffer(buf, 0x78, *(unsigned short*) p);
		fcn_00526120(buf, 0x100);
		return 1;
	}
	return 0;
}
