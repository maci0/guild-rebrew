#include <string.h>

void __cdecl fcn_00425bf0(void*, int, char*);
void* __cdecl fcn_00425ec0(void*, int, int, int*);
void __cdecl fcn_00428720(char*);
void* __cdecl fcn_00428800(int);

extern void* g_6b7ea0;

/* Script call frame: one slot per nested function call. */
typedef struct EvtCallFrame {
	char* code;                 /* 0x00, function descriptor being entered */
	int depth;                  /* 0x04 */
	int flags;                  /* 0x08 */
	int splice;                 /* 0x0c */
	char pad_10[0xa0];
} EvtCallFrame;                 /* 0xb0 */

typedef struct EvtFunction {
	char pad_00[0x20];
	int stack_depth;            /* 0x20 */
	char argc;                  /* 0x24 */
	char pad_25[3];
	int types[8];               /* 0x28, parameter type codes */
	int params[8][8];           /* 0x48, per-parameter descriptors, stride 0x20 */
} EvtFunction;

typedef struct EvtContext {
	char pad_00[0x118];
	int depth;                  /* 0x118, call depth */
	char pad_11c[0x0c];
	EvtCallFrame frames[16];    /* 0x128, 0x128..0xc27 */
	EvtCallFrame* frame;        /* 0xc28, frame being filled */
	char pad_c2c[0x0c];
	int splice;                 /* 0xc38 */
} EvtContext;

typedef struct EvtSymbol {
	unsigned char kind;         /* 0x00, low nibble is the value type code */
	char pad_01[0x2b];
	char* data;                 /* 0x2c */
} EvtSymbol;

/* Enters a script function: finds a free call frame, binds the arguments to
 * their parameters by type code (1 int, 2 byte, 6 string, 7 float) and resets
 * the interpreter's depth to the function's stack size. */

/* ADDRESS: GOLDTL 0x00427c40 */
void __cdecl fcn_00427c40(EvtContext* ip, EvtFunction* fn)
{
	EvtSymbol* sym;
	EvtCallFrame* slot;
	int args[8];
	char storage[0x300];
	int pos;
	int n;
	int k;

	pos = 0;
	if (fn == 0) {
		fcn_00425bf0(ip, ip->depth, (char*) 0x679518);
		return;
	}
	while (pos < 0x10) {
		if (ip->frames[pos].code == 0) {
			break;
		}
		pos++;
	}
	if (pos >= 0x10) {
		fcn_00425bf0(ip, ip->depth, (char*) 0x6794ec);
		return;
	}
	n = fn->argc;
	if (pos > 0) {
		ip->depth++;
		for (k = 0; k < n; k++) {
			sym = (EvtSymbol*) fcn_00428800(0);
			if (fn->types[k] == 6) {
				strcpy(&storage[k * 0x60], (char*) sym);
			} else {
				args[k] = (int) sym;
			}
		}
		if (n == 0) {
			ip->depth++;
		}
	} else {
		for (k = 0; k < n; k++) {
			if (fn->types[k] == 6) {
				strcpy(&storage[k * 0x60], (char*) 0x14cb540 + k * 0x60);
			} else {
				args[k] = ((int*) g_6b7ea0)[k];
			}
		}
	}

	slot = &ip->frames[pos];
	ip->frame = slot;
	slot->splice = ip->splice;
	slot->code = (char*) fn;
	for (k = 0; k < n; k++) {
		sym = (EvtSymbol*) fcn_00425ec0(ip, fn->types[k], 1, fn->params[k]);
		if (sym == 0) {
			fcn_00425bf0(ip, ip->depth, (char*) 0x6794c0);
			fcn_00428720((char*) ip);
			return;
		}
		switch (sym->kind & 0x0f) {
		case 1:
			*(int*) sym->data = args[k];
			break;
		case 2:
			*sym->data = (char) args[k];
			break;
		case 6:
			strcpy(sym->data, &storage[k * 0x60]);
			break;
		case 7:
			*(float*) sym->data = (float) args[k];
			break;
		default:
			break;
		}
	}
	ip->depth = fn->stack_depth;
	ip->frame->depth = fn->stack_depth;
	ip->frame->flags = 0;
}
