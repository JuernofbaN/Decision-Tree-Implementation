
hw2: main.o DecisionTree.o DecisionTreeNode.o
	g++ main.o DecisionTree.o DecisionTreeNode.o -o hw2
	
main.o: main.cpp
	g++ -c main.cpp

auxArrayFunctions.o: DecisionTree.cpp
	g++ -c DecisionTree.cpp

sorting.o: DecisionTreeNode.cpp
	g++ -c DecisionTreeNode.cpp

clean:
	rm *.o hw2