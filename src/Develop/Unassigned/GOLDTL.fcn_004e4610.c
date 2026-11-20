extern int g_772f3c;
extern int g_772f3c;



int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(void*);

void __cdecl fcn_004e4610(int a1)
{
	void* p;

	if (*(int*) ((char*)&g_772f3c) != 0) {
		return;
	}
	p = (void*) evt_FindScriptById(a1);
	if (p != 0) {
		evt_RequestScriptExit(p);
	}
}
