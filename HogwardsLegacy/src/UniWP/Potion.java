package UniWP;

public abstract class Potion extends MagicItem {

    public Potion(String name, int usages, int price, int weight) {
        super(name, usages, price, weight);
    }

    public void drink(Wizard drinker) {
        useOn(drinker);
    }

    @Override
    public String usageString() {
        return getUsages() == 1 ? "gulp" : "gulps";
    }
}
