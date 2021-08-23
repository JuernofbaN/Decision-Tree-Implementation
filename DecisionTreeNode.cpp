/**
*Author:Turan Mert Duran
* ID: 21601418
* Section: 1
* Assignment: 2
*/
#include "DecisionTreeNode.h"
#include <iostream>
#include <cstring>
#include <fstream>
DecisionTreeNode::DecisionTreeNode()
{
	leftN = NULL;
	rightN = NULL;
	isLeaf = false;
	featureId = -1;
	classId = -1;
	usedSamples = NULL;
	usedSamplesL = NULL;
	numFeatures = -1;
}
