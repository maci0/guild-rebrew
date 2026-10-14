/* ADDRESS: GOLD 0x004acdc0 */
// fcn_004acdc0 — copy derefs of two globals. Reg-rotation: target p->eax/q->edx; local form scores 17/27.

void __cdecl fcn_004acdc0(void)
{
	int* p;
	int* q;
	p = *(int**) 0x600f48;
	q = *(int**) 0x600f4c;
	*(int*) 0x6f0714 = *p;
	*(int*) 0x6f071c = *q;
}
