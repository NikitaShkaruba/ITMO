package itmo.dbs.models;

import lombok.Data;
import javax.persistence.*;

@Data
@Entity
@Table(name = "animals")
public class Animal {
    @Id @GeneratedValue private Long id;
    private String name;

    @OneToOne
    @JoinColumn(name="textures_id")
    private Texture texture;

    Animal() {}
    public Animal(String name, Texture texture) {
        this.name = name;
        this.texture = texture;
    }
}