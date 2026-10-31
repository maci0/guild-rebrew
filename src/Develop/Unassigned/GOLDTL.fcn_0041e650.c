/* Drains the pending queue through the two notification helpers, then
 * uninitialises COM. */

struct Node;
__declspec(dllimport) void __stdcall CoUninitialize(void);
void __cdecl ReleaseVideoInterfaces(char*);
void __cdecl FreeVideoListNode(struct Node*);

/* ADDRESS: GOLDTL 0x0041e650 */
void __cdecl fcn_0041e650(void)
{
	char* node;

	node = *(char**) 0x6b6f84;
	if (node != 0) {
		do {
			ReleaseVideoInterfaces(node);
			node = *(char**) 0x6b6f84;
			FreeVideoListNode((struct Node*) node);
			node = *(char**) 0x6b6f84;
		} while (node != 0);
	}
	CoUninitialize();
}
