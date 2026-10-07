// FUNCTION: GOLD 0x00500970
// FUNCTION: GOLDTL 0x005037c0

extern char g_6997e8[];

int __cdecl fcn_005015e0(void** dynamic, void** existing, void** static_ptr, int entity_id);
void* __cdecl fcn_00502cd0(int list, int a, int b, int c);
void* __cdecl fcn_00502fe0(int a, int b, int c);
int __cdecl fcn_00502e30(char* list, int b);
int __cdecl sprintf(char* buf, const char* fmt, ...);

int __cdecl fcn_005037c0(int a, int b, int c)
{
	char* list_head;
	void* r;
	void* dyn;
	void* exi;
	void* sta;
	char buf[0x200];

	if (b == 0) {
		return 0;
	}
	if (!fcn_005015e0(&dyn, &exi, &sta, a)) {
		sprintf(buf, g_6997e8, b, c);
		return 0;
	}
	if (dyn != 0) {
		list_head = (char*) dyn + 0x5d;
	} else if (exi != 0) {
		list_head = (char*) exi + 0x14;
	} else if (sta != 0) {
		list_head = (char*) sta + 0x178;
	} else {
		return 0;
	}
	r = fcn_00502cd0(*(int*) list_head, 1, 0, b);
	if (r == 0) {
		return (int) fcn_00502fe0(a, b, c);
	}
	*(int*) ((char*) r + 0xe) += c;
	return (int) r;
}
