package itmo.dbs.models;

import itmo.dbs.models.custom_types.HealthCondition;
import lombok.Data;
import org.hibernate.annotations.Type;

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

    @Type(type = "itmo.dbs.models.custom_types.HealthConditionType")
    @Column(name = "state")
    private HealthCondition healthCondition;

    public Pet() {}
    public Pet(String name, Animal animal, User user, Date birthDate, Date deathDate) {
        this.name = name;
        this.animal = animal;
        this.user = user;
        this.birthDate = birthDate;
        this.deathDate = deathDate;
        this.ageType = new AgeType("Egg");
    }
}
