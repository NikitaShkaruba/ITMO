package sigma;

import java.util.ArrayList;
import java.util.List;

// Todo: Make type private variable a Enum, not String
public class Token {
    private String type; 
    private String text;

    private Token parent;
    private ArrayList<Token> children = new ArrayList<>();

    // Construct leaf token
    public Token(String text, String type) {
        this.type = type;
        this.text = text;
    }
    // Construct parent token
    public Token(String text, String type, List<Token> children) {
        this(text, type);

        for(Token child : children)
            addChild(child);
    }

    public void addChild(Token child) {
        this.children.add(child);
        child.setParent(this);
    }
    public ArrayList<Token> getChildren() {
        return children;
    }

    private void setParent(Token parent) {
        this.parent = parent;
    }

    public String getType() {
        return type;
    }
    public String getText() {
        return text;
    }
}
