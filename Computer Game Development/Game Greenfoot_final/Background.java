import greenfoot.*;  // (World, Actor, GreenfootImage, Greenfoot and MouseInfo)

/**
 * Write a description of class Background here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Background extends World
{

    /**
     * Constructor for objects of class Background.
     * 
     */
    public Background()
    {    
        // Create a new world with 600x400 cells with a cell size of 1x1 pixels.
        super(900, 700, 1); 
        prepare();
    }
    
    /**
     * Prepare the world for the start of the program.
     * That is: create the initial objects and add them to the world.
     */
    private void prepare()
    {
        Rocket rocket = new Rocket();
        addObject(rocket,195,380);
        Asteroid asteroid = new Asteroid();
        addObject(asteroid,712,78);
        Asteroid asteroid2 = new Asteroid();
        addObject(asteroid2,862,298);
        Asteroid asteroid3 = new Asteroid();
        addObject(asteroid3,718,485);
        Asteroid asteroid4 = new Asteroid();
        addObject(asteroid4,842,140);
        Asteroid asteroid5 = new Asteroid();
        addObject(asteroid5,795,633);
        Asteroid asteroid6 = new Asteroid();
        addObject(asteroid6,609,154);
        Luck luck = new Luck();
        addObject(luck,685,313);
        Luck luck2 = new Luck();
        addObject(luck2,859,435);
        Luck luck3 = new Luck();
        addObject(luck3,814,55);
        Luck luck4 = new Luck();
        addObject(luck4,828,578);
        Luck luck5 = new Luck();
        addObject(luck5,76,666);
        Luck luck6 = new Luck();
        addObject(luck6,595,474);
        Asteroid asteroid7 = new Asteroid();
        addObject(asteroid7,298,663);
        Luck luck7 = new Luck();
        addObject(luck7,560,602);
        Asteroid asteroid8 = new Asteroid();
        addObject(asteroid8,441,61);
        Asteroid asteroid9 = new Asteroid();
        addObject(asteroid9,406,555);
        Asteroid asteroid10 = new Asteroid();
        addObject(asteroid10,486,648);
        Luck luck8 = new Luck();
        addObject(luck8,168,581);
        Asteroid asteroid11 = new Asteroid();
        addObject(asteroid11,56,516);
        Luck luck9 = new Luck();
        addObject(luck9,293,512);
        rocket.setLocation(68,166);
        Luck luck10 = new Luck();
        addObject(luck10,446,394);
        Luck luck11 = new Luck();
        addObject(luck11,728,199);
        Asteroid asteroid12 = new Asteroid();
        addObject(asteroid12,208,412);
        Luck luck12 = new Luck();
        addObject(luck12,110,275);
        asteroid12.setLocation(382,365);
        asteroid12.setLocation(570,305);
        asteroid11.setLocation(79,570);
        asteroid7.setLocation(175,643);
        luck9.setLocation(275,658);
        asteroid9.setLocation(317,558);
        Luck luck13 = new Luck();
        addObject(luck13,233,415);
        Luck luck14 = new Luck();
        addObject(luck14,394,192);
        Asteroid asteroid13 = new Asteroid();
        addObject(asteroid13,481,496);
    }
    
   
}
