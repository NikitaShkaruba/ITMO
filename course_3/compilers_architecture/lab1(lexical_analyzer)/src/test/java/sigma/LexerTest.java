package sigma;

import org.junit.Test;

public class LexerTest {
    private Lexer lexer = new Lexer();

    @Test public void isConst() {
        assert(lexer.analyze("3228").equals("Const"));
    }

    @Test public void isIdentifier() {
        assert(lexer.analyze("myVar").equals("Identifier"));
    }
}
