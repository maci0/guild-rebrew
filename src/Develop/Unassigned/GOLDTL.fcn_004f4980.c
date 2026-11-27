


typedef struct
{
	char pad[0x1c];
	char kind;
	unsigned char sub;
	char tail[6];
} Rec24;
// SIZE 0x24

extern char g_68ff68[];

int __cdecl gm_FindLawByKindAndSub(char* obj, int sub, Rec24* out)
{
	int i;

	for (i = 0; i < 29; i++) {
		if (obj[0x166] == ((Rec24*)g_68ff68)[i].kind && sub == ((Rec24*)g_68ff68)[i].sub) {
			*out = ((Rec24*)g_68ff68)[i];
			return 1;
		}
	}
	return 0;
}
