package sigma;

import java.util.ArrayList;
import java.util.List;

public class Token {
    private String type;
    private String value;

    private Token parent;
    private ArrayList<Token> children = new ArrayList<>();

    // Construct leaf token
    public Token(String value, String type) {
        this.type = type;
        this.value = value;
    }
    // Construct parent token
    public Token(String value, String type, List<Token> children) {
        this(value, type);

        for(Token child : children)
            addChild(child);
    }

    public void addChild(Token child) {
        this.children.add(child);
        child.setParent(this);
    }
    private void setParent(Token parent) {
        this.parent = parent;
    }

    public String getType() {
        return type;
    }
    public String getValue() {
        return value;
    }
}
