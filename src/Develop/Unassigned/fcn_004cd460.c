int __cdecl fcn_004fbc90(void *);

/* ADDRESS: GOLDTL 0x004cd460 */
int __cdecl fcn_004cd460(void *a1, char *p)
{
	if (p != 0) {
		p[0] = 2;
		p[1] = 0;
		*(int *) (p + 6) = 0;
	}
	if (fcn_004fbc90((void *) ((char *) a1 + 0x10)) == 0) {
		return 1;
	}
	if (p != 0) {
		p[0] = 1;
	}
	return 0;
}
