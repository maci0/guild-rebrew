int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

/* ADDRESS: GOLD 0x0044ee70 */
/* ADDRESS: GOLDTL 0x0044d770 */
int __cdecl fcn_0044d770(void* h)
{
	int c;

	if (vfs_ReadData((char*) &h, 1, 1, h) == 0) {
		return 0x2b;
	}
	c = *(signed char*) &h;
	if (c < 0 || c >= 0x3b) {
		c = 0x27;
	}
	return c;
}
