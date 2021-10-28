#ifndef __EVENT_H__
#define __EVENT_H__

#include "signal.h"

#define EventQueueSize 16

// Event numbers.
typedef enum event_ident {
  EventSignal,        // This event is actually signals
  EventFrameTick,
  EventFireButton,
  EventUpPress,
  EventDownPress,
  EventLeftPress,
  EventRightPress,
  EventUpRelease,
  EventDownRelease,
  EventLeftRelease,
  EventRightRelease,
} event_ident_t;

// Summary of event classes, used to speed up dispatching.
typedef enum event_class {
  EventClassSignal = 1,        // I react to signals
  EventClassTime = 2,          // I want to know about some time related event
  EventClassGamePad = 4,       // I react to a game pad
  EventClassCollision = 8,     // Let me know if some collision occured
} event_class_t;

typedef uint16_t event_class_mask_t;

// An event which optionally can have arguments tied to it.
typedef struct event {
  event_ident_t event;
  event_class_t event_class;
  union {
    signal_t event_signals;   // EventSignal
  };
} event_t;

#endif // __EVENT_H__
