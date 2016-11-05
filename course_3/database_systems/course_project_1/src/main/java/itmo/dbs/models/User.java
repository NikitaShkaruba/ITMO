package itmo.dbs.models;

import lombok.Data;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

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

    @ManyToMany(cascade={CascadeType.ALL})
    @JoinTable(name="friends",
            joinColumns={@JoinColumn(name="from_id")},
            inverseJoinColumns={@JoinColumn(name="to_id")})
    private Set<User> friends = new HashSet<User>();

    @ManyToMany(cascade={CascadeType.ALL})
    @JoinTable(name="user_cosmetics",
            joinColumns={@JoinColumn(name="user_id")},
            inverseJoinColumns={@JoinColumn(name="cosmetic_id")})
    private Set<Cosmetic> ownedCosmetics = new HashSet<Cosmetic>();

    User() {}
    public User(String name, int phone, int moneyAmount, Pet pet, Photo photo) {
        this.name = name;
        this.phone = phone;
        this.moneyAmount = moneyAmount;
        this.pet = pet;
        this.photo = photo;
    }

    @Override
    public boolean equals(Object o) {
        if(o == null)
            return false;

        User account = (User) o;
        return id.equals(account.id);
    }

    @Override
    public int hashCode() {
        int result = (int) (id ^ (id >>> 32));
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + new Long(phone).hashCode();
        return result;
    }

    @Override
    public String toString() {
        return name;
    }
}
