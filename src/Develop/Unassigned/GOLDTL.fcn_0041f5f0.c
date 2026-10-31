char* __cdecl FindVideoById(int id);
void __cdecl ReleaseVideoInterfaces(char* v);
struct Node;
void __cdecl FreeVideoListNode(struct Node* node);

/* ADDRESS: GOLDTL 0x0041f5f0 */
int __cdecl CloseVideo(int id)
{
	char* node;

	node = FindVideoById(id);
	if (node != 0) {
		ReleaseVideoInterfaces(node);
		FreeVideoListNode((struct Node*)node);
		return 1;
	}
	return 0;
}
