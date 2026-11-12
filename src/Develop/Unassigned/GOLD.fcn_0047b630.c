/* ADDRESS: GOLD 0x0047b630 */
int __cdecl fcn_0047b630(int x, int y, int* surface, char* sprite, int factor)
{
	unsigned int* line_count;
	unsigned int* run;
	unsigned short* row_output;
	unsigned short* output;
	unsigned short* pixels;
	unsigned int carry;
	unsigned int n;
	unsigned int i;
	int height;
	int divisor;
	int row;
	int emit;
	int clipped;
	int screen_y;
	line_count = (unsigned int*) (sprite + 0x32);
	run = (unsigned int*) (sprite + 0x36);
	row_output = (unsigned short*) surface[7] + surface[4] * y + x;
	height = *(unsigned short*) (sprite + 0xa);
	if (height + y < *(int*) 0x6f045c) {
		return 0;
	}
	divisor = factor & 0xff;
	if (height / divisor + y > *(int*) 0x5fed60) {
		height = (*(int*) 0x5fed60 - y) * divisor;
	}
	carry = 0;
	clipped = y < *(int*) 0x6f045c;
	for (row = 0; row < height; row++) {
		emit = row % divisor == 0;
		screen_y = row / divisor + y;
		output = row_output;
		for (i = 0; i < *line_count; i++) {
			output += ((run[0] >> 1) + carry) / (unsigned int) divisor;
			carry = (run[0] >> ((carry + 1) & 0x1f)) % (unsigned int) divisor;
			if (emit) {
				pixels = (unsigned short*) (run + 2);
				for (n = 0; n < (run[1] + carry) / (unsigned int) divisor; n++) {
					if (!clipped || screen_y >= *(int*) 0x6f045c) {
						*output = (*(unsigned short**)0x6f0460)[*pixels];
					}
					pixels += divisor;
					output++;
				}
				carry = (run[1] + carry) % (unsigned int) divisor;
			}
			run = (unsigned int*) ((char*) run + run[1] * 2 + 8);
		}
		if (emit) {
			row_output += surface[4];
		}
		line_count = run;
		run++;
	}
	return 1;
}
