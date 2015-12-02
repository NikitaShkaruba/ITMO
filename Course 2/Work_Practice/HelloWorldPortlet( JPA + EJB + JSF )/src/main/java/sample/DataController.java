package sample;

import javax.ejb.Local;
import javax.ejb.Remote;
import java.util.List;

/**
 * Created by nikita on 12/1/15.
 * <p>
 * My contacts:
 * GitHub: https://github.com/SigmaOne
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 */

@Remote
public interface DataController {
    public List<String> getWords();
}
