package sigma;

import sun.reflect.generics.reflectiveObjects.NotImplementedException;
import java.util.ArrayList;

// Lexically analyzes some text
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
        } else if (words.size() == 0) {
            return "Syntax error";
        } else {
            throw new NotImplementedException();
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
        // Var <Список переменных>;
        return false;
    }
    private boolean isOperandList(String str) {
        //  <Идент> | <Идент> , <Список переменных>
        return false;
    }
    private boolean isOperand(String str) {
        // <Идент> | <Const>
        return false;
    }

    private boolean areComputations(String str) {
        // <Список операторов>
        return false;
    }
    private boolean isOperatorsLists(String str) {
        // <Оператор> | <Оператор> <Список операторов>
        return false;
    }
    private boolean isOperator(String str) {
        // <Присваивание> | < Сложный оператор >
        return false;
    }
    private boolean isUnaryOperator(String str) {
        // '-'
        return false;
    }
    private boolean isBinaryOperator(String str) {
		// '-' | '+' | '*' | '/' | '<' | '>' | '=='
        return false;
	}
    private boolean isComplexOperator(String str) {
		// IF <Выражение> THEN <Оператор> | IF <Выражение> THEN <Оператор> ELSE <Оператор>
        return false;
	}

    private boolean isAssignment(String str) {
		// <Идент> := <Выражение>;
        return false;
	}
    private boolean isExpression(String str) {
		// <Ун.оп.><Подвыражение> | <Подвыражение>
        return false;
	}
    private boolean isSubExpression(String str) {
		// <Бин.оп.> <Подвыражение>
        return false;
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
		// <Буква> <Идент> | <Буква>

        if (tokens.size() == 1 && tokens.get(0).getType() == "Letter")
            return true;

        ArrayList<Token> others = new ArrayList(tokens.subList(1, tokens.size()));
        if (tokens.get(0).getType() == "Letter" && isIdentifier(others))
            return true;

        return false;
	}
    private boolean isConst(ArrayList<Token> tokens) {
		// <Цифра> <Const> | <Цифра>

        if (tokens.size() == 1 && tokens.get(0).getType() == "Digit")
            return true;

        ArrayList<Token> others = new ArrayList(tokens.subList(1, tokens.size()));
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
        // <letter>
        return Character.isLetter(c);
    }
	private boolean isDigit(char c) {
	    // <digit>
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
