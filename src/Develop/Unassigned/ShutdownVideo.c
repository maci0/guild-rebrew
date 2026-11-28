extern char tp_VideoListHead[];
/* Drains the pending queue through the two notification helpers, then
 * uninitialises COM. */

struct Node;
__declspec(dllimport) void __stdcall CoUninitialize(void);
void __cdecl ReleaseVideoInterfaces(char*);
void __cdecl FreeVideoListNode(struct Node*);

/* ADDRESS: GOLDTL 0x0041e650 */
/* ADDRESS: GOLDDE 0x0041c080 */
void __cdecl ShutdownVideo(void)
{
	char* node;

	node = *(char**) &tp_VideoListHead;
	if (node != 0) {
		do {
			ReleaseVideoInterfaces(node);
			node = *(char**) &tp_VideoListHead;
			FreeVideoListNode((struct Node*) node);
			node = *(char**) &tp_VideoListHead;
		} while (node != 0);
	}
	CoUninitialize();
}
