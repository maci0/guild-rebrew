


int __cdecl fcn_004ed240(void);
void __cdecl fcn_004ecaa0(int);
int __cdecl fcn_004edae0(void);
int __cdecl fcn_004ed800(void);

int __cdecl fcn_004ed200(int a1)
{
	if (a1 != 0) {
		if (fcn_004ed240() != 0) {
			fcn_004ecaa0(1);
			return fcn_004edae0();
		}
		return 0;
	}
	if (fcn_004ed800() != 0) {
		fcn_004ecaa0(1);
	}
	return 1;
}
