package controllers;

import org.neo4j.driver.v1.*;
import static org.neo4j.driver.v1.Values.parameters;

public class NeoFourJController {
  private Driver driver;
  private Session session;

  public NeoFourJController() {
    AuthToken authToken = AuthTokens.basic(System.getenv("JOVIAN_NEO4J_USER"), System.getenv("JOVIAN_NEO4J_PASS"));
    driver = GraphDatabase.driver( "bolt://146.185.143.190:7687", authToken);
    session = driver.session();
  }
  public void finalize() {
    session.close();
    driver.close();
  }

  public void fillDatabase() {
    int usersAmount = 1000000;
    for (int i = 0; i < usersAmount; i++) {
      String name = "user" + i;
      String surname = i % 2 == 0 ? "Ivanov" : "Petrov"; // Simulate heavy generator
      String email = surname + i + "@gmail.com";

      this.insertUser(name, surname, email);
    }
  }
  public void searchDatabase() {
    String surname = "Ivanov";

    StatementResult result = session.run("MATCH (a:User) WHERE a.surname = {surname} RETURN a.name AS name, a.surname AS surname, a.email as email", parameters("surname", surname));
    while(result.hasNext()) {
      Record user = result.next();
      System.out.println(user);
    }
  }

  public StatementResult insertUser(String name, String surname, String email) {
    return session.run("CREATE (a:User { name: {name}, surname: {surname}, email: {email} })", parameters("name", name, "surname", surname, "email", email));
  }
  public Record selectUser(String surname) {
    StatementResult result = session.run("MATCH (a:User) WHERE a.surname = {surname} RETURN a.name AS name, a.surname AS surname, a.email as email", parameters("surname", surname));
    return result.hasNext() ? result.next() : null;
  }
}
