package sample;

import javax.faces.bean.ManagedBean;

/**
 * Created by Nikita Shkaruba on 11/29/15.
 * <p>
 * My contacts:
 * GitHub: https://github.com/SigmaOne
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 */

@ManagedBean(name = "WorldSpeaker")
public class WorldSpeaker {
    public WorldSpeaker() {}

    public String getMessage() {
        return "Hello, my lovely world!";
    }
}
