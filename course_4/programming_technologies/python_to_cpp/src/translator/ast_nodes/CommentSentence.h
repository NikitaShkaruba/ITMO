#include <string>
#include "Sentence.hh"

class CommentSentence : public Sentence {
public:
  CommentSentence(string content) {
    this->type = static_cast<int>(AstType::DocString);
    this->children = vector<Sentence*>();
    this->content = content;
  }

  string toString(string tabs) {
    return "\n" + tabs + "/**" + tabs + TAB + content + tabs + "*/\n";
  }

private:
  string content;
};
