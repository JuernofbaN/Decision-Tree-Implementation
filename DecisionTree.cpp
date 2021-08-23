/**
*Author:Turan Mert Duran
* ID: 21601418
* Section: 1
* Assignment: 2
*/
#include "DecisionTree.h"
#include "DecisionTreeNode.h"
#include <math.h>       /* log */
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
DecisionTree::DecisionTree() {
    root = NULL;
}
double DecisionTree::calculateEntropy(const int* classCounts, const int numClasses)
{
    double sum = 0;
    double InternalSUM = 0;
    for (int i = 0; i < numClasses; i++)
        sum += classCounts[i];

    for (int i = 0; i < numClasses; i++)
    {
        if (classCounts[i] != 0) {
            double tool = classCounts[i] / sum;
            InternalSUM = InternalSUM + (log2(tool) * tool);
        }
    }
    return -InternalSUM;
}
double DecisionTree::calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId) {
    int classSize;
    double numberOfFalses ;
    double numberOfTrues;
    double pLeftChild;
    double pRightChild;
    numberOfFalses = 0;
    numberOfTrues = 0;
    classSize = 0;
    pLeftChild = 0;
    pRightChild = 0;
    for (int i = 0; i < numSamples; i++) {
        if (usedSamples[i] == true) {
            classSize = labels[i];
            if (data[i][featureId] == true) {
                numberOfTrues++;
            }
            else {
                numberOfFalses++;
            }
        }
    }
    int* sizeOfLeft;
    sizeOfLeft = new int[classSize];
    int* currentClassCounts;
    currentClassCounts = new int[classSize];
    int* sizeOfRight;
    sizeOfRight = new int[classSize];
    pLeftChild = numberOfFalses / (numberOfTrues + numberOfFalses);
    pRightChild = numberOfTrues / (numberOfTrues + numberOfFalses);
    for (int i = 0; i < numSamples; i++) {
        if (usedSamples[i] == 1) {
            currentClassCounts[labels[i] - 1] = currentClassCounts[labels[i] - 1] +1 ;
            if (data[i][featureId] == 1) {
                sizeOfRight[labels[i] - 1] = sizeOfRight[labels[i] - 1] + 1;
            }
            else {
                sizeOfLeft[labels[i] - 1]  = sizeOfLeft[labels[i] - 1] + 1;
            }
        }
    }
    double hLeft=pLeftChild* calculateEntropy(sizeOfLeft, classSize);
    double hRight = pRightChild * calculateEntropy(sizeOfRight, classSize);
    double Hp = calculateEntropy(currentClassCounts, classSize);
    return Hp - (hLeft + hRight);
}
int DecisionTree::bestFeature(const bool** data, const int* labels, const int numSamples, const int numFeatures, bool* useSamples)
{
    int bestFeatureId = -1;
    double temp = 0;
    double testId = 0;
    for (int i = 0; i < numFeatures; i++) {
        testId = calculateInformationGain(data, labels, numSamples, numFeatures, useSamples, i);
   
        if (temp < testId) {
            bestFeatureId = i;
        }
    }
    return bestFeatureId;
}
int DecisionTree::classFinder( bool* usedSamples, const int* labels, int numSamples) {
    for (int i = 0; i < numSamples; i++) {
        if (usedSamples[i] == true)
            return labels[i];
    }
    return 0;
}
void usedSamplesChangerForLeft(const bool** data, const int* labels, const int numSamples, const int numFeatures, bool* usedSamples, int featureId) {
    for (int i = 0; i < numSamples; i++) {
        if (data[i][featureId] == true) {
            usedSamples[i] = false;
        }
    }
}
void usedSamplesChanger(const bool** data, const int* labels, const int numSamples, const int numFeatures, bool* usedSamples, int featureId ) {
    for (int i = 0; i < numSamples; i++) {
        if (data[i][featureId] == false) {
            usedSamples[i] = false;
       }
    }
}
void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures)
{
    root = new DecisionTreeNode;
    root->usedSamplesL = new bool[numSamples];
    root->usedSamples = new bool[numSamples];
    for (int j = 0; j < numSamples; j++) {
        root->usedSamples[j] = true;
        root->usedSamplesL[j] = true;
    }
    int bestF = bestFeature(data, labels, numSamples, numFeatures, root->usedSamples);
    root->featureId = bestF;
    root->isLeaf = false;
    root->numFeatures = numFeatures;
    usedSamplesChanger(data, labels, numSamples, numFeatures, root->usedSamples, bestF);
    usedSamplesChangerForLeft(data, labels, numSamples, numFeatures, root->usedSamplesL, bestF);
    DecisionTreeNode* cur;
    cur = root;
    recursionTrain(data, labels, cur->leftN, cur->usedSamplesL, numSamples, numFeatures, bestF);
    recursionTrain(data, labels, cur->rightN, cur->usedSamples, numSamples, numFeatures, bestF);
}
void DecisionTree::recursionTrain(const bool** data, const int* labels, DecisionTreeNode* node, bool* usedSamples, const int numSamples, int numFeatures, int featureId) {
    node = new DecisionTreeNode;
    node->usedSamples = new bool[numSamples];
    node->usedSamplesL = new bool[numSamples];
    for (int j = 0; j <= numSamples - 1; j++) {
        node->usedSamples[j] = usedSamples[j];
        node->usedSamplesL[j] = usedSamples[j];
    }
    int bestFeatureId = bestFeature(data, labels, numSamples, numFeatures, usedSamples);

    usedSamplesChangerForLeft(data, labels, numSamples, numFeatures, node->usedSamplesL, bestFeatureId);
    usedSamplesChanger(data, labels, numSamples, numFeatures, node->usedSamples, bestFeatureId);
    if ( (leafOrNode(labels, numSamples, node->usedSamples) == true) || bestFeatureId == -1) // It is leaf then true
    {
        node->isLeaf = true; // It has been checked and it is leaf.
        node->classId = classFinder(usedSamples, labels, numFeatures); // Giving accurate class name to leaf
        return;
    }
    else
    {
        node->isLeaf = false;
        node->featureId = bestFeatureId;
        recursionTrain(data, labels, node->leftN, node->usedSamplesL, numSamples, numFeatures, bestFeatureId);
        recursionTrain(data, labels, node->rightN, node->usedSamples, numSamples, numFeatures, bestFeatureId);
    }
}
bool DecisionTree::leafOrNode(const int* labels, const int numSamples, bool* usedSamples) {
    for (int i = 0; i < numSamples; i++) {
        if (usedSamples[i] == true) {
            for (int j = 0; j < numSamples; j++) {
                if (usedSamples[j] == true) {
                    if (labels[j] != labels[i])
                        return false;
                }
            }
        }
    }
    return true;
}
int DecisionTree::predict(const bool* data) {
    int classId = 0;
    DecisionTreeNode* cur;
    cur = root;
    while (classId != 0) {
        if(data[cur->featureId] == true){
            cur = cur->rightN;
        }
        else {
            cur = cur->leftN;
        }
        if (cur->isLeaf == true) {
            classId = cur->classId;
        }
    }
    return classId;
}
double DecisionTree::test(const bool** data, const int* labels, const int numSamples) {
    int trues = 0;
    int falses = 0;
    for (int i = 0; i < numSamples; i++) {
        if (predict(data[i]) == labels[i]) {
            trues++;
        }
        else {
            falses++;
        }
    }
    double accuracy = trues / (trues + falses);
    return accuracy * 100;
}
void DecisionTree::printPreorder(DecisionTreeNode* cur, int& ctr) {
    if (cur == NULL) {
        return;
    }
    if (cur->isLeaf) {
        for (int j = 0; j < ctr; j++) {
            std::cout << "   " << endl;
        }
        std::cout << "class = " << cur->classId << endl;
    }
    else {
        for (int j = 0; j < ctr; j++) {
           std::cout << "   ";
        }
        std::cout << cur->featureId << endl;
    }
    ctr++;
    printPreorder(cur->leftN, ctr);
    printPreorder(cur->rightN, ctr);
}
void DecisionTree::print(){
    int i = 0;
    DecisionTreeNode* cur = root;
    std::cout << "Decison Tree : " << endl;
    printPreorder(root, i);
}