#include <string.h>

extern float g_6628a0;

int __cdecl fcn_0045a2e0(char* text, int c, int r);
int __cdecl _ftol(void);

/* ADDRESS: GOLDTL 0x0045a3a0 */
int __cdecl fcn_0045a3a0(char* text, char* fmt)
{
	int width;
	int count;
	float ratio;
	int lines;
	int q;
	int div;
	int r;
	int c;
	int cstart;
	int limit;
	int pos;
	int rem;
	int sum;
	int code;
	int cellofs;
	int cells;
	int stride;
	int xpos;
	int x0;
	int rows;
	int widths[15];
	char linebuf[0x3c];
	float chw;
	int best;
	int besti;
	int i;

	width = *(int*) text;
	count = *(int*) (fmt + 0x20);
	ratio = g_6628a0 / *(float*) (fmt + 0x14);
	lines = count / width;
	if (lines != 0) {
		goto tail_block;
	}
	q = width / count;
	if (count <= 0) {
		goto done;
	}
	div = q * q;
	cells = 0x3c;
	xpos = 0;
	x0 = 0;
	cellofs = 0;
	stride = (count * 8 - count) * 4;
	rows = count;

outer:
	r = 0;
	cstart = 0;
	limit = x0 + q;
	goto cond1;

reload:
	r = 0;
	cstart = 0;
	goto cond1;

cond1:
	if ((unsigned) x0 >= (unsigned) limit) {
		goto after1;
	}
	sum = 0;
	pos = 0;
	rem = limit - x0;
	code = 0;
cond2:
	if ((unsigned) cstart >= (unsigned) (q + cstart)) {
		goto after2;
	}
	code = *(unsigned char*) (*(int*) (text + 0x10) + pos + cstart);
	chw = ((float) code * *(float*) (text + 0x84)
		+ *(float*) (text + 0x54) - *(float*) (fmt + 4)) * ratio;
	sum += (int) chw;
	cstart++;
	if ((unsigned) cstart < (unsigned) (q + cstart - 1)) {
		goto cond2;
	}
after2:
	if (--rem != 0) {
		pos += width;
		goto cond2;
	}
after1:
	if (div != 0) {
		*(char*) (*(int*) (fmt + 0x28) + xpos + r) = (char) (sum / div);
	}
	memset(linebuf, 0, cells);
	c = cstart;
	if ((unsigned) x0 >= (unsigned) limit) {
		goto after3;
	}
loop3:
	if ((unsigned) c >= (unsigned) (q + c)) {
		goto next3;
	}
loop4:
	besti = fcn_0045a2e0(text, c, x0);
	widths[besti]++;
	c++;
	if ((unsigned) c < (unsigned) (q + c)) {
		goto loop4;
	}
next3:
	x0++;
	if ((unsigned) x0 < (unsigned) limit) {
		goto loop3;
	}
after3:
	best = 0;
	besti = -1;
	for (i = 0; i < 15; i++) {
		if ((unsigned) widths[i] > (unsigned) best) {
			best = widths[i];
			besti = i;
		}
	}
	*(int*) (*(int*) (fmt + 0x24) + cellofs) = besti < 0 ? 0 : besti;
	r++;
	cellofs += 0x1c;
	x0++;
	if (r < count) {
		goto reload;
	}
	x0 = limit;
	xpos += count;
	cellofs += stride;
	rows--;
	if (rows != 0) {
		goto outer;
	}
	goto done;

tail_block:
	/* Multi-line arm 0x45a5d9-0x45a90b. First fills the character plane
	 * row by row for `lines` text lines, then halves the grid repeatedly
	 * and averages 2x2 blocks with the weighted /5 rule while copying the
	 * verdict entries down the mip chain. */
	{
		unsigned char* bytes;
		unsigned char* plane;
		int* verdict;
		float f84;
		float f54;
		float f4;
		int step;
		int bo;
		int vo;
		int pos;
		int level;
		int w;
		int y;
		int x;
		int cell;
		int sum4;
		int avg;
		int t1;
		int t2;
		int src;
		int dst;

		bytes = *(unsigned char**) (text + 0x10);
		plane = *(unsigned char**) (fmt + 0x28);
		verdict = *(int**) (fmt + 0x24);
		f84 = *(float*) (text + 0x84);
		f54 = *(float*) (text + 0x54);
		f4 = *(float*) (fmt + 4);
		step = lines * 0x1c;
		pos = 0;
		vo = 0;
		for (y = 0; y < lines; y++) {
			bo = y * width;
			for (x = 0; x < count; x++) {
				code = *(unsigned char*) (bytes + bo + x);
				chw = ((float) code * f84 + f54 - f4)
				    * ratio;
				plane[pos + x * lines] = (char) (int) chw;
				verdict[vo] = fcn_0045a2e0(text, x, y);
				vo += step;
			}
			pos += lines;
		}
		if (lines <= 1)
			goto done;
		level = lines;
		y = 0;
		while (level > 1) {
			w = count / level;
			cell = level >> 1;
			if (w != 0) {
				for (y = 0; y < w; y++) {
					for (x = 0; x < w; x++) {
						src = (y & (count - 1))
						    * step + (x & (count - 1))
						    * 0x1c;
						sum4 = (unsigned char) plane
						    [(y & (count - 1)) * lines
						    + (x & (count - 1))]
						    + (unsigned char) plane
						    [((y + 1) & (count - 1))
						    * lines + (x & (count - 1))]
						    + (unsigned char) plane
						    [(y & (count - 1)) * lines
						    + ((x + 1) & (count - 1))]
						    + (unsigned char) plane
						    [((y + 1) & (count - 1))
						    * lines
						    + ((x + 1) & (count - 1))];
						avg = sum4 >> 2;
						t1 = (avg + 2 * ((unsigned char)
						    plane[(y & (count - 1))
						    * lines + (x & (count - 1))]
						    + (unsigned char) plane
						    [((y + 1) & (count - 1))
						    * lines
						    + (x & (count - 1))]))
						    / 5;
						t2 = (avg + 2 * ((unsigned char)
						    plane[(y & (count - 1))
						    * lines
						    + ((x + 1) & (count - 1))]
						    + (unsigned char) plane
						    [((y + 1) & (count - 1))
						    * lines
						    + ((x + 1) & (count - 1))]))
						    / 5;
						dst = (y * cell + x) * step;
						plane[(y * cell + x) * cell
						    + 0] = (char) t1;
						plane[(y * cell + x) * cell
						    + cell] = (char) t2;
						plane[(y * cell + x) * cell
						    + cell * 2] = (char) avg;
						verdict[dst] = verdict[src];
						verdict[dst + cell * 0x1c]
						    = verdict[src];
						verdict[dst + cell * 0x38]
						    = verdict[src];
					}
				}
			}
			level = cell;
		}
	}
	goto done;

done:
	return 0;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")
unsigned char _tlead_GOLDTL_fcn_0045a3a0[48] = {
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90
};
