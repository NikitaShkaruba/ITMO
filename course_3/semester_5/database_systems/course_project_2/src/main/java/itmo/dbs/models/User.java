package itmo.dbs.models;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;
import org.springframework.data.mongodb.core.mapping.Field;

@Document(collection = "users")
public class User {
    @Id public String id;
    public String name;
    public String phone;
    public byte[] photo;

    @Field(value = "money_amount")
    public int moneyAmount;

    @Field(value = "is_admin")
    public boolean isAdmin;

    // References
    public String pet;
    public String[] friends;

    public User() {}
    public User(String name, String phone, boolean isAdmin) {
        this.name = name;
        this.phone = phone;
        this.isAdmin = isAdmin;
    }
}
