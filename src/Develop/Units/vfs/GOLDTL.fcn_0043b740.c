


// SIZE 0x84
typedef struct Event {
	int id;
	char name[0x80];
} Event;

void __cdecl vfs_WriteInt(int, int);
void __cdecl vfs_WriteCString(int, char*);
char* __cdecl d3_FindEventName(int);

void __cdecl d3_WriteEventTable(int w, Event* ev)
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
		vfs_WriteInt(w, n);
		for (i = 0; i < 7; i++) {
			if (ev[i].id != 0) {
				vfs_WriteCString(w, d3_FindEventName(i));
				vfs_WriteCString(w, ev[i].name);
			}
		}
	} else {
		vfs_WriteInt(w, 0);
	}
}
