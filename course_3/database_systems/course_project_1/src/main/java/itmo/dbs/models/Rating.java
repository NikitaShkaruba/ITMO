package itmo.dbs.models;

import lombok.Data;
import javax.persistence.*;

@Data
@Entity
@Table(name = "ratings")
public class Rating {
    @Id @GeneratedValue private Long id;

    @OneToOne @JoinColumn(name="user_id")
    private User user;

    public Rating() {}
    public Rating(User user) {
        this.user = user;
    }
}
