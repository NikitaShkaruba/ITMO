#pragma once

#include <pypa/ast/ast.hh>

using namespace pypa;
using namespace std;

void convert_comment(const std::shared_ptr<AstStatement> &statement) {
  AstDocString const & doc_comment = static_cast<const AstDocString &>(*statement);
  String s = doc_comment.doc;
  printf("/*%s*/\n", s.c_str());
}

void convert_print(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_import(const shared_ptr<AstStatement>& statement) {
  printf("sht");
}

void convert_raise(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_repr(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_return(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_set(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_setcomp(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_slice(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_slicetype(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_statement(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_str(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_subscript(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_suite(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_tryexcept(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_tryfinally(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_tuple(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_unaryop(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_while(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_with(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_yield(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_yieldexpr(const shared_ptr<AstStatement>& statement) {
 printf("sht");
}

void convert_to_cpp(AstModulePtr ast_module_pointer) {
  AstStmtList ast_nodes = ast_module_pointer->body->items;

  for (size_t nodes_index = 0; nodes_index < ast_nodes.size(); nodes_index++) {
    std::shared_ptr<AstStatement> & statement = ast_nodes.at(nodes_index);


    AstType s = statement->type;
    if (s == AstType::DocString) {
      convert_comment(statement);
    } else if (s == AstType::Import) {
      convert_import(statement);
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
      convert_print(statement);
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
      printf("Convert Error");
    }
  }
}
