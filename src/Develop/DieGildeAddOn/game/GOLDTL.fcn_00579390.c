


extern unsigned char g_773d75;

void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

void __cdecl fcn_00579390(void* a1, void* a2)
{
	char buf[0x400];

	fcn_004c51a0(*(int*) a1, *(int*) ((char*) a2 + 4),
	    g_773d75, *(int*) ((char*) a1 + 0xc));
	fcn_004c5420(*(int*) ((char*) a2 + 4), 0x1cc, 4, 1, 0);
	io_FormatTextBuffer(buf, 0x40fe, *(unsigned short*) a2, *(int*) ((char*) a1 + 0xc));
	fcn_00545d40(*(int*) a1, -1, buf, 1, 0x5f4, 0);
}
