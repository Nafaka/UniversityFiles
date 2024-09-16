package UniWP;

public class HealingSpell extends Spell {
    private boolean type;
    private boolean percentage;
    private int amount;

    public HealingSpell(String name, int manaCost, MagicLevel levelNeeded, boolean type, boolean percentage, int amount) {
        super(name, manaCost, levelNeeded);
        if (amount < 0 || (percentage && (amount < 0 || amount > 100)))
            throw new IllegalArgumentException();
        this.type = type;
        this.percentage = percentage;
        this.amount = amount;
    }

    @Override
    public void doEffect(MagicEffectRealization target) {
        if (type) {
            if (percentage) {
                target.healPercent(amount);
            } else {
                target.heal(amount);
            }
        } else {
            if (percentage) {
                target.enforceMagicPercent(amount);
            } else {
                target.enforceMagic(amount);
            }
        }
    }

    @Override
    public String additionalOutputString() {
        return String.format("; +%d %s%s", amount, (percentage ? "% " : ""), (type ? "HP" : "MP"));
    }
}
