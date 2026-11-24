
/* fcn_005e3a57 - if(--a[1] < 0) return fcn_005e5990(a); return (unsigned char)*(*a)++; */

int __cdecl fcn_005e5990(void*);

int __cdecl fcn_005e3a57(void* a)
{
	unsigned int c;

	if (--*(int*) ((char*) a + 4) >= 0) {
		c = *(*(unsigned char**) a)++;
		return (int) c;
	}
	return fcn_005e5990(a);
}
