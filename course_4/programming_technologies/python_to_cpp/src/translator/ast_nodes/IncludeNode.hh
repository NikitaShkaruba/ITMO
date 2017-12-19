#include "Node.hh"
#include <pypa/ast/types.hh>
#include <string>

class IncludeNode : public Node {
public:
  IncludeNode(string lib_name) {
    this->type = static_cast<int>(AstType::Import);
    this->children = vector<Node*>();
    this->lib_name = lib_name;
  }

private:
  string lib_name;
};
