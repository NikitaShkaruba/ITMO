package Lab9.ManagedBeans;

import java.io.Serializable;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.context.FacesContext;

// I do need this class just because of my Option 1131
@ManagedBean(name="controller", eager=true)
@SessionScoped
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
