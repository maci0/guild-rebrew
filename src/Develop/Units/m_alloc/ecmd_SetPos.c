extern char* evt_CurrentScript;
extern char g_676724[];



void __cdecl d3_SetNodePosition(char*, char*);
void __cdecl evt_LogScriptError(void*, int, char*);

int __cdecl ecmd_SetPos(char** objectRef, int* posX, int* posY, int* posZ)
{
	if (*objectRef != 0) {
		*(int*) (*objectRef + 0x4c) = *posX;
		*(int*) (*objectRef + 0x50) = *posY;
		*(int*) (*objectRef + 0x54) = *posZ;
		d3_SetNodePosition(*objectRef, *objectRef + 0x4c);
		return 0;
	}
		evt_LogScriptError(evt_CurrentScript, *(int*) ((char*) evt_CurrentScript + 0x118), g_676724);
	return 0;
}
