#pragma once

#include <pypa/ast/ast.hh>
#include <translator/lib/ast_nodes/IncludeSentence.h>
#include <translator/lib/ast_nodes/FunctionDefinitionSentence.h>
#include "string.h"
#include "vector"
#include "map"
#include "translator/lib/ast_nodes/Sentence.h"

using namespace std;
using namespace pypa;

const string FUNCTION_NAME_MAIN = "main";

class AbstractSyntaxTree {
public:
  /**
   * Добавляет одну ноду
   */
  void addNode(Sentence* child) {
    this->nodes.push_back(child);
  }

  /**
   * Добавляет хедер - как и ноду, только в начало @see addNode
   */
  void addHeader(IncludeSentence* includeNode) {
    this->nodes.insert(nodes.begin(), (Sentence*) includeNode);
  }

  /**
   * Проверяет, нужен ли скрипту меин для выполнения. Питону он не обязателен, а cpp - необходим.
   */
  bool isMainNeeded() {
    return isNoMainScript() && !isLib();
  }

  /**
   * Заносит всё, кроме хедеров в меин
   */
  void packMain() {
    FunctionDefinitionSentence* mainFunction = new FunctionDefinitionSentence(FUNCTION_NAME_MAIN);

    for (unsigned long i = 0; i < nodes.size();) {
      if (nodes.at(i)->getType() == static_cast<int>(AstType::Import)) {
        i++;
        continue;
      }

      mainFunction->addChild(nodes.at(i));
      nodes.erase(nodes.begin() + i);
    }

    addNode(mainFunction);
  }

  /**
   * Превращает дерево в строку
   */
  string toString() {
    string ast_as_string = "";

    for (unsigned long i = 0; i < nodes.size(); i++) {
      ast_as_string += nodes.at(i)->toString();
    }

    return ast_as_string;
  }

private:

  /**
   * Проверяет, что у скрипта нет меина
   */
  bool isNoMainScript() {
    for (unsigned long i = 0; i < nodes.size(); i++) {
      if (nodes.at(i)->getType() != static_cast<int>(AstType::FunctionDef)) {
        continue;
      }

      FunctionDefinitionSentence* functionNode = static_cast<FunctionDefinitionSentence*>(nodes.at(i));
      if (functionNode->getName() == FUNCTION_NAME_MAIN) {
        return false;
      }
    }

    return true;
  }

  /**
   * Проверяет, является ли файл библиотекой
   */
  bool isLib() {
    for (unsigned long i = 0; i < nodes.size(); i++) {
      if (nodes.at(i)->getType() != static_cast<int>(AstType::FunctionDef) && nodes.at(i)->getType() != static_cast<int>(AstType::Import)) {
        return false;
      }
    }

    return true;
  }

  vector<Sentence*> nodes;

};

