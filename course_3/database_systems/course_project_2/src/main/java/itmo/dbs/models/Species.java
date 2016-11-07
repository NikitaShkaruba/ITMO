package itmo.dbs.models;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document(collection = "species")
public class Species {
    @Id private String id;
    private String name;
    private byte[] texture;

    public Species() {}
    public Species(String name, byte[] texture) {
        this.name = name;
        this.texture = texture;
    }

    public String getId() {
        return this.id;
    }
}
