package sigma;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

// Lexically analyzes one code line
public class Lexer {
    public String analyze(String text) {
        // 0. Tokenize
        List<Token> tokens = tokenizeText(text);

        // 1. Evaluate 
        Token root = evaluateTokens(tokens);

        // 2. Return root's type
        printLexicalTree(root);
        return root.getType();
    }

    private List<Token> tokenizeText(String text) {
        ArrayList<Token> words = new ArrayList<>();
        ArrayList<Token> word = new ArrayList<>();

        for (int i = 0; i < text.length(); i++) {
            char c = text.charAt(i);

            try {
                String charType = detectCharType(c);
                Token token = new Token(String.valueOf(c), charType);

                if (token.getType().equals("Space") || i == text.length() - 1) {
                    if (!token.getType().equals("Space")) {
                        word.add(token);
                    }

                    if (!word.isEmpty()) {
                        String content = getStringFromSimpleTokens(word);
                        String wordType = detectWordType(word);
                        Token parent = new Token(content, wordType, word);
                        word = new ArrayList<>();

                        words.add(parent);
                    }
                } else if (token.getType().equals("Comma") || token.getType().equals("Semicolon")) {
                    // Add accumulated token
                    String content = getStringFromSimpleTokens(word);
                    String wordType = detectWordType(word);
                    Token parent = new Token(content, wordType, word);
                    words.add(parent);
                    word = new ArrayList<>();

                    // Add bind token
                    Token bindToken = new Token(token.getText(), token.getType());
                    words.add(bindToken);
                } else {
                    word.add(token);
                }
            } catch (Exception ex) {
                // throw new Exception("Syntax error");
                return null;
            }
        }

        return words;
    }

    private Token evaluateTokens(List<Token> tokens) {
        // Todo: Refactor this
        for(int matchingAmount = 2; matchingAmount <= tokens.size();) {
            boolean isFoundSomething = false;

            for(int j = tokens.size() - matchingAmount; j >= 0; j--) {
                List<Token> matchedTokens = tokens.subList(j, j + matchingAmount);
                String type = detectWordsPair(matchedTokens);

                if (type != null) {
                    String content = getStringFromTokens(matchedTokens);
                    Token parent = new Token(content, type, matchedTokens);
                    tokens.removeAll(matchedTokens);
                    tokens.add(j, parent);

                    isFoundSomething = true;
                    break;
                }
            }

            // If doesn't found anything with this matchingAmount
            if (!isFoundSomething) {
                matchingAmount++;
            }
        }

        return tokens.get(0);
    }

    private String detectWordsPair(List<Token> tokens) {
        if (isOperandList(tokens)) {
            return "Operand list";
        } else if (isOperand(tokens)) {
            return "Operand";   
        } else if (areComputations(tokens)) {
            return "Computations";
        } else if (isOperatorsList(tokens)) {
            return "Operators list";
        } else if (isOperator(tokens)) {
            return "Operator";
        } else if (isComplexOperator(tokens)) {
            return "Complex operator";
        } else if (isAssignment(tokens)) {
            return "Assignment";
        } else if (isExpression(tokens)) {
            return "Expression";
        } else if (isSubexpression(tokens)) {
            return "Subexpression";
        } else if (isVariablesDeclaration(tokens)) {
            return "Variables declaration";
        } else if (isVariablesList(tokens)) {
            return "Variables list";
        } else {
            return null;
        }
    }
   
	private String detectWordType(ArrayList<Token> tokens) throws Exception {
        if (isIdentifier(tokens)) {
	        return "Identifier";
        } else if (isConst(tokens)) {
            return "Const";
        } else if (isVarKeyword(tokens)) {
            return "Var keyword";
        } else {
            throw new Exception("No such word in Grammar");
        }
    }

	public String detectCharType(char c) throws Exception {
	    if (isLetter(c)) {
	        return "Letter";
        } else if (isDigit(c)) {
            return "Digit";
        } else if (isSpace(c)) {
            return "Space";
        } else if (isComma(c)) {
            return "Comma";
        } else if (isSemicolon(c)) {
            return "Semicolon";
        } else {
            throw new Exception("No such char in Grammar");
        }
    }

    private String getStringFromTokens(List<Token> tokens) {
        StringBuilder str = new StringBuilder();

        for(Token token: tokens) {
            str.append(token.getText()).append(" ");
        }

        return str.toString();
    }
    private String getStringFromSimpleTokens(List<Token> tokens) {
        StringBuilder str = new StringBuilder();

        for(Token token: tokens) {
            str.append(token.getText());
        }

        return str.toString();
    }

