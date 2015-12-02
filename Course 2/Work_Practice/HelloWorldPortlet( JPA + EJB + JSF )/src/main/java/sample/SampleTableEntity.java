package sample;

import javax.persistence.*;

/**
 * Created by root on 12/1/15.
 */
@Entity
@Table(name = "sampleTable", schema = "sql498356", catalog = "")
public class SampleTableEntity {
    private int id;
    private String string;

    @Id
    @Column(name = "id")
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    @Basic
    @Column(name = "string")
    public String getString() {
        return string;
    }

    public void setString(String string) {
        this.string = string;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        SampleTableEntity that = (SampleTableEntity) o;

        if (id != that.id) return false;
        if (string != null ? !string.equals(that.string) : that.string != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = id;
        result = 31 * result + (string != null ? string.hashCode() : 0);
        return result;
    }
}
