#ifndef ERROR_H
#define ERROR_H

#include "../../game_common.h"

/* Error and Logging Functions */
extern void __cdecl DispatchLogOutput(int output_mask, char* msg);
extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern void __cdecl ReportFatalError(char* msg, ...);
extern void __cdecl ReportMessage(char* msg, ...);

/* Initialization */
extern int __cdecl InitializeLogAndErrorHandler(void);
extern void __cdecl ShutdownLogAndErrorHandler(void);

#endif /* ERROR_H */
