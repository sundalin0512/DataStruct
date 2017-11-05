#include "avlTree.hpp"
using namespace std;

int main()
{
	Sdalin::avlTree a;
	a.insert(11);
	a.insert(12);
	a.insert(13);
	a.insert(10);
	a.insert(9);
	a.insert(8);
	a.erase(9);
	a.erase(8);


	//
	Sdalin::Queue<Sdalin::avlTree::Node*> a1 = a.layer();


	//Sdalin::Tree<int> a;
	//a.insert(50);
	//a.insert(30);
	//a.insert(60);
	//a.insert(10);
	//a.insert(40);
	//a.insert(55);
	//a.insert(75);
	//a.insert(54);
	////a.erase(54);
	////a.insert(54);

	////DLR: 50  30  10  40  60  55  54  75 
	//Sdalin::Queue<Sdalin::Tree<int>::Node*> a1 = a.DLR();
	////LDR: 10  30  40  50  54  55  60  75
	//Sdalin::Queue<Sdalin::Tree<int>::Node*> a2 = a.LDR();
	////LRD: 10  40  30  54  55  75  60  50
	//Sdalin::Queue<Sdalin::Tree<int>::Node*> a3 = a.LRD();
	return 0;
}