package itmo.dbs.models;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document(collection = "food")
public class Food {
    @Id public String id;
    public String name;
    public int satiety;

    public Food() {}
    public Food(String name, int satiety) {
        this.name = name;
        this.satiety = satiety;
    }
}
