typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

enum {
  TD_LEFT_BRACKET,
  TD_RIGHT_BRACKET,
  TD_QUOTE,
  TD_SLASH_PIPE,
  TD_LAYER,
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void change_layer_finished (qk_tap_dance_state_t *state, void *user_data);
void change_layer_reset (qk_tap_dance_state_t *state, void *user_data);

void td_left_bracket(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1){
        SEND_STRING("(");
    } else if (state->count == 2){
        SEND_STRING("{");
    } else if (state->count == 3){
        SEND_STRING("[");
        reset_tap_dance (state);
    }
}

void td_right_bracket(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1){
        SEND_STRING(")");
    } else if (state->count == 2){
        SEND_STRING("}");
    } else if (state->count == 3){
        SEND_STRING("]");
        reset_tap_dance (state);
    }
}

void td_quote(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1){
        SEND_STRING("'");
    } else if (state->count == 2){
        SEND_STRING("\"");
        reset_tap_dance (state);
    }
}

void td_slash_pipe(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1){
        SEND_STRING("\\");
    } else if (state->count == 2){
        SEND_STRING("|");
        reset_tap_dance (state);
    }
}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap change_layer_tap_state = {
  .is_press_action = true,
  .state = 0
};

void change_layer_finished (qk_tap_dance_state_t *state, void *user_data) {
  change_layer_tap_state.state = cur_dance(state);
  switch (change_layer_tap_state.state) {
    case SINGLE_TAP: register_code(KC_SPC); break;
    case SINGLE_HOLD: layer_on(3); break;
    case DOUBLE_HOLD: layer_on(1); break;
    default:
      for (uint8_t i = 0; i < state->count; i++) {
          register_code(KC_SPC);
          unregister_code(KC_SPC);
      }
      break;
  }
}

void change_layer_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (change_layer_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_SPC); break;
    case SINGLE_HOLD: layer_off(3); break;
    case DOUBLE_HOLD: layer_off(1); break;
  }
  change_layer_tap_state.state = 0;
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LEFT_BRACKET] = ACTION_TAP_DANCE_FN (td_left_bracket),
  [TD_RIGHT_BRACKET] = ACTION_TAP_DANCE_FN (td_right_bracket),
  [TD_QUOTE] = ACTION_TAP_DANCE_FN (td_quote),
  [TD_SLASH_PIPE] = ACTION_TAP_DANCE_FN (td_slash_pipe),
  [TD_LAYER]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, change_layer_finished , change_layer_reset)
};
