typedef int (__stdcall *DDSURFACE_GETDESC_FN)(void *, int *);

struct DDSURFACE_VTBL {
	char pad[0x58];
	DDSURFACE_GETDESC_FN fn;
};

struct DDSURFACE_OBJ {
	struct DDSURFACE_VTBL *vtbl;
};

int __cdecl d2_QuerySurfaceDesc(char *, int *);

/* ADDRESS: GOLD 0x00479110 */
int __cdecl d2_QuerySurfaceDesc(char *parent, int *out)
{
	struct DDSURFACE_OBJ *obj;
	int result;

	if (*(int *) (parent + 0x20) == 0)
		return 0;
	*out = 0x7c;
	obj = *(struct DDSURFACE_OBJ **) (parent + 0x20);
	result = obj->vtbl->fn(obj, out);
	return result == 0;
}
