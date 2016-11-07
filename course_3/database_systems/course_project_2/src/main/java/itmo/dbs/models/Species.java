package itmo.dbs.models;

import org.springframework.data.annotation.Id;

public class Species {
    @Id public String id;
    public String name;
    public byte[] texture;

    public Species() {}
    public Species(String name, byte[] texture) {
        this.name = name;
        this.texture = texture;
    }
}
