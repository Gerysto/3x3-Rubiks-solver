#ifndef _SOLVER_
#define _SOLVER_
#include <queue>
#include <set>
#include "state.hh"


class Solver {
    
    private:
    
    State state;

    
    
    public:

    Solver(State state);

    MoveSequence solve();
};

#endif