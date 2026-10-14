


typedef struct Task Task;

// SIZE 0x194
struct Task {
	void (__cdecl* run)(Task* t);
	void (__cdecl* done)(Task* t);
	unsigned char level;
	char kind;
	char pad0a[2];
	int state;
	unsigned char flags;
	char pad11[3];
	char* owner;
	char pad18[0x24 - 0x18];
	Task* prev;
	Task* next;
	char pad2c[4];
	int param;
	char pad34[0xf0 - 0x34];
	char name[0x40];
	char name2[0x40];
	int a170;
	int a174;
	float a178;
	char pad17c[0x190 - 0x17c];
	unsigned char b190;
	char pad191[3];
};

int __cdecl fcn_004050c0(Task* t);
char* __cdecl fcn_00404dc0(char* e, char* name, int flag);
int __cdecl fcn_00404f60(Task* t);
void __cdecl fcn_00406560(char* e);

void __cdecl fcn_004065c0(Task* t)
{
	char* e;
	char* s;

	e = t->owner;
	if ((*(int*) (e + 0x70) != 0 || *(int*) (e + 0x7c) != 0) && (t->flags & 1) == 0) {
		t->state = -1;
		return;
	}
	t->flags |= 1;
	if (t->state == 0) {
		if ((*(unsigned char*) (e + 0x8c) & 0x10) == 0) {
			fcn_004050c0(t);
			return;
		}
		s = fcn_00404dc0(e, t->name, 1);
		*(char**) (e + 0x70) = s;
		if (s == 0) {
			fcn_004050c0(t);
			return;
		}
		*(unsigned char*) (s + 0x6c) = 1;
		*(int*) (*(char**) (e + 0x70) + 0x70) &= ~3;
		*(unsigned char*) (*(char**) (e + 0x70) + 0x6d) |= 0x10;
		return;
	}
	if (fcn_00404f60(t) == -1) {
		fcn_00406560(e);
		fcn_004050c0(t);
	}
}
