package itmo.dbs.models;

import lombok.Data;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;

@Data
@Entity
@Table(name = "cosmetics")
public class Cosmetic {
    @Id @GeneratedValue private Long id;
    private String name;
    private String type;
    private Long price;

    public Cosmetic() {}
    public Cosmetic(String name, String type, long price) {
        this.name = name;
        this.type = type;
        this.price = price;
    }
}

