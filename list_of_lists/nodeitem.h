/*
 * nodeitem.h
 * This implementation uses shared_ptr
 *
 * Sunday 18 September 2022 01:28:41 AM IST
 */

#ifndef SRC_NODEITEM_H_
#define SRC_NODEITEM_H_

#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <cstdarg>
#include <memory>
using namespace std;

typedef int LogicalOperator;
typedef list<int> GUIDset;

enum loperation { AND = 1, OR };

/**
 * @class NodeItem
 */
class NodeItem
{
protected:
	GUIDset identifiers;    // list<int> identifiers;
	LogicalOperator loperator;
	int totalIDs;
public:
	NodeItem() { loperator = AND; totalIDs = 0; }
	void addId (int id);
	void addLOperator (loperation op) { loperator = op; }
	bool evalCondition();
	int getTotalIDs();
	void printIDs();
};


class BaseNode
{
public:
	virtual bool evalCondition() = 0;
	virtual void printNode() = 0;
};

typedef shared_ptr<BaseNode> BaseNodePtr;

class CompositeNode : virtual BaseNode
{
protected:
	//list<BaseNode*> children;
	list<BaseNodePtr> children;
	LogicalOperator loperator;
	string nodeName;
	string nodeType;
public:
	CompositeNode (string name) { loperator = AND; nodeName = name; nodeType = "Composite"; }
	void addChildren (int num, ...);
	void addOperator (loperation op) { loperator = op; }
	bool evalCondition();
	void printNode();
};


class LeafNode: virtual BaseNode
{
protected:
	NodeItem condition;
	//LogicalOperator loperator;
	string nodeName;
	string nodeType;
public:
	LeafNode (string name) { nodeName = name; nodeType = "Leaf"; }
	void addChildren (int num, ...);
	//void addOperator (loperation op) { loperator = op; }
	void addOperator (loperation op) { condition.addLOperator(op); }
	bool evalCondition();
	void printNode();
};

#endif /* SRC_NODEITEM_H_ */
