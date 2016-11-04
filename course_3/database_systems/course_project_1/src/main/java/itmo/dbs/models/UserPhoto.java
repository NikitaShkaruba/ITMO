package itmo.dbs.models;

import lombok.Data;
import javax.persistence.*;

@Data
@Entity
@Table(name = "user_photoes")
public class UserPhoto {
    @Id @GeneratedValue private Long id;
    @Lob private byte[] data;

    UserPhoto() {}
    public UserPhoto(byte[] data) {
        this.data = data;
    }
}
