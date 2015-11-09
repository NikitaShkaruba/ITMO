package Lab4;

import javax.management.MBeanServer;
import javax.management.ObjectName;
import java.lang.management.ManagementFactory;

/**
 * Created by Nikita Shkaruba on 11/5/2015.
 * This project have a Readme.md on my GitHub, check it out, if you misunderstand something (!)
 *
 * My contacts:
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 * GitHub: https://github.com/SigmaOne
 */
public class Main {
    public static void main(String[] args) throws Exception {
        Controller controller = new Controller();

        MBeanServer mbs = ManagementFactory.getPlatformMBeanServer();
        ObjectName name = new ObjectName("MBeans:type=PointCounter");
        mbs.registerMBean(controller.getPointCounterMBean(), name);

        controller.startApplication();
    }
}
