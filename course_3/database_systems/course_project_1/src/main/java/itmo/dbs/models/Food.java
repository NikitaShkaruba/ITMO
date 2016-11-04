package itmo.dbs.models;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;
import lombok.Data;

@Data
@Entity
@Table(name = "food")
public class Food {
    @Id @GeneratedValue private Long id;
    private String name;
    private Integer satiety;

    Food() {} // Jpa only
    public Food(String name, int satiety) {
        this.name = name;
        this.satiety = satiety;
    }
}
