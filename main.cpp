#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
using namespace std;

struct node {
    int key;
    node *left;
    node *right;
	node *par;
};

node *make_node(int key, node *left, node *right) {
    node *n = new node;
    n -> key = key;
    n -> left = left;
    n->right = right;
	n -> par = NULL;
    return n;
}

node *buildtree(int key, node *subl, node *subr) {
    //builds tree in bottom up way
    node *root = make_node(key, subl, subr);
    
    return root;
}

void printtree(node *root) {
	//for debugging purpose
	
    cout<< root -> key << endl;
    if (root -> left != NULL) {
		printtree(root -> left);
    }
	if (root -> right != NULL) {
		printtree(root -> right);
	}
}

void printancestors(vector<int> anc) {
	if (anc.empty()) {
		cout << "No ancestors found";
	}
	
    for (int i = 0; i < anc.size(); i++) {
        cout << anc[i] << " ";
    }
	cout << endl;
}

node *dfs(int key, node *root) {
	/*returns the node that has key we are looking for
	and finds parents*/
	
	stack<node*> st;
	st.push(root);
	map<int, bool> m;
	
	root -> par = NULL;
	m.insert(make_pair(root -> key, true));
	node *curr = root;
	
	bool found = false;
	
	while (!st.empty() && !found) {
		curr = st.top();
		st.pop();
		
		if (curr -> key == key) {
			found = true;
		}
		
		if (curr -> left != NULL && !m.count(curr -> left ->key)) {
			st.push(curr -> left);
			curr -> left -> par = curr;
			m.insert(make_pair(curr -> left -> key, true));
		}
		
		if (curr -> right != NULL && !m.count(curr -> right -> key)) {
			st.push(curr -> right);
			curr -> right -> par = curr;
			m.insert(make_pair(curr -> right -> key, true));
		}
	}
	
	if (!found) {
		throw "Key doesn't exist in the tree";
	}
	
	return curr;
}

vector<int> findancestors(int key, node *root) {
    vector<int> ancestors;
    
    node *curr = dfs(key, root);
    
	while (curr -> par != NULL) {
		ancestors.push_back(curr -> par -> key);
		curr = curr -> par;
	}
	
    return ancestors;
}

int lowestcommonancestor(int key1, int key2, node *root) {
    vector<int> key1ancestors = findancestors(key1, root);
    vector<int> key2ancestors = findancestors(key2, root);
	
	//findancestors returns ancestors from bottom to top
	
	int i = 0;
	int j = 0;
	
	while (i < key1ancestors.size() && j < key2ancestors.size()) {
		if (key1ancestors[i] == key2ancestors[j]) {
            return key1ancestors[i];
        } else if (key1ancestors[i] > key2ancestors[j]) {
			j++;
		} else {
			i++;
		}
	}
    
    return NULL;
}

void testbalancedtree() {
	node *sub1 = buildtree(3 ,make_node(2, NULL, NULL), make_node(4, NULL, NULL));
    node *sub2 = buildtree(6, make_node(5, NULL, NULL), make_node(7, NULL, NULL));
    node *root = buildtree(9, sub1, sub2);
	
	vector<int> anc = findancestors(5, root);
	printancestors(anc);
	vector<int> anc2 = findancestors(2, root);
	printancestors(anc2);
	vector<int> anc3 = findancestors(3, root);
	printancestors(anc3);
    
	cout << lowestcommonancestor(2, 4, root) <<endl;
	cout << lowestcommonancestor(3, 6, root) << endl;
	cout << lowestcommonancestor(2, 3, root) << endl;
}

void testunbalancedtree() {
	node *sub1 = buildtree(3 ,make_node(2, NULL, NULL), make_node(NULL, NULL, NULL));
    node *sub2 = buildtree(6, make_node(NULL, NULL, NULL), make_node(7, NULL, NULL));
    node *root = buildtree(9, sub1, sub2);
	
	vector<int> anc = findancestors(7, root);
	printancestors(anc);
	vector<int> anc2 = findancestors(2, root);
	printancestors(anc2);
	vector<int> anc3 = findancestors(3, root);
	printancestors(anc3);
    
	cout << lowestcommonancestor(2, 7, root) <<endl;
	cout << lowestcommonancestor(3, 6, root) << endl;
	cout << lowestcommonancestor(2, 3, root) << endl;
}

int main()
{
	testbalancedtree();
	testunbalancedtree();
   
    return 0;
}

