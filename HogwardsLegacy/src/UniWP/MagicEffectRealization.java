package UniWP;

import java.util.Set;


public interface MagicEffectRealization {
    default void takeDamage(int amount) {
        if (amount < 0) throw new IllegalArgumentException("No go");
    }

    default void takeDamagePercent(int percentage) {
        if (percentage < 0 || percentage > 100) {throw new IllegalArgumentException("No go");}
    }

    default void weakenMagic(int amount) {
        if (amount < 0) throw new IllegalArgumentException("No go");
    }

    default void weakenMagicPercent(int percentage) {
        if (percentage < 0 || percentage > 100) throw new IllegalArgumentException("No go");
    }

    default void heal(int amount) {
        if (amount < 0) throw new IllegalArgumentException("No go");

    }

    default void healPercent(int percentage) {
        if (percentage < 0 || percentage > 100) throw new IllegalArgumentException("No go");
    }

    default void enforceMagic(int amount) {
        if (amount < 0) throw new IllegalArgumentException("No go");
    }

    default void enforceMagicPercent(int percentage) {
        if (percentage < 0 || percentage > 100) throw new IllegalArgumentException("No go");
    }

    default boolean isProtected(Spell s) {
        if (s == null) throw new IllegalArgumentException("No go");
        return false;
    }

    default void setProtection(Set<AttackingSpell> attacks) {
        if (attacks == null) throw new IllegalArgumentException("No go");
    }

    default void removeProtection(Set<AttackingSpell> attacks) {
        if (attacks == null) throw new IllegalArgumentException("No go");
    }
}
