import greenfoot.*;  // (World, Actor, GreenfootImage, Greenfoot and MouseInfo)

/**
 * Write a description of class Rocket here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Rocket extends Actor
{
    int score = 0;
    
    public void act()
    {
        getWorld().showText(" Scor: " + score, 70, 30);
        checkkey();
        end();
        addscore();     
    }
    
    public void checkkey(){
        if(Greenfoot.isKeyDown("left")){
            if(getX()>=215){
                setLocation(getX() -2,getY());
                }
            }
            if(Greenfoot.isKeyDown("right")){
            if(getX()<=598){
                setLocation(getX() +2,getY());
                }
            }
            if(Greenfoot.isKeyDown("up")){
                setLocation(getX(),getY() -2);
            }
            
            if(Greenfoot.isKeyDown("down")){
                setLocation(getX(),getY() +2);
            }
            
    }
    public void end(){
        if(isTouching(Asteroid.class)){
            getWorld().showText("Joc Terminat \n Scor final: " + score, 300, 300);
            Greenfoot.stop();}
        }
    public void addscore(){
        if( isTouching(Luck.class)){
            score = score + 20;

        removeTouching(Luck.class);
    }
    }
    public void eat(Class clss)
    {
        Actor actor = getOneObjectAtOffset(0, 0, clss);
        if(actor != null) {
            getWorld().removeObject(actor);
        }
    }
    
     public boolean canSee(Class clss)
    {
        Actor actor = getOneObjectAtOffset(0, 0, clss);
        return actor != null;        
    }
      public void lookForBee()
    {
         if ( canSee(Luck.class) ) 
        {
            eat(Luck.class);
            Greenfoot.playSound("mixkit-classic-alarm-995.wav");
        }
    }
        
}

