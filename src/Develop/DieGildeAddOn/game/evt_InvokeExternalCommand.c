extern char g_6b7e98[];
extern char evt_WaitingScriptTask[];
void __cdecl free(void* p);

/* ADDRESS: GOLDTL 0x00429490 */
/* ADDRESS: GOLDDE 0x00423eb0 */
int __cdecl evt_InvokeExternalCommand(char* ctx)
{
	char* cb;
	int result;
	int i;

	cb = *(char**) (ctx + 0xc5c);
	*(char**) &evt_WaitingScriptTask = cb;
	*(int*) (ctx + 0xc5c) = 0;
	*(int*) (*(char**) &g_6b7e98 + 0xc60) = 0;
	switch (*(int*) (cb + 0x20)) {
	case 0:
		result = ((int (__cdecl*) (void)) * (void**) (cb + 0x44))();
		break;
	case 1:
		result = ((int (__cdecl*) (void*)) * (void**) (cb + 0x44))(ctx + 0xc64);
		break;
	case 2:
		result = ((int (__cdecl*) (void*, void*)) * (void**) (cb + 0x44))(ctx + 0xc64, ctx + 0xc68);
		break;
	case 3:
		result = ((int (__cdecl*) (void*, void*, void*)) * (void**) (cb + 0x44))(ctx + 0xc64, ctx + 0xc68, ctx + 0xc6c);
		break;
	case 4:
		result = ((int (__cdecl*) (void*, void*, void*, void*)) * (void**) (cb + 0x44))(ctx + 0xc64, ctx + 0xc68, ctx + 0xc6c, ctx + 0xc70);
		break;
	case 5:
		result = ((int (__cdecl*) (void*, void*, void*, void*, void*)) * (void**) (cb + 0x44))(ctx + 0xc64, ctx + 0xc68, ctx + 0xc6c, ctx + 0xc70, ctx + 0xc74);
		break;
	case 6:
		result = ((int (__cdecl*) (void*, void*, void*, void*, void*, void*)) * (void**) (cb + 0x44))(ctx + 0xc64, ctx + 0xc68, ctx + 0xc6c, ctx + 0xc70, ctx + 0xc74, ctx + 0xc78);
		break;
	case 7:
		result = ((int (__cdecl*) (void*, void*, void*, void*, void*, void*, void*)) * (void**) (cb + 0x44))(ctx + 0xc64, ctx + 0xc68, ctx + 0xc6c, ctx + 0xc70, ctx + 0xc74, ctx + 0xc78, ctx + 0xc7c);
		break;
	default:
		goto done;
	}
done:
	if (*(int*) (ctx + 0xc60) == 0) {
		*(int*) (ctx + 0xc5c) = 0;
		*(int*) &evt_WaitingScriptTask = 0;
		for (i = 0; i < *(int*) (cb + 0x20); i++) {
			if (*(int*) (cb + 0x24 + i * 4) == 6) {
				free(*(void**) (ctx + 0xc64 + i * 4));
			}
			*(int*) (ctx + 0xc64 + i * 4) = 0;
		}
	} else {
		*(char**) (ctx + 0xc5c) = cb;
	}
	*(int*) &evt_WaitingScriptTask = 0;
	return result;
}
