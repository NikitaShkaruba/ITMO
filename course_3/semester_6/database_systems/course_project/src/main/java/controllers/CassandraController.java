package controllers;

import com.datastax.driver.core.Cluster;
import com.datastax.driver.core.ResultSet;
import com.datastax.driver.core.Session;

public class CassandraController {
  private Session session;

  public CassandraController() {
    Cluster cluster = Cluster.builder().
      addContactPoint("146.185.143.190").
      withPort(9042).
      withClusterName("Course 3 dbs test cluster").
      build();

    session = cluster.connect();
    this.useTestNamespace();
    this.prepareUsersTable();
  }

  public void fillDatabase() {
    int usersAmount = 1000000;
    for (int i = 0; i < usersAmount; i++) {
      String name = "user" + i;
      String surname = i % 2 == 0 ? "Ivanov" : "Petrov"; // Simulate heavy generator
      String email = surname + i + "@gmail.com";

      this.insertUser(i, name, surname, email);
    }
  }
  public void searchDatabase() {
    int usersAmount = 1000000;
    for (int i = 0; i < usersAmount; i++) {
      ResultSet set = this.getUser(i);
      System.out.println(set);
    }
  }

  // Initialization
  private void useTestNamespace() {
    session.execute("CREATE KEYSPACE IF NOT EXISTS test_keyspace WITH replication = {'class': 'SimpleStrategy', 'replication_factor' : 3}");
    session.execute("USE test_keyspace");
  }
  private void prepareUsersTable() {
    session.execute("CREATE TABLE IF NOT EXISTS users(id int PRIMARY KEY, name text, surname text, email text);");
  }

  // Users integration
  private void insertUser(int id, String name, String surname, String email) {
    session.execute("INSERT INTO users (id, name, surname, email) VALUES (" + id + ", '" + name + "', '" + surname + "', '" + email + "')");
  }
  private ResultSet getUser(int id) {
    if (id <= 0) {
      throw new Error("CassandraController Error");
    }

    return session.execute("SELECT * FROM users WHERE id = " + id);
  }
}
