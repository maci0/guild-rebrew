/* Selects the best record (stride 0x24) between 0x666960 and the end pointer
   at 0x6ad804. When a filter object is supplied, three interface queries fill
   a filter buffer and the per-record check goes through interface slot 0x28;
   the best record is the lowest score from fcn_0060f6ae (ties broken by the
   record dword at +8). The selected candidate starts at 0x666938. Returns the
   first dword of the selected record. */
typedef struct Vtbl0060f791 {
	char pad0[8];
	void (__stdcall* release)(void*);
	char padc[0xc];
	void (__stdcall* v18)(void*, void*);
	void (__stdcall* v1c)(void*, void*);
	void (__stdcall* v20)(void*, void*);
	char pad24[4];
	int (__stdcall* v28)(void*, int, int, int, int, int, int);
} Vtbl0060f791;

void __cdecl fcn_006195e3(int);
int __cdecl fcn_0060f6ae(void*);

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0060f791 */
int __cdecl fcn_0060f791(int a1, int a2, int a3, int a4)
{
	char* e;
	char* bestp;
	char* end;
	int iface = 0;
	int unk;
	int out;
	char buf[0xd4];
	int best;
	int score;

	fcn_006195e3(1);
	if (a1) {
		(*(Vtbl0060f791**)*(int*)a1)->v18((void*)a1, &iface);
		(*(Vtbl0060f791**)*(int*)a1)->v1c((void*)a1, buf);
		(*(Vtbl0060f791**)*(int*)a1)->v20((void*)a1, &out);
	}
	best = -1;
	bestp = (char*)0x666938;
	end = *(char**)0x6ad804;
	e = (char*)0x666960;
	if (e < end) {
		while (e < end) {
			if (*(int*)e != 0) {
				if (a1 == 0 ||
				    (*(Vtbl0060f791**)*(int*)iface)->v28((void*)iface, *(int*)e,
					a2, a3, unk, *(int*)(buf + 4), *(int*)buf) >= 0) {
					if (*(int*)a4 == *(int*)e) {
						bestp = e;
						break;
					}
					if (*(int*)(e + 0x20) != 0) {
						score = fcn_0060f6ae(e);
						if (score != -1 && score <= best &&
						    (score != best || *(int*)(e + 8) < *(int*)(bestp + 8))) {
							best = score;
							bestp = e;
						}
					}
				}
			}
			e += 0x24;
		}
	}
	if (iface) {
		(*(Vtbl0060f791**)*(int*)iface)->release((void*)iface);
		iface = 0;
	}
	fcn_006195e3(0);
	return *(int*)bestp;
}
