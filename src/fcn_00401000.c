// FUNCTION: GOLD 0x00401000
// SIZE: 52
// fcn_00401000 — crc32(a, n).

unsigned int __cdecl fcn_00401000(char* a, unsigned int n)
{
	unsigned int crc;
	unsigned int i;
	crc = 0xffffffff;
	for (i = 0; i < n; i++) {
		crc = ((unsigned int*) 0x5eb380)[(crc ^ (unsigned char) a[i]) & 0xff] ^ (crc >> 8);
	}
	return ~crc;
}
