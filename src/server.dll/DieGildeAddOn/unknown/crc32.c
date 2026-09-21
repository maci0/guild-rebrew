/* crc32 - proper C (zlib-style, 8-byte unrolled) */

// FUNCTION: SERVER 0x100011f0
// SIZE: 309

/* CRC table at 0x100241a0 (256 entries, zlib 1.1.3 polynomial). */
extern unsigned int g_crc_table_241a0[256];

/* Computes the CRC-32 of buf[0..len) seeded with crc.
 * Returns 0 when buf is NULL (zlib init convention). */

unsigned int __cdecl crc32(unsigned int crc, unsigned char* buf, unsigned int len)
{
	unsigned int c;

	if (buf == 0)
		return 0;
	c = crc ^ 0xffffffff;
	while (len >= 8) {
		c = g_crc_table_241a0[(c ^ *buf++) & 0xff] ^ (c >> 8);
		c = g_crc_table_241a0[(c ^ *buf++) & 0xff] ^ (c >> 8);
		c = g_crc_table_241a0[(c ^ *buf++) & 0xff] ^ (c >> 8);
		c = g_crc_table_241a0[(c ^ *buf++) & 0xff] ^ (c >> 8);
		c = g_crc_table_241a0[(c ^ *buf++) & 0xff] ^ (c >> 8);
		c = g_crc_table_241a0[(c ^ *buf++) & 0xff] ^ (c >> 8);
		c = g_crc_table_241a0[(c ^ *buf++) & 0xff] ^ (c >> 8);
		c = g_crc_table_241a0[(c ^ *buf++) & 0xff] ^ (c >> 8);
		len -= 8;
	}
	if (len != 0) {
		do {
			c = g_crc_table_241a0[(c ^ *buf++) & 0xff] ^ (c >> 8);
		} while (--len != 0);
	}
	return c ^ 0xffffffff;
}

// GLOBAL: SERVER 0x100241a0
extern unsigned int g_crc_table_241a0[256];
