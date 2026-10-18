struct Node;
__declspec(dllimport) void __stdcall CoUninitialize(void);
void __cdecl fcn_0041f7f0(char*);
void __cdecl fcn_0041f940(struct Node*);

/* ADDRESS: GOLD 0x00422d90 */
void __cdecl fcn_00422d90(void)
{
	char* node;

	node = *(char**) 0x6323a4;
	if (node != 0) {
		do {
			fcn_0041f7f0(node);
			node = *(char**) 0x6323a4;
			fcn_0041f940((struct Node*) node);
			node = *(char**) 0x6323a4;
		} while (node != 0);
	}
	CoUninitialize();
}
