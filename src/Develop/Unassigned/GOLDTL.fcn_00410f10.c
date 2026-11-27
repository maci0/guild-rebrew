


extern char* evt_CurrentScript;
extern int g_6791c8;
int __cdecl sb_PrepareVoice(int a, int b);
int __cdecl sb_StartVoice(int o, int a, int b);

int __cdecl PlaySampleHandle(int* a, int* b)
{
	int o;

	if (*(int*) (evt_CurrentScript + 0x104) != g_6791c8) {
		return 0;
	}
	o = sb_PrepareVoice(*a, *b);
	if (o == 0) {
		return o;
	}
	return sb_StartVoice(o, 0, 0);
}
