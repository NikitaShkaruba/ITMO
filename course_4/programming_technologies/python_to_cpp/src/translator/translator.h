#pragma once

#include <translator/lib/abstract_syntax_tree.h>
#include <translator/lib/ast_nodes/CommentSentence.h>
#include <pypa/ast/ast.hh>
#include <map>
#include <translator/lib/ast_nodes/PrintSentence.h>

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
        _translate_function_def(statement);
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

    if (root->isMainNeeded()) {
      root->packMain();
    }

    return root;
  }

private:

  static void _translate_comment(const std::shared_ptr<AstStatement> &statement) {
    AstDocString const &comment_statement = static_cast<const AstDocString &>(*statement);
    String comment_content = comment_statement.doc;

    root->addNode(new CommentSentence(comment_content));
  }

  static void _translate_print(const shared_ptr<AstStatement> &statement) {
    root->addNode(_create_printNode(statement));
  }

  static PrintSentence* _create_printNode(const shared_ptr<AstStatement> &statement) {
    AstPrint const &print_statement = static_cast<const AstPrint &>(*statement);

    String print_parts = "";
    for (unsigned long i = 0; i < print_statement.values.size(); i++) {
      AstExpression print_argument_statement = *print_statement.values.at(i);

      string value;
      if (print_argument_statement.type == AstType::Str) {
        AstStr const &string_statement = static_cast<const AstStr &>(*print_statement.values.at(i));
        value = "\"" + string_statement.value +"\"";
      } else if (print_argument_statement.type == AstType::Name) {
        AstName const &name_statement = static_cast<const AstName &>(*print_statement.values.at(i));
        value = name_statement.id;
      } else {
        throw "Not supported statement type";
      }

      String space = print_parts.empty() ? "" : " + "; // Add space if not first
      print_parts = print_parts.append(space + value);
    }

    return new PrintSentence(print_parts);
  }

  static void _translate_import(const shared_ptr<AstStatement> &statement) {
    AstPrint const & import_statement = static_cast<const AstPrint &>(*statement);

    AstAlias const & arguments = static_cast<const AstAlias &> (*import_statement.destination);
    AstName const & name = static_cast<const AstName &> (*arguments.name);
    String lib_name = name.id;

    if (name.id == "sys") {
      root->addHeader(new IncludeSentence("cstdio"));
      root->addHeader(new IncludeSentence("stdio.h"));
    } else {
      throw "undefined import!";
    }
  }

  static void _translate_function_def(const shared_ptr<AstStatement> &statement) {
    AstFunctionDef const & function_statement = static_cast<const AstFunctionDef &>(*statement);

    // Собираем имя функции
    AstExpr const & name_expression = static_cast<const AstExpr &>(function_statement.name);
    AstName const & name_statement = static_cast<const AstName &>(*name_expression);
    string function_name = name_statement.id;

    // Собираем аргументы и их дефолтные значения
    vector<String> argument_names;
    vector<String> argument_default_values;
    AstArguments const & arguments_expression = static_cast<const AstArguments &>(function_statement.args);
    for (unsigned long i = 0; i < arguments_expression.arguments.size(); i++) {
      AstName const & argument_name_expression = static_cast<const AstName &>(*arguments_expression.arguments.at(i));
      string argument_name = argument_name_expression.id;

      string argument_default_value = "";
      if (arguments_expression.defaults.at(i) != nullptr) {
        AstStr const & argument_default_value_expression = static_cast<const AstStr  &>(*arguments_expression.defaults.at(i));
        argument_default_value = argument_default_value_expression.value;
      }

      argument_names.push_back(argument_name);
      argument_default_values.push_back(argument_default_value);
    }

    // Собираем тело функции
    vector<Sentence*> children;
    AstSuite & body_expression = static_cast<AstSuite &>(*function_statement.body);
    for (unsigned long i = 0; i < body_expression.items.size(); i++) {
//      AstStatement const & nested_expression = static_cast<const AstStatement  &>(*body_expression.items.at(i));
      std::shared_ptr<AstStatement> &nested_statement = body_expression.items.at(i);

      switch (nested_statement->type) {
        case AstType::Print:
          children.push_back(_create_printNode(nested_statement));
          break;

        case AstType::Pass:
          break;
        default:
          break;
      }
    }
//    AstExpr const & name_expression = static_cast<const AstExpr &>(function_statement.name);
//    AstName const & name_statement = static_cast<const AstName &>(*name_expression);
//    string function_name = name_statement.id;


    root->addNode(new FunctionDefinitionSentence(function_name, argument_names, argument_default_values, children));
  }

  static void _translate_assignment(const shared_ptr<AstStatement> &statement) {
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

  static void _translate_raise(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_repr(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_return(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_set(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_setcomp(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_slice(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_slicetype(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_statement(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_str(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_subscript(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_suite(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_tryexcept(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_tryfinally(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_tuple(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_unaryop(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_while(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_with(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_yield(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static void _translate_yieldexpr(const shared_ptr<AstStatement> &statement) {
    printf("sht");
  }

  static AbstractSyntaxTree* root;
};
