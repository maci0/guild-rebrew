#include <string.h>

// SIZE 0xb0
struct frame_427b40 {
	char* name;
	int line;
	int pad8;
	int result;
	int regs[8];
	char pad30[0x80];
};

// SIZE 0xc3c
struct script_427b40 {
	char pad0[0x118];
	int line;
	int pad11c;
	int pad120;
	unsigned int flags;
	struct frame_427b40 frames[16];
	struct frame_427b40* cur;
	int padc2c[3];
	int result;
};

// FUNCTION: GOLD 0x004292b0
// SIZE: 249
// FUNCTION: GOLDTL 0x427b40
// SIZE: 249

/* Returns from the current script function to its caller frame; returns 0
 * when the outermost frame ended. */
int __cdecl fcn_00427b40(struct script_427b40* s)
{
	int i;
	int k;

	if (strcmp(s->cur->name, "exit") == 0) {
		return 0;
	}
	for (i = 15; i >= 0; i--) {
		if (s->frames[i].name != 0) {
			break;
		}
	}
	if (i < 0) {
		return 0;
	}
	if (i >= 1) {
		for (k = 0; k < 8; k++) {
			s->cur->regs[k] = 0;
		}
		s->result = s->cur->result;
		s->cur = &s->frames[i - 1];
		s->line = s->cur->line;
		s->frames[i].name = 0;
		s->frames[i].line = 0;
		return 1;
	}
	for (k = 0; k < 8; k++) {
		s->cur->regs[k] = 0;
	}
	s->result = s->cur->result;
	s->cur = 0;
	s->flags &= ~1;
	s->frames[i].name = 0;
	s->frames[i].line = 0;
	return 0;
}
