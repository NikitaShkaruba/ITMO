#include "Sentence.hh"
#include <pypa/ast/types.hh>
#include <string>

class IncludeSentence : public Sentence {
public:
  IncludeSentence(string lib_name) {
    this->type = static_cast<int>(AstType::Import);
    this->children = vector<Sentence*>();
    this->lib_name = lib_name;
  }

  string toString(string tabs) {
    return "#include <" + lib_name + ">\n";
  }

private:
  string lib_name;
};
