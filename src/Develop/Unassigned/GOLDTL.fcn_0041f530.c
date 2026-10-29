


typedef struct Events Events;

// SIZE 0x34
typedef struct {
	void* m[8];
	long (__stdcall* GetEvent)(Events* self, long* code, long* p1, long* p2, long timeout);
	void* m9[3];
	long (__stdcall* FreeEventParams)(Events* self, long code, long p1, long p2);
} EventsVtbl;

// SIZE 0x4
struct Events {
	EventsVtbl* vtbl;
};

char* __cdecl fcn_0041f9b0(int id);

long __cdecl fcn_0041f530(int id, long* p1, long* p2)
{
	char* o;
	long code;
	Events* ev;

	o = fcn_0041f9b0(id);
	code = 0;
	if (o != 0) {
		ev = *(Events**) (o + 0x124);
		while (ev->vtbl->GetEvent(ev, &code, p1, p2, 0) >= 0) {
			ev = *(Events**) (o + 0x124);
			ev->vtbl->FreeEventParams(ev, code, *p1, *p2);
			if (code == 1 || code == 0xe) {
				break;
			}
			ev = *(Events**) (o + 0x124);
		}
	}
	return code;
}
