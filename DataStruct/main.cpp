#include "bTree.hpp"
#include "Vector.hpp"
using namespace std;

int main()
{
	Sdalin::List<int> vec;

	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(8);
	vec.push_back(9);
	vec.resize(3);

	//Sdalin::BTree<int> a;
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
	//Sdalin::Queue<Sdalin::BTree<int>::Node*> a1 = a.DLR();
	////LDR: 10  30  40  50  54  55  60  75
	//Sdalin::Queue<Sdalin::BTree<int>::Node*> a2 = a.LDR();
	////LRD: 10  40  30  54  55  75  60  50
	//Sdalin::Queue<Sdalin::BTree<int>::Node*> a3 = a.LRD();
	return 0;
}