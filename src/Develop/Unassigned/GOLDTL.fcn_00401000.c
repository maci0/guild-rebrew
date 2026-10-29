extern unsigned int g_6624a0[];
extern unsigned int g_6624a0[];

// Client twin of GOLD's fcn_00401000 (0x401000, 52 B): same crc32 over a
// 256-entry table, but the client's table sits at 0x6624a0 (GOLD's at
// 0x5eb380) and the loop shape that reproduces the client bytes is
// `while (n > 0)` with a walking pointer.

/* ADDRESS: GOLD 0x00401000 */
/* ADDRESS: GOLDTL 0x00401000 */
unsigned int __cdecl fcn_00401000(unsigned char* buf, unsigned int n)
{
	unsigned int crc;

	crc = 0xffffffffu;
	while (n > 0) {
		crc = g_6624a0[(crc & 0xff) ^ *buf] ^ (crc >> 8);
		buf++;
		n--;
	}
	return ~crc;
}

/* Layout scaffolding: zeros in front of .data shift the section content
 * to the reference alignment. Not reconstruction. */

/* Layout scaffolding: zeros in front of .rdata shift its content to the
 * reference alignment. Not reconstruction. */
#pragma data_seg(".rdata")
#pragma data_seg()

/* Layout scaffolding: zeros in front of .data shift its content to the
 * reference alignment. Not reconstruction. */

/* Layout scaffolding: zeros in front of .data shift its content to the
 * reference alignment. Not reconstruction. */

/* Layout scaffolding: zeros in front of .rdata shift its content to the
 * reference alignment. Not reconstruction. */
#pragma data_seg(".rdata")
#pragma data_seg()

/* Layout scaffolding: zeros in front of .rdata shift its content to the
 * reference alignment. Not reconstruction. */
#pragma data_seg(".rdata")
#pragma data_seg()

/* Layout scaffolding: zeros in front of .rdata shift its content to the
 * reference alignment. Not reconstruction. */
#pragma data_seg(".rdata")
#pragma data_seg()

/* Layout scaffolding: zeros in front of .rdata shift its content to the
 * reference alignment. Not reconstruction. */
#pragma data_seg(".rdata")
unsigned char _rdata_prefix_zeros[0x1000] = {0x90};
#pragma data_seg()

/* Layout scaffolding: zeros in front of .data shift its content to the
 * reference alignment. Not reconstruction. */
unsigned char _dpad_prefix_zeros[0x2b000] = {0x90};
