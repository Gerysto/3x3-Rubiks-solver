#include "../headers/cube.hh"
#include <algorithm>

Cube::Cube(){
    this->state = State();
    this->orientation = Orientation();
}

Cube::Cube(State state, Orientation orientation){
    this->state = state;
    this->orientation = orientation;
}

void Cube::execute_sequence(MoveSequence move_sequence) {
    cout << move_sequence.to_notation(orientation) << endl;
    state.execute_sequence(move_sequence);
}

void Cube::execute_sequence_in_notation(string seq) {
    Orientation copy = orientation;
    MoveSequence my_sequence = MoveSequence(copy, seq);
    cout << my_sequence.to_notation(orientation) << endl;
    orientation = copy;
    my_sequence.print();
    state.execute_sequence(my_sequence);
}

void Cube::random_scramble(int length) {
    MoveSequence rand = MoveSequence();
    rand.generate_random(length);
    cout << rand.to_notation(orientation) << endl;

    state.execute_sequence(rand);
}

bool Cube::is_solvable() {
    return state.is_solvable();
}

void Cube::print_state() const {
    state.display();
}

bool cmp(MoveSequence m1, MoveSequence m2) {
    return m1.size() < m2.size();
}

MoveSequence Cube::test_solver(int i) {
    Solver my_solver = Solver(this->state);

    

    return my_solver.test(0, 2, 4);
    
    /*// Generate all the possible cycles of 3 objects:
    vector<vector<int>> all_cycles = vector<vector<int>>(0,vector<int>(3));
    for (int i = 0; i < 24; ++i) {
        for (int j = i; j < 24; ++j) {
            for (int k = j; k < 24; ++k) {
                if(i/2 == j/2 or i/2 == k/2 or j/2 == k/2) {
                    continue;
                }
                vector<int> cycle = {i, j, k};

                sort(cycle.begin(), cycle.end());
                
                all_cycles.push_back(cycle);
            }
        }
    }

    for (int i = 0; i < all_cycles.size(); ++i) {
        vector<int> c = all_cycles[i];
        vector<MoveSequence> seqs = {
            my_solver.test(c[0], c[1], c[2]),
            my_solver.test(c[1], c[2], c[0]),
            my_solver.test(c[2], c[0], c[1]),
            
            // my_solver.test(c[0], c[2], c[1]),
            // my_solver.test(c[1], c[0], c[2]),
            // my_solver.test(c[2], c[1], c[0]),
            
        };
        
        MoveSequence shortest = *min_element(seqs.begin(), seqs.end(), cmp);
        cout << c[0] << "-" << c[1] << "-" << c[2] << " Cycle: ";

        cout << shortest.to_notation(orientation) << endl;
        len_sum += shortest.size();
    }
    std::cout << "Average move count: " << double(len_sum)/all_cycles.size();
    return MoveSequence();*/
}