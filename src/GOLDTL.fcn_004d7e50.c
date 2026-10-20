/* Build the two dialog windows for the current city record and initialize
 * their screen offsets. */

int __cdecl fcn_00470820(int, int, int);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00468df0(int, int, int, unsigned int, unsigned int);
void __cdecl fcn_00469090(int);
int __cdecl fcn_004677e0(int, int, int, int, unsigned int, int, int,
                        unsigned int);
void __cdecl fcn_00519190(int);
void __cdecl fcn_004d0ec0(void);
void __cdecl fcn_004d0c70(void);

/* ADDRESS: GOLDTL 0x004d7e50 */
void __cdecl fcn_004d7e50(void)
{
	int v1;

	v1 = fcn_00470820(0, 0, 0x68bed0);
	*(unsigned int*) 0x772f14 = v1;
	fcn_00471d80(v1, 3);
	fcn_004727a0(v1, 0);
	*(unsigned int*) 0x68b7a8 = fcn_00468df0(0x10, 0xc, 0xbf,
	                                         *(unsigned int*) 0x14a9a14,
	                                         *(unsigned int*) 0x772514);
	*(unsigned int*) (*(unsigned int*) 0x1015ea0 +
	                  *(unsigned int*) 0x68b7a8 * 0x2f4 + 0x6c) = 1;
	fcn_00469090(*(unsigned int*) 0x68b7a8);
	*(unsigned int*) 0x68b7a4 = fcn_004677e0(
	    (*(int*) (*(unsigned int*) 0x77255c + 0xc) - 0x190) / 2, 0x37, 0x190, 0,
	    *(unsigned int*) 0x68bfbc, 0x83, 0x42, *(unsigned int*) 0x772514);
	*(unsigned int*) (*(unsigned int*) 0x1015ea0 +
	                  *(unsigned int*) 0x68b7a4 * 0x2f4 + 0x84) = 0x54;
	*(unsigned int*) (*(unsigned int*) 0x1015ea0 +
	                  *(int*) (*(unsigned int*) 0x772514 * 0x3cc + 0x10161bc) *
	                      0x2f4 +
	                  0x5c) = 1;
	fcn_004727a0(*(unsigned int*) 0x68bfc0, 0);
	fcn_00519190(0x6811b0);
	fcn_004d0ec0();
	fcn_004d0c70();
}
