package Lab9;

import java.io.Serializable;
import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;

@ManagedBean(name="helloWorld", eager=true)
@ApplicationScoped
public class HelloWorldController implements Serializable {
    public String getName() {
        return "Sigma";
    }
}
