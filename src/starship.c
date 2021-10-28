#include "statemachine.h"

typedef struct starship {
  SM_t sm;    // keep state machine internally
  unsigned smart_bombs;
  unsigned damage;
} starship_t;

// The actual starship, we have one of these.
starship_t starship;

static void moving (event_t event, void *data, SM_t *sm) {

}

void initialState () {
}

// Create a new starship.
SM_t *starshipInitialState () {
  starship = (starship_t) {
    .sm = { .state = initialState,
    },
    .smart_bombs = 5
  };
  return &starship.sm;
}
