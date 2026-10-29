/* ADDRESS: GOLDTL 0x004721e0 */
int* __cdecl fcn_004721e0(int a, int b, int c)
{
	int n;
	int value;
	int count;
	int* ptr;
	int* arr;
	int* store;

	n = *(int*) 0x772534;
	value = *(int*) (0x1038144 + (b + n * 175) * 4);
	ptr = (int*) (0x1015f40 + value * 108);
	count = *(int*) (0x1015f6c + value * 108);
	if (a > count - 1) {
		return ptr;
	}
	arr = (int*) ptr[10];
	store = *(int**) 0x1015ea0;
	store[arr[a] * 189 + 18] = (c == 0);
	return store;
}
