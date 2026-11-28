


extern char str_fmt_s[];

int __cdecl d2_ShowPrivilegMessage(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

/* ADDRESS: GOLDDE 0x004e59a0 */
int __cdecl gm_CheckPriv46Rank7(unsigned char* obj, int* request)
{
	char buf[0x100];

	if (*request != 3 && *request != 1) {
		return 1;
	}
	if (obj[0xd] > 7) {
		return 4;
	}
	if (obj[0xd] < 7) {
		return 1;
	}
	if (*request == 3 && obj[2] == 6) {
		io_FormatTextBuffer(buf, 0x1e02, (obj[9] != 0 ? 0x11e : 0x114) + obj[0xd]);
		d2_ShowPrivilegMessage(buf, 0, 0x657c7);
		return 2;
	}
	if (*request == 1 && obj[2] == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1e01);
	}
	return 2;
}
