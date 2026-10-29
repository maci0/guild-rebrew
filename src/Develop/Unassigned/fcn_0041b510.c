typedef void* Obj41b510;

/* ADDRESS: GOLDTL 0x0041b510 */
void __cdecl fcn_0041b510(int a1, int a2, int a3, int a4, int a5, int a6)
{
	int vp[4];
	unsigned int packed;
	Obj41b510 obj;
	void** vtbl;
	int t860;
	int t864;

	if (*(Obj41b510*) 0x6b5de4 == 0) {
		return;
	}
	vp[0] = a1;
	vp[1] = a2;
	t860 = *(int*) 0x14ce860 - 1;
	t864 = *(int*) 0x14ce864 - 1;
	vp[3] = t864;
	vp[2] = t860;
	obj = *(Obj41b510*) 0x6b5de0;
	vtbl = *(void***) obj;
	((void (__stdcall*) (Obj41b510)) vtbl[0x88 / 4])(obj);
	packed = (unsigned int) (unsigned char) a4 | 0xffffff00;
	packed <<= 8;
	packed |= (unsigned int) (a5 & 0xff);
	packed <<= 8;
	packed |= (unsigned int) (a6 & 0xff);
	obj = *(Obj41b510*) 0x6b5de4;
	vtbl = *(void***) obj;
	((void (__stdcall*) (Obj41b510, int, int, int*, int, unsigned int)) vtbl[0x18 / 4])(obj, a3, -1, vp, 0x20, packed);
	obj = *(Obj41b510*) 0x6b5de0;
	vtbl = *(void***) obj;
	((void (__stdcall*) (Obj41b510)) vtbl[0x8c / 4])(obj);
}
