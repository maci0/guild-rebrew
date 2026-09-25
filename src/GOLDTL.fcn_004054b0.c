// FUNCTION: GOLD 0x00404b90
// SIZE: 144
// FUNCTION: GOLDTL 0x004054b0
// SIZE: 144

typedef struct Task Task;
// SIZE 0x18
struct Task {
	void (__cdecl* run)(Task* t);
	void (__cdecl* done)(Task* t);
	unsigned char level;
	char pad9[3];
	int count;
	char pad10[4];
	int active;
};

int __cdecl fcn_004054b0(char* e)
{
	Task* t;
	char* s;

	if (*(Task**) (e + 0x128) == 0) {
		return 0;
	}
	t = *(Task**) (e + 0x128);
	if (t != 0 && t->active != 0 && t->run != 0) {
		t->run(t);
		t->count++;
		if (t->done != 0) {
			s = *(char**) (e + 0x70);
			if (s != 0 && *(int*) (e + 0x80) == 0 &&
			    (int) *(char*) (e + 0x85) != *(unsigned char*) (s + 0x6c) &&
			    *(int*) s >= (int) t->level) {
				t->done(t);
				*(char*) (e + 0x85) = *(char*) (*(char**) (e + 0x70) + 0x6c);
			}
		}
	}
	return 1;
}
