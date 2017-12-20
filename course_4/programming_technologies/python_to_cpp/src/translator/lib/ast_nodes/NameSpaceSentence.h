#include "Sentence.h"
#include <pypa/ast/types.hh>
#include <string>

class NameSpaceSentence : public Sentence {
public:
  NameSpaceSentence(string namespace_name) {
    this->type = static_cast<int>(AstType::ImportFrom);
    this->children = vector<Sentence*>();
    this->namespace_name = namespace_name;
  }

  string toString(string tabs) {
    return "\nusing namespace " + namespace_name + ";\n";
  }

private:
  string namespace_name;
};
