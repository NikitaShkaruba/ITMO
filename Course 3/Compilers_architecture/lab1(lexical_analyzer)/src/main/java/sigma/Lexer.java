package sigma;

// Lexically analyzes some text
public class Lexer {
    public String analyze(String text) {
        return "Syntax error";
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

    private boolean isIdentifier(String str) {
		// <Буква> <Идент> | <Буква>
        return false;
	}
    private boolean isConst(String str) {
		// <Цифра> <Const> | <Цифра>
        return false;
	}
}
