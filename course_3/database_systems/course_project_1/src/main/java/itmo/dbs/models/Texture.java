package itmo.dbs.models;

import lombok.Data;
import javax.persistence.*;

@Data
@Entity
@Table(name = "textures")
public class Texture {
    @Id @GeneratedValue private Long id;
    @Lob private byte[] texture;

    Texture() {} // Jpa only
    public Texture(byte[] texture) {
        this.texture = texture;
    }
}