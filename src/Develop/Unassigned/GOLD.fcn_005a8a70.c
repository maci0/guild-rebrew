
/* fcn_005a8a70: if ([0x6f26c0]) fcn_005b1960([0x6f26c0]); [0x6f26c0]=0. */

int __cdecl ls_FreeListNodes(int);

void __cdecl ls_FreeList774a78(void)
{
	int h;
	h = *(int*) 0x6f26c0;
	if (h != 0) {
		ls_FreeListNodes(h);
	}
	*(int*) 0x6f26c0 = 0;
}
