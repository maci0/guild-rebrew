// FUNCTION: GOLDTL 0x00503890
// SIZE: 150

extern char g_6997e8[];

int __cdecl fcn_005015e0(void** dynamic, void** existing, void** static_ptr, int entity_id);
void* __cdecl fcn_00502cd0(int list, int a, int b, int c);
void* __cdecl fcn_00502fe0(int a, int b, int c);
int __cdecl fcn_00502e30(char* list, int b);
int __cdecl sprintf(char* buf, const char* fmt, ...);

int __cdecl fcn_00503890(int a, int b, int c)
{
	char* list_head;
	void* exi;
	void* sta;
	char* r;

	if (!fcn_005015e0((void**) &a, &exi, &sta, a)) {
		return 0;
	}
	if (a != 0) {
		list_head = (char*) a + 0x5d;
	} else if (exi != 0) {
		list_head = (char*) exi + 0x14;
	} else if (sta != 0) {
		list_head = (char*) sta + 0x178;
	} else {
		return 0;
	}
	r = fcn_00502cd0(*(int*) list_head, 1, 0, b);
	if (r == 0) {
		return 0;
	}
	if (*(int*) (r + 0xe) < c) {
		return 0;
	}
	*(int*) (r + 0xe) -= c;
	if (*(int*) (r + 0xe) <= 0) {
		fcn_00502e30(list_head, b);
	}
	return 1;
}
