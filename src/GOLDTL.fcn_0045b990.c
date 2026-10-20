/* Bilinear sample of a byte texture: returns 0 for a sample outside the
 * texture or a missing coordinate output, else the interpolated height
 * through *out.  tex[8] is the edge length, tex[10] the byte plane. */

/* ADDRESS: GOLDTL 0x0045b990 */
int __cdecl fcn_0045b990(float* tex, float* pt, int* outx, int* outy, float* out)
{
	unsigned char* data;
	int width;
	int x;
	int y;
	float s;
	float fx;
	float fy;
	float t10;
	float t01;

	if (tex == 0) {
		return 0;
	}
	x = (int) ((pt[0] - tex[0]) / tex[4]);
	y = (int) ((pt[2] - tex[2]) / tex[6]);
	width = *(int*) (tex + 8);
	if (x < 0 || x >= width || y < 0 || y >= width || outx == 0 || outy == 0) {
		return 0;
	}
	*outx = x;
	*outy = y;
	if (out == 0) {
		return 1;
	}
	data = *(unsigned char**) (tex + 10);
	width = *(int*) (tex + 8);
	s = ((float) data[width * y + x] + *(float*) 0x6628cc) * tex[5] + tex[1];
	fy = (pt[2] - (y * tex[6] + tex[2])) / tex[6];
	t10 = ((float) data[width * ((y + 1) & (width - 1)) + x] + *(float*) 0x6628cc) * tex[5] + tex[1];
	fx = (pt[0] - (x * tex[4] + tex[0])) / tex[4];
	t01 = ((float) data[width * y + ((x + 1) & (width - 1))] + *(float*) 0x6628cc) * tex[5] + tex[1];
	*out = (t01 - s) * fx + (t10 - s) * fy + s;
	return 1;
}
