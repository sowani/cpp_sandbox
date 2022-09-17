/*
 * nodeitem.cpp
 * This implementation uses shared_ptr
 *
 * Sunday 18 September 2022 01:28:41 AM IST
 */

#include "nodeitem.h"

/**
 * @fn void addId(int)
 * @pre
 * @post
 * @param id
 */
void NodeItem::addId(int id)
{
	identifiers.insert (identifiers.end(), id);
	totalIDs++;
}

/**
 * @fn int getTotalIDs()
 * @pre
 * @post
 * @return Total number of IDs stored: int
 */
int NodeItem::getTotalIDs()
{
	return totalIDs;
}

/**
 * @fn void printIDs()
 * @pre
 * @post
 */
void NodeItem::printIDs()
{
	// copy (identifiers.begin(), identifiers.end(), ostream_iterator<int> (cout, " "));
	list<int>::iterator it;
	for (it = identifiers.begin(); it != identifiers.end(); ++it)
		cout << *it << " ";
	cout << endl;
}

bool NodeItem::evalCondition()
{
	bool result;

	if (loperator == AND)
		result = 1;
	else if (loperator == OR)
		result = 0;

	GUIDset::iterator it;
	for (it = identifiers.begin(); it != identifiers.end(); ++it)
	{
		//cout << "condition = " << *it << endl;
		if (loperator == AND)
		{
			result = result && *it;
		} else if (loperator == OR)
		{
			result = result || *it;
		}
	}
	//cout << "NodeItem result = " << result << endl;
	return result;
}

// -----------------------------------------------------------------------------

// ---- Composite node implementation ----
void CompositeNode::addChildren (int num, ...)
{
	va_list nodelist;
	//BaseNode *node;
	BaseNodePtr node;

	va_start (nodelist, num);
	for (int i = 0; i < num; i++)
	{
		//node = va_arg (nodelist, BaseNode*);
		node = va_arg (nodelist, BaseNodePtr);
		cout << nodeName << " adding node ";
		node->printNode();
		children.push_back(node);
	}
	va_end (nodelist);
}

bool CompositeNode::evalCondition()
{
	bool result, res1;

	//cout << "composite node " << nodeName << " [" << children.size() << "] evalCondition" << endl;
	// foreach node in children
	//   evalCondition (node, operator);

	if (children.size() == 0)
		return true;

	//cout << "eval further" << endl;

	if (loperator == AND)
		result = 1;
	else if (loperator == OR)
		result = 0;

	//list<BaseNode*>::iterator it;
	list<BaseNodePtr>::iterator it;
	for (it = children.begin(); it != children.end(); ++it)
	{
		if (loperator == AND)
		{
			res1 = (*it)->evalCondition();
			result = result && res1;
		}
		else if (loperator == OR)
		{
			res1 = (*it)->evalCondition();
			result = result || res1;
		}
	}

	cout << "composite node " << nodeName << " returned: " << result << endl;
	return result;
}

void CompositeNode::printNode()
{
	cout << "node name: " << nodeName;
	cout << " , type: " << nodeType << ", operator: " << loperator << endl;
}

// ---- Leaf node implementation ----
void LeafNode::addChildren (int num, ...)
{
	va_list condlist;
	int guid;

	va_start (condlist, num);
	for (int i = 0; i < num; i++)
	{
		guid = va_arg (condlist, int);
		condition.addId(guid);
		//mConditions.push_back(guid);
	}
	va_end (condlist);
}

bool LeafNode::evalCondition()
{
	bool result;
	//cout << "leaf node " << nodeName << " evalCondition" << endl;
	result = condition.evalCondition();
	cout << "leaf node " << nodeName << " returned: " << result << endl;
	return result;
}

void LeafNode::printNode()
{
	cout << "node name: " << nodeName;
	cout << ", type: " << nodeType << endl;
}
