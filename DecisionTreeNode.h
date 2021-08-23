/**
*Author:Turan Mert Duran
* ID: 21601418
* Section: 1
* Assignment: 2
*/
#pragma once

class DecisionTreeNode {

public:
    DecisionTreeNode();
    DecisionTreeNode* leftN;
    DecisionTreeNode* rightN;
    bool isLeaf;
    int featureId;
    int classId;
    bool* usedSamples;
    bool* usedSamplesL;
    int numFeatures;

};



