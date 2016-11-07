package itmo.dbs.models;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;
import java.util.Date;

@Document(collection = "pets")
public class Pet {
    @Id public String id;
    public String name;
    // public User user;
    public String species;
    public Date birth_date;
    public Date death_date;
    public int happiness;
    public int hungriness;
    public int illness;

    public Pet() {}
    public Pet(String name, Species species) {
        this.name = name;
        this.species = species.id;

        this.birth_date = new Date();
        this.happiness = 2;
        this.hungriness = 8;
        this.illness = 0;
    }
}
