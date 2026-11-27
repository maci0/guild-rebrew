extern char g_773dd4;



void __cdecl SelectTextureSet(char*, int, char, int);

char __cdecl d3_ApplySeasonTextureSet(char* obj)
{
	int s;

	s = *(int*) (obj + 0x220);
	if (s != 2 && s != 4) {
		if (s == 3) {
			SelectTextureSet(obj, *(int*) (obj + 0x1ec) + 0xf4, g_773dd4, 1);
		} else {
			SelectTextureSet(obj, *(int*) (obj + 0x1ec) + 0xf4, g_773dd4, 1);
		}
	}
	return 1;
}
