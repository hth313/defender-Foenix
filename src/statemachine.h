#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include <stdint.h>
#include "event.h"

#ifndef MaxStateMachine
#define MaxStateMachine 32
#endif

struct SM;

// A state is a function that gets and event with associated
// data and the state machine itself which can be altered depending
// on the internal transition.
typedef void (*state_t)(event_t*, struct SM*);

// A state machine. A typical implementation use this the first element
// in its state structure.
typedef struct SM {
  state_t state;       // the current state, 0 means ended
  event_class_mask_t event_class_mask;
      // Event classes it may react on. Set to zero to disable the
      // state machine.
} SM_t;

// Pointers to state machines. A null pointer means that there is
// nothing there. It is assumed that the there are no gaps, if you
// physically delete a state machine from the list, then the list
// needs to be compacted.
// You can disable a statemachine in an efficient way by setting the
// .event_class_mask to 0, while allowing it to keep its place in
// list.
extern SM_t *sm[MaxStateMachine];



#endif // __STATE_MACHINE_H__
