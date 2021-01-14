

#pragma once;
#include <vector>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;
namespace ufl_cap4053 { namespace fundamentals {
	/*
	General reference:
	https://codereview.stackexchange.com/questions/47395/tree-template-class-implementation-for-c
	https://stackoverflow.com/questions/34602748/how-to-initialize-to-zero-null-in-a-template
	*/
	template <class T> class TreeNode {
	private:
		T root;
		vector<TreeNode<T>*> children;
	public:
		//initializer lists
		TreeNode<T>() : root(), children() {
		}//Constructor for TreeNode.Should store a default - constructed data value and start with no children.
		TreeNode<T>(T element) : root(element), children() {
		}//Constructor for TreeNode.Should store element as its data value and start with no children.
		const T& getData() const {
			return root;
		}//Returns a reference to the stored data.
		size_t getChildCount() const { //Returns the number of children of this node.
			return children.size();
		}
		TreeNode<T>* getChild(size_t index) {
			if (root != T{} && children.size() != 0)
				return children.at(index);
			return nullptr;
		}//Returns the child node at specified by index.
		TreeNode<T>* getChild(size_t index) const {
			if (root != T{} && children.size() !=0)
				return children.at(index);
			return nullptr;
		}//Returns the child node at specified by index.Note: this is the const version of this method.
		void addChild(TreeNode<T>* child) {
			if (root != T{})
				children.push_back(child);
		}//Add child to the children of this node.
		void removeChild(size_t index) {
			if (root != T{} && children.size() != 0)
				children.erase(index);
		}//Remove the child node at specified by index.
		void breadthFirstTraverse(void(*dataFunction)(const T)) const {
			//https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
			if (root == T{})
				return;
			if (children.empty() == true) {
				dataFunction(root);
				return;
			}
			list<TreeNode<T>*> temp;
			//list<TreeNode<T>*> visited;
			dataFunction(root);
			for (size_t j = 0; j < children.size(); j++)
				//if (visited.find((temp2->children).at(j)) != visited.end())
				temp.push_back((children).at(j));
			while (!temp.empty())
			{
				TreeNode<T>* temp2 = temp.front();
				temp.pop_front();
				dataFunction(temp2->root);
				//visited.push_back(temp2);
				for (size_t j = 0; j < (temp2->children).size(); j++)
					//if (visited.find((temp2->children).at(j)) != visited.end())
					temp.push_back((temp2->children).at(j));
			}
		}//Breadth - first traversal starting at this node.Calls dataFunction on the element to process it.
		void preOrderTraverse(void(*dataFunction)(const T)) const {
			//https://www.geeksforgeeks.org/iterative-preorder-traversal/
			//stack
			if (root == T{})
				return;
			if (children.empty() == true) {
				dataFunction(root);
				return;
			}
			stack<TreeNode<T>*> temp;
			//list<TreeNode<T>*> visited;
			dataFunction(root);
			for (size_t i = children.size(); i > 0; i--)
				temp.push(children.at(i - 1));
			while (temp.empty() == false) {
				TreeNode<T>* temp2 = temp.top();
				//visited.push_back(temp2);
				temp.pop();
				dataFunction(temp2->root);
				for (size_t j = (temp2->children).size(); j > 0; j--)
					//if (find(visited.begin(), visited.end(), (temp2->children).at(j - 1)) != visited.end())
					temp.push((temp2->children).at(j - 1));
					/*if (visited.find((temp2->children).at(j-1)) != visited.end())
						temp.push((temp2->children).at(j - 1));*/
			}
			/*if (root != nullptr) {
				dataFunction(root);
				for (size_t i = 0;i < children.size();i++)
					preOrderTraverse(children.at(i));
			}
			return;*/
			//list<TreeNode<T>*> tempList;	
		}//Pre - order traversal starting at this node.Calls dataFunction on the element to process it.
		void postOrderTraverse(void(*dataFunction)(const T)) const {
			//https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
			if (root == T{})
				return;
			for (size_t j = 0; j < children.size(); j++)
				(*(children.at(j))).postOrderTraverse(*dataFunction);
			//if (children.empty() == true) { // would make it so it only work on bottom nodes
			dataFunction(root);
			//}
			/*if (root != nullptr) {
				for (size_t i = 0;i < children.size();i++)
					postOrderTraverse(children.at(i));
				dataFunction(root);
			}
			return;*/
		}//Post - order traversal starting at this node.Calls dataFunction on the element to process it.
	};
}}  // namespace ufl_cap4053::fundamentals
