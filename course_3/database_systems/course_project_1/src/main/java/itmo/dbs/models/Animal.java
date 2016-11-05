package itmo.dbs.models;

import lombok.Data;
import javax.persistence.*;

@Data
@Entity
@Table(name = "animals")
public class Animal {
    @Id @GeneratedValue private Long id;
    private String name;

    @OneToOne @JoinColumn(name="texture_id")
    private Texture texture;

    public Animal() {}
    public Animal(String name, Texture texture) {
        this.name = name;
        this.texture = texture;
    }
}