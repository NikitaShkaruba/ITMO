package itmo.dbs.models;

import lombok.Data;
import javax.persistence.*;

@Data
@Entity
@Table(name = "sceneries")
public class Scenery {
    @Id @GeneratedValue private Long id;
    private String name;
    @Lob private byte[] texture;

    public Scenery() {}
    public Scenery(String name, byte[] texture) {
        this.name = name;
        this.texture = texture;
    }
}

