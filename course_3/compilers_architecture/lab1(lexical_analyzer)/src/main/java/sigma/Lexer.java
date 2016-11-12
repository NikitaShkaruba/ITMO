package sigma;

import java.lang.UnsupportedOperationException;
import java.util.ArrayList;

// Lexically analyzes one code line
public class Lexer {
    public String analyze(String text) {
        ArrayList<Token> words = new ArrayList<>();
        ArrayList<Token> word = new ArrayList<>();
        Token root;

        // Gather words
        for (int i = 0; i < text.length(); i++) {
            char c = text.charAt(i);

            try {
                String type = detectChar(c);
                Token token = new Token(String.valueOf(c), type);

                if (token.getType().equals("Space") || i == text.length() - 1) {
                    word.add(token);

                    String content = getStringFromSimpleTokens(word);
                    String wordType = detectWordType(word);
                    Token parent = new Token(content, wordType, word);

                    words.add(parent);
                } else {
                    word.add(token);
                }
            } catch (Exception ex) {
                return "Syntax error";
            }
        }

        // Return root's type
        if (words.size() == 1) {
            String content = getStringFromTokens(words);
            root = words.get(0);
            printLexicalTree(root);

            return root.getType();
        } else if (words.size() > 1) {
            String content = getStringFromTokens(words);
            return null;
        } else {
            return "Syntax error";
        }
    }

    private String getStringFromTokens(ArrayList<Token> tokens) {
        StringBuilder str = new StringBuilder();

        for(Token token: tokens) {
            str.append(token.getText()).append(" ");
        }

        return str.toString();
    }
    private String getStringFromSimpleTokens(ArrayList<Token> tokens) {
        StringBuilder str = new StringBuilder();

        for(Token token: tokens) {
            str.append(token.getText());
        }

        return str.toString();
    }

    private boolean isVariableDeclarations(String text) {
        // Var <List of variables>;
        throw new UnsupportedOperationException();
    }
    private boolean isOperandList(String str) {
        //  <Identifier> | <Identifier> , <List of variables>
        throw new UnsupportedOperationException();
    }
    private boolean isOperand(String str) {
        // <Identifier> | <Const>
        throw new UnsupportedOperationException();
    }

    private boolean areComputations(String str) {
        // <List of operators>
        throw new UnsupportedOperationException();
    }
    private boolean isOperatorsLists(String str) {
        // <Operator> | <Operator> <List of operators>
        throw new UnsupportedOperationException();
    }
    private boolean isOperator(String str) {
        // <Assignment> | <Complex operator> | <Unary operator> | <Binary operator>
        throw new UnsupportedOperationException();
    }
    private boolean isUnaryOperator(String str) {
        // '-'
        throw new UnsupportedOperationException();
    }
    private boolean isBinaryOperator(String str) {
		// '-' | '+' | '*' | '/' | '<' | '>' | '=='
        throw new UnsupportedOperationException();
	}
    private boolean isComplexOperator(String str) {
		// IF <Expression> THEN <Operator> | IF <Expression> THEN <Operator> ELSE <Operator>
        throw new UnsupportedOperationException();
	}

    private boolean isAssignment(String str) {
		// <Identifier> := <Expression>;
        throw new UnsupportedOperationException();
	}
    private boolean isExpression(String str) {
		// <Unary operator><Subexpression> | <Subexpression>
        throw new UnsupportedOperationException();
	}
    private boolean isSubExpression(String str) {
		// <Binary operator> <Subexpression>
        throw new UnsupportedOperationException();
	}

	private String detectWordType(ArrayList<Token> tokens) throws Exception {
        if (isIdentifier(tokens))
	        return "Identifier";
        if (isConst(tokens))
            return "Const";
        else
            throw new Exception("No such word in Grammar");
    }
    private boolean isIdentifier(ArrayList<Token> tokens) {
		// <Letter><Identifier> | <Letter>

        if (tokens.size() == 1 && tokens.get(0).getType() == "Letter")
            return true;

        ArrayList<Token> others = new ArrayList<>(tokens.subList(1, tokens.size()));
        if (tokens.get(0).getType() == "Letter" && isIdentifier(others))
            return true;

        return false;
	}
    private boolean isConst(ArrayList<Token> tokens) {
		// <Digit><Const> | <Digit>

        if (tokens.size() == 1 && tokens.get(0).getType() == "Digit")
            return true;

        ArrayList<Token> others = new ArrayList<>(tokens.subList(1, tokens.size()));
        if (tokens.get(0).getType() == "Digit" && isConst(others))
            return true;

        return false;
	}

	public String detectChar(char c) throws Exception {
	    if (isLetter(c))
	        return "Letter";
        if (isDigit(c))
            return "Digit";
        if (isSpace(c))
            return "Space";
        else
            throw new Exception("No such char in Grammar");
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
        return Character.isSpaceChar(c);
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
