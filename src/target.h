#ifndef __TARGET_H__
#define __TARGET_H__

#ifdef __CALYPSI_TARGET_65816__
#include "intrinsics65816.h"
#endif

#if defined(__CALYPSI_TARGET_65816__)
#define ProtectStart()  __interrupt_state_t _st_ = __get_interrupt_state(); \
                        __disable_interrupts();
#define ProtectEnd()    __restore_interrupt_state(_st_);


#endif

#endif // __TARGET_H__
