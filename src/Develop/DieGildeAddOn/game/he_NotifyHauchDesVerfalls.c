


extern char g_774a80[];
extern char g_774e80[];
char g_6ab50c[] = "_NACHRICHTEN_FRIEDHOF_00";

char* __cdecl strcat(char*, const char*);
#pragma intrinsic(strcat)
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);

void __cdecl he_NotifyHauchDesVerfalls(char* recipient, unsigned char* entity, unsigned short* id, int includeDetails)
{
	io_FormatTextBuffer(g_774a80, 0x40ad, 0x40a3, *(unsigned short*) entity, *(int*) (entity + 0x16c), *id);
	if (includeDetails != 0) {
		io_FormatTextBuffer(g_774e80, 0x40ae, (entity[9] != 0 ? 0x230 : 0x20d) + entity[0x165]);
		strcat(g_774a80, g_774e80);
	}
	he_PostEntityMessage(*(int*) (recipient + 4), -1, g_774a80, 0, 0x5fa, g_6ab50c);
}
unsigned char _dpad_6ab52c[20] = {
    0x48, 0x52, 0x49, 0x43, 0x48, 0x54, 0x45, 0x4e, 0x5f, 0x44, 0x4f, 0x4d, 0x49, 0x5a, 0x49, 0x4c,
    0x5f, 0x30, 0x33, 0x00
};
unsigned char _dpad_6ab541[23] = {
    0x4e, 0x41, 0x43, 0x48, 0x52, 0x49, 0x43, 0x48, 0x54, 0x45, 0x4e, 0x5f, 0x44, 0x4f, 0x4d, 0x49,
    0x5a, 0x49, 0x4c, 0x5f, 0x30, 0x31, 0x00
};

