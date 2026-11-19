extern char s_679060[];

void __cdecl io_FormatTextBuffer(void* dst, void* fmt, ...);
void __cdecl fcn_004fa5f0(void* buf, int mode, int y);

/* ADDRESS: GOLDTL 0x004f7310 */
int __cdecl fcn_004f7310(char* entity, int* command)
{
	char buf[0x100];
	int v;
	int r;

	v = *command;
	if (v != 3 && v != 1) {
		return 1;
	}
	if (*(unsigned char*) (entity + 0xd) < 3) {
		r = 2;
		if (v == 3 && *(char*) (entity + 2) == 6) {
			io_FormatTextBuffer(buf, (void*) 0x1d34,
			    (*(char*) (entity + 9) ? 10 : 0) + 0x114 + *(unsigned char*) (entity + 0xd));
			fcn_004fa5f0(buf, 0, 0x657c7);
			return r;
		}
		if (v == 1 && *(char*) (entity + 2) == 6) {
			io_FormatTextBuffer((char*) command + 0x14, s_679060, 0x1d33);
		}
		return r;
	}
	return 4;
}
