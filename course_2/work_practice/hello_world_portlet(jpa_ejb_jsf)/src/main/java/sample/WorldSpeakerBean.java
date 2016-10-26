package sample;

import org.hibernate.ejb.HibernatePersistence;

import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.spi.PersistenceProvider;
import java.util.HashMap;
import java.util.List;

/**
 * Created by Nikita Shkaruba on 11/29/15.
 * <p>
 * My contacts:
 * GitHub: https://github.com/SigmaOne
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 */

@ManagedBean(name = "WorldSpeaker")
public class WorldSpeakerBean {
    @EJB
    DataController dataController;

    public WorldSpeakerBean() {}

    public String getMessage() {
        List<String> sacredStrings = dataController.getWords();
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < sacredStrings.size(); i++)
            sb.append(sacredStrings.get(i) + " ");

        return sb.toString();
    }
}