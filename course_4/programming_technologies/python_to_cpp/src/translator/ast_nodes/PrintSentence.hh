#include "Sentence.hh"
#include <pypa/ast/types.hh>
#include <string>

class PrintSentence : public Sentence {
public:
  PrintSentence(string print_string) {
    this->type = static_cast<int>(AstType::Print);
    this->children = vector<Sentence*>();
    this->print_string = print_string;
  }

  string toString(string tabs = "") {
    return tabs + "printf(\"%s\", \"" + print_string + "\")\n";
  }

private:
  string print_string;
};
