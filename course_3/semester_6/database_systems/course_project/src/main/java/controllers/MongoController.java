package controllers;

import com.mongodb.*;

public class MongoController {
  private DBCollection users;

  public MongoController() {
    MongoClient mongoClient = new MongoClient("146.185.143.190", 27017);
    DB db = mongoClient.getDB("course_project_2_db");
    users = db.getCollection("users");
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

  private WriteResult insertUser(String name, String surname, String email) {
    BasicDBObject doc = new BasicDBObject("type", "user").append("name", name).append("surname", surname).append("email", email);
    return users.insert(doc);
  }
  private DBObject selectOneUser() {
    DBObject user = users.findOne();
    return user;
  }
}
