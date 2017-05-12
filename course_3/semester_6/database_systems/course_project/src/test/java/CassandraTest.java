import org.junit.Test;
import controllers.*;

public class CassandraTest {
  @Test public void insertTest() {
    CassandraController cassandraController = new CassandraController();
    cassandraController.fillDatabase();
    cassandraController.searchDatabase();
  }
}
