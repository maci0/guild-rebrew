int __cdecl fcn_004fbc90(void *);

/* ADDRESS: GOLDTL 0x004cd460 */
int __cdecl fcn_004cd460(void *a1, char *result)
{
	if (result != 0) {
		result[0] = 2;
		result[1] = 0;
		*(int *) (result + 6) = 0;
	}
	if (fcn_004fbc90((void *) ((char *) a1 + 0x10)) == 0) {
		return 1;
	}
	if (result != 0) {
		result[0] = 1;
	}
	return 0;
}
