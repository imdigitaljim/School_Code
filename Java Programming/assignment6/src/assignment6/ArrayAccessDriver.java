package assignment6;
/*
Bach, James
COP-3252
Assignment 6
3/21/2015
*/

// ArrayAccessDriver.java
import javax.swing.JFrame;

public class ArrayAccessDriver
{   
   // execute application
   public static void main( String args[] )
   {
      ArrayAccess application = new ArrayAccess();
      application.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
      application.setSize( 400, 200 );
      application.setVisible( true );
   }
} // end class ArrayAccessDriver