extern int g_772f3c;
extern int g_772f3c;



int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(void*);

void __cdecl evt_StopScriptIfActive(int scriptId)
{
	void* p;

	if (*(int*) ((char*)&g_772f3c) != 0) {
		return;
	}
	p = (void*) evt_FindScriptById(scriptId);
	if (p != 0) {
		evt_RequestScriptExit(p);
	}
}
