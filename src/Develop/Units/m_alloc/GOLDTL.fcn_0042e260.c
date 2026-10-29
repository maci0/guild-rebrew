typedef struct VAL_SUB {
	char pad_000[0x68];
	void* f068;
} VAL_SUB;

typedef struct VAL_OBJ {
	char pad_000[0x34];
	void* f034;
	char pad_038[0x38];
	void* f070;
	void* f074;
	void* f078;
	void* f07c;
	void* f080;
} VAL_OBJ;

extern int __cdecl m_is_tracked(void* p);
extern void __cdecl fcn_0042e220(void);

/* ADDRESS: GOLDTL 0x0042e260 */
void __cdecl fcn_0042e260(VAL_OBJ* o)
{
	void* p;

	if (o == 0) {
		return;
	}
	if (!m_is_tracked(o)) {
		fcn_0042e220();
		__asm { int 3 }
	}
	p = o->f034;
	if (p != 0 && !m_is_tracked(p)) {
		fcn_0042e220();
		__asm { int 3 }
	}
	if (o->f070 != 0 && (p = ((VAL_SUB*) o->f070)->f068) != 0 && !m_is_tracked(p)) {
		fcn_0042e220();
		__asm { int 3 }
	}
	if (o->f074 != 0 && (p = ((VAL_SUB*) o->f074)->f068) != 0 && !m_is_tracked(p)) {
		fcn_0042e220();
		__asm { int 3 }
	}
	p = o->f078;
	if (p != 0 && !m_is_tracked(p)) {
		fcn_0042e220();
		__asm { int 3 }
	}
	if (o->f07c != 0 && (p = ((VAL_SUB*) o->f07c)->f068) != 0 && !m_is_tracked(p)) {
		fcn_0042e220();
		__asm { int 3 }
	}
	p = o->f080;
	if (p != 0 && !m_is_tracked(p)) {
		fcn_0042e220();
		__asm { int 3 }
	}
}
