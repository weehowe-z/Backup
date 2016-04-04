package FileSocket;

import java.awt.*;
import java.awt.event.*;

public class GUI {
   private Frame mainFrame;
   private Label headerLabel;
   private Label statusLabel;
   private Panel controlPanel;
   private TextField textField;
   private boolean Flag = true;//whether has started a surver thread

   public GUI(){
      prepareGUI();
   }

   public static void main(String[] args){
      GUI demo = new GUI();
      demo.show();
   }

   private void prepareGUI(){
      mainFrame = new Frame("File Share Socket Demo");
      mainFrame.setSize(500,500);
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
      statusLabel.setSize(200,100);

      controlPanel = new Panel();
      controlPanel.setLayout(new FlowLayout());

      mainFrame.add(headerLabel);
      mainFrame.add(controlPanel);
      mainFrame.add(statusLabel);
      mainFrame.setVisible(true);
   }

   private void show(){
      runServer();
      headerLabel.setText("Press <ENTER> to begin download.");
      mainFrame.addKeyListener(new CustomKeyListener());
      textField  = new TextField(10);

      FileDialog fd = new FileDialog(mainFrame, "Choose a file", FileDialog.LOAD);
      fd.setDirectory("C:\\");
      fd.setVisible(true);
      fd.setFile("*.xml");
      String filename = fd.getFile();
      if (filename == null)
        System.out.println("You cancelled the choice");
      else
        System.out.println("You chose " + filename);

      // Button chooseButton = new Button("Choose Upload File");
      // Button pathButton = new Button("Choose Download Path");
      // // button.addActionListener(new ActionListener() {
      // //    public void actionPerformed(ActionEvent e) {
      // //       statusLabel.setText("Entered text:");
      // //    }
      // // });
      // // controlPanel.add(textField);
      //
      // chooseButton.setOnAction(
      // new EventHandler<ActionEvent>() {
      //   @Override
      //   public void handle(final ActionEvent e) {
      //       File file = fileChooser.showOpenDialog(stage);
      //       if (file != null) {
      //           openFile(file);
      //       }
      //   }
      // });

      // controlPanel.add(chooseButton);
      // controlPanel.add(pathButton);
      mainFrame.setVisible(true);
      statusLabel.setText("Socket running, you can see the terminal for more details.");
   }

   private void runServer() {
      if (Flag) {
          Flag = false;
          System.out.println("[GUI]:Server thread begin....");
          Thread Server = new Thread(new Server());
          Server.start();
      }
      else {
        System.out.println("[GUI]:Server already started, don't press <ENTER> again!");
      }
   }

   private void runClient() {
        System.out.println("[GUI]:Client thread begin....");
        Thread Client = new Thread(new Client());
        Client.start();
   }

   class CustomKeyListener implements KeyListener{
      public void keyTyped(KeyEvent e) {
      }

      public void keyPressed(KeyEvent e) {
         if(e.getKeyCode() == KeyEvent.VK_ESCAPE){
            // statusLabel.setText("Entered text: " + textField.getText());
            System.exit(-1);
         }
         else if (e.getKeyCode() == KeyEvent.VK_ENTER){
           statusLabel.setText("Download finish, press <ESC> to quit.");
          //  runServer();
          //  try {
          //    Thread.sleep(2000);
          //  }
          //  catch (Exception exception){
          //    System.out.println(exception);
          //  }
           runClient();
         }
      }

      public void keyReleased(KeyEvent e) {
      }
   }
}
