
// fcn_004bf410 — clear slot a: free + reset.

int __cdecl fcn_0046e700(int);

void __cdecl fcn_004bf410(int a)
{
	fcn_0046e700(*(int*) (0xf812a0 + a * 8));
	*(int*) (0xf812a0 + a * 8) = 0xffffffff;
	*(int*) (0xf812a4 + a * 8) = 0;
}
