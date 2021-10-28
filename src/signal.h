#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#include <stdint.h>
#include "target.h"

// A signal is a bit in a mask
#if SIGNAL_WIDTH == 32
typedef uint32_t signal_t;
#elif SIGNAL_WIDTH == 64
typedef uint64_t signal_t;
#else
typedef uint16_t signal_t;
#endif

extern signal_t read_signals_safe ();

// The global signals, activated signals are set here, but use
// the appropriate function to do it.
extern signal_t signals;

// set signals, this can be used from interrupts
inline void set_signals_safe (signal_t mask) {
  signals |= mask;
}

// set signals, this should be used from ordinary code
inline void set_signals (signal_t mask) {
  ProtectStart();
  set_signals_safe(mask);
  ProtectEnd();
}

#endif // __SIGNAL_H__
