package sample;

import org.hibernate.ejb.HibernatePersistence;

import javax.faces.bean.ManagedBean;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.spi.PersistenceProvider;
import java.util.HashMap;
import java.util.List;

/**
 * Created by nikita on 11/24/15.
 * <p>
 * My contacts:
 * GitHub: https://github.com/SigmaOne
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 */

@ManagedBean(name = "WorldSpeaker")
public class WorldSpeaker {
    public static final String SELECT_QUERY = "select string from STableEntity";

    public WorldSpeaker() {}

    public String getMessage() {
        // Get proper entity manager
        PersistenceProvider provider = new HibernatePersistence();
        EntityManagerFactory factory = provider.createEntityManagerFactory("NewPersistenceUnit", new HashMap());
        EntityManager entityManager = factory.createEntityManager();

        // Gain data and work with it
        List<String> sacredStrings = entityManager.createQuery(SELECT_QUERY).getResultList();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < sacredStrings.size(); i++)
            sb.append(sacredStrings.get(i) + " ");

        return sb.toString();
    }
}