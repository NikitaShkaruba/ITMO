package itmo.dbs.models;

import lombok.Data;
import javax.persistence.*;
import java.sql.Date;

@Data
@Entity
@Table(name = "pets")
public class Pet {
    @Id @GeneratedValue private Long id;
    private String name;
    private Date birthDate;
    private Date deathDate;

    @OneToOne @JoinColumn(name="animal_id")
    private Animal animal;

    @OneToOne @JoinColumn(name="user_id")
    private User user;

    @OneToOne @JoinColumn(name="age_type_id")
    private AgeType ageType;
    // private HealthCondition healthCondition;

    Pet() {}
    public Pet(String name, Animal animal, User user, Date birthDate, Date deathDate/*, AgeType ageType */) {
        this.name = name;
        this.animal = animal;
        //this.user = user;
        this.birthDate = birthDate;
        this.deathDate = deathDate;
        // this.ageType = ageType;
    }
}
