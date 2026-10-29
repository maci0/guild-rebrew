struct node_510b40 {
	char pad0[0x1fc];
	struct node_510b40* p1fc;
	char pad200[4];
	struct node_510b40* p204;
};

/* ADDRESS: GOLDTL 0x00510b40 */
void __cdecl fcn_00510b40(struct node_510b40* n)
{
	struct node_510b40* cur;

	cur = n->p1fc;
	while (n->p204 == 0 && cur != 0) {
		n->p204 = cur->p204;
		cur = cur->p1fc;
	}
}
