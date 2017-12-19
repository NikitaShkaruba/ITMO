#pragma once

#include <pypa/ast/ast.hh>
#include "string.h"
#include "vector"
#include "map"

using namespace std;
using namespace pypa;

const string TAB = "  ";

class Sentence {
public:

  int getType() {
    return type;
  }

  vector<Sentence*> getChildren() {
    return children;
  }

  bool addChild(Sentence* child) {
    children.push_back(child);
    return true;
  }

  virtual string toString(string tabs = "") {
    throw "Sentence->print() Not overloaded";
  }

protected:
  int type;
  vector<Sentence*> children;
};
