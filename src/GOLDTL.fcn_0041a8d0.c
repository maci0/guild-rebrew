unsigned int __cdecl fcn_0041a950(int);

struct rec_41a8d0 {
	unsigned int f0;
	unsigned int f4;
	int pad8;
	int fc;
};

/* ADDRESS: GOLDTL 0x0041a8d0 */
int __cdecl fcn_0041a8d0(struct rec_41a8d0* a, struct rec_41a8d0* b)
{
	if (a->f0 < b->f0) {
		return -1;
	}
	if (a->f0 > b->f0) {
		return 1;
	}
	if (a->f4 < b->f4) {
		return -1;
	}
	if (a->f4 > b->f4) {
		return 1;
	}
	if (fcn_0041a950(a->fc) < fcn_0041a950(b->fc)) {
		return -1;
	}
	return fcn_0041a950(a->fc) > fcn_0041a950(b->fc);
}
