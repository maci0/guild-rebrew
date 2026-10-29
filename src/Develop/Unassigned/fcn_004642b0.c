/* zlib 1.1.3 trees.c set_data_type(): classifies the current block as
 * binary or ASCII from the literal-tree frequency sums and stores the
 * result (Z_BINARY 0 / Z_ASCII 1) into deflate_state.data_type. */

/* ADDRESS: GOLDTL 0x004642b0 */
void __cdecl fcn_004642b0(char* s)
{
	int n;
	unsigned ascii_freq;
	unsigned bin_freq;

	n = 0;
	ascii_freq = 0;
	bin_freq = 0;
	while (n < 7) {
		bin_freq += *(unsigned short*) (s + 0x8c + n * 4);
		n++;
	}
	while (n < 0x80) {
		ascii_freq += *(unsigned short*) (s + 0x8c + n * 4);
		n++;
	}
	while (n < 0x100) {
		bin_freq += *(unsigned short*) (s + 0x8c + n * 4);
		n++;
	}
	*(unsigned char*) (s + 0x1c) =
	    (unsigned char) (bin_freq > (ascii_freq >> 2) ? 0 : 1);
}
