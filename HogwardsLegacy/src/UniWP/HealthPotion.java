package UniWP;

public class HealthPotion extends Potion {
    private int health;

    public HealthPotion(String name, int usages, int price, int weight, int health) {
        super(name, usages, price, weight);
        if (health < 0) throw new IllegalArgumentException("No go");
        this.health = health;
    }

    @Override
    public String additionalOutputString() {
        return "; +" + health + " HP";
    }

    @Override
    public void useOn(MagicEffectRealization target) {
        if (tryUsage()) {
            target.heal(health);
        }
    }
}