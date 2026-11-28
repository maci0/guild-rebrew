/* Forced include of the German server target only (server_de.dll, /FI; docs/de/decisions.md D14).
 *
 * The German server.dll is a build with diagnostic logging compiled out: it contains none of the
 * message literals the English server passes to LogMessageInternal and no call to it, while
 * argument work with side effects (sprintf into a message buffer) is still there. Calls therefore
 * go to an empty function that the optimizer removes together with its constant arguments. The
 * stub uses the signature of error.h; the slightly different local prototypes in some sources only
 * draw C type warnings. */
#ifndef SERVERDE_BUILD_H
#define SERVERDE_BUILD_H

static __inline void __cdecl srv_LogCompiledOut(char* file, unsigned int line, char* msg, int level)
{
}

#define LogMessageInternal srv_LogCompiledOut

#endif
