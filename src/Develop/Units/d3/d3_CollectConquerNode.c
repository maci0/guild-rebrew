extern char g_68b820[];
extern char g_9b46c0[];
extern char g_772f10[];
/* fcn_004d36b0 — register the game in the pending table unless it exists. */

int __cdecl fcn_0064f170(int, int, int);

/* ADDRESS: GOLDTL 0x004d36b0 */
/* ADDRESS: GOLDDE 0x004c09a0 */
char __cdecl d3_CollectConquerNode(int node)
{
	int index;

	if (fcn_0064f170(node, (int) &g_68b820, 0xa) == 0) {
		index = *(int*) &g_772f10;
		*(int*) ((int) &g_9b46c0 + index * 4) = node;
		*(int*) &g_772f10 = index + 1;
	}
	return 1;
}
