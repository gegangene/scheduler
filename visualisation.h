//
// Created by Bartłomiej Pruszczyk on 13/01/2024.
//

#ifndef OS_2_1_VISUALISATION_H
#define OS_2_1_VISUALISATION_H

// shows are there new processes gained in current tact
bool newComeVisualise(std::vector<int>[], int&);
// visualises work of algorithm based on given vector {id : tacts : arrivingTact} and result [float]
void visualisation(std::vector<int>[], float);
void visualisation(std::vector<int>[], float,std::vector<int>[]);
// performs "waiting" by counting from INT_MIN/(5*givenInt) to 0
void wait(int);

#endif //OS_2_1_VISUALISATION_H
