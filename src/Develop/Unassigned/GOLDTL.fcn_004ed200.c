


int __cdecl fcn_004ed240(void);
void __cdecl ahm_ResetAlchemyState(int);
int __cdecl fcn_004edae0(void);
int __cdecl fcn_004ed800(void);

int __cdecl fcn_004ed200(int a1)
{
	if (a1 != 0) {
		if (fcn_004ed240() != 0) {
			ahm_ResetAlchemyState(1);
			return fcn_004edae0();
		}
		return 0;
	}
	if (fcn_004ed800() != 0) {
		ahm_ResetAlchemyState(1);
	}
	return 1;
}
