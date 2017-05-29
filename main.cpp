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

node *buildtree(int key, node *left, node *right) {
    //builds tree in bottom up way
	
    node *root = new node;
    root -> key = key;
    root -> left = left;
    root -> right = right;
	root -> par = NULL;
	if (root -> left != NULL) {
		root -> left -> par = root;
	}
	if (root -> right != NULL) {
		root -> right -> par = root;
	}
	
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
	and finds parents
	 returns NULL if the key doesn't exist. */
	
	stack<node*> st;
	st.push(root);
	
	node *curr = root;
	
	bool found = false;
	
	while (!st.empty() && !found) {
		curr = st.top();
		st.pop();
		
		if (curr -> key == key) {
			found = true;
		}
		
		if (curr -> left != NULL) {
			st.push(curr -> left);
		}
		
		if (curr -> right != NULL) {
			st.push(curr -> right);
		}
	}
	
	if (!found) {
		return NULL;
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
	sort(key1ancestors.begin(), key1ancestors.end());
	sort(key2ancestors.begin(), key2ancestors.end());
	
	
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
	node *sub1 = buildtree(3 ,buildtree(2, NULL, NULL), buildtree(4, NULL, NULL));
    node *sub2 = buildtree(6, buildtree(5, NULL, NULL), buildtree(7, NULL, NULL));
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
	node *sub1 = buildtree(3 ,buildtree(2, NULL, NULL), NULL);
    node *sub2 = buildtree(6, NULL, buildtree(7, NULL, NULL));
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

