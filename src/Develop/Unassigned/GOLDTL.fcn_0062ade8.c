/* Native body is size-optimized code (direct memory pushes, "cmp [m],0"
 * and "and [m],0"), so this definition carries the matching codegen pragma. */
typedef struct TBL_62ade8 {
	char pad[0xd8];
	void *fn0;
} TBL_62ade8;

typedef struct TBL2_62ade8 {
	char pad[0x18];
	void *fn0;
	void *fn4;
} TBL2_62ade8;

typedef struct OBJ_62ade8 {
	char pad4[4];
	void **p1;
	char pad8[4];
	void **p2;
	char pad3[0x50];
	int f60;
	int f64;
} OBJ_62ade8;

#pragma optimize("s", on)

/* ADDRESS: GOLDTL 0x0062ade8 */
int __fastcall fcn_0062ade8(void *self)
{
	OBJ_62ade8 *o;
	void **p;

	o = (OBJ_62ade8 *)self;
	if (o->f60 == 0)
		return (int)0x8876086c;
	p = o->p1;
	((void (__stdcall *)(void *, int))((TBL_62ade8 *)p[0])->fn0)(p, o->f64);
	p = o->p2;
	((void (__stdcall *)(void *))((TBL2_62ade8 *)p[0])->fn4)(p);
	o->f60 = 0;
	return 0;
}
