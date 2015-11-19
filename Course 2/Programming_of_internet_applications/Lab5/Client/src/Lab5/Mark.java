package Lab5;

import java.awt.*;

/**
 * Created by nikita on 11/19/15.
 * <p/>
 * My contacts:
 * GitHub: https://github.com/SigmaOne
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 */
public class Mark extends Point {
    public enum States {suspended, in, outside }

    public States state;
    public Mark(Mark src) {
        super(src);

        this.state = src.state;
    }
    public Mark(Point src, States state) {
        super(src);
        this.state = state;
    }

}
