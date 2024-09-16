package UniWP;

public class ManaPotion extends Potion {
    private int mana;

    public ManaPotion(String name, int usages, int price, int weight, int mana) {
        super(name, usages, price, weight);
        if (mana < 0) throw new IllegalArgumentException("No go");
        this.mana = mana;
    }

    @Override
    public String additionalOutputString() {
        return "; +" + mana + " MP";
    }

    @Override
    public void useOn(MagicEffectRealization target) {
        if (tryUsage()) {
            target.enforceMagic(mana);
        }
    }
}