#include <string.h>

/* The native caller 0x406120 keeps a live edx across the call to 0x4050c0
 * and reads it again afterwards, which MSVC 6 only emits when the callee is
 * defined in the same translation unit. Both bodies live in this file. */

/* ADDRESS: GOLDTL 0x004050c0 */
int __cdecl fcn_004050c0(char* task)
{
    char* next;
    char* previous;
    char* owner;

    if (task == 0) {
        return 0;
    }
    next = *(char**) (task + 0x28);
    if (next == 0) {
        owner = *(char**) (task + 0x14);
        if (owner != 0 && task == *(char**) (owner + 0x128)) {
            *(char**) (owner + 0x128) = next;
            __asm {
                mov ecx, 0x65
                xor eax, eax
                rep stosd
            }
            return 1;
        }
    }
    previous = *(char**) (task + 0x24);
    if (previous != 0) {
        *(char**) (previous + 0x28) = next;
    }
    next = *(char**) (task + 0x28);
    if (next != 0) {
        *(char**) (next + 0x24) = previous;
    }
    if (previous == 0) {
        owner = *(char**) (task + 0x14);
        if (owner != 0) {
            *(char**) (owner + 0x128) = next;
        }
    }
    memset(task, 0, 0x194);
    return 1;
}

typedef struct Task Task;

/* SIZE 0x194 */
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

int __cdecl fcn_00406670(char* p, char* s);

/* ADDRESS: GOLDTL 0x00406120 */
int __cdecl fcn_00406120(char* e)
{
	Task* t;

	if (e == 0) {
		return 0;
	}
	t = *(Task**) (e + 0x128);
	if (t == 0) {
		return 0;
	}
	t->b190 = 1;
	while (t->next != 0) {
		fcn_004050c0((char*) t->next);
	}
	if ((*(unsigned char*) (e + 0x8c) & 0x10) != 0) {
		fcn_00406670(e, "sitzend/aufstehen");
	}
	return 1;
}
