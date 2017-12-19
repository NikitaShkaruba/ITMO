
#pragma once

#include <pypa/ast/ast.hh>
#include <translator/ast_nodes/IncludeNode.hh>
#include "string.h"
#include "vector"
#include "map"
#include "translator/ast_nodes/Node.hh"

using namespace std;
using namespace pypa;

class AbstractSyntaxTree {
public:
  void addChild(Node* child) {
    this->nodes.push_back(child);
  }

  void addHeader(IncludeNode* includeNode) {
    this->nodes.insert(nodes.begin(), (Node*) includeNode);
  }

private:
  vector<Node*> nodes;
};

