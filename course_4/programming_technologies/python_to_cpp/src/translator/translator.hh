#pragma once

#include <translator/abstract_syntax_tree.hh>
#include <translator/ast_nodes/CommentSentence.h>
#include <pypa/ast/ast.hh>
#include <map>
#include <translator/ast_nodes/PrintSentence.hh>

using namespace pypa;
using namespace std;

class Translator {
public:

  static AbstractSyntaxTree* translate_to_cpp(AstModulePtr ast_module_pointer) {
    AstStmtList ast_nodes = ast_module_pointer->body->items;

    root = new AbstractSyntaxTree();

    for (size_t nodes_index = 0; nodes_index < ast_nodes.size(); nodes_index++) {
      std::shared_ptr<AstStatement> &statement = ast_nodes.at(nodes_index);

      AstType s = statement->type;
      if (s == AstType::DocString) {
        _translate_comment(statement);
      } else if (s == AstType::Import) {
        _translate_import(statement);
      } else if (s == AstType::Alias) {

      } else if (s == AstType::Arguments) {


      } else if (s == AstType::Assert) {


      } else if (s == AstType::Assign) {


      } else if (s == AstType::Attribute) {


      } else if (s == AstType::AugAssign) {


      } else if (s == AstType::BinOp) {


      } else if (s == AstType::Bool) {


      } else if (s == AstType::BoolOp) {


      } else if (s == AstType::Break) {


      } else if (s == AstType::Call) {


      } else if (s == AstType::ClassDef) {


      } else if (s == AstType::Compare) {


      } else if (s == AstType::Complex) {


      } else if (s == AstType::Comprehension) {


      } else if (s == AstType::Continue) {


      } else if (s == AstType::Delete) {


      } else if (s == AstType::Dict) {


      } else if (s == AstType::DictComp) {


      } else if (s == AstType::Ellipsis) {


      } else if (s == AstType::EllipsisObject) {


      } else if (s == AstType::Except) {


      } else if (s == AstType::Exec) {


      } else if (s == AstType::Expression) {


      } else if (s == AstType::ExpressionStatement) {


      } else if (s == AstType::ExtSlice) {


      } else if (s == AstType::For) {


      } else if (s == AstType::FunctionDef) {


      } else if (s == AstType::Generator) {


      } else if (s == AstType::Global) {


      } else if (s == AstType::If) {


      } else if (s == AstType::IfExpr) {


      } else if (s == AstType::ImportFrom) {


      } else if (s == AstType::Index) {


      } else if (s == AstType::Keyword) {


      } else if (s == AstType::Lambda) {


      } else if (s == AstType::List) {


      } else if (s == AstType::ListComp) {


      } else if (s == AstType::Module) {


      } else if (s == AstType::Name) {


      } else if (s == AstType::None) {


      } else if (s == AstType::Number) {


      } else if (s == AstType::Pass) {


      } else if (s == AstType::Print) {
        _translate_print(statement);
      } else if (s == AstType::Raise) {


      } else if (s == AstType::Repr) {


      } else if (s == AstType::Return) {


      } else if (s == AstType::Set) {


      } else if (s == AstType::SetComp) {


      } else if (s == AstType::Slice) {


      } else if (s == AstType::SliceType) {


      } else if (s == AstType::Statement) {


      } else if (s == AstType::Str) {


      } else if (s == AstType::Subscript) {


      } else if (s == AstType::Suite) {


      } else if (s == AstType::TryExcept) {


      } else if (s == AstType::TryFinally) {


      } else if (s == AstType::Tuple) {


      } else if (s == AstType::UnaryOp) {


      } else if (s == AstType::While) {


      } else if (s == AstType::With) {


      } else if (s == AstType::Yield) {


      } else if (s == AstType::YieldExpr) {

      } else {
        throw "Translate Error";
      }
    }

    if (root->isNoMainScript()) {
      root->packMain();
    }

    return root;
  }

private:

  void static _translate_comment(const std::shared_ptr<AstStatement> &statement) {
    AstDocString const &comment_statement = static_cast<const AstDocString &>(*statement);
    String comment_content = comment_statement.doc;

    root->addNode(new CommentSentence(comment_content));
  }

  void static _translate_print(const shared_ptr<AstStatement> &statement) {
    AstPrint const &print_statement = static_cast<const AstPrint &>(*statement);

    String print_parts = "";
    for (unsigned long i = 0; i < print_statement.values.size(); i++) {
      AstStr const &string_statements = static_cast<const AstStr &>(*print_statement.values.at(i));

      String space = print_parts.empty() ? "" : " "; // Add space if not first
      print_parts = print_parts.append(space + string_statements.value);
    }

    root->addNode(new PrintSentence(print_parts));
  }

  void static _translate_import(const shared_ptr<AstStatement> &statement) {
    AstPrint const &import_statement = static_cast<const AstPrint &>(*statement);

    AstAlias const &arguments = static_cast<const AstAlias &> (*import_statement.destination);
    AstName const &name = static_cast<const AstName &> (*arguments.name);
    String lib_name = name.id;

    if (name.id == "sys") {
      root->addHeader(new IncludeSentence("cstdio"));
      root->addHeader(new IncludeSentence("iostream"));
      root->addHeader(new IncludeSentence("fstream"));
      root->addHeader(new IncludeSentence("stdio.h"));
    } else {
      throw "undefined import!";
    }
  }

  void static _translate_raise(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_repr(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_return(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_set(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_setcomp(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_slice(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_slicetype(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_statement(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_str(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_subscript(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_suite(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_tryexcept(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_tryfinally(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_tuple(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_unaryop(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_while(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_with(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_yield(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  void static _translate_yieldexpr(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static AbstractSyntaxTree* root;
};
