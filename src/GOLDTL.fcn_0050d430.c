// FUNCTION: GOLD 0x00509ff0
// SIZE: 82
// FUNCTION: GOLDTL 0x0050d430
// SIZE: 82

extern char g_7f4ca0[];

int __cdecl fcn_005015e0(void**, void**, void**, int);

short* __cdecl fcn_0050d430(short* entity)
{
	void* dynamic_ent;

	fcn_005015e0(&dynamic_ent, (void**) 0, (void**) &entity, *(int*) (entity + 5));
	if (entity == (short*) 0) {
		if (dynamic_ent != (void*) 0 && *(unsigned short*) ((int) dynamic_ent + 0x25) != 0xffff) {
			return (short*) ((char*) g_7f4ca0 +
			    (unsigned int) *(unsigned short*) ((int) dynamic_ent + 0x25) * 0x21c);
		}
		entity = (short*) 0;
	}
	return entity;
}
