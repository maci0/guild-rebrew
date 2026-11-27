extern unsigned short* g_772f24;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl ai_ShouldConfessTrialTorture(int*);
int __cdecl IsRandomSecondChoice(int*);
int __cdecl ai_SelectRandomTorture(int*);
int __cdecl ai_ShouldSpareTrialTorture(int*);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl ai_ShouldAcquitTrial(char*, int*);
int __cdecl ai_ChooseProzessSentence(char*, int*);


/* ADDRESS: GOLDTL 0x004dfba0 */
void __cdecl cut_HandleProzessEvent(char* context, int* ev)
{
	char* e;

	*(int*) (context + 0x94) = -1;
	switch (ev[0]) {
	case 0:
		if (*(int*) (context + 0x10) == ev[6]) {
			e = gm_LookupEntityRecordById(ev[6]);
			*(float*) (context + 0x98) = *(int*) (e + 0x24) + *(float*) (e + 0x1c);
			*(int*) (context + 0x94) = ai_ShouldConfessTrialTorture(ev);
		}
		break;
	case 1:
		if (*(int*) (context + 0x10) == ev[5])
			*(int*) (context + 0x94) = IsRandomSecondChoice(ev);
		break;
	case 2:
		if (*(int*) (context + 0x10) == ev[5])
			*(int*) (context + 0x94) = ai_SelectRandomTorture(ev);
		break;
	case 3:
		if (*(int*) (context + 0x10) == ev[10]) {
			*(int*) (context + 0x94) = ai_ShouldSpareTrialTorture(ev);
			if (*(int*) (context + 0x94) == 1)
				cm_RequestCopyEntityData(*(int*) (context + 0x10), ev[6], 0x23, 1);
		}
		break;
	case 6:
		if (*(int*) (context + 0x10) == ev[6])
			*(int*) (context + 0x94) = gm_RandomMod(2);
		break;
	case 4:
		if (*(int*) (context + 0x10) == ev[7] || *(int*) (context + 0x10) == ev[8] || *(int*) (context + 0x10) == ev[9]) {
			e = gm_LookupEntityRecordById(((int*)g_772f24)[1]);
			*(int*) (context + 0x94) = ai_ShouldAcquitTrial(e, ev);
		}
		break;
	case 5:
		if (*(int*) (context + 0x10) == ev[7]) {
			e = gm_LookupEntityRecordById(ev[7]);
			*(int*) (context + 0x94) = ai_ChooseProzessSentence(e, ev);
		}
		break;
	}
}
