#include <string.h>


// SIZE 0x194
typedef struct {
	int used;
	char pad[0x190];
} T405080;

extern char* g_6b5c20;

T405080* __cdecl fcn_00405080(void)
{
	int i;

	for (i = 0; i < 2000;) {
		if (((T405080*)g_6b5c20)[i++].used == 0) {
			break;
		}
	}
	if (i >= 2000) {
		return 0;
	}
	return &((T405080*)g_6b5c20)[i - 1];
}

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
            memset(task, 0, 0x194);
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
