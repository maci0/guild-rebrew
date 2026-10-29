/* Drains the pending queue through the two notification helpers, then
 * uninitialises COM. */

struct Node;
__declspec(dllimport) void __stdcall CoUninitialize(void);
void __cdecl fcn_0041f7f0(char*);
void __cdecl fcn_0041f940(struct Node*);

/* ADDRESS: GOLDTL 0x0041e650 */
void __cdecl fcn_0041e650(void)
{
	char* node;

	node = *(char**) 0x6b6f84;
	if (node != 0) {
		do {
			fcn_0041f7f0(node);
			node = *(char**) 0x6b6f84;
			fcn_0041f940((struct Node*) node);
			node = *(char**) 0x6b6f84;
		} while (node != 0);
	}
	CoUninitialize();
}
