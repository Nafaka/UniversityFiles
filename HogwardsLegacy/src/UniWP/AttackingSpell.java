package UniWP;

import java.util.Set;

public class AttackingSpell extends Spell {
    private boolean type;
    private boolean percentage;
    private int amount;

    public AttackingSpell(String name, int manaCost, MagicLevel levelNeeded, boolean type, boolean percentage, int amount) {
        super(name, manaCost, levelNeeded);
        if (amount < 0 || (percentage && (amount < 0 || amount > 100)))
            throw new IllegalArgumentException();
        this.type = type;
        this.percentage = percentage;
        this.amount = amount;
    }

    @Override
    public void doEffect(MagicEffectRealization target) {
        if (target.isProtected(this)) {
            target.removeProtection(Set.of(this));
        } else {
            if (type) {
                if (percentage) {
                    target.takeDamagePercent(amount);
                } else {
                    target.takeDamage(amount);
                }
            } else {
                if (percentage) {
                    target.weakenMagicPercent(amount);
                } else {
                    target.weakenMagic(amount);
                }
            }
        }
    }

    @Override
    public String additionalOutputString() {
        return String.format("; -%d %s%s", amount, (percentage ? "% " : ""), (type ? "HP" : "MP"));
    }
}