package itmo.dbs.models;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document(collection = "ratings")
public class Rating {
    @Id public String id;
    public int position;

    // References
    public String user;

    public Rating() {}
    public Rating(int position, User user){
        this.position = position;
        this.user = user.id;
    }

    public String getId() {
        return this.id;
    }
}
