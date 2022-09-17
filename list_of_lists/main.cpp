/*
 * main.cpp
 * This implementation uses shared_ptr
 *
 * Sunday 18 September 2022 01:28:41 AM IST
 */

#include "nodeitem.h"
using namespace std;

int main (int argc, char **argv)
{
	/*
	CompositeNode *root = new CompositeNode ("root");
	CompositeNode *node1 = new CompositeNode ("n1");
	CompositeNode *node2 = new CompositeNode ("n2");
	CompositeNode *node3 = new CompositeNode ("n3");
	CompositeNode *node4 = new CompositeNode ("n4");
	*/
	shared_ptr<CompositeNode> root = make_shared<CompositeNode> ("root");
	shared_ptr<CompositeNode> node1 = make_shared<CompositeNode> ("n1");
	shared_ptr<CompositeNode> node2 = make_shared<CompositeNode> ("n2");
	shared_ptr<CompositeNode> node3 = make_shared<CompositeNode> ("n3");
	shared_ptr<CompositeNode> node4 = make_shared<CompositeNode> ("n4");

	cout << "Creating root node and composite nodes" << endl;
	root->printNode();
	root->addChildren(3, node1, node2, node4);
	root->addOperator(AND);

	node2->addChildren(1, node3);
	//LeafNode *node7 = new LeafNode ("n7");
	shared_ptr<LeafNode> node7 = make_shared<LeafNode> ("n7");
	node7->addChildren(3, 1, 0, 1);
	node7->addOperator(OR);

	//LeafNode *node8 = new LeafNode ("n8");
	shared_ptr<LeafNode> node8 = make_shared<LeafNode> ("n8");
	node8->addChildren(3, 1, 1, 1);
	node8->addOperator(AND);
	node3->addChildren(2, node7, node8);
	node3->addOperator(OR);

	cout << "Creating 2 leaf nodes" << endl;
	//LeafNode *node5 = new LeafNode ("c1");
	shared_ptr<LeafNode> node5 = make_shared<LeafNode> ("c1");
	node5->addChildren(3, 0, 1, 1);
	node5->addOperator(AND);
	//node4->printNode();
	//cout << "result = " << node4->evalCondition() << endl;

	//LeafNode *node6 = new LeafNode ("c2");
	shared_ptr<LeafNode> node6 = make_shared<LeafNode> ("c2");
	node6->addChildren(2, 0, 1);
	node6->addOperator(OR);
	//node5->printNode();
	//cout << "result = " << node5->evalCondition() << endl;

	node4->addChildren(2, node5, node6);
	node4->addOperator(AND);
	//node4->evalCondition();

	cout << "------------------------" << endl;
	root->evalCondition();
	cout << "done!" << endl;
	return 0;
}
