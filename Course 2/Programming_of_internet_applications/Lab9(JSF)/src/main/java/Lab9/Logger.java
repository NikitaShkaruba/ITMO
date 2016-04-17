package Lab9;

import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;

@ManagedBean(name="logger", eager=true)
@ApplicationScoped
public class Logger {
    float x = 0, y = 0;

    public float getX() {
        return x;
    }
    public void setX(float value) {
        x = value;
    }
    public float getY() {
        return y;
    }
    public void setY(float value) {
        y = value;
    }
}
