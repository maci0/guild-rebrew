


extern char* evt_CurrentScript;

int __cdecl evt_SeekSemicolon(void)
{
	while (*(char**) (evt_CurrentScript + 0x118) < (char*) (*(int*) (evt_CurrentScript + 0x120) + *(int*) (evt_CurrentScript + 0x11c))) {
		if (**(char**) (evt_CurrentScript + 0x118) == ';') {
			(*(char**) (evt_CurrentScript + 0x118))++;
			return 1;
		}
		(*(char**) (evt_CurrentScript + 0x118))++;
	}
	return 0;
}
