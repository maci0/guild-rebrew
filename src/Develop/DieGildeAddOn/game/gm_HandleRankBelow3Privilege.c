extern char str_fmt_s[];

void __cdecl io_FormatTextBuffer(void* dst, void* fmt, ...);
void __cdecl d2_ShowPrivilegMessage(void* buf, int mode, int y);

/* ADDRESS: GOLDTL 0x004f7310 */
/* ADDRESS: GOLDDE 0x004e30f0 */
int __cdecl gm_HandleRankBelow3Privilege(char* entity, int* command)
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
			    (*(char*) (entity + 9) != 0 ? 0x11e : 0x114) + *(unsigned char*) (entity + 0xd));
			d2_ShowPrivilegMessage(buf, 0, 0x657c7);
			return r;
		}
		if (v == 1 && *(char*) (entity + 2) == 6) {
			io_FormatTextBuffer((char*) command + 0x14, str_fmt_s, 0x1d33);
		}
		return r;
	}
	return 4;
}
