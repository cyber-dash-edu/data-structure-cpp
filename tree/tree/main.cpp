//
// Created by alei_go@163.com(抖音: cyberdash_yuan) on 2020/11/1.
//

#include <iostream>
#include <fstream>

using namespace std;

#include "tree_node.h"
#include "tree.h"
#include "tree.cpp"

void visit(TreeNode<int> *p) {
  cout << p->data << " ";
}

int main(void) {
  int num;
  int i = 0;

  Tree<int> tree;

  cout << "Input the nodes num in the binary tree: ";
  cin >> num;

  for (i = 0; i < num; i++) {
    tree.Insert(i);
  }

  if (tree.Find(10)) {
    cout << "find 10 in list." << endl;
  }

  cout << "node num: " << tree.count_node() << endl;
  cout << "depth: " << tree.find_depth() << endl;
  cout << "show tree: " << endl;
  tree.show_tree();

  cout << "preorder: " << endl;
  tree.PreOrder(cout);
  tree.preorder( visit);
  cout << "postorder: " << endl;
  tree.PostOrder(cout);
  tree.postorder(visit);
  cout << "levelorder: " << endl;
  tree.LevelOrder(cout);

  cout << "--- " << endl;
  Tree<int> tree_1;
  char *gl = (char *) "(0(1(2))(2))";
  tree_1.create_tree(gl);
  cout <<tree_1.count_node() ;
  tree_1.show_tree();

  cout << endl;

  tree_1.CyberDashShow();

  return 0;
}

