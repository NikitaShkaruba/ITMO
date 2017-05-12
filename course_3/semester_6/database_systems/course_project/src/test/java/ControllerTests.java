import org.junit.Test;
import controllers.*;

public class ControllerTests {
  @Test public void cassandraTest() {
    CassandraController cassandraController = new CassandraController();

    cassandraController.fillDatabase();
    cassandraController.searchDatabase();
  }

  @Test public void neoFourJTest() {
    NeoFourJController neoFourJController = new NeoFourJController();

    neoFourJController.fillDatabase();
    neoFourJController.searchDatabase();
  }
}
