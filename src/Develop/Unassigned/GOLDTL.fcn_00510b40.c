struct D3_SCENE_NODE_LINK {
	char pad0[0x1fc];
	struct D3_SCENE_NODE_LINK* p1fc;
	char pad200[4];
	struct D3_SCENE_NODE_LINK* p204;
};

/* ADDRESS: GOLDTL 0x00510b40 */
void __cdecl d3_InheritSceneNodeData(struct D3_SCENE_NODE_LINK* n)
{
	struct D3_SCENE_NODE_LINK* cur;

	cur = n->p1fc;
	while (n->p204 == 0 && cur != 0) {
		n->p204 = cur->p204;
		cur = cur->p1fc;
	}
}
