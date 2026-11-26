extern int* g_6b7d78;



int __cdecl _strnicmp(int, int, int);

int* __cdecl sb_FindBankByName(int key)
{
	int* node;

	node = g_6b7d78;
	while (node != 0) {
		if (_strnicmp((int) node, key, 0x32) == 0) {
			break;
		}
		node = (int*) node[0x13c / 4];
	}
	return node;
}
