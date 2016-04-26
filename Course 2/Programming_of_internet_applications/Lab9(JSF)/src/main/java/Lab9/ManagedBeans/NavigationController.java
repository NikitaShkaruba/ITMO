package Lab9.ManagedBeans;

import javax.faces.context.FacesContext;
import javax.faces.bean.SessionScoped;
import javax.faces.bean.ManagedBean;
import java.io.Serializable;

// I need this class just because of my Option 1131
// It's easy to write navigation rules right in link elements
@ManagedBean(name="controller", eager=true)
@SessionScoped
public class NavigationController implements Serializable {
    public String getPage() {
        String s = FacesContext.getCurrentInstance().getViewRoot().getViewId();

        return s.equals("/faces/home.xhtml")? "main" : "home";
    }
}
