#pragma once
#include <vector>
#include <map>
#include <string>
#include <functional>

class State {
public:
    std::string name;
    // void addPossible(State& p);
    // void transition(State& newState);
    std::function<std::string(State& s)> transitionTo;
    State(std::string id) : name(id) {}
    bool operator==(State& other) {
        if (name == other.name) {
            return true;
        }
        return false;
    }
    State() : name("") {}
    ~State() {}
};

class StatusStateMachine {
public:
    // enum StateName {idle, operational, fault, reset};

    State currentState;
    State newState;
    int recoveryCounter = 0;
    int recoveryCounterMax;

    // std::vector<State&> states;

    /*  Do an iteration - transition
     *  Poll new state
     *  if new state == current state - no transition
     *  if new state != current state - figure out transition
     *  return transition (possibly event)
     */
    int iterate();

    StatusStateMachine();
    ~StatusStateMachine() {};
};
