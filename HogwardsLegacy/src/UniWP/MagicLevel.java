package UniWP;

public enum MagicLevel {
    NOOB(50, "*"),
    ADEPT(100, "**"),
    STUDENT(200, "***"),
    EXPERT(500, "****"),
    MASTER(1000, "*****");

    private final int MP;
    private final String STARS;

    MagicLevel(int MP, String STARS) {
        this.MP = MP;
        this.STARS = STARS;
    }

    public int toMana() {
        return MP;
    }
    
    @Override
    public String toString() {
        return STARS;
    }
}