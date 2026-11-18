extern char* evt_CurrentScript;
extern char g_676724[];



void __cdecl fcn_00438b40(char*, char*);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl ecmd_SetPos(char** objectRef, int* posX, int* posY, int* posZ)
{
	if (*objectRef != 0) {
		*(int*) (*objectRef + 0x4c) = *posX;
		*(int*) (*objectRef + 0x50) = *posY;
		*(int*) (*objectRef + 0x54) = *posZ;
		fcn_00438b40(*objectRef, *objectRef + 0x4c);
		return 0;
	}
		fcn_00425bf0(evt_CurrentScript, *(int*) ((char*) evt_CurrentScript + 0x118), g_676724);
	return 0;
}
