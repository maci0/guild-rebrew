int __cdecl fcn_00508e40(int id);
int __cdecl fcn_005462a0(void);
int __cdecl fcn_005463a0(int a, ...);
void __cdecl fcn_005ca560(int *out);
int __cdecl fcn_005cf720(int a, int b, int c, int d);

/* ADDRESS: GOLDTL 0x005cbe00 */
int __cdecl fcn_005cbe00(int *src, unsigned limit, int *out, int arg3)
{
	int *rec;
	int found;
	int count;

	if (limit == 0) {
		count = 0;
		if (src[0x72] & 0x400) {
			rec = (int *) fcn_005463a0(1, 0, 0x47);
			while (rec) {
				if (rec[0x2b] == src[1]) {
					found = fcn_00508e40(rec[0x2c]);
				} else if (rec[0x2c] == src[1]) {
					found = fcn_00508e40(rec[0x2b]);
				} else {
					rec = (int *) fcn_005462a0();
					continue;
				}
				if (found)
					count = 1;
				break;
			}
		}
		rec = (int *) fcn_005463a0(2, 2, *(unsigned short *) src, 0,
		                           0x18);
		while (rec) {
			if (fcn_00508e40(rec[0x31]))
				count++;
			rec = (int *) fcn_005462a0();
		}
		return count;
	}
	{
		int *dst;
		int n;

		count = 0;
		if (src[0x72] & 0x400) {
			rec = (int *) fcn_005463a0(1, 0, 0x47);
			while (rec) {
				if (rec[0x2b] == src[1]) {
					found = fcn_00508e40(rec[0x2c]);
				} else if (rec[0x2c] == src[1]) {
					found = fcn_00508e40(rec[0x2b]);
				} else {
					rec = (int *) fcn_005462a0();
					continue;
				}
				if (found) {
					out[0] = found;
					out[0xb] = 0;
					count = 1;
				}
				break;
			}
		}
		rec = (int *) fcn_005463a0(2, 2, *(unsigned short *) src, 0,
		                           0x18);
		if (rec) {
			dst = (int *) ((char *) out + count * 0x38);
			for (;;) {
				if (count >= limit)
					break;
				found = fcn_00508e40(rec[0x31]);
				if (found) {
					dst[0] = found;
					dst[0xb] = 1;
					count++;
					dst = (int *) ((char *) dst + 0x38);
				}
				rec = (int *) fcn_005462a0();
				if (!rec)
					break;
			}
		}
		if (count > 0) {
			n = count;
			do {
				fcn_005ca560(out);
				out[0xc] = fcn_005cf720(
				    *(unsigned short *) out[0],
				    *(unsigned short *) src, arg3, 0);
				out = (int *) ((char *) out + 0x38);
				n--;
			} while (n);
		}
		return count;
	}
}
