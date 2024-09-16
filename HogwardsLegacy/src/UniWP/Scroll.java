package UniWP;

public class Scroll extends MagicItem {
    private Spell spell;

    public Scroll(String name, int usages, int price, int weight, Spell spell) {
        super(name, usages, price, weight);
        if (spell == null) throw new IllegalArgumentException();
        this.spell = spell;
    }

    @Override
    public String additionalOutputString() {
        return String.format("; casts %s", spell);
    }

    @Override
    public void useOn(MagicEffectRealization target) {
        if (tryUsage()) {
            spell.cast(this, target);
        }
    }
}
