package UniWP;


import java.util.List;

public class Concoction extends Potion {
    private int health;
    private int mana ;
    private List<Spell> spells;

    public Concoction(String name, int usages, int price, int weight, int health, int mana, List<Spell> spells) {
        super(name, usages, price, weight);
        if (spells == null) throw new IllegalArgumentException("No go");
        if (health == 0 && mana == 0 && spells.isEmpty()) throw new IllegalArgumentException("No go");
        this.health = health;
        this.mana = mana;
        this.spells =  spells;
    }

    @Override
    public String additionalOutputString() {
        StringBuilder sb = new StringBuilder();
        if (health != 0) sb.append("; ").append(health > 0 ? "+" : "").append(health).append(" HP");
        if (mana != 0) sb.append("; ").append(mana > 0 ? "+" : "").append(mana).append(" MP");
        if (!spells.isEmpty()) sb.append("; cast ").append(spells);
        return sb.toString();
    }

    @Override
    public void useOn(MagicEffectRealization target) {
        if (target == null) throw new IllegalArgumentException("No go"); //CHECK
        if (tryUsage()) {
            if (health > 0) target.heal(health);
            else if (health < 0)target.takeDamage(Math.abs(health));
            if (mana > 0) target.enforceMagic(mana);
            else if(mana < 0)  target.weakenMagic(Math.abs(mana));
            for (Spell spell : spells) {
                spell.cast(this, target);
            }
        }
    }
}
