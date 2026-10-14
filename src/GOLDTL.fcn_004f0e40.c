


typedef struct
{
	char data[0x5c];
	int active;
	int x60;
	int x64;
} Sub68;
// SIZE 0x68

typedef struct
{
	int id;
	int flags;
	float s[3];
	int x14;
	Sub68 sub[3];
	int used[3];
	int h[3];
	void* fn;
	void* ctx;
} Slot170;
// SIZE 0x170

typedef struct
{
	char b[0x38];
} Set;
// SIZE 0x38

#include "client_types.h"
extern Slot170_7731b8 g_7731b8[8];
extern Set g_772ff8[8];

Slot170* __cdecl fcn_004f0c90(int id);
int __cdecl fcn_004ef250(Set* p);

void __cdecl fcn_004f0e40(int id, void* fn, void* ctx)
{
	Slot170* s;

	if (id == -1) {
		return;
	}
	s = fcn_004f0c90(id);
	if (s == 0) {
		return;
	}
	if (fn != 0) {
		s->fn = fn;
		s->ctx = ctx;
	} else {
		s->fn = (void*) fcn_004ef250;
		s->ctx = &g_772ff8[s - ((Slot170*)g_7731b8)];
	}
}
