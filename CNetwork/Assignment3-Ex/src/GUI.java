package FileSocket;

import java.io.File;
import java.awt.*;
import java.awt.event.*;

public class GUI {
   private Frame mainFrame;
   private Label headerLabel;
   private Label statusLabel;
   private Panel controlPanel;
   private TextField textField;
   private FileDialog fd;//file selector
   private boolean Flag = true;//whether has started a surver thread
   private TextField portText;
   private TextField addressText;
   private File file = null;
   private String filename = null;

   public GUI(){
      prepareGUI();
   }

   public static void main(String[] args){
      GUI demo = new GUI();
      demo.show();
   }

   private void prepareGUI(){
      mainFrame = new Frame("File Share Socket Demo");
      mainFrame.setSize(400,500);
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
      headerLabel.setText("Press <ENTER> to begin download.");
      // mainFrame.addKeyListener(new CustomKeyListener());

      //As Server
      fd = new FileDialog(mainFrame, "Select file");
      Label portLabel = new Label("[Server]Please enter server's port number:");
      Button chooseButton = new Button("Choose File");
      Button serverStartButton = new Button("Start Server");
      portText  = new TextField("2680",6);

      chooseButton.addActionListener(new ActionListener() {
         @Override
         public void actionPerformed(ActionEvent e) {
             chooseFile();
         }
      });

      serverStartButton.addActionListener(new ActionListener() {
         @Override
         public void actionPerformed(ActionEvent e) {
             startServer();
         }
      });

      controlPanel.add(portLabel);
      controlPanel.add(portText);
      controlPanel.add(chooseButton);
      controlPanel.add(serverStartButton);

      Label splitLabel = new Label("-----------------------------------------------------------------------------------------------------");
      controlPanel.add(splitLabel);

      //As Client
      Label addressLabel = new Label("[Client]Please enter the target url:");
      Button downloadStartButton = new Button("Start Download");
      addressText  = new TextField("0.0.0.0:2680",18);

      downloadStartButton.addActionListener(new ActionListener() {
         @Override
         public void actionPerformed(ActionEvent e) {
             startDownload();
         }
      });

      controlPanel.add(addressLabel);
      controlPanel.add(addressText);
      controlPanel.add(downloadStartButton);




      // controlPanel.add(pathButton);
      mainFrame.setVisible(true);
      // statusLabel.setText("Socket running, you can see the terminal for more details.");
   }

   private void chooseFile(){
       fd.setVisible(true);
       File files[] = fd.getFiles();
       if (files.length == 1){
         filename = fd.getFile();
         file = fd.getFiles()[0];
         System.out.println("[GUI]:You've selected '" + filename +"'");
         statusLabel.setText("You've selected '" + filename +"'");
       }
   }

   private void startServer(){
      //  if (file == null){
      //    System.out.println("[GUI]:Please choose a file to send!");
      //    statusLabel.setText("Please choose a file to send!");
      //    return;
      //  }
       if (portText.getText().equals("")){
         runServer(file,filename,2680);
       }
       else {
         int portNumber = Integer.parseInt(portText.getText());
         runServer(file,filename,portNumber);
       }
   }

   private void startDownload(){
       if (addressText.getText().equals("")){
         System.out.println("[GUI]:Please specify the download url!");
         statusLabel.setText("Please specify the download url!");
         return;
       }
       String url = addressText.getText();
       String attrs[] = url.split(":");
       if (attrs.length != 2){
         System.out.println("[GUI]:Please specify correct url!");
         statusLabel.setText("Please specify the correct url!");
         return;
       }
       runClient(attrs[0],Integer.parseInt(attrs[1]));
   }

   private void runServer(File file, String filename, int portNumber) {
      if (Flag) {
          Flag = false;
          System.out.println("[GUI]:Server thread begin....");
          Thread Server = new Thread(new Server(file,filename,portNumber));
          Server.start();
      }
      else {
        System.out.println("[GUI]:Server already started, don't press <ENTER> again!");
      }
   }

   private void runClient(String hostname, int portNumber) {
        System.out.println("[GUI]:Client thread begin....");
        Thread Client = new Thread(new Client(hostname, portNumber));
        Client.start();
   }

  //  class CustomKeyListener implements KeyListener{
  //     public void keyTyped(KeyEvent e) {
  //     }
   //
  //     public void keyPressed(KeyEvent e) {
  //        if(e.getKeyCode() == KeyEvent.VK_ESCAPE){
  //           // statusLabel.setText("Entered text: " + textField.getText());
  //           System.exit(-1);
  //        }
  //        else if (e.getKeyCode() == KeyEvent.VK_ENTER){
  //          statusLabel.setText("Download finish, press <ESC> to quit.");
  //         //  runServer();
  //         //  try {
  //         //    Thread.sleep(2000);
  //         //  }
  //         //  catch (Exception exception){
  //         //    System.out.println(exception);
  //         //  }
  //          runClient();
  //        }
  //     }
   //
  //     public void keyReleased(KeyEvent e) {
  //     }
  //  }
}
