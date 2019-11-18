#include"binarySortTree.h"
#include <iostream>
using namespace std;

int main(){
	G::BinarySortTree<int> bst;
	bst.insert(5);
	bst.insert(2);
	bst.insert(3);
	bst.insert(1);
	bst.insert(7);
	bst.insert(6);

	return 0;
}