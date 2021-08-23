/**
*Author:Turan Mert Duran
* ID: 21601418
* Section: 1
* Assignment: 2
*/
#pragma once
#include "DecisionTreeNode.h"
using namespace std;
#include <iostream>
#include <cstring>
class DecisionTree {
public:

    DecisionTree();
    DecisionTreeNode* root;
    double calculateEntropy(const int* classCounts, const int numClasses);

    double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId);
    
    int bestFeature(const bool** data, const int* labels, const int numSamples, const int numFeatures, bool* useSamples);
    
    int classFinder( bool* useSamples, const int* labels, int numFeatures);

    void recursionTrain(const bool** data, const int* labels, DecisionTreeNode* cur, bool* usedSamples, const int numSamples, int numFeatures, int featureId);

    void train(const bool** data, const int* labels, const int numSamples, const int numFeatures);

    bool leafOrNode(const int* labels, const int numSamples, bool* usedSamples);

    int predict(const bool* data);

    double test(const bool** data, const int* labels, const int numSamples);

    void printPreorder(DecisionTreeNode* cur, int& i);

    void print();

    void train(const string txtLocation, const int numSamples, const int numFeatures);
    
};



