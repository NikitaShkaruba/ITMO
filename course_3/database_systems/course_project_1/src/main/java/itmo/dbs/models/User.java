package itmo.dbs.models;

import lombok.Data;

import javax.persistence.*;

@Data
@Entity
@Table(name = "users")
public class User {
    @Id @GeneratedValue private Long id;
    private String name;
    private long phone;
    private long moneyAmount;

    @OneToOne
    @JoinColumn(name="pet_id")
    private Pet pet;

    @OneToOne
    @JoinColumn(name="photo_id")
    private Photo photo;

    User() {}
    public User(String name, int phone, int moneyAmount, Pet pet, Photo photo) {
        this.name = name;
        this.phone = phone;
        this.moneyAmount = moneyAmount;
        this.pet = pet;
        this.photo = photo;
    }
}
