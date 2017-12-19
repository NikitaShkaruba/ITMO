#include <cstdio>

#include <pypa/parser/parser.hh>
#include <translator/translator.hh>
#include "translator/translator.cc" // It is necessary, coz it builds really kinky

namespace pypa {
  void dump(AstPtr);
}

int main(int argc, char const** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <python_file_path>\n", argv[0]);
    return 1;
  }

  pypa::AstModulePtr ast;
  pypa::SymbolTablePtr symbols;
  pypa::ParserOptions options;
  options.printerrors = true;
  options.printdbgerrors = true;
  pypa::Lexer lexer(argv[1]);

  // Parse python file
  bool parsed_successfully = pypa::parse(lexer, ast, symbols, options);
  if (!parsed_successfully) {
    fprintf(stderr, "Parsing failed\n");
    return 1;
  }

  // Dump python ast to stdout
  dump(ast);

  // Construct syntax tree
  AbstractSyntaxTree* cpp_abstract_syntax_tree = Translator::translate_to_cpp(ast);
  if (!cpp_abstract_syntax_tree) {
    return 1;
  }

  // Print cpp ast
  printf("%s", cpp_abstract_syntax_tree->toString().c_str());

  return 0;
}
