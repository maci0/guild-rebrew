extern char g_774964;
extern char g_774964;



extern char g_7f4ca0[];

int __cdecl ls_CanSaveGame(void)
{
	unsigned char* entity;
	int canSave;

	canSave = 1;
	if (*(char*) ((char*)&g_774964) != 0) {
		for (entity = (unsigned char*) g_7f4ca0 + 2; (int) entity < (int) g_7f4ca0 + 0x65402; entity += 0x21c) {
			if (entity[6] > 0 && (entity[0] == 6 || entity[0] == 7) && *(int*) (entity + 0x20a) != -1) {
				canSave = 0;
				break;
			}
		}
	} else {
		canSave = 0;
	}
	return canSave;
}
