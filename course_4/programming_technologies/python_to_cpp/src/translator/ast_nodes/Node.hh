#pragma once

#include <pypa/ast/ast.hh>
#include "string.h"
#include "vector"
#include "map"

using namespace std;
using namespace pypa;

class Node {
public:
  int type;
  vector<Node*> children;
};
