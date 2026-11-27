/* ADDRESS: GOLD 0x0045f160 */
char __cdecl d3_SampleHeightmap(float* tex, float* pt, int* outx, int* outy, float* out)
{
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
	if (x < 0 || x >= *(int*) (tex + 8) || y < 0 || y >= *(int*) (tex + 8) || outx == 0 || outy == 0) {
		return 0;
	}
	*outx = x;
	*outy = y;
	if (out != 0) {
		s = ((float) (*(unsigned char**) (tex + 10))[*(int*) (tex + 8) * y + x] + 0.5f) * tex[5] + tex[1];
		fy = (pt[2] - (y * tex[6] + tex[2])) / tex[6];
		t10 = ((float) (*(unsigned char**) (tex + 10))[*(int*) (tex + 8) * ((y + 1) & (*(int*) (tex + 8) - 1)) + x] + 0.5f) * tex[5] + tex[1];
		fx = (pt[0] - (x * tex[4] + tex[0])) / tex[4];
		t01 = ((float) (*(unsigned char**) (tex + 10))[*(int*) (tex + 8) * y + ((x + 1) & (*(int*) (tex + 8) - 1))] + 0.5f) * tex[5] + tex[1];
		*out = (t01 - s) * fx + (t10 - s) * fy + s;
	}
	return 1;
}
