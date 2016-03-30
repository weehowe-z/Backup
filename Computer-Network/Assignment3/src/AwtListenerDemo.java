package FileSocket;

import java.awt.*;
import java.awt.event.*;

public class AwtListenerDemo {
   private Frame mainFrame;
   private Label headerLabel;
   private Label statusLabel;
   private Panel controlPanel;
   private TextField textField;

   public AwtListenerDemo(){
      prepareGUI();
   }

   public static void main(String[] args){
      AwtListenerDemo  awtListenerDemo = new AwtListenerDemo();
      awtListenerDemo.showKeyListenerDemo();
   }

   private void prepareGUI(){
      mainFrame = new Frame("File Share Socket Demo");
      mainFrame.setSize(400,400);
      mainFrame.setLayout(new GridLayout(3, 1));
      mainFrame.addWindowListener(new WindowAdapter() {
         public void windowClosing(WindowEvent windowEvent){
            System.exit(0);
         }
      });

      headerLabel = new Label();
      headerLabel.setAlignment(Label.CENTER);
      statusLabel = new Label();
      statusLabel.setAlignment(Label.CENTER);
      statusLabel.setSize(350,100);

      controlPanel = new Panel();
      controlPanel.setLayout(new FlowLayout());

      mainFrame.add(headerLabel);
      mainFrame.add(controlPanel);
      mainFrame.add(statusLabel);
      mainFrame.setVisible(true);
   }

   private void showKeyListenerDemo(){
      headerLabel.setText("Press <ENTER> to begin download.");
      mainFrame.addKeyListener(new CustomKeyListener());
      textField  = new TextField(10);
      // Button button = new Button("Download");
      // button.addActionListener(new ActionListener() {
      //    public void actionPerformed(ActionEvent e) {
      //       statusLabel.setText("Entered text:");
      //    }
      // });
      // controlPanel.add(textField);
      // controlPanel.add(button);
      mainFrame.setVisible(true);
   }

   class CustomKeyListener implements KeyListener{
      public void keyTyped(KeyEvent e) {
      }

      public void keyPressed(KeyEvent e) {
         if(e.getKeyCode() == KeyEvent.VK_ESCAPE){
            // statusLabel.setText("Entered text: " + textField.getText());
            // statusLabel.setText("Begin Download");
            System.exit(-1);
         }
         else if (e.getKeyCode() == KeyEvent.VK_ENTER){
           statusLabel.setText("Socket running");
         }
      }

      public void keyReleased(KeyEvent e) {
      }
   }
}
