


typedef struct
{
	char type;
	char name[0x40];
} Name41;
// SIZE 0x41

extern char* lpObjektePROT;

int __cdecl fcn_005014d0(int i)
{
	Name41* e;

	e = &((Name41*)lpObjektePROT)[i];
	if (e->type == 1 || e->type == 0x1a || e->type == 0xb || e->type == 0x1c || e->type == 0x1b ||
	    e->type == 3 || e->type == 4) {
		return 1;
	}
	return 0;
}
