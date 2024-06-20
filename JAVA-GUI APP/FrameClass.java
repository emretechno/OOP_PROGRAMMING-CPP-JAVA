import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.sound.sampled.*;
import java.io.File;
import java.io.IOException;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.net.URI;
import java.net.URISyntaxException;
public class FrameClass {
    private final JFrame frame;
    private JLabel animated;
    private int xCoordinate = 50;
    private int yCoordinate = 50;
    private int xVelocity = 2;
    private int yVelocity = 2;
    private int fontSize = 20;
    private int fontSizeVelocity = 1;
    private final String fontName = "Arial";
    private Clip backgroundMusicClip;



    public FrameClass(String title) {
        frame = new JFrame();
        frame.setTitle(title);
        frame.setSize(600, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

   set_Image();
        frame.setLayout(null);
        frame.setVisible(true);
        playBackgroundMusic(getClass().getResource("/d4vd - Romantic Homicide.wav"));
    }

    private void playBackgroundMusic(java.net.URL musicFilePath) {
        try {
            File musicFile = new File(musicFilePath.toURI()); // Convert URL to File
            AudioInputStream audioInput = AudioSystem.getAudioInputStream(musicFile);
            Clip clip = AudioSystem.getClip();
            clip.open(audioInput);
            clip.loop(Clip.LOOP_CONTINUOUSLY);  // Loop the music continuously
            clip.start();

        } catch (LineUnavailableException | IOException | UnsupportedAudioFileException | URISyntaxException e) {
            e.printStackTrace();
        }
    }

    public void set_Image() {
        ImagePanel imagePanel = new ImagePanel();
        frame.setContentPane(imagePanel);
    }

    public void add_animation() {
        animated = new JLabel("You go out with me ?");
        animated.setBounds(xCoordinate, yCoordinate, 400, 80);
        animated.setForeground(Color.RED);
        animated.setFont(new Font(fontName, Font.BOLD, fontSize));
        animated.setOpaque(false);
        frame.add(animated);

        Timer tm = new Timer(50, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                xCoordinate += xVelocity;
                yCoordinate += yVelocity;

                if (xCoordinate + 400 >= frame.getWidth() || xCoordinate <= 0){
                    xVelocity = -xVelocity;
                    addInstagramLabel(50,600,"Click HERE -> TO SAY YES!","https://www.instagram.com/direct/t/17842440608626210/");
                }

                if (yCoordinate + 80 >= frame.getHeight() || yCoordinate <= 0){
                    yVelocity = -yVelocity;
                    addInstagramLabel(200,400,"Click here if you not sure :(","https://tr.pinterest.com/pin/clark--455074737358263883/");

                }

                animated.setBounds(xCoordinate, yCoordinate, 400, 80);

                fontSize += fontSizeVelocity;
                if (fontSize >= 40 || fontSize <= 20) {
                    fontSizeVelocity = -fontSizeVelocity;
                }
                animated.setFont(new Font(fontName, Font.BOLD, fontSize));

                if (xCoordinate > 500) {
                    ((Timer) e.getSource()).stop();

                }
            }
        });
        tm.start();
    }
    private void addInstagramLabel(int a, int b, String text, String url) {
        JLabel instagramLabel = new JLabel(text);
        instagramLabel.setBounds(a, b, 400, 80);
        instagramLabel.setForeground(Color.RED);
        Font currentFont = instagramLabel.getFont();
        Font newFont = new Font(currentFont.getName(), Font.PLAIN, 18);
        instagramLabel.setFont(newFont);
        instagramLabel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        instagramLabel.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {

                openApp(url);
            }
        });
        frame.add(instagramLabel);
        frame.revalidate();
        frame.repaint();
    }

    private void openApp(String url){
        try {
            URI uri = new URI(url);
            Desktop.getDesktop().browse(uri);
        } catch (IOException | URISyntaxException ex) {
            ex.printStackTrace();

        }
    }


    private static class ImagePanel extends JPanel {
        private final Image backgroundImage;

        public ImagePanel() {
            // Load the image using getClass().getResource()
            backgroundImage = new ImageIcon(getClass().getResource("/images.jpg")).getImage();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            g.drawImage(backgroundImage, 0, 0, getWidth(), getHeight(), this);
        }
    }

    public static void main(String[] args) {
        FrameClass frameClass = new FrameClass("Animated Frame");

        frameClass.add_animation();
    }
}
