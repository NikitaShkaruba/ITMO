package MBeans;

/**
 * Created by Nikita Shkaruba on 11/9/2015.
 * <p>
 * My contacts:
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 * GitHub: https://github.com/SigmaOne
 */
public class PointCounter implements PointCounterMBean {
    private int allCount = 0;
    private int hitCount = 0;

    public PointCounter() {}

    public void addHitPoint() {
        allCount++;
        hitCount++;

        tryBeep();
    }
    public void addMissPoint() {
        allCount++;

        tryBeep();
    }
    public void removeHitPoint() {
        allCount--;
        hitCount--;

        tryBeep();
    }
    public void removeMissPoint() {
        allCount--;

        tryBeep();
    }
    public void shiftToHit() {
        hitCount++;
    }
    public void shiftToMiss() {
        hitCount--;
    }

    @Override
    public int getAllCount() {
        return allCount;
    }

    @Override
    public int getHitCount() {
        return hitCount;
    }

    private void tryBeep() {
        if (allCount % 15 == 0)
            System.out.println("You have added " + allCount + " points, congratulations!");
    }
}
