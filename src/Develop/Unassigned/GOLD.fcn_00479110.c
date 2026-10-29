typedef int (__stdcall *fcn_00479110_f)(void *, int *);

struct fcn_00479110_vt {
	char pad[0x58];
	fcn_00479110_f fn;
};

struct fcn_00479110_obj {
	struct fcn_00479110_vt *vtbl;
};

int __cdecl fcn_00479110(char *, int *);

/* ADDRESS: GOLD 0x00479110 */
int __cdecl fcn_00479110(char *parent, int *out)
{
	struct fcn_00479110_obj *obj;
	int result;

	if (*(int *) (parent + 0x20) == 0)
		return 0;
	*out = 0x7c;
	obj = *(struct fcn_00479110_obj **) (parent + 0x20);
	result = obj->vtbl->fn(obj, out);
	return result == 0;
}
