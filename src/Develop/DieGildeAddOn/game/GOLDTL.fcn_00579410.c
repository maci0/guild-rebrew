


void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

void __cdecl fcn_00579410(void* recipient, void* entity)
{
	char buf[0x400];

	io_FormatTextBuffer(buf, 0x40ff, *(unsigned short*) entity);
	fcn_00545d40(*(int*) recipient, -1, buf, 1, 0x5f4, 0);
}
