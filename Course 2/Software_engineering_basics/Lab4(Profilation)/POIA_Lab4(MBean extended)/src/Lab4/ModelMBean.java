package Lab4;

import javax.management.NotificationEmitter;

/**
 * Created by Nikita Shkaruba on 11/9/2015.
 *
 * My contacts:
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 * GitHub: https://github.com/SigmaOne
 */

// Point counter MBean
public interface ModelMBean extends NotificationEmitter {
    int getAllPointsCount();
    int getHitPointsCount();
}
