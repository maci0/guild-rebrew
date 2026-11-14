/* ADDRESS: GOLD 0x004ff8c0 */
int __cdecl fcn_004ff8c0(int a, int b)
{
	unsigned short w;
	char* o;

	w = *(unsigned short*) ((char*) 0x7d6a70 + a * 0x2a90 + b * 0x80);
	o = *(char**) 0x91aaf0 + w * 0x40 + w;
	if (*o == 0x17 || *o == 0x25) {
		return 0;
	}
	if (a == 0) {
		return (int) (*(float*) 0x6f1b9c * *(float*) ((char*) 0x7d6a78 + b * 0x80) * 0.0025 + 0.5);
	}
	return (int) (*(int*) ((char*) 0x7d6a60 + a * 0x2a90) * *(float*) ((char*) 0x7d6a78 + a * 0x2a90 + b * 0x80) * 0.0005);
}
