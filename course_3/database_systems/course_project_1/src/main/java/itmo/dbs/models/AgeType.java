package itmo.dbs.models;

import lombok.Data;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;

@Data
@Entity
@Table(name = "age_types")
public class AgeType {
    @Id @GeneratedValue private Long id;
    private String name;

    public AgeType() {}
    public AgeType(String name) {
        this.name = name;
    }
}
