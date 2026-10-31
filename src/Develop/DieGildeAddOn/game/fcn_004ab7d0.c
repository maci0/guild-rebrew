void *__cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_00507e70(int, int, int);
int __cdecl _ftol(void);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_005b2a40(void *, int, int *);

/* ADDRESS: GOLDTL 0x004ab7d0 */
int __cdecl fcn_004ab7d0(int a1, char *a2, char *a3)
{
	int h;
	void *p;
	int arr[4];
	int n;
	int i;

	h = *(int *) (a2 + 0x10);
	if (a3 == 0 || a1 == 0)
		return 0;
	p = gm_LookupEntityRecordById(*(int *) (a2 + 4));
	if (p == 0)
		return 0;
	arr[0] = (int) gm_LookupEntityRecordById(*(int *) (a2 + 0xc));
	if (arr[0] == 0)
		return 0;
	n = 1;
	arr[1] = (int) gm_LookupEntityRecordById(*(int *) (a2 + 8));
	if (arr[1] == 0)
		n = 2;
	arr[n] = (int) gm_LookupEntityRecordById(*(int *) (a3 + 0xc));
	if (arr[n] == 0)
		n++;
	arr[n] = (int) gm_LookupEntityRecordById(*(int *) (a3 + 8));
	if (arr[n] == 0)
		n++;
	fcn_005100f0(*(int *) (a1 + 4), -h);
	fcn_004c5420(*(int *) (a1 + 4), 0x1cc, 4, 8, 0);
	for (i = 0; i < n; i++) {
		fcn_00507e70(a1, arr[i], 4);
		fcn_004c54c0(*(unsigned short *) p, *(unsigned short *) arr[i], -(0x32 - _ftol()), 1);
	}
	fcn_005b2a40(p, n, arr);
	return 0x44;
}
