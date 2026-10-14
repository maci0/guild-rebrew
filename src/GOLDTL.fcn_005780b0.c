


int __cdecl fcn_00545580(int, void (__cdecl*)(void), void (__cdecl*)(void));
int __cdecl fcn_00530ab0(int, char*, int, int, int);
void __cdecl fcn_00578380(void);
void __cdecl fcn_005784d0(void);
void __cdecl fcn_00578860(void);
void __cdecl fcn_00578a10(void);
void __cdecl fcn_00579690(void);
void __cdecl fcn_005797a0(void);
void __cdecl fcn_00579cf0(void);
void __cdecl fcn_00579de0(void);
void __cdecl fcn_00578e10(void);
void __cdecl fcn_00578ed0(void);
void __cdecl fcn_00579320(void);
void __cdecl fcn_00579460(void);
void __cdecl fcn_0057a130(void);
void __cdecl fcn_0057a180(void);
void __cdecl fcn_0057a260(void);
void __cdecl fcn_0057a3d0(void);
void __cdecl fcn_0057a700(void);
void __cdecl fcn_0057ad50(void);
void __cdecl fcn_0057ae40(void);
void __cdecl fcn_0057ae50(void);
void __cdecl fcn_0057b330(void);
void __cdecl fcn_0057b390(void);
void __cdecl fcn_0057b770(void);
void __cdecl fcn_0057b7a0(void);
void __cdecl fcn_0057b000(void);
void __cdecl fcn_0057b1f0(void);

int __cdecl fcn_005780b0(void)
{
	if (fcn_00545580(0x88, fcn_00578380, fcn_005784d0) || fcn_00545580(0x89, fcn_00578860, fcn_00578a10)
	    || fcn_00545580(0x8c, fcn_00579690, fcn_005797a0) || fcn_00545580(0x8d, fcn_00579cf0, fcn_00579de0)
	    || fcn_00545580(0x8a, fcn_00578e10, fcn_00578ed0) || fcn_00545580(0x8b, fcn_00579320, fcn_00579460)
	    || fcn_00545580(0x8d, fcn_00579cf0, fcn_00579de0) || fcn_00545580(0x8e, fcn_0057a130, fcn_0057a180)
	    || fcn_00545580(0x8f, fcn_0057a260, fcn_0057a3d0) || fcn_00545580(0x90, fcn_0057a700, fcn_0057ad50)
	    || fcn_00545580(0x91, fcn_0057ae40, fcn_0057ae50) || fcn_00545580(0x93, fcn_0057b330, fcn_0057b390)
	    || fcn_00545580(0x94, fcn_0057b770, fcn_0057b7a0) || fcn_00545580(0x92, fcn_0057b000, fcn_0057b1f0)) {
		return 1;
	}
	fcn_00530ab0(0x8d, "grabpflege", 1, 0x513, -1);
	fcn_00530ab0(0x8c, "Rohstoffsuchen", 1, 0x500, 0xac);
	fcn_00530ab0(0x8f, "Upgraden", 0, 0x512, -1);
	fcn_00530ab0(0x8a, 0, 0, 0x514, -1);
	fcn_00530ab0(0x88, 0, 0, 0x511, -1);
	return 0;
}
