// FUNCTION: GOLDTL 0x0050d4f0
// SIZE: 62

int __cdecl fcn_005015e0(void**, void**, void**, int);

unsigned short __cdecl fcn_0050d4f0(short* entity)
{
	void* dynamic_ent;

	fcn_005015e0(&dynamic_ent, (void**) 0, (void**) &entity, *(int*) (entity + 5));
	if (entity != (short*) 0) {
		return *entity;
	}
	if (dynamic_ent != (void*) 0) {
		return *(unsigned short*) ((int) dynamic_ent + 0x25);
	}
	return (short) 0xffff;
}
