#include <math.h>       /* log */
#include <iostream>
#include "DecisionTree.h"
/**
*Author:Turan Mert Duran
* ID: 21601418
* Section: 1
* Assignment: 2
*/
using namespace std;

int main(int argc, const char* argv[]) {

    DecisionTree* a;
    a = new DecisionTree();
    // a->train("C:\Users\Turan\Desktop\Yeni klasör(2)\test_data.txt", 473, 44);
    bool** data = new bool* [25];
    for (int i = 0; i < 25; i++) {
        data[i] = new bool[25];
    }
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            if (i % 2 == 0) {
                data[i][j] = true;
            }
            else {
                data[i][j] = false;
            }
        }
    }
    int* labels = new int[25];
    for (int i = 0; i < 25; i++)
        labels[i] = (i / 3) + 1;

    a->train((const bool**)data, labels, 25, 25);

    std::cout << a->root->featureId;

    //std::cout << // a->root->rightN->featureId;
    //cout << a->root->leftN->featureId;
    std::cout << a->root->classId;

    return 0;

}