    private boolean isOperandList(List<Token> tokens) {
        //  <Identifier> | <Identifier> , <List of variables>
        return false;
    }
    private boolean isOperand(List<Token> tokens) {
        // <Identifier> | <Const>
        return false;
    }

    private boolean areComputations(List<Token> tokens) {
        // <List of operators>
        return false;
    }
    private boolean isOperatorsList(List<Token> tokens) {
        // <Operator> | <Operator> <List of operators>
        return false;
    }
    private boolean isOperator(List<Token> tokens) {
        // <Assignment> | <Complex operator> | <Unary operator> | <Binary operator>
        return false;
    }

    private boolean isComplexOperator(List<Token> tokens) {
		// IF <Expression> THEN <Operator> | IF <Expression> THEN <Operator> ELSE <Operator>
        return false;
	}

    private boolean isAssignment(List<Token> tokens) {
		// <Identifier> := <Expression>;
        return false;
	}
    private boolean isExpression(List<Token> tokens) {
		// <Unary operator><Subexpression> | <Subexpression>
        return false;
	}
    private boolean isSubexpression(List<Token> tokens) {
		// <Binary operator> <Subexpression>
        return false;
	}

    private boolean isVariablesDeclaration(List<Token> tokens) {
        // Var <List of variables>;
        return false;
    }
    private boolean isVariablesList(List<Token> tokens) {
        // <Identifier> | <Identifier><Comma> <List of variables>

        if (tokens.size() == 1 && Objects.equals(tokens.get(0).getType(), "Identifier") || tokens.get(0).getType().equals("Variables list")) {
            return true;
        }

        Token potentialIdentifier = tokens.get(0);
        Token potentialComma = tokens.get(1);
        ArrayList<Token> potentialVariablesList = new ArrayList<>(tokens.subList(2, tokens.size()));

        if (tokens.size() >= 3 && Objects.equals(potentialIdentifier.getType(), "Identifier") && Objects.equals(potentialComma.getType(), "Comma") && isVariablesList(potentialVariablesList) ) {
            return true;
        }

        return false;
    }
    private boolean isIdentifier(ArrayList<Token> tokens) {
		// <Letter><Identifier> | <Letter>

        if (tokens.size() == 1 && Objects.equals(tokens.get(0).getType(), "Letter")) {
            return true;
        }

        ArrayList<Token> others = new ArrayList<>(tokens.subList(1, tokens.size()));
        if (Objects.equals(tokens.get(0).getType(), "Letter") && isIdentifier(others)) {
            return true;
        }

        return false;
	}
    private boolean isConst(ArrayList<Token> tokens) {
		// <Digit><Const> | <Digit>

        if (tokens.size() == 1 && Objects.equals(tokens.get(0).getType(), "Digit")) {
            return true;
        }

        ArrayList<Token> others = new ArrayList<>(tokens.subList(1, tokens.size()));
        if (Objects.equals(tokens.get(0).getType(), "Digit") && isConst(others)) {
            return true;
        }

        return false;
	}

    private boolean isVarKeyword(ArrayList<Token> tokens) {
        // Var
        return getStringFromSimpleTokens(tokens).equals("Var");
    }
    private boolean isIfKeyword(ArrayList<Token> tokens) {
        // IF
        return getStringFromSimpleTokens(tokens).equals("IF");
    }
    private boolean isThenKeyword(ArrayList<Token> tokens) {
        // THEN
        return getStringFromSimpleTokens(tokens).equals("THEN");
    }
    private boolean isElseKeyword(ArrayList<Token> tokens) {
        // ELSE
        return getStringFromSimpleTokens(tokens).equals("ELSE");
    }

    private boolean isLetter(char c) {
        // <Letter>
        return Character.isLetter(c);
    }
	private boolean isDigit(char c) {
	    // <Digit>
	    return Character.isDigit(c);
    }
    private boolean isSpace(char c) {
        // <Space>
        return Character.isSpaceChar(c);
    }
    private boolean isComma(char c) {
        // ,
        return c == ',';
    }
    private boolean isAssignmentOperator(char c) {
        // =
        return c == '=';
    }
    private boolean isSemicolon(char c) {
        // ;
        return c == ';';
    }
    private boolean isUnaryOperator(char c) {
        // '-'
        return c == '-';
    }
    private boolean isBinaryOperator(String str) {
		// '-' | '+' | '*' | '/' | '<' | '>' | '=='
        return false;
	}

    private void printLexicalTree(Token root) {
        printNode(root, 0);
    }
    private void printNode(Token token, int indentCount) {
        StringBuffer indent = new StringBuffer();
        for(int i = 0; i < indentCount; i++) {
            indent.append("\t");
        }

        System.out.println(indent + token.getText());

        for(Token child : token.getChildren()) {
            printNode(child, indentCount + 1);
        }
    }
}
