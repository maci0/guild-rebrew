#ifndef G_1552000_H
#define G_1552000_H

/* sockaddr_in layout; GOLDTL 0x1552000 is the UDP broadcast destination,
 * 0x1552010 the bound local address. */
struct sin_402220 {
	short family;
	unsigned short port;
	unsigned long addr;
	char zero[8];
};

#endif
