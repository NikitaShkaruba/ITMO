package itmo.databases;

import javax.ws.rs.ApplicationPath;
import org.glassfish.jersey.server.ResourceConfig;

/**
 * Class-configuration, which finds all the resource controllers
 */
@ApplicationPath("/")
public class Main extends ResourceConfig {
    public Main() {
       // Add a package to scan for rest controllers
       packages("itmo.databases.controllers");
    }
}
