package itmo.dbs.models;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document(collection = "entertainments")
public class Entertainment {
    @Id public String id;
    public String name;
    public int quality;

    public Entertainment() {}
    public Entertainment(String name, int quality) {
        this.name = name;
        this.quality = quality;
    }

    public String getId() {
        return this.id;
    }
}
