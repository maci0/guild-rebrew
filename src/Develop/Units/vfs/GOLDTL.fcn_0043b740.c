


// SIZE 0x84
typedef struct Event {
	int id;
	char name[0x80];
} Event;

void __cdecl fcn_00401360(int, int);
void __cdecl fcn_00401230(int, char*);
char* __cdecl fcn_0043b550(int);

void __cdecl fcn_0043b740(int w, Event* ev)
{
	int n;
	int i;

	if (ev != 0) {
		n = 0;
		for (i = 0; i < 7; i++) {
			if (ev[i].id != 0) {
				n++;
			}
		}
		fcn_00401360(w, n);
		for (i = 0; i < 7; i++) {
			if (ev[i].id != 0) {
				fcn_00401230(w, fcn_0043b550(i));
				fcn_00401230(w, ev[i].name);
			}
		}
	} else {
		fcn_00401360(w, 0);
	}
}
