package itmo.dbs.models.custom_types;

public class HealthCondition {
    public long happiness;
    public long hungriness;
    public long cleanliness;

    public HealthCondition() {
        // Just for test
        this.happiness = 1;
        this.hungriness = 2;
        this.cleanliness = 3;
    }
    public HealthCondition(long happiness, long hungriness, long cleanliness) {
        this.happiness = happiness;
        this.hungriness = hungriness;
        this.cleanliness = cleanliness;
    }
}
