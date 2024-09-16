package UniWP;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class Wizard implements MagicSource, Trader, MagicEffectRealization {
    private String name;
    private MagicLevel level;
    private int basicHP;
    private int HP ;
    private int basicMP;
    private int MP ;
    private int money;
    private Set<Spell> knownSpells;
    private Set<AttackingSpell> protectedFrom ;
    private int carryingCapacity ;
    private Set<Tradeable> inventory ;

    public Wizard(String name , MagicLevel level, int basicHP, int HP, int basicMP, int MP, int money, Set<Spell> knownSpells, Set<AttackingSpell> protectedFrom, int carryingCapacity, Set<Tradeable> inventory)   {
        if (name == null || name.isEmpty() || level == null || basicHP < 0|| HP < 0 || basicMP < level.toMana() || MP < 0 || money < 0 || carryingCapacity < 0 || knownSpells == null || protectedFrom == null || inventory == null)
            throw new IllegalArgumentException();
        this.name = name;
        this.level = level;
        this.basicHP = basicHP;
        this.HP = HP;
        this.basicMP = basicMP;
        this.MP = MP;
        this.money = money;
        this.carryingCapacity = carryingCapacity;
        this.knownSpells = new HashSet<>(knownSpells);
        this.protectedFrom = new HashSet<>(protectedFrom);
        this.inventory = new HashSet<>(inventory);
        if(inventoryTotalWeight() > carryingCapacity) throw new IllegalArgumentException();
    }

    public boolean isDead() {
        return this.HP == 0;
    }

    private int inventoryTotalWeight() {
        int totalWeight = 0;
        for (Tradeable item : this.inventory) {
            totalWeight += item.getWeight();
        }
        return totalWeight;
    }

    public boolean learn(Spell s) {
        if (s == null) throw new IllegalArgumentException();
        if (isDead()) return false;
        return knownSpells.add(s);
    }

    public boolean forget(Spell s) {
        if (s == null) throw new IllegalArgumentException("No go");
        if (isDead()) return false;
        return knownSpells.remove(s);
    }

    public boolean castSpell(Spell s, MagicEffectRealization target) {
        if (s == null || target == null) throw new IllegalArgumentException();
        if (isDead() || !knownSpells.contains(s)) return false;
        s.cast(this, target);
        return true;
    }

    public boolean castRandomSpell(MagicEffectRealization target) {
        if (target == null) throw new IllegalArgumentException();
        if (knownSpells.isEmpty()) return false;
        Spell randomSpell = knownSpells.stream().skip((int) (knownSpells.size() * Math.random())).findFirst().orElse(null);
        return castSpell(randomSpell, target);
    }

    public boolean useItem(Tradeable item, MagicEffectRealization target) {
        if (item == null || target == null) throw new IllegalArgumentException();
        if (isDead() || !inventory.contains(item)) return false;
        item.useOn(target);
        return true;
    }

    public boolean useRandomItem(MagicEffectRealization target) {
        if (this.inventory.isEmpty()) return false;
        Tradeable randomItem = inventory.stream().skip((int) (inventory.size() * Math.random())).findFirst().orElse(null);
        return useItem(randomItem, target);
    }

    public boolean sellItem(Tradeable item, Trader target) {
        if (item == null || target == null) throw new IllegalArgumentException();
        if (isDead()) return false;
        return item.purchase(this, target);
    }

    public boolean sellRandomItem(Trader target) {
        if (inventory.isEmpty()) return false;
        Tradeable randomItem = inventory.stream().skip((int) (inventory.size() * Math.random())).findFirst().orElse(null);
        return sellItem(randomItem, target);
    }

    @Override
    public String toString() {
        String knutOrKnuts = money == 1 ? "Knut" : "Knuts";
        String knownSpellsStr = knownSpells.isEmpty() ? "[]" : knownSpells.toString();
        String inventoryStr = inventory.isEmpty() ? "[]" : inventory.toString();
        return String.format("[%s(%s): %d/%d %d/%d; %d %s; knows %s; carries %s]",
                name, level.toString(), HP, basicHP, MP, basicMP, money, knutOrKnuts,
                knownSpellsStr, inventoryStr);
    }

    @Override
    public boolean provideMana(MagicLevel levelNeeded, int manaAmount) {
        if(levelNeeded == null || manaAmount < 0) throw new IllegalArgumentException("No go");
        if (isDead()) return false;
        if (level.ordinal() < levelNeeded.ordinal() || MP < manaAmount) return false;
        MP -= manaAmount;
        return true;
    }

    @Override
    public boolean possesses(Tradeable item) {
        if(item == null) throw new IllegalArgumentException("No go");
        return inventory.contains(item);
    }

    @Override
    public boolean canAfford(int amount) {
        if (amount < 0) throw new IllegalArgumentException();
        return money >= amount;
    }

    @Override
    public boolean hasCapacity(int weight) {
        if (weight < 0) throw new IllegalArgumentException();
        int sum = 0;
        sum = inventoryTotalWeight() + weight;
        if(sum<= carryingCapacity) return true;
        else return false;

    }

    @Override
    public boolean pay(int amount) {
        if (amount < 0) throw new IllegalArgumentException();
        if (isDead()) return false;
        if (money >= amount) {
            money -= amount;
            return true;
        }
        return false;
    }

    @Override
    public boolean earn(int amount) {
        if (amount < 0) throw new IllegalArgumentException();
        if (isDead()) return false;
        money += amount;
        return true;
    }

    @Override
    public boolean addToInventory(Tradeable item) {
        if (item == null) throw new IllegalArgumentException();
        if (this.hasCapacity(item.getWeight())) {
            return inventory.add(item);
        }
        return false;
    }

    @Override
    public boolean removeFromInventory(Tradeable item) {
        if (item == null) throw new IllegalArgumentException();
        return inventory.remove(item);
    }

    @Override
    public boolean canSteal() {
        return !isDead();
    }

    @Override
    public boolean steal(Trader thief) {
        if (thief == null) throw new IllegalArgumentException();
        if (thief == null || !thief.canSteal()) return false;
        if (inventory.isEmpty()) return false;
        Tradeable stolenItem = inventory.stream().skip((int) (inventory.size() * Math.random())).findFirst().orElse(null);
        return stolenItem != null && inventory.remove(stolenItem) && thief.addToInventory(stolenItem);
    }

    @Override
    public boolean isLootable() {
        return isDead();
    }

    @Override
    public boolean canLoot() {
        return !isDead();
    }

    @Override
    public boolean loot(Trader looter) {
        if (looter == null) throw new IllegalArgumentException();
        if (looter.canLoot() == false) return false;
        boolean test = false;
        if (this.isLootable()) {
            for (Iterator<Tradeable> it = this.inventory.iterator(); it.hasNext();) {
                Tradeable t = it.next();
                it.remove();
                if (looter.addToInventory(t)) {
                    test = true;
                }

            }
        } return test;
    }

    @Override
    public void takeDamage(int amount) {
        if (amount < 0) throw new IllegalArgumentException();
        HP = Math.max(0, HP - amount);
    }

    @Override
    public void takeDamagePercent(int percentage) {
        if (percentage < 0 || percentage > 100) {throw new IllegalArgumentException("No go");}
        HP = (int) Math.max(0, HP - basicHP * (percentage / 100.0));
    }

    @Override
    public void weakenMagic(int amount) {
        if (amount < 0) throw new IllegalArgumentException();
        MP = Math.max(0, MP - amount);
    }

    @Override
    public void weakenMagicPercent(int percentage) {
        if (percentage < 0 || percentage > 100) throw new IllegalArgumentException();
        MP =  (int) Math.max(0, MP - basicMP * (percentage / 100.0));
    }

    @Override
    public void heal(int amount) {
        if (amount < 0) throw new IllegalArgumentException();
        HP = HP + amount;
    }

    @Override
    public void healPercent(int percentage) {
        if (percentage < 0 || percentage > 100) throw new IllegalArgumentException();
        HP = (int)(HP + basicHP * (percentage / 100.0));
    }

    @Override
    public void enforceMagic(int amount) {
        if (amount < 0) throw new IllegalArgumentException();
        MP =  MP + amount;
    }

    @Override
    public void enforceMagicPercent(int percentage) {
        if (percentage < 0 || percentage > 100) {throw new IllegalArgumentException("No go");}
        MP = (int)(MP + basicMP * (percentage / 100.0));
    }

    @Override
    public boolean isProtected(Spell s) {
        if (s == null) {throw new IllegalArgumentException("No go");}
        return protectedFrom.contains(s);
    }

    @Override
    public void setProtection(Set<AttackingSpell> attacks) {
        if (attacks == null) throw new IllegalArgumentException();
        protectedFrom.addAll(attacks);
    }

    @Override
    public void removeProtection(Set<AttackingSpell> attacks) {
        if (attacks == null) throw new IllegalArgumentException();
        protectedFrom.removeAll(attacks);
    }
}
