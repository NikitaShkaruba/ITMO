package sample;

import javax.faces.bean.ManagedBean;

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
    final static String sacredPhrase = "Hello World!";

    public WorldSpeaker() {}

    public String getMessage() {
        return "WorldSpeaker says: " + sacredPhrase;
    }
}
