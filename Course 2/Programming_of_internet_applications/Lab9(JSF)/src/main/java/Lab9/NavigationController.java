package Lab9;

import java.io.Serializable;
import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;
import javax.faces.context.FacesContext;

@ManagedBean(name="controller", eager=true)
@ApplicationScoped
public class NavigationController implements Serializable {
    public String getPage() {
        String s = FacesContext.getCurrentInstance().getViewRoot().getViewId();
        if (s.equals("/faces/home.xhtml")) {
            return "main";
        } else {
            return "home";
        }
    }
}
