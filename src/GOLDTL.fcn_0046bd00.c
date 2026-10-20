/* Forwarding thunk: the three incoming arguments are copied back into
 * their own stack homes and the body tail-jumps into fcn_00479e00. */

int __cdecl fcn_00479e00(int a, int b, int c);

/* ADDRESS: GOLDTL 0x0046bd00 */
int __cdecl fcn_0046bd00(int a, int b, int c)
{
	return fcn_00479e00(a, b, c);
}
