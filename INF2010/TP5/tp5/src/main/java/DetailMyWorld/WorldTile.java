package DetailMyWorld;

public class WorldTile {

    //Classe qui represente un tile du world, juste pour stocker les coord pour avoir le plus haut-gauche dans notre queue

    private Integer xPos;
    private Integer yPos;
    int value;

    public WorldTile(int x, int y, int value){
        xPos = x;
        yPos = y;
        this.value = value;
    }

    public Integer getXPos() {
        return xPos;
    }

    public void setXPos(int xPos) {
        this.xPos = xPos;
    }

    public Integer getyPos() {
        return yPos;
    }

    public void setyPos(int yPos) {
        this.yPos = yPos;
    }

    public Integer getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }
}
