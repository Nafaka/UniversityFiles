package UniWP;

public interface Tradeable {

    int getPrice();

    int getWeight();

    private boolean transfer(Trader from, Trader to) {
        if(from.removeFromInventory(this) && to.addToInventory(this))
            return true;
        return false;
    }

    default boolean give(Trader giver, Trader taker) throws IllegalArgumentException {
        if (giver == null || taker == null || giver == taker) {
            throw new IllegalArgumentException("No go");
        }
        if(giver.possesses(this) && taker.hasCapacity(this.getWeight())){
            return transfer(giver,taker);
        }
        return false;
    }

    default boolean purchase(Trader seller, Trader buyer) throws IllegalArgumentException {
        if (seller == null || buyer == null || seller == buyer) {
            throw new IllegalArgumentException("No go");
        }
        if(seller.possesses(this) && buyer.canAfford(this.getPrice()) && buyer.hasCapacity(this.getWeight())) {
            buyer.pay(getPrice());
            seller.earn(getPrice());
            return transfer(seller, buyer);
        }
        return false;
    }

    void useOn(MagicEffectRealization target);
}