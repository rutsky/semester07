/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package hello;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import org.netbeans.microedition.lcdui.SplashScreen;

/**
 * @author bob
 */
public class HelloMIDlet extends MIDlet implements CommandListener, ItemCommandListener {

    private boolean midletPaused = false;

    //<editor-fold defaultstate="collapsed" desc=" Generated Fields ">//GEN-BEGIN:|fields|0|
    private Command exitCommand;
    private Command okCommand;
    private Command backCommand;
    private Command backCommand1;
    private Form form;
    private StringItem stringItem;
    private SplashScreen splashScreen;
    private Form isOOP;
    private ChoiceGroup choiceGroup;
    private Form isWeb;
    private List list;
    private Form form1;
    private TextField textField;
    private Image image1;
    private Font font;
    //</editor-fold>//GEN-END:|fields|0|

    /**
     * The HelloMIDlet constructor.
     */
    public HelloMIDlet() {
    }

    //<editor-fold defaultstate="collapsed" desc=" Generated Methods ">//GEN-BEGIN:|methods|0|
    //</editor-fold>//GEN-END:|methods|0|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: initialize ">//GEN-BEGIN:|0-initialize|0|0-preInitialize
    /**
     * Initilizes the application.
     * It is called only once when the MIDlet is started. The method is called before the <code>startMIDlet</code> method.
     */
    private void initialize() {//GEN-END:|0-initialize|0|0-preInitialize
        // write pre-initialize user code here
//GEN-LINE:|0-initialize|1|0-postInitialize
        // write post-initialize user code here
    }//GEN-BEGIN:|0-initialize|2|
    //</editor-fold>//GEN-END:|0-initialize|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: startMIDlet ">//GEN-BEGIN:|3-startMIDlet|0|3-preAction
    /**
     * Performs an action assigned to the Mobile Device - MIDlet Started point.
     */
    public void startMIDlet() {//GEN-END:|3-startMIDlet|0|3-preAction
        // write pre-action user code here
        switchDisplayable(null, getSplashScreen());//GEN-LINE:|3-startMIDlet|1|3-postAction
        // write post-action user code here
    }//GEN-BEGIN:|3-startMIDlet|2|
    //</editor-fold>//GEN-END:|3-startMIDlet|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: resumeMIDlet ">//GEN-BEGIN:|4-resumeMIDlet|0|4-preAction
    /**
     * Performs an action assigned to the Mobile Device - MIDlet Resumed point.
     */
    public void resumeMIDlet() {//GEN-END:|4-resumeMIDlet|0|4-preAction
        // write pre-action user code here
//GEN-LINE:|4-resumeMIDlet|1|4-postAction
        // write post-action user code here
    }//GEN-BEGIN:|4-resumeMIDlet|2|
    //</editor-fold>//GEN-END:|4-resumeMIDlet|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: switchDisplayable ">//GEN-BEGIN:|5-switchDisplayable|0|5-preSwitch
    /**
     * Switches a current displayable in a display. The <code>display</code> instance is taken from <code>getDisplay</code> method. This method is used by all actions in the design for switching displayable.
     * @param alert the Alert which is temporarily set to the display; if <code>null</code>, then <code>nextDisplayable</code> is set immediately
     * @param nextDisplayable the Displayable to be set
     */
    public void switchDisplayable(Alert alert, Displayable nextDisplayable) {//GEN-END:|5-switchDisplayable|0|5-preSwitch
        // write pre-switch user code here
        Display display = getDisplay();//GEN-BEGIN:|5-switchDisplayable|1|5-postSwitch
        if (alert == null) {
            display.setCurrent(nextDisplayable);
        } else {
            display.setCurrent(alert, nextDisplayable);
        }//GEN-END:|5-switchDisplayable|1|5-postSwitch
        // write post-switch user code here
    }//GEN-BEGIN:|5-switchDisplayable|2|
    //</editor-fold>//GEN-END:|5-switchDisplayable|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: commandAction for Displayables ">//GEN-BEGIN:|7-commandAction|0|7-preCommandAction
    /**
     * Called by a system to indicated that a command has been invoked on a particular displayable.
     * @param command the Command that was invoked
     * @param displayable the Displayable where the command was invoked
     */
    public void commandAction(Command command, Displayable displayable) {//GEN-END:|7-commandAction|0|7-preCommandAction
        // write pre-action user code here
        if (displayable == form) {//GEN-BEGIN:|7-commandAction|1|19-preAction
            if (command == exitCommand) {//GEN-END:|7-commandAction|1|19-preAction
                // write pre-action user code here
                exitMIDlet();//GEN-LINE:|7-commandAction|2|19-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|3|33-preAction
        } else if (displayable == isOOP) {
            if (command == backCommand) {//GEN-END:|7-commandAction|3|33-preAction
                // write pre-action user code here
                switchDisplayable(null, getForm());//GEN-LINE:|7-commandAction|4|33-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|5|50-preAction
        } else if (displayable == isWeb) {
            if (command == backCommand1) {//GEN-END:|7-commandAction|5|50-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsOOP());//GEN-LINE:|7-commandAction|6|50-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|7|56-preAction
        } else if (displayable == list) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|7|56-preAction
                // write pre-action user code here
                listAction();//GEN-LINE:|7-commandAction|8|56-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|9|24-preAction
        } else if (displayable == splashScreen) {
            if (command == SplashScreen.DISMISS_COMMAND) {//GEN-END:|7-commandAction|9|24-preAction
                // write pre-action user code here
                switchDisplayable(null, getForm());//GEN-LINE:|7-commandAction|10|24-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|11|7-postCommandAction
        }//GEN-END:|7-commandAction|11|7-postCommandAction
        // write post-action user code here
    }//GEN-BEGIN:|7-commandAction|12|
    //</editor-fold>//GEN-END:|7-commandAction|12|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: exitCommand ">//GEN-BEGIN:|18-getter|0|18-preInit
    /**
     * Returns an initiliazed instance of exitCommand component.
     * @return the initialized component instance
     */
    public Command getExitCommand() {
        if (exitCommand == null) {//GEN-END:|18-getter|0|18-preInit
            // write pre-init user code here
            exitCommand = new Command("Exit", Command.EXIT, 0);//GEN-LINE:|18-getter|1|18-postInit
            // write post-init user code here
        }//GEN-BEGIN:|18-getter|2|
        return exitCommand;
    }
    //</editor-fold>//GEN-END:|18-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: form ">//GEN-BEGIN:|14-getter|0|14-preInit
    /**
     * Returns an initiliazed instance of form component.
     * @return the initialized component instance
     */
    public Form getForm() {
        if (form == null) {//GEN-END:|14-getter|0|14-preInit
            // write pre-init user code here
            form = new Form("Welcome!", new Item[] { getStringItem() });//GEN-BEGIN:|14-getter|1|14-postInit
            form.addCommand(getExitCommand());
            form.setCommandListener(this);//GEN-END:|14-getter|1|14-postInit
            // write post-init user code here
        }//GEN-BEGIN:|14-getter|2|
        return form;
    }
    //</editor-fold>//GEN-END:|14-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: stringItem ">//GEN-BEGIN:|16-getter|0|16-preInit
    /**
     * Returns an initiliazed instance of stringItem component.
     * @return the initialized component instance
     */
    public StringItem getStringItem() {
        if (stringItem == null) {//GEN-END:|16-getter|0|16-preInit
            // write pre-init user code here
            stringItem = new StringItem("Hello,", "Think of one of popular programming languages, and I\'ll try to guess it");//GEN-BEGIN:|16-getter|1|16-postInit
            stringItem.addCommand(getOkCommand());
            stringItem.setItemCommandListener(this);//GEN-END:|16-getter|1|16-postInit
            // write post-init user code here
        }//GEN-BEGIN:|16-getter|2|
        return stringItem;
    }
    //</editor-fold>//GEN-END:|16-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: splashScreen ">//GEN-BEGIN:|22-getter|0|22-preInit
    /**
     * Returns an initiliazed instance of splashScreen component.
     * @return the initialized component instance
     */
    public SplashScreen getSplashScreen() {
        if (splashScreen == null) {//GEN-END:|22-getter|0|22-preInit
            // write pre-init user code here
            splashScreen = new SplashScreen(getDisplay());//GEN-BEGIN:|22-getter|1|22-postInit
            splashScreen.setTitle("Splash Screen");
            splashScreen.setCommandListener(this);
            splashScreen.setImage(getImage1());
            splashScreen.setText("Splash screen!");
            splashScreen.setTextFont(getFont());//GEN-END:|22-getter|1|22-postInit
            // write post-init user code here
        }//GEN-BEGIN:|22-getter|2|
        return splashScreen;
    }
    //</editor-fold>//GEN-END:|22-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: image1 ">//GEN-BEGIN:|25-getter|0|25-preInit
    /**
     * Returns an initiliazed instance of image1 component.
     * @return the initialized component instance
     */
    public Image getImage1() {
        if (image1 == null) {//GEN-END:|25-getter|0|25-preInit
            // write pre-init user code here
            try {//GEN-BEGIN:|25-getter|1|25-@java.io.IOException
                image1 = Image.createImage("/hello/logo.png");
            } catch (java.io.IOException e) {//GEN-END:|25-getter|1|25-@java.io.IOException
                e.printStackTrace();
            }//GEN-LINE:|25-getter|2|25-postInit
            // write post-init user code here
        }//GEN-BEGIN:|25-getter|3|
        return image1;
    }
    //</editor-fold>//GEN-END:|25-getter|3|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: font ">//GEN-BEGIN:|27-getter|0|27-preInit
    /**
     * Returns an initiliazed instance of font component.
     * @return the initialized component instance
     */
    public Font getFont() {
        if (font == null) {//GEN-END:|27-getter|0|27-preInit
            // write pre-init user code here
            font = Font.getDefaultFont();//GEN-LINE:|27-getter|1|27-postInit
            // write post-init user code here
        }//GEN-BEGIN:|27-getter|2|
        return font;
    }
    //</editor-fold>//GEN-END:|27-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: commandAction for Items ">//GEN-BEGIN:|17-itemCommandAction|0|17-preItemCommandAction
    /**
     * Called by a system to indicated that a command has been invoked on a particular item.
     * @param command the Command that was invoked
     * @param displayable the Item where the command was invoked
     */
    public void commandAction(Command command, Item item) {//GEN-END:|17-itemCommandAction|0|17-preItemCommandAction
        // write pre-action user code here
        if (item == choiceGroup) {//GEN-BEGIN:|17-itemCommandAction|1|53-preAction
            if (command == backCommand1) {//GEN-END:|17-itemCommandAction|1|53-preAction
                // write pre-action user code here
//GEN-LINE:|17-itemCommandAction|2|53-postAction
                // write post-action user code here
            } else if (command == okCommand) {//GEN-LINE:|17-itemCommandAction|3|41-preAction
                // write pre-action user code here
                method();//GEN-LINE:|17-itemCommandAction|4|41-postAction
                // write post-action user code here
            }//GEN-BEGIN:|17-itemCommandAction|5|30-preAction
        } else if (item == stringItem) {
            if (command == okCommand) {//GEN-END:|17-itemCommandAction|5|30-preAction
                // write pre-action user code here
                switchDisplayable(null, getList());//GEN-LINE:|17-itemCommandAction|6|30-postAction
                // write post-action user code here
            }//GEN-BEGIN:|17-itemCommandAction|7|17-postItemCommandAction
        }//GEN-END:|17-itemCommandAction|7|17-postItemCommandAction
        // write post-action user code here
    }//GEN-BEGIN:|17-itemCommandAction|8|
    //</editor-fold>//GEN-END:|17-itemCommandAction|8|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: okCommand ">//GEN-BEGIN:|29-getter|0|29-preInit
    /**
     * Returns an initiliazed instance of okCommand component.
     * @return the initialized component instance
     */
    public Command getOkCommand() {
        if (okCommand == null) {//GEN-END:|29-getter|0|29-preInit
            // write pre-init user code here
            okCommand = new Command("Next", Command.OK, 0);//GEN-LINE:|29-getter|1|29-postInit
            // write post-init user code here
        }//GEN-BEGIN:|29-getter|2|
        return okCommand;
    }
    //</editor-fold>//GEN-END:|29-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: backCommand ">//GEN-BEGIN:|32-getter|0|32-preInit
    /**
     * Returns an initiliazed instance of backCommand component.
     * @return the initialized component instance
     */
    public Command getBackCommand() {
        if (backCommand == null) {//GEN-END:|32-getter|0|32-preInit
            // write pre-init user code here
            backCommand = new Command("Back", Command.BACK, 0);//GEN-LINE:|32-getter|1|32-postInit
            // write post-init user code here
        }//GEN-BEGIN:|32-getter|2|
        return backCommand;
    }
    //</editor-fold>//GEN-END:|32-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isOOP ">//GEN-BEGIN:|28-getter|0|28-preInit
    /**
     * Returns an initiliazed instance of isOOP component.
     * @return the initialized component instance
     */
    public Form getIsOOP() {
        if (isOOP == null) {//GEN-END:|28-getter|0|28-preInit
            // write pre-init user code here
            isOOP = new Form("OOP", new Item[] { getChoiceGroup() });//GEN-BEGIN:|28-getter|1|28-postInit
            isOOP.addCommand(getBackCommand());
            isOOP.setCommandListener(this);//GEN-END:|28-getter|1|28-postInit
            // write post-init user code here
        }//GEN-BEGIN:|28-getter|2|
        return isOOP;
    }
    //</editor-fold>//GEN-END:|28-getter|2|



    //<editor-fold defaultstate="collapsed" desc=" Generated Method: method ">//GEN-BEGIN:|42-if|0|42-preIf
    /**
     * Performs an action assigned to the method if-point.
     */
    public void method() {//GEN-END:|42-if|0|42-preIf
        // enter pre-if user code here
        if (choiceGroup.getSelectedIndex() == 0) {//GEN-LINE:|42-if|1|43-preAction
            // write pre-action user code here
            switchDisplayable(null, getIsWeb());//GEN-LINE:|42-if|2|43-postAction
            // write post-action user code here
        } else {//GEN-LINE:|42-if|3|44-preAction
            // write pre-action user code here
            switchDisplayable(null, getForm());//GEN-LINE:|42-if|4|44-postAction
            // write post-action user code here
        }//GEN-LINE:|42-if|5|42-postIf
        // enter post-if user code here
    }//GEN-BEGIN:|42-if|6|
    //</editor-fold>//GEN-END:|42-if|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: choiceGroup ">//GEN-BEGIN:|36-getter|0|36-preInit
    /**
     * Returns an initiliazed instance of choiceGroup component.
     * @return the initialized component instance
     */
    public ChoiceGroup getChoiceGroup() {
        if (choiceGroup == null) {//GEN-END:|36-getter|0|36-preInit
            // write pre-init user code here
            choiceGroup = new ChoiceGroup("Is it object oriented?", Choice.EXCLUSIVE);//GEN-BEGIN:|36-getter|1|36-postInit
            choiceGroup.append("Yes", null);
            choiceGroup.append("No", null);
            choiceGroup.addCommand(getOkCommand());
            choiceGroup.addCommand(getBackCommand1());
            choiceGroup.setItemCommandListener(this);
            choiceGroup.setDefaultCommand(getBackCommand1());
            choiceGroup.setFitPolicy(Choice.TEXT_WRAP_DEFAULT);
            choiceGroup.setSelectedFlags(new boolean[] { false, false });//GEN-END:|36-getter|1|36-postInit
            // write post-init user code here
        }//GEN-BEGIN:|36-getter|2|
        return choiceGroup;
    }
    //</editor-fold>//GEN-END:|36-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: backCommand1 ">//GEN-BEGIN:|49-getter|0|49-preInit
    /**
     * Returns an initiliazed instance of backCommand1 component.
     * @return the initialized component instance
     */
    public Command getBackCommand1() {
        if (backCommand1 == null) {//GEN-END:|49-getter|0|49-preInit
            // write pre-init user code here
            backCommand1 = new Command("Back", Command.BACK, 0);//GEN-LINE:|49-getter|1|49-postInit
            // write post-init user code here
        }//GEN-BEGIN:|49-getter|2|
        return backCommand1;
    }
    //</editor-fold>//GEN-END:|49-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isWeb ">//GEN-BEGIN:|47-getter|0|47-preInit
    /**
     * Returns an initiliazed instance of isWeb component.
     * @return the initialized component instance
     */
    public Form getIsWeb() {
        if (isWeb == null) {//GEN-END:|47-getter|0|47-preInit
            // write pre-init user code here
            isWeb = new Form("Web");//GEN-BEGIN:|47-getter|1|47-postInit
            isWeb.addCommand(getBackCommand1());
            isWeb.setCommandListener(this);//GEN-END:|47-getter|1|47-postInit
            // write post-init user code here
        }//GEN-BEGIN:|47-getter|2|
        return isWeb;
    }
    //</editor-fold>//GEN-END:|47-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: list ">//GEN-BEGIN:|54-getter|0|54-preInit
    /**
     * Returns an initiliazed instance of list component.
     * @return the initialized component instance
     */
    public List getList() {
        if (list == null) {//GEN-END:|54-getter|0|54-preInit
            // write pre-init user code here
            list = new List("list", Choice.IMPLICIT);//GEN-BEGIN:|54-getter|1|54-postInit
            list.append("List Element 1", null);
            list.append("List Element 2", null);
            list.append("List Element 3", null);
            list.setCommandListener(this);
            list.setSelectedFlags(new boolean[] { false, false, false });//GEN-END:|54-getter|1|54-postInit
            // write post-init user code here
        }//GEN-BEGIN:|54-getter|2|
        return list;
    }
    //</editor-fold>//GEN-END:|54-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: listAction ">//GEN-BEGIN:|54-action|0|54-preAction
    /**
     * Performs an action assigned to the selected list element in the list component.
     */
    public void listAction() {//GEN-END:|54-action|0|54-preAction
        // enter pre-action user code here
        String __selectedString = getList().getString(getList().getSelectedIndex());//GEN-BEGIN:|54-action|1|58-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("List Element 1")) {//GEN-END:|54-action|1|58-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsWeb());//GEN-LINE:|54-action|2|58-postAction
                // write post-action user code here
            } else if (__selectedString.equals("List Element 2")) {//GEN-LINE:|54-action|3|59-preAction
                // write pre-action user code here
                method();//GEN-LINE:|54-action|4|59-postAction
                // write post-action user code here
            } else if (__selectedString.equals("List Element 3")) {//GEN-LINE:|54-action|5|60-preAction
                // write pre-action user code here
//GEN-LINE:|54-action|6|60-postAction
                // write post-action user code here
            }//GEN-BEGIN:|54-action|7|54-postAction
        }//GEN-END:|54-action|7|54-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|54-action|8|
    //</editor-fold>//GEN-END:|54-action|8|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: form1 ">//GEN-BEGIN:|61-getter|0|61-preInit
    /**
     * Returns an initiliazed instance of form1 component.
     * @return the initialized component instance
     */
    public Form getForm1() {
        if (form1 == null) {//GEN-END:|61-getter|0|61-preInit
            // write pre-init user code here
            form1 = new Form("form1", new Item[] { getTextField() });//GEN-LINE:|61-getter|1|61-postInit
            // write post-init user code here
        }//GEN-BEGIN:|61-getter|2|
        return form1;
    }
    //</editor-fold>//GEN-END:|61-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: textField ">//GEN-BEGIN:|63-getter|0|63-preInit
    /**
     * Returns an initiliazed instance of textField component.
     * @return the initialized component instance
     */
    public TextField getTextField() {
        if (textField == null) {//GEN-END:|63-getter|0|63-preInit
            // write pre-init user code here
            textField = new TextField("textField", null, 32, TextField.ANY);//GEN-LINE:|63-getter|1|63-postInit
            // write post-init user code here
        }//GEN-BEGIN:|63-getter|2|
        return textField;
    }
    //</editor-fold>//GEN-END:|63-getter|2|

    /**
     * Returns a display instance.
     * @return the display instance.
     */
    public Display getDisplay () {
        return Display.getDisplay(this);
    }

    /**
     * Exits MIDlet.
     */
    public void exitMIDlet() {
        switchDisplayable (null, null);
        destroyApp(true);
        notifyDestroyed();
    }

    /**
     * Called when MIDlet is started.
     * Checks whether the MIDlet have been already started and initialize/starts or resumes the MIDlet.
     */
    public void startApp() {
        if (midletPaused) {
            resumeMIDlet ();
        } else {
            initialize ();
            startMIDlet ();
        }
        midletPaused = false;
    }

    /**
     * Called when MIDlet is paused.
     */
    public void pauseApp() {
        midletPaused = true;
    }

    /**
     * Called to signal the MIDlet to terminate.
     * @param unconditional if true, then the MIDlet has to be unconditionally terminated and all resources has to be released.
     */
    public void destroyApp(boolean unconditional) {
    }

}
