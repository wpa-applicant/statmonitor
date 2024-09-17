#include <vector>

class State {
public:
    std::vector<State&> possibles;
    void addPossible(State& p);

    State() {}
    State(std::vector<State&> possible) : possibles(possible) {}
};

void State::addPossible(State& p) {
    possibles.push_back(p);
}


class StatusStateMachine {
public:
    // enum StateName {idle, operational, fault, reset};

    State oldState;
    State newState;

    std::vector<State&> states;

    /*  Do an iteration
     *  Poll new state
     *  if new state == old state - no transition
     *  if new state != old state - figure out transition
     *  return transition
     */
    int iterate();

    StatusStateMachine();
    ~StatusStateMachine();
};


StatusStateMachine::StatusStateMachine() {
    State idle, operational, fault, reset;

    idle.addPossible(operational);

    operational.addPossible(operational);
    operational.addPossible(fault);

    fault.addPossible(fault);
    fault.addPossible(reset);

    reset.addPossible(reset);
    reset.addPossible(operational);
}

int StatusStateMachine::iterate() {
    // newState = get new state
    // if(newState == oldState) {
    //     return Transitions::none;
    // }


    // oldState = newState
}
