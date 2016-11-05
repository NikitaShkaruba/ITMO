package itmo.dbs.models;

import lombok.Data;
import javax.persistence.*;

@Data
@Entity
@Table(name = "photos")
public class Photo {
    @Id @GeneratedValue private Long id;
    @Lob private byte[] data;

    public Photo() {}
    public Photo(byte[] data) {
        this.data = data;
    }
}
