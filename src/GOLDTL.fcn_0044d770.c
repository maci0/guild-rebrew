int __cdecl vfs_ReadData(void*, int, int, void*);

// FUNCTION: GOLD 0x44ee70
// FUNCTION: GOLDTL 0x44d770
int __cdecl fcn_0044d770(void* h)
{
	int c;

	if (vfs_ReadData(&h, 1, 1, h) == 0) {
		return 0x2b;
	}
	c = *(signed char*) &h;
	if (c < 0 || c >= 0x3b) {
		c = 0x27;
	}
	return c;
}
