


extern char* evt_CurrentScript;
extern int evt_ActiveContextId;
int __cdecl sb_PrepareVoice(int a, int b);
int __cdecl sb_StartVoice(int o, int a, int b);

/* ADDRESS: GOLDDE 0x0040fd10 */
int __cdecl PlaySampleHandle(int* a, int* b)
{
	int o;

	if (*(int*) (evt_CurrentScript + 0x104) != evt_ActiveContextId) {
		return 0;
	}
	o = sb_PrepareVoice(*a, *b);
	if (o == 0) {
		return o;
	}
	return sb_StartVoice(o, 0, 0);
}
