package sample;

import org.hibernate.ejb.HibernatePersistence;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.spi.PersistenceProvider;
import java.util.HashMap;
import java.util.List;

/**
 * Created by nikita on 12/1/15.
 * <p>
 * My contacts:
 * GitHub: https://github.com/SigmaOne
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 */

@Stateless
public class DataControllerImpl implements DataController {
    public static final String SELECT_QUERY = "select string from SampleTableEntity";

    public List<String> getWords() {
        // Get proper entity manager
        PersistenceProvider provider = new HibernatePersistence();
        EntityManagerFactory factory = provider.createEntityManagerFactory("NewPersistenceUnit", new HashMap());
        EntityManager entityManager = factory.createEntityManager();

        return entityManager.createQuery(SELECT_QUERY).getResultList();
    }
}
