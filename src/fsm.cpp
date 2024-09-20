#include "fsm.h"


StatusStateMachine::StatusStateMachine() {
    State idle("idle");
    State operational("operational");
    State fault("fault");
    State reset("reset");

    idle.transitionTo = [] (State& s) {
        return "";
    };
    operational.transitionTo = [&](State& s) {
        if(s == fault) {
            return "recovering";
        }
        return "";
    };
    fault.transitionTo = [&] (State& s) {
        if(s == operational) {
            return "recovered";
        } else if (s == reset) {
            return "reset_start";
        } else if (s == fault) {
            return "fault";
        }
        return "";
    };
    reset.transitionTo = [&] (State& s) {
        if(s == reset) {
            return "reset_start";
        } else if (s == operational) {
            return "reset_done";
        }
        return "";
    };

}

int StatusStateMachine::iterate() {
    // newState = get new state
    // if(newState == currentState) {
    //     return Transitions::none;
    // }

    // currentState.transition(newState);

    // currentState = newState

    return 0;
}
