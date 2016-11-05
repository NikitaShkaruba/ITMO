package itmo.dbs.models;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;

@Data
@Entity
@Table(name = "entertainments")
public class Entertainment {
    @Id @GeneratedValue private Long id;
    private String name;
    private Integer quality;

    public Entertainment() {}
    public Entertainment(String name, int quality) {
        this.name = name;
        this.quality = quality;
    }
}

