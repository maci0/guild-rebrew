typedef struct {
	unsigned char pad_000[0xd4];
	unsigned char rest : 7;
	unsigned char f7 : 1;
} H_4106b0;

int __cdecl fcn_0041dd90(int);
int __cdecl fcn_00425bf0(void *, int, int);

/* ADDRESS: GOLDTL 0x004106b0 */
int __cdecl fcn_004106b0(int *o, unsigned char *p)
{
	H_4106b0 *h;
	int *g;

	h = (H_4106b0 *) o[0];
	if (fcn_0041dd90((int) h) == 0) {
		g = (int *) *(int *) 0x6b7e98;
		fcn_00425bf0(g, *(int *) ((char *) g + 0x118), 0x676c7c);
		return 0;
	}
	h->f7 = p[0];
	return 0;
}
