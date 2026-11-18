/* ADDRESS: GOLDTL 0x004a7710 */
int __cdecl fcn_004a7710(int* indices, int a1)
{
	int i;
	int key;
	int hits;

	hits = 1;
	i = a1 ? 2 : 0;
	if (indices[i] < 0) {
		return 0;
	}
	if (indices[i + 1] < 0) {
		return 0;
	}
	key = *(int*) (0x1007ce4 + indices[i] * 16);
	i++;
	while (i < 5) {
		if (indices[i] < 0) {
			break;
		}
		if (key == *(int*) (0x1007ce4 + indices[i] * 16)) {
			hits++;
		}
		i++;
	}
	return hits;
}
