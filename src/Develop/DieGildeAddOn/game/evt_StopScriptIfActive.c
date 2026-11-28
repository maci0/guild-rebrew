extern int cut_SkipMode;
extern int cut_SkipMode;



int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(void*);

/* ADDRESS: GOLDDE 0x004d1000 */
void __cdecl evt_StopScriptIfActive(int scriptId)
{
	void* p;

	if (*(int*) ((char*)&cut_SkipMode) != 0) {
		return;
	}
	p = (void*) evt_FindScriptById(scriptId);
	if (p != 0) {
		evt_RequestScriptExit(p);
	}
}
