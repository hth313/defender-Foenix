#include "statemachine.h"
#include "event.h"
#include "signal.h"


event_t event_queue[EventQueueSize];

unsigned eventWriteIndex;
unsigned eventReadIndex;

inline unsigned advance_event_queue (unsigned i) {
  i = i + 1;
  if (i == EventQueueSize) {
    i = 0;
  }
  return i;
}

SM_t *state_machine[MaxStateMachine];

// Step the state machine
void step () {
  // Process all active signals, reset and repeat until no more
  // signals are active.
  signal_t active_signals;
start:
  while ((active_signals = read_signals_safe())) {
    SM_t **psm = &state_machine[0];
    event_t signal_event = (event_t) {
      .event = EventSignal,
      .event_signals = active_signals
    };
    SM_t *sm;
    while ((sm = *psm)) {
      if ((EventClassSignal & sm->event_class_mask) != 0) {
        sm->state(&signal_event, sm);
      }
      psm++;
    }

    // Process one event from the event queue.
    if (eventReadIndex != eventWriteIndex) {
      event_t* event = &event_queue[eventReadIndex];
      eventReadIndex = advance_event_queue(eventReadIndex);
      event_class_t ec = event->event_class;
      SM_t **psm = &state_machine[0];
      SM_t *sm;
      while ((sm = *psm)) {
        if ((ec & sm->event_class_mask) != 0) {
          sm->state(event, sm);
        }
        psm++;
      }
      goto start;
    }
  }
}
