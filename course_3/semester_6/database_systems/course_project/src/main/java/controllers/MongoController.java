package controllers;

import com.mongodb.*;
import org.neo4j.driver.v1.StatementResult;

import static org.neo4j.driver.v1.Values.parameters;

public class MongoController {
  MongoClient mongoClient;
  DB db;
  DBCollection users;

  public MongoController() {
    mongoClient = new MongoClient("146.185.143.190", 27017);
    db = mongoClient.getDB("course_project_2_db");
    users = db.getCollection("users");

    this.insertUser("Nikita", "Shkaruba", "sh.sigmaone@gmail.com");
  }

  public void fillDatabase() {
    int usersAmount = 1000000;
    for (int i = 0; i < usersAmount; i++) {
      String name = "user" + i;
      String surname = i % 2 == 0 ? "Petrov" : "Ivanov"; // Simulate heavy generator
      String email = surname + i + "@gmail.com";

      this.insertUser(name, surname, email);
    }
  }
  public void searchDatabase() {
    DBObject user = this.selectOneUser();
    System.out.println(user);
  }

  public WriteResult insertUser(String name, String surname, String email) {
    BasicDBObject doc = new BasicDBObject("type", "user").append("name", name).append("surname", surname).append("email", email);
    return users.insert(doc);
  }
  public DBObject selectOneUser() {
    DBObject user = users.findOne();
    return user;
  }
}
