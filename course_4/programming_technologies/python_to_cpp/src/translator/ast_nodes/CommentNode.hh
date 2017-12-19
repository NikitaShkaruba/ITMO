#include <string>
#include "Node.hh"

class CommentNode : public Node {
public:
  CommentNode(string content) {
    this->type = static_cast<int>(AstType::DocString);
    this->children = vector<Node*>();
    this->content = content;
  }

private:
  string content;
};
