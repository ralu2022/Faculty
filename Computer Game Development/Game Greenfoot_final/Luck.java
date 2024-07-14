import greenfoot.*; 


public class Luck extends Actor
{
    public void end()
    {
        if(getY() >=599||getY() <=1){
            getWorld().removeObject(this);
        }
    }
    public void checkdouble(Actor i)
    {
        if( i != null){
            getWorld().removeObject(i);
        }
    }
    
    public void move(int speed){
        setLocation(getX(),getY() + speed);
        
    }
    
    public void act()
    {
        int speed = -2;
        Luck b = new Luck();
        Actor i = getOneIntersectingObject(Luck.class);
        move(speed);
        checkdouble(i);
        end();
    }
}
