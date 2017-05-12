package itmo.dbs.models;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;
import org.springframework.data.mongodb.core.mapping.Field;

import java.util.Date;

@Document(collection = "pets")
public class Pet {
    @Id public String id;
    public String name;
    public int happiness;
    public int hungriness;
    public int illness;

    @Field(value = "birth_date")
    public Date birthDate;

    @Field(value = "death_date")
    public Date deathDate;

    // References
    public String user;
    public String species;

    public Pet() {}
    public Pet(String name, Species species, User user) {
        this.name = name;
        this.species = species.id;
        this.user = user.id;

        this.birthDate = new Date();
        this.happiness = 2;
        this.hungriness = 8;
        this.illness = 0;
    }
}
