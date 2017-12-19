#include <string>
#include "Sentence.h"

class FunctionSentence : public Sentence {
public:
  FunctionSentence(string name) {
    this->type = static_cast<int>(AstType::FunctionDef);
    this->children = vector<Sentence*>();

    this->name = name;
  }

  string getName() {
    return name;
  }

  string toString(string tabs) {
    string children_content = "";
    for (unsigned long i = 0; i < children.size(); i++) {
      children_content += children.at(i)->toString(tabs + TAB);
    }

    return "\nint " + name + "() {" + children_content +"}";
  }

private:
  string name;
};
