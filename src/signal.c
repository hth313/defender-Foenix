#include "signal.h"

signal_t signals;

// read signals, this also has the effect of resetting them
signal_t read_signals_safe () {
  ProtectStart();
  signal_t snapshot = signals;
  signals = 0;
  ProtectEnd();
  return snapshot;
}
