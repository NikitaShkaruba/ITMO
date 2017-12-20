#include <string>
#include "Sentence.h"

class FunctionDefinitionSentence : public Sentence {
public:
  FunctionDefinitionSentence(string name, vector<string> argument_names, vector<string> argument_default_values, vector<Sentence*> children) {
    this->type = static_cast<int>(AstType::FunctionDef);
    this->children = children;

    this->name = name;
    this->argument_names = argument_names;
    this->argument_default_values = argument_default_values;
  }

  FunctionDefinitionSentence(string name) {
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

    string arguments_string = "";
    for (unsigned long i = 0; i < argument_names.size(); i++) {
      string argument_type = "string";
      string argument_name = argument_names.at(i);
      string argument_default_value = argument_default_values.at(i);

      string next_argument = argument_type + " " + argument_name;

      // Если есть дефолтное значение
      if (argument_default_value != "") {
        next_argument = next_argument + " = \"" + argument_default_value + "\"";
      }

      // Если параметров несколько - свой implode()
      if (i > 0) {
        next_argument = ", " + next_argument;
      }

      arguments_string += next_argument;
    }

    return "\nint " + name + "(" + arguments_string + ") {\n" + children_content +"}";
  }

private:
  string name;
  vector<string> argument_names;
  vector<string> argument_default_values;
};
