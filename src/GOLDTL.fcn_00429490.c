void __cdecl fcn_0064dfda(void* p);

/* ADDRESS: GOLDTL 0x00429490 */
int __cdecl fcn_00429490(char* a0)
{
	char* v1;
	int v3;
	int i;

	v1 = *(char**) (a0 + 0xc5c);
	*(char**) 0x6b7ebc = v1;
	*(int*) (a0 + 0xc5c) = 0;
	*(int*) (*(char**) 0x6b7e98 + 0xc60) = 0;
	switch (*(int*) (v1 + 0x20)) {
	case 0:
		v3 = ((int (__cdecl*) (void)) * (void**) (v1 + 0x44))();
		break;
	case 1:
		v3 = ((int (__cdecl*) (void*)) * (void**) (v1 + 0x44))(a0 + 0xc64);
		break;
	case 2:
		v3 = ((int (__cdecl*) (void*, void*)) * (void**) (v1 + 0x44))(a0 + 0xc64, a0 + 0xc68);
		break;
	case 3:
		v3 = ((int (__cdecl*) (void*, void*, void*)) * (void**) (v1 + 0x44))(a0 + 0xc64, a0 + 0xc68, a0 + 0xc6c);
		break;
	case 4:
		v3 = ((int (__cdecl*) (void*, void*, void*, void*)) * (void**) (v1 + 0x44))(a0 + 0xc64, a0 + 0xc68, a0 + 0xc6c, a0 + 0xc70);
		break;
	case 5:
		v3 = ((int (__cdecl*) (void*, void*, void*, void*, void*)) * (void**) (v1 + 0x44))(a0 + 0xc64, a0 + 0xc68, a0 + 0xc6c, a0 + 0xc70, a0 + 0xc74);
		break;
	case 6:
		v3 = ((int (__cdecl*) (void*, void*, void*, void*, void*, void*)) * (void**) (v1 + 0x44))(a0 + 0xc64, a0 + 0xc68, a0 + 0xc6c, a0 + 0xc70, a0 + 0xc74, a0 + 0xc78);
		break;
	case 7:
		v3 = ((int (__cdecl*) (void*, void*, void*, void*, void*, void*, void*)) * (void**) (v1 + 0x44))(a0 + 0xc64, a0 + 0xc68, a0 + 0xc6c, a0 + 0xc70, a0 + 0xc74, a0 + 0xc78, a0 + 0xc7c);
		break;
	default:
		goto done;
	}
done:
	if (*(int*) (a0 + 0xc60) == 0) {
		*(int*) (a0 + 0xc5c) = 0;
		*(int*) 0x6b7ebc = 0;
		for (i = 0; i < *(int*) (v1 + 0x20); i++) {
			if (*(int*) (v1 + 0x24 + i * 4) == 6) {
				fcn_0064dfda(*(void**) (a0 + 0xc64 + i * 4));
			}
			*(int*) (a0 + 0xc64 + i * 4) = 0;
		}
	} else {
		*(char**) (a0 + 0xc5c) = v1;
	}
	*(int*) 0x6b7ebc = 0;
	return v3;
}
