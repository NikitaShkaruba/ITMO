#include "Node.hh"
#include <pypa/ast/types.hh>
#include <string>

class PrintNode : public Node {
public:
  PrintNode(string print_string) {
    this->type = static_cast<int>(AstType::Print);
    this->children = vector<Node*>();
    this->print_string = print_string;
  }

private:
  string print_string;
};
