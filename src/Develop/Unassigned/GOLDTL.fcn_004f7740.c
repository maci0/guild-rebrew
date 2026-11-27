


void __cdecl gm_RunDuelChallengeAction(void*, void*);
extern char g_679060[];
void __cdecl io_FormatTextBuffer(void*, int, int);

int __cdecl gm_HandleDuelChallengeCommand(void* entity, void* params)
{
	int mode;

	mode = *(int*) params;
	if (mode == 3 || mode == 1) {
		if (*(unsigned char*) ((char*) entity + 0xd) >= 3 &&
		    (*(int*) ((char*) entity + 0x1c8) & 0x400) == 0) {
			if (mode == 3) {
				gm_RunDuelChallengeAction(entity, params);
				return 2;
			}
			if (mode == 1 && *(char*) ((char*) entity + 2) == 6) {
				io_FormatTextBuffer((char*) params + 0x14, (int) "%s", 0x1d65);
			}
			return 2;
		}
	}
	return 1;
}
