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
    private Command okCommand1;
    private Command okCommand2;
    private Command okCommand3;
    private Form menu;
    private StringItem stringItem;
    private SplashScreen splashScreen;
    private List isWeb;
    private List isVM;
    private List isBrowser;
    private List JavaScript;
    private Form Fail;
    private StringItem stringItem1;
    private Form Success;
    private List isMS;
    private List CSharp;
    private List Java;
    private List isOOP;
    private List isIndent;
    private List Python;
    private List Ruby;
    private List isRegexp;
    private List PHP;
    private List Perl;
    private List isCompilable;
    private List isOOP1;
    private List isTemplate;
    private List CPlusPLus;
    private List Delphi;
    private List isBegin;
    private List Pascal;
    private List C;
    private List isDB;
    private List PLSQL;
    private List MATLAB;
    private Image image1;
    private Font font;
    private Ticker ticker;
    private Ticker ticker1;
    private Ticker ticker2;
    private Ticker ticker3;
    private Ticker ticker4;
    private Ticker ticker5;
    private Ticker ticker6;
    private Ticker ticker7;
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
        if (displayable == C) {//GEN-BEGIN:|7-commandAction|1|236-preAction
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|1|236-preAction
                // write pre-action user code here
                CAction();//GEN-LINE:|7-commandAction|2|236-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|3|206-preAction
        } else if (displayable == CPlusPLus) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|3|206-preAction
                // write pre-action user code here
                CPlusPLusAction();//GEN-LINE:|7-commandAction|4|206-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|5|112-preAction
        } else if (displayable == CSharp) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|5|112-preAction
                // write pre-action user code here
                CSharpAction();//GEN-LINE:|7-commandAction|6|112-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|7|214-preAction
        } else if (displayable == Delphi) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|7|214-preAction
                // write pre-action user code here
                DelphiAction();//GEN-LINE:|7-commandAction|8|214-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|9|161-preAction
        } else if (displayable == Fail) {
            if (command == okCommand3) {//GEN-END:|7-commandAction|9|161-preAction
                // write pre-action user code here
                switchDisplayable(null, getMenu());//GEN-LINE:|7-commandAction|10|161-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|11|120-preAction
        } else if (displayable == Java) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|11|120-preAction
                // write pre-action user code here
                JavaAction();//GEN-LINE:|7-commandAction|12|120-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|13|91-preAction
        } else if (displayable == JavaScript) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|13|91-preAction
                // write pre-action user code here
                JavaScriptAction();//GEN-LINE:|7-commandAction|14|91-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|15|258-preAction
        } else if (displayable == MATLAB) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|15|258-preAction
                // write pre-action user code here
                MATLABAction();//GEN-LINE:|7-commandAction|16|258-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|17|172-preAction
        } else if (displayable == PHP) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|17|172-preAction
                // write pre-action user code here
                PHPAction();//GEN-LINE:|7-commandAction|18|172-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|19|250-preAction
        } else if (displayable == PLSQL) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|19|250-preAction
                // write pre-action user code here
                PLSQLAction();//GEN-LINE:|7-commandAction|20|250-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|21|228-preAction
        } else if (displayable == Pascal) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|21|228-preAction
                // write pre-action user code here
                PascalAction();//GEN-LINE:|7-commandAction|22|228-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|23|180-preAction
        } else if (displayable == Perl) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|23|180-preAction
                // write pre-action user code here
                PerlAction();//GEN-LINE:|7-commandAction|24|180-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|25|141-preAction
        } else if (displayable == Python) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|25|141-preAction
                // write pre-action user code here
                PythonAction();//GEN-LINE:|7-commandAction|26|141-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|27|149-preAction
        } else if (displayable == Ruby) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|27|149-preAction
                // write pre-action user code here
                RubyAction();//GEN-LINE:|7-commandAction|28|149-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|29|157-preAction
        } else if (displayable == Success) {
            if (command == okCommand1) {//GEN-END:|7-commandAction|29|157-preAction
                // write pre-action user code here
                switchDisplayable(null, getMenu());//GEN-LINE:|7-commandAction|30|157-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|31|222-preAction
        } else if (displayable == isBegin) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|31|222-preAction
                // write pre-action user code here
                isBeginAction();//GEN-LINE:|7-commandAction|32|222-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|33|85-preAction
        } else if (displayable == isBrowser) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|33|85-preAction
                // write pre-action user code here
                isBrowserAction();//GEN-LINE:|7-commandAction|34|85-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|35|188-preAction
        } else if (displayable == isCompilable) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|35|188-preAction
                // write pre-action user code here
                isCompilableAction();//GEN-LINE:|7-commandAction|36|188-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|37|244-preAction
        } else if (displayable == isDB) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|37|244-preAction
                // write pre-action user code here
                isDBAction();//GEN-LINE:|7-commandAction|38|244-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|39|135-preAction
        } else if (displayable == isIndent) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|39|135-preAction
                // write pre-action user code here
                isIndentAction();//GEN-LINE:|7-commandAction|40|135-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|41|106-preAction
        } else if (displayable == isMS) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|41|106-preAction
                // write pre-action user code here
                isMSAction();//GEN-LINE:|7-commandAction|42|106-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|43|128-preAction
        } else if (displayable == isOOP) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|43|128-preAction
                // write pre-action user code here
                isOOPAction();//GEN-LINE:|7-commandAction|44|128-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|45|194-preAction
        } else if (displayable == isOOP1) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|45|194-preAction
                // write pre-action user code here
                isOOP1Action();//GEN-LINE:|7-commandAction|46|194-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|47|166-preAction
        } else if (displayable == isRegexp) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|47|166-preAction
                // write pre-action user code here
                isRegexpAction();//GEN-LINE:|7-commandAction|48|166-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|49|200-preAction
        } else if (displayable == isTemplate) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|49|200-preAction
                // write pre-action user code here
                isTemplateAction();//GEN-LINE:|7-commandAction|50|200-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|51|79-preAction
        } else if (displayable == isVM) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|51|79-preAction
                // write pre-action user code here
                isVMAction();//GEN-LINE:|7-commandAction|52|79-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|53|71-preAction
        } else if (displayable == isWeb) {
            if (command == List.SELECT_COMMAND) {//GEN-END:|7-commandAction|53|71-preAction
                // write pre-action user code here
                isWebAction();//GEN-LINE:|7-commandAction|54|71-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|55|19-preAction
        } else if (displayable == menu) {
            if (command == exitCommand) {//GEN-END:|7-commandAction|55|19-preAction
                // write pre-action user code here
                exitMIDlet();//GEN-LINE:|7-commandAction|56|19-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|57|24-preAction
        } else if (displayable == splashScreen) {
            if (command == SplashScreen.DISMISS_COMMAND) {//GEN-END:|7-commandAction|57|24-preAction
                // write pre-action user code here
                switchDisplayable(null, getMenu());//GEN-LINE:|7-commandAction|58|24-postAction
                // write post-action user code here
            }//GEN-BEGIN:|7-commandAction|59|7-postCommandAction
        }//GEN-END:|7-commandAction|59|7-postCommandAction
        // write post-action user code here
    }//GEN-BEGIN:|7-commandAction|60|
    //</editor-fold>//GEN-END:|7-commandAction|60|

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

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: menu ">//GEN-BEGIN:|14-getter|0|14-preInit
    /**
     * Returns an initiliazed instance of menu component.
     * @return the initialized component instance
     */
    public Form getMenu() {
        if (menu == null) {//GEN-END:|14-getter|0|14-preInit
            // write pre-init user code here
            menu = new Form("Welcome!", new Item[] { getStringItem() });//GEN-BEGIN:|14-getter|1|14-postInit
            menu.addCommand(getExitCommand());
            menu.setCommandListener(this);//GEN-END:|14-getter|1|14-postInit
            // write post-init user code here
        }//GEN-BEGIN:|14-getter|2|
        return menu;
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
            stringItem = new StringItem("", "Think of one of popular programming languages, and I\'ll try to guess it");//GEN-BEGIN:|16-getter|1|16-postInit
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
        if (item == stringItem) {//GEN-BEGIN:|17-itemCommandAction|1|30-preAction
            if (command == okCommand) {//GEN-END:|17-itemCommandAction|1|30-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsWeb());//GEN-LINE:|17-itemCommandAction|2|30-postAction
                // write post-action user code here
            }//GEN-BEGIN:|17-itemCommandAction|3|17-postItemCommandAction
        }//GEN-END:|17-itemCommandAction|3|17-postItemCommandAction
        // write post-action user code here
    }//GEN-BEGIN:|17-itemCommandAction|4|
    //</editor-fold>//GEN-END:|17-itemCommandAction|4|


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











    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: okCommand1 ">//GEN-BEGIN:|156-getter|0|156-preInit
    /**
     * Returns an initiliazed instance of okCommand1 component.
     * @return the initialized component instance
     */
    public Command getOkCommand1() {
        if (okCommand1 == null) {//GEN-END:|156-getter|0|156-preInit
            // write pre-init user code here
            okCommand1 = new Command("To Menu", Command.OK, 0);//GEN-LINE:|156-getter|1|156-postInit
            // write post-init user code here
        }//GEN-BEGIN:|156-getter|2|
        return okCommand1;
    }
    //</editor-fold>//GEN-END:|156-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: okCommand2 ">//GEN-BEGIN:|158-getter|0|158-preInit
    /**
     * Returns an initiliazed instance of okCommand2 component.
     * @return the initialized component instance
     */
    public Command getOkCommand2() {
        if (okCommand2 == null) {//GEN-END:|158-getter|0|158-preInit
            // write pre-init user code here
            okCommand2 = new Command("To Menu", Command.OK, 0);//GEN-LINE:|158-getter|1|158-postInit
            // write post-init user code here
        }//GEN-BEGIN:|158-getter|2|
        return okCommand2;
    }
    //</editor-fold>//GEN-END:|158-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: okCommand3 ">//GEN-BEGIN:|160-getter|0|160-preInit
    /**
     * Returns an initiliazed instance of okCommand3 component.
     * @return the initialized component instance
     */
    public Command getOkCommand3() {
        if (okCommand3 == null) {//GEN-END:|160-getter|0|160-preInit
            // write pre-init user code here
            okCommand3 = new Command("To Menu", Command.OK, 0);//GEN-LINE:|160-getter|1|160-postInit
            // write post-init user code here
        }//GEN-BEGIN:|160-getter|2|
        return okCommand3;
    }
    //</editor-fold>//GEN-END:|160-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isWeb ">//GEN-BEGIN:|70-getter|0|70-preInit
    /**
     * Returns an initiliazed instance of isWeb component.
     * @return the initialized component instance
     */
    public List getIsWeb() {
        if (isWeb == null) {//GEN-END:|70-getter|0|70-preInit
            // write pre-init user code here
            isWeb = new List("Web?", Choice.IMPLICIT);//GEN-BEGIN:|70-getter|1|70-postInit
            isWeb.append("Yes", null);
            isWeb.append("No", null);
            isWeb.setTicker(getTicker2());
            isWeb.setCommandListener(this);
            isWeb.setSelectedFlags(new boolean[] { false, false });//GEN-END:|70-getter|1|70-postInit
            // write post-init user code here
        }//GEN-BEGIN:|70-getter|2|
        return isWeb;
    }
    //</editor-fold>//GEN-END:|70-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: isWebAction ">//GEN-BEGIN:|70-action|0|70-preAction
    /**
     * Performs an action assigned to the selected list element in the isWeb component.
     */
    public void isWebAction() {//GEN-END:|70-action|0|70-preAction
        // enter pre-action user code here
        String __selectedString = getIsWeb().getString(getIsWeb().getSelectedIndex());//GEN-BEGIN:|70-action|1|74-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes")) {//GEN-END:|70-action|1|74-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsVM());//GEN-LINE:|70-action|2|74-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|70-action|3|75-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsCompilable());//GEN-LINE:|70-action|4|75-postAction
                // write post-action user code here
            }//GEN-BEGIN:|70-action|5|70-postAction
        }//GEN-END:|70-action|5|70-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|70-action|6|
    //</editor-fold>//GEN-END:|70-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isVM ">//GEN-BEGIN:|78-getter|0|78-preInit
    /**
     * Returns an initiliazed instance of isVM component.
     * @return the initialized component instance
     */
    public List getIsVM() {
        if (isVM == null) {//GEN-END:|78-getter|0|78-preInit
            // write pre-init user code here
            isVM = new List("VM-based?", Choice.IMPLICIT);//GEN-BEGIN:|78-getter|1|78-postInit
            isVM.append("Yes", null);
            isVM.append("No", null);
            isVM.setTicker(getTicker3());
            isVM.setCommandListener(this);
            isVM.setSelectedFlags(new boolean[] { false, false });//GEN-END:|78-getter|1|78-postInit
            // write post-init user code here
        }//GEN-BEGIN:|78-getter|2|
        return isVM;
    }
    //</editor-fold>//GEN-END:|78-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: isVMAction ">//GEN-BEGIN:|78-action|0|78-preAction
    /**
     * Performs an action assigned to the selected list element in the isVM component.
     */
    public void isVMAction() {//GEN-END:|78-action|0|78-preAction
        // enter pre-action user code here
        String __selectedString = getIsVM().getString(getIsVM().getSelectedIndex());//GEN-BEGIN:|78-action|1|81-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes")) {//GEN-END:|78-action|1|81-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsMS());//GEN-LINE:|78-action|2|81-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|78-action|3|82-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsBrowser());//GEN-LINE:|78-action|4|82-postAction
                // write post-action user code here
            }//GEN-BEGIN:|78-action|5|78-postAction
        }//GEN-END:|78-action|5|78-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|78-action|6|
    //</editor-fold>//GEN-END:|78-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isBrowser ">//GEN-BEGIN:|84-getter|0|84-preInit
    /**
     * Returns an initiliazed instance of isBrowser component.
     * @return the initialized component instance
     */
    public List getIsBrowser() {
        if (isBrowser == null) {//GEN-END:|84-getter|0|84-preInit
            // write pre-init user code here
            isBrowser = new List("Browser?", Choice.IMPLICIT);//GEN-BEGIN:|84-getter|1|84-postInit
            isBrowser.append("Yes", null);
            isBrowser.append("No", null);
            isBrowser.setTicker(getTicker5());
            isBrowser.setCommandListener(this);
            isBrowser.setSelectedFlags(new boolean[] { false, false });//GEN-END:|84-getter|1|84-postInit
            // write post-init user code here
        }//GEN-BEGIN:|84-getter|2|
        return isBrowser;
    }
    //</editor-fold>//GEN-END:|84-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: isBrowserAction ">//GEN-BEGIN:|84-action|0|84-preAction
    /**
     * Performs an action assigned to the selected list element in the isBrowser component.
     */
    public void isBrowserAction() {//GEN-END:|84-action|0|84-preAction
        // enter pre-action user code here
        String __selectedString = getIsBrowser().getString(getIsBrowser().getSelectedIndex());//GEN-BEGIN:|84-action|1|87-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes")) {//GEN-END:|84-action|1|87-preAction
                // write pre-action user code here
                switchDisplayable(null, getJavaScript());//GEN-LINE:|84-action|2|87-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|84-action|3|88-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsOOP());//GEN-LINE:|84-action|4|88-postAction
                // write post-action user code here
            }//GEN-BEGIN:|84-action|5|84-postAction
        }//GEN-END:|84-action|5|84-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|84-action|6|
    //</editor-fold>//GEN-END:|84-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: JavaScript ">//GEN-BEGIN:|90-getter|0|90-preInit
    /**
     * Returns an initiliazed instance of JavaScript component.
     * @return the initialized component instance
     */
    public List getJavaScript() {
        if (JavaScript == null) {//GEN-END:|90-getter|0|90-preInit
            // write pre-init user code here
            JavaScript = new List("JavaScript?", Choice.IMPLICIT);//GEN-BEGIN:|90-getter|1|90-postInit
            JavaScript.append("Yes!", null);
            JavaScript.append("No", null);
            JavaScript.setCommandListener(this);
            JavaScript.setSelectedFlags(new boolean[] { false, false });//GEN-END:|90-getter|1|90-postInit
            // write post-init user code here
        }//GEN-BEGIN:|90-getter|2|
        return JavaScript;
    }
    //</editor-fold>//GEN-END:|90-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: JavaScriptAction ">//GEN-BEGIN:|90-action|0|90-preAction
    /**
     * Performs an action assigned to the selected list element in the JavaScript component.
     */
    public void JavaScriptAction() {//GEN-END:|90-action|0|90-preAction
        // enter pre-action user code here
        String __selectedString = getJavaScript().getString(getJavaScript().getSelectedIndex());//GEN-BEGIN:|90-action|1|94-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|90-action|1|94-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|90-action|2|94-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|90-action|3|95-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|90-action|4|95-postAction
                // write post-action user code here
            }//GEN-BEGIN:|90-action|5|90-postAction
        }//GEN-END:|90-action|5|90-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|90-action|6|
    //</editor-fold>//GEN-END:|90-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: Fail ">//GEN-BEGIN:|98-getter|0|98-preInit
    /**
     * Returns an initiliazed instance of Fail component.
     * @return the initialized component instance
     */
    public Form getFail() {
        if (Fail == null) {//GEN-END:|98-getter|0|98-preInit
            // write pre-init user code here
            Fail = new Form("Sorry...", new Item[] { getStringItem1() });//GEN-BEGIN:|98-getter|1|98-postInit
            Fail.addCommand(getOkCommand3());
            Fail.setCommandListener(this);//GEN-END:|98-getter|1|98-postInit
            // write post-init user code here
        }//GEN-BEGIN:|98-getter|2|
        return Fail;
    }
    //</editor-fold>//GEN-END:|98-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: stringItem1 ">//GEN-BEGIN:|100-getter|0|100-preInit
    /**
     * Returns an initiliazed instance of stringItem1 component.
     * @return the initialized component instance
     */
    public StringItem getStringItem1() {
        if (stringItem1 == null) {//GEN-END:|100-getter|0|100-preInit
            // write pre-init user code here
            stringItem1 = new StringItem("", "I don\'t know this language :(");//GEN-LINE:|100-getter|1|100-postInit
            // write post-init user code here
        }//GEN-BEGIN:|100-getter|2|
        return stringItem1;
    }
    //</editor-fold>//GEN-END:|100-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: Success ">//GEN-BEGIN:|103-getter|0|103-preInit
    /**
     * Returns an initiliazed instance of Success component.
     * @return the initialized component instance
     */
    public Form getSuccess() {
        if (Success == null) {//GEN-END:|103-getter|0|103-preInit
            // write pre-init user code here
            Success = new Form("Hooray!");//GEN-BEGIN:|103-getter|1|103-postInit
            Success.addCommand(getOkCommand1());
            Success.setCommandListener(this);//GEN-END:|103-getter|1|103-postInit
            // write post-init user code here
        }//GEN-BEGIN:|103-getter|2|
        return Success;
    }
    //</editor-fold>//GEN-END:|103-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isMS ">//GEN-BEGIN:|105-getter|0|105-preInit
    /**
     * Returns an initiliazed instance of isMS component.
     * @return the initialized component instance
     */
    public List getIsMS() {
        if (isMS == null) {//GEN-END:|105-getter|0|105-preInit
            // write pre-init user code here
            isMS = new List("Microsoft?", Choice.IMPLICIT);//GEN-BEGIN:|105-getter|1|105-postInit
            isMS.append("Yes", null);
            isMS.append("No", null);
            isMS.setTicker(getTicker4());
            isMS.setCommandListener(this);
            isMS.setSelectedFlags(new boolean[] { false, false });//GEN-END:|105-getter|1|105-postInit
            // write post-init user code here
        }//GEN-BEGIN:|105-getter|2|
        return isMS;
    }
    //</editor-fold>//GEN-END:|105-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: isMSAction ">//GEN-BEGIN:|105-action|0|105-preAction
    /**
     * Performs an action assigned to the selected list element in the isMS component.
     */
    public void isMSAction() {//GEN-END:|105-action|0|105-preAction
        // enter pre-action user code here
        String __selectedString = getIsMS().getString(getIsMS().getSelectedIndex());//GEN-BEGIN:|105-action|1|109-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes")) {//GEN-END:|105-action|1|109-preAction
                // write pre-action user code here
                switchDisplayable(null, getCSharp());//GEN-LINE:|105-action|2|109-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|105-action|3|110-preAction
                // write pre-action user code here
                switchDisplayable(null, getJava());//GEN-LINE:|105-action|4|110-postAction
                // write post-action user code here
            }//GEN-BEGIN:|105-action|5|105-postAction
        }//GEN-END:|105-action|5|105-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|105-action|6|
    //</editor-fold>//GEN-END:|105-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: CSharp ">//GEN-BEGIN:|111-getter|0|111-preInit
    /**
     * Returns an initiliazed instance of CSharp component.
     * @return the initialized component instance
     */
    public List getCSharp() {
        if (CSharp == null) {//GEN-END:|111-getter|0|111-preInit
            // write pre-init user code here
            CSharp = new List("C#?", Choice.IMPLICIT);//GEN-BEGIN:|111-getter|1|111-postInit
            CSharp.append("Yes!", null);
            CSharp.append("No", null);
            CSharp.setCommandListener(this);
            CSharp.setSelectedFlags(new boolean[] { false, false });//GEN-END:|111-getter|1|111-postInit
            // write post-init user code here
        }//GEN-BEGIN:|111-getter|2|
        return CSharp;
    }
    //</editor-fold>//GEN-END:|111-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: CSharpAction ">//GEN-BEGIN:|111-action|0|111-preAction
    /**
     * Performs an action assigned to the selected list element in the CSharp component.
     */
    public void CSharpAction() {//GEN-END:|111-action|0|111-preAction
        // enter pre-action user code here
        String __selectedString = getCSharp().getString(getCSharp().getSelectedIndex());//GEN-BEGIN:|111-action|1|114-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|111-action|1|114-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|111-action|2|114-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|111-action|3|115-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|111-action|4|115-postAction
                // write post-action user code here
            }//GEN-BEGIN:|111-action|5|111-postAction
        }//GEN-END:|111-action|5|111-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|111-action|6|
    //</editor-fold>//GEN-END:|111-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: Java ">//GEN-BEGIN:|119-getter|0|119-preInit
    /**
     * Returns an initiliazed instance of Java component.
     * @return the initialized component instance
     */
    public List getJava() {
        if (Java == null) {//GEN-END:|119-getter|0|119-preInit
            // write pre-init user code here
            Java = new List("Java?", Choice.IMPLICIT);//GEN-BEGIN:|119-getter|1|119-postInit
            Java.append("Yes!", null);
            Java.append("No", null);
            Java.setCommandListener(this);
            Java.setSelectedFlags(new boolean[] { false, false });//GEN-END:|119-getter|1|119-postInit
            // write post-init user code here
        }//GEN-BEGIN:|119-getter|2|
        return Java;
    }
    //</editor-fold>//GEN-END:|119-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: JavaAction ">//GEN-BEGIN:|119-action|0|119-preAction
    /**
     * Performs an action assigned to the selected list element in the Java component.
     */
    public void JavaAction() {//GEN-END:|119-action|0|119-preAction
        // enter pre-action user code here
        String __selectedString = getJava().getString(getJava().getSelectedIndex());//GEN-BEGIN:|119-action|1|123-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|119-action|1|123-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|119-action|2|123-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|119-action|3|124-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|119-action|4|124-postAction
                // write post-action user code here
            }//GEN-BEGIN:|119-action|5|119-postAction
        }//GEN-END:|119-action|5|119-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|119-action|6|
    //</editor-fold>//GEN-END:|119-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isOOP ">//GEN-BEGIN:|127-getter|0|127-preInit
    /**
     * Returns an initiliazed instance of isOOP component.
     * @return the initialized component instance
     */
    public List getIsOOP() {
        if (isOOP == null) {//GEN-END:|127-getter|0|127-preInit
            // write pre-init user code here
            isOOP = new List("Object Oriented?", Choice.IMPLICIT);//GEN-BEGIN:|127-getter|1|127-postInit
            isOOP.append("Yes", null);
            isOOP.append("No", null);
            isOOP.setTicker(getTicker());
            isOOP.setCommandListener(this);
            isOOP.setSelectedFlags(new boolean[] { false, false });//GEN-END:|127-getter|1|127-postInit
            // write post-init user code here
        }//GEN-BEGIN:|127-getter|2|
        return isOOP;
    }
    //</editor-fold>//GEN-END:|127-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: isOOPAction ">//GEN-BEGIN:|127-action|0|127-preAction
    /**
     * Performs an action assigned to the selected list element in the isOOP component.
     */
    public void isOOPAction() {//GEN-END:|127-action|0|127-preAction
        // enter pre-action user code here
        String __selectedString = getIsOOP().getString(getIsOOP().getSelectedIndex());//GEN-BEGIN:|127-action|1|131-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes")) {//GEN-END:|127-action|1|131-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsIndent());//GEN-LINE:|127-action|2|131-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|127-action|3|132-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsRegexp());//GEN-LINE:|127-action|4|132-postAction
                // write post-action user code here
            }//GEN-BEGIN:|127-action|5|127-postAction
        }//GEN-END:|127-action|5|127-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|127-action|6|
    //</editor-fold>//GEN-END:|127-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isIndent ">//GEN-BEGIN:|134-getter|0|134-preInit
    /**
     * Returns an initiliazed instance of isIndent component.
     * @return the initialized component instance
     */
    public List getIsIndent() {
        if (isIndent == null) {//GEN-END:|134-getter|0|134-preInit
            // write pre-init user code here
            isIndent = new List("Indent-based?", Choice.IMPLICIT);//GEN-BEGIN:|134-getter|1|134-postInit
            isIndent.append("Yes", null);
            isIndent.append("No", null);
            isIndent.setTicker(getTicker1());
            isIndent.setCommandListener(this);
            isIndent.setSelectedFlags(new boolean[] { false, false });//GEN-END:|134-getter|1|134-postInit
            // write post-init user code here
        }//GEN-BEGIN:|134-getter|2|
        return isIndent;
    }
    //</editor-fold>//GEN-END:|134-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: isIndentAction ">//GEN-BEGIN:|134-action|0|134-preAction
    /**
     * Performs an action assigned to the selected list element in the isIndent component.
     */
    public void isIndentAction() {//GEN-END:|134-action|0|134-preAction
        // enter pre-action user code here
        String __selectedString = getIsIndent().getString(getIsIndent().getSelectedIndex());//GEN-BEGIN:|134-action|1|138-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes")) {//GEN-END:|134-action|1|138-preAction
                // write pre-action user code here
                switchDisplayable(null, getPython());//GEN-LINE:|134-action|2|138-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|134-action|3|139-preAction
                // write pre-action user code here
                switchDisplayable(null, getRuby());//GEN-LINE:|134-action|4|139-postAction
                // write post-action user code here
            }//GEN-BEGIN:|134-action|5|134-postAction
        }//GEN-END:|134-action|5|134-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|134-action|6|
    //</editor-fold>//GEN-END:|134-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: Python ">//GEN-BEGIN:|140-getter|0|140-preInit
    /**
     * Returns an initiliazed instance of Python component.
     * @return the initialized component instance
     */
    public List getPython() {
        if (Python == null) {//GEN-END:|140-getter|0|140-preInit
            // write pre-init user code here
            Python = new List("Python?", Choice.IMPLICIT);//GEN-BEGIN:|140-getter|1|140-postInit
            Python.append("Yes!", null);
            Python.append("No", null);
            Python.setCommandListener(this);
            Python.setSelectedFlags(new boolean[] { false, false });//GEN-END:|140-getter|1|140-postInit
            // write post-init user code here
        }//GEN-BEGIN:|140-getter|2|
        return Python;
    }
    //</editor-fold>//GEN-END:|140-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: PythonAction ">//GEN-BEGIN:|140-action|0|140-preAction
    /**
     * Performs an action assigned to the selected list element in the Python component.
     */
    public void PythonAction() {//GEN-END:|140-action|0|140-preAction
        // enter pre-action user code here
        String __selectedString = getPython().getString(getPython().getSelectedIndex());//GEN-BEGIN:|140-action|1|143-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|140-action|1|143-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|140-action|2|143-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|140-action|3|144-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|140-action|4|144-postAction
                // write post-action user code here
            }//GEN-BEGIN:|140-action|5|140-postAction
        }//GEN-END:|140-action|5|140-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|140-action|6|
    //</editor-fold>//GEN-END:|140-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: Ruby ">//GEN-BEGIN:|148-getter|0|148-preInit
    /**
     * Returns an initiliazed instance of Ruby component.
     * @return the initialized component instance
     */
    public List getRuby() {
        if (Ruby == null) {//GEN-END:|148-getter|0|148-preInit
            // write pre-init user code here
            Ruby = new List("Ruby?", Choice.IMPLICIT);//GEN-BEGIN:|148-getter|1|148-postInit
            Ruby.append("Yes!", null);
            Ruby.append("No", null);
            Ruby.setCommandListener(this);
            Ruby.setSelectedFlags(new boolean[] { false, false });//GEN-END:|148-getter|1|148-postInit
            // write post-init user code here
        }//GEN-BEGIN:|148-getter|2|
        return Ruby;
    }
    //</editor-fold>//GEN-END:|148-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: RubyAction ">//GEN-BEGIN:|148-action|0|148-preAction
    /**
     * Performs an action assigned to the selected list element in the Ruby component.
     */
    public void RubyAction() {//GEN-END:|148-action|0|148-preAction
        // enter pre-action user code here
        String __selectedString = getRuby().getString(getRuby().getSelectedIndex());//GEN-BEGIN:|148-action|1|152-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|148-action|1|152-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|148-action|2|152-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|148-action|3|153-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|148-action|4|153-postAction
                // write post-action user code here
            }//GEN-BEGIN:|148-action|5|148-postAction
        }//GEN-END:|148-action|5|148-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|148-action|6|
    //</editor-fold>//GEN-END:|148-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: ticker ">//GEN-BEGIN:|133-getter|0|133-preInit
    /**
     * Returns an initiliazed instance of ticker component.
     * @return the initialized component instance
     */
    public Ticker getTicker() {
        if (ticker == null) {//GEN-END:|133-getter|0|133-preInit
            // write pre-init user code here
            ticker = new Ticker("Support Inheritance, Incapsulation and Polymorphysm?");//GEN-LINE:|133-getter|1|133-postInit
            // write post-init user code here
        }//GEN-BEGIN:|133-getter|2|
        return ticker;
    }
    //</editor-fold>//GEN-END:|133-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isRegexp ">//GEN-BEGIN:|165-getter|0|165-preInit
    /**
     * Returns an initiliazed instance of isRegexp component.
     * @return the initialized component instance
     */
    public List getIsRegexp() {
        if (isRegexp == null) {//GEN-END:|165-getter|0|165-preInit
            // write pre-init user code here
            isRegexp = new List("Has regexp?", Choice.IMPLICIT);//GEN-BEGIN:|165-getter|1|165-postInit
            isRegexp.append("Yes", null);
            isRegexp.append("No", null);
            isRegexp.setTicker(getTicker6());
            isRegexp.setCommandListener(this);
            isRegexp.setSelectedFlags(new boolean[] { false, false });//GEN-END:|165-getter|1|165-postInit
            // write post-init user code here
        }//GEN-BEGIN:|165-getter|2|
        return isRegexp;
    }
    //</editor-fold>//GEN-END:|165-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: isRegexpAction ">//GEN-BEGIN:|165-action|0|165-preAction
    /**
     * Performs an action assigned to the selected list element in the isRegexp component.
     */
    public void isRegexpAction() {//GEN-END:|165-action|0|165-preAction
        // enter pre-action user code here
        String __selectedString = getIsRegexp().getString(getIsRegexp().getSelectedIndex());//GEN-BEGIN:|165-action|1|168-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes")) {//GEN-END:|165-action|1|168-preAction
                // write pre-action user code here
                switchDisplayable(null, getPerl());//GEN-LINE:|165-action|2|168-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|165-action|3|169-preAction
                // write pre-action user code here
                switchDisplayable(null, getPHP());//GEN-LINE:|165-action|4|169-postAction
                // write post-action user code here
            }//GEN-BEGIN:|165-action|5|165-postAction
        }//GEN-END:|165-action|5|165-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|165-action|6|
    //</editor-fold>//GEN-END:|165-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: PHP ">//GEN-BEGIN:|171-getter|0|171-preInit
    /**
     * Returns an initiliazed instance of PHP component.
     * @return the initialized component instance
     */
    public List getPHP() {
        if (PHP == null) {//GEN-END:|171-getter|0|171-preInit
            // write pre-init user code here
            PHP = new List("PHP?", Choice.IMPLICIT);//GEN-BEGIN:|171-getter|1|171-postInit
            PHP.append("Yes!", null);
            PHP.append("No", null);
            PHP.setCommandListener(this);
            PHP.setSelectedFlags(new boolean[] { false, false });//GEN-END:|171-getter|1|171-postInit
            // write post-init user code here
        }//GEN-BEGIN:|171-getter|2|
        return PHP;
    }
    //</editor-fold>//GEN-END:|171-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: PHPAction ">//GEN-BEGIN:|171-action|0|171-preAction
    /**
     * Performs an action assigned to the selected list element in the PHP component.
     */
    public void PHPAction() {//GEN-END:|171-action|0|171-preAction
        // enter pre-action user code here
        String __selectedString = getPHP().getString(getPHP().getSelectedIndex());//GEN-BEGIN:|171-action|1|175-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|171-action|1|175-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|171-action|2|175-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|171-action|3|176-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|171-action|4|176-postAction
                // write post-action user code here
            }//GEN-BEGIN:|171-action|5|171-postAction
        }//GEN-END:|171-action|5|171-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|171-action|6|
    //</editor-fold>//GEN-END:|171-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: Perl ">//GEN-BEGIN:|179-getter|0|179-preInit
    /**
     * Returns an initiliazed instance of Perl component.
     * @return the initialized component instance
     */
    public List getPerl() {
        if (Perl == null) {//GEN-END:|179-getter|0|179-preInit
            // write pre-init user code here
            Perl = new List("Perl?", Choice.IMPLICIT);//GEN-BEGIN:|179-getter|1|179-postInit
            Perl.append("Yes!", null);
            Perl.append("No", null);
            Perl.setCommandListener(this);
            Perl.setSelectedFlags(new boolean[] { false, false });//GEN-END:|179-getter|1|179-postInit
            // write post-init user code here
        }//GEN-BEGIN:|179-getter|2|
        return Perl;
    }
    //</editor-fold>//GEN-END:|179-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: PerlAction ">//GEN-BEGIN:|179-action|0|179-preAction
    /**
     * Performs an action assigned to the selected list element in the Perl component.
     */
    public void PerlAction() {//GEN-END:|179-action|0|179-preAction
        // enter pre-action user code here
        String __selectedString = getPerl().getString(getPerl().getSelectedIndex());//GEN-BEGIN:|179-action|1|183-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|179-action|1|183-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|179-action|2|183-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|179-action|3|184-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|179-action|4|184-postAction
                // write post-action user code here
            }//GEN-BEGIN:|179-action|5|179-postAction
        }//GEN-END:|179-action|5|179-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|179-action|6|
    //</editor-fold>//GEN-END:|179-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isCompilable ">//GEN-BEGIN:|187-getter|0|187-preInit
    /**
     * Returns an initiliazed instance of isCompilable component.
     * @return the initialized component instance
     */
    public List getIsCompilable() {
        if (isCompilable == null) {//GEN-END:|187-getter|0|187-preInit
            // write pre-init user code here
            isCompilable = new List("Is it compilable?", Choice.IMPLICIT);//GEN-BEGIN:|187-getter|1|187-postInit
            isCompilable.append("Yes", null);
            isCompilable.append("No", null);
            isCompilable.setCommandListener(this);
            isCompilable.setSelectedFlags(new boolean[] { false, false });//GEN-END:|187-getter|1|187-postInit
            // write post-init user code here
        }//GEN-BEGIN:|187-getter|2|
        return isCompilable;
    }
    //</editor-fold>//GEN-END:|187-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: isCompilableAction ">//GEN-BEGIN:|187-action|0|187-preAction
    /**
     * Performs an action assigned to the selected list element in the isCompilable component.
     */
    public void isCompilableAction() {//GEN-END:|187-action|0|187-preAction
        // enter pre-action user code here
        String __selectedString = getIsCompilable().getString(getIsCompilable().getSelectedIndex());//GEN-BEGIN:|187-action|1|190-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes")) {//GEN-END:|187-action|1|190-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsOOP1());//GEN-LINE:|187-action|2|190-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|187-action|3|191-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsDB());//GEN-LINE:|187-action|4|191-postAction
                // write post-action user code here
            }//GEN-BEGIN:|187-action|5|187-postAction
        }//GEN-END:|187-action|5|187-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|187-action|6|
    //</editor-fold>//GEN-END:|187-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isOOP1 ">//GEN-BEGIN:|193-getter|0|193-preInit
    /**
     * Returns an initiliazed instance of isOOP1 component.
     * @return the initialized component instance
     */
    public List getIsOOP1() {
        if (isOOP1 == null) {//GEN-END:|193-getter|0|193-preInit
            // write pre-init user code here
            isOOP1 = new List("Is it object oriented?", Choice.IMPLICIT);//GEN-BEGIN:|193-getter|1|193-postInit
            isOOP1.append("Yes", null);
            isOOP1.append("No", null);
            isOOP1.setCommandListener(this);
            isOOP1.setSelectedFlags(new boolean[] { false, false });//GEN-END:|193-getter|1|193-postInit
            // write post-init user code here
        }//GEN-BEGIN:|193-getter|2|
        return isOOP1;
    }
    //</editor-fold>//GEN-END:|193-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: isOOP1Action ">//GEN-BEGIN:|193-action|0|193-preAction
    /**
     * Performs an action assigned to the selected list element in the isOOP1 component.
     */
    public void isOOP1Action() {//GEN-END:|193-action|0|193-preAction
        // enter pre-action user code here
        String __selectedString = getIsOOP1().getString(getIsOOP1().getSelectedIndex());//GEN-BEGIN:|193-action|1|197-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes")) {//GEN-END:|193-action|1|197-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsTemplate());//GEN-LINE:|193-action|2|197-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|193-action|3|198-preAction
                // write pre-action user code here
                switchDisplayable(null, getIsBegin());//GEN-LINE:|193-action|4|198-postAction
                // write post-action user code here
            }//GEN-BEGIN:|193-action|5|193-postAction
        }//GEN-END:|193-action|5|193-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|193-action|6|
    //</editor-fold>//GEN-END:|193-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isTemplate ">//GEN-BEGIN:|199-getter|0|199-preInit
    /**
     * Returns an initiliazed instance of isTemplate component.
     * @return the initialized component instance
     */
    public List getIsTemplate() {
        if (isTemplate == null) {//GEN-END:|199-getter|0|199-preInit
            // write pre-init user code here
            isTemplate = new List("Have templates?", Choice.IMPLICIT);//GEN-BEGIN:|199-getter|1|199-postInit
            isTemplate.append("Yes", null);
            isTemplate.append("No", null);
            isTemplate.setCommandListener(this);
            isTemplate.setSelectedFlags(new boolean[] { false, false });//GEN-END:|199-getter|1|199-postInit
            // write post-init user code here
        }//GEN-BEGIN:|199-getter|2|
        return isTemplate;
    }
    //</editor-fold>//GEN-END:|199-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: isTemplateAction ">//GEN-BEGIN:|199-action|0|199-preAction
    /**
     * Performs an action assigned to the selected list element in the isTemplate component.
     */
    public void isTemplateAction() {//GEN-END:|199-action|0|199-preAction
        // enter pre-action user code here
        String __selectedString = getIsTemplate().getString(getIsTemplate().getSelectedIndex());//GEN-BEGIN:|199-action|1|203-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes")) {//GEN-END:|199-action|1|203-preAction
                // write pre-action user code here
                switchDisplayable(null, getCPlusPLus());//GEN-LINE:|199-action|2|203-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|199-action|3|204-preAction
                // write pre-action user code here
                switchDisplayable(null, getDelphi());//GEN-LINE:|199-action|4|204-postAction
                // write post-action user code here
            }//GEN-BEGIN:|199-action|5|199-postAction
        }//GEN-END:|199-action|5|199-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|199-action|6|
    //</editor-fold>//GEN-END:|199-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: CPlusPLus ">//GEN-BEGIN:|205-getter|0|205-preInit
    /**
     * Returns an initiliazed instance of CPlusPLus component.
     * @return the initialized component instance
     */
    public List getCPlusPLus() {
        if (CPlusPLus == null) {//GEN-END:|205-getter|0|205-preInit
            // write pre-init user code here
            CPlusPLus = new List("C++?", Choice.IMPLICIT);//GEN-BEGIN:|205-getter|1|205-postInit
            CPlusPLus.append("Yes!", null);
            CPlusPLus.append("No", null);
            CPlusPLus.setCommandListener(this);
            CPlusPLus.setSelectedFlags(new boolean[] { false, false });//GEN-END:|205-getter|1|205-postInit
            // write post-init user code here
        }//GEN-BEGIN:|205-getter|2|
        return CPlusPLus;
    }
    //</editor-fold>//GEN-END:|205-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: CPlusPLusAction ">//GEN-BEGIN:|205-action|0|205-preAction
    /**
     * Performs an action assigned to the selected list element in the CPlusPLus component.
     */
    public void CPlusPLusAction() {//GEN-END:|205-action|0|205-preAction
        // enter pre-action user code here
        String __selectedString = getCPlusPLus().getString(getCPlusPLus().getSelectedIndex());//GEN-BEGIN:|205-action|1|208-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|205-action|1|208-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|205-action|2|208-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|205-action|3|209-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|205-action|4|209-postAction
                // write post-action user code here
            }//GEN-BEGIN:|205-action|5|205-postAction
        }//GEN-END:|205-action|5|205-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|205-action|6|
    //</editor-fold>//GEN-END:|205-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: Delphi ">//GEN-BEGIN:|213-getter|0|213-preInit
    /**
     * Returns an initiliazed instance of Delphi component.
     * @return the initialized component instance
     */
    public List getDelphi() {
        if (Delphi == null) {//GEN-END:|213-getter|0|213-preInit
            // write pre-init user code here
            Delphi = new List("Delphi?", Choice.IMPLICIT);//GEN-BEGIN:|213-getter|1|213-postInit
            Delphi.append("Yes!", null);
            Delphi.append("No", null);
            Delphi.setCommandListener(this);
            Delphi.setSelectedFlags(new boolean[] { false, false });//GEN-END:|213-getter|1|213-postInit
            // write post-init user code here
        }//GEN-BEGIN:|213-getter|2|
        return Delphi;
    }
    //</editor-fold>//GEN-END:|213-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: DelphiAction ">//GEN-BEGIN:|213-action|0|213-preAction
    /**
     * Performs an action assigned to the selected list element in the Delphi component.
     */
    public void DelphiAction() {//GEN-END:|213-action|0|213-preAction
        // enter pre-action user code here
        String __selectedString = getDelphi().getString(getDelphi().getSelectedIndex());//GEN-BEGIN:|213-action|1|217-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|213-action|1|217-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|213-action|2|217-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|213-action|3|218-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|213-action|4|218-postAction
                // write post-action user code here
            }//GEN-BEGIN:|213-action|5|213-postAction
        }//GEN-END:|213-action|5|213-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|213-action|6|
    //</editor-fold>//GEN-END:|213-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isBegin ">//GEN-BEGIN:|221-getter|0|221-preInit
    /**
     * Returns an initiliazed instance of isBegin component.
     * @return the initialized component instance
     */
    public List getIsBegin() {
        if (isBegin == null) {//GEN-END:|221-getter|0|221-preInit
            // write pre-init user code here
            isBegin = new List("begin/end?", Choice.IMPLICIT);//GEN-BEGIN:|221-getter|1|221-postInit
            isBegin.append("Yes", null);
            isBegin.append("No", null);
            isBegin.setTicker(getTicker7());
            isBegin.setCommandListener(this);
            isBegin.setSelectedFlags(new boolean[] { false, false });//GEN-END:|221-getter|1|221-postInit
            // write post-init user code here
        }//GEN-BEGIN:|221-getter|2|
        return isBegin;
    }
    //</editor-fold>//GEN-END:|221-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: isBeginAction ">//GEN-BEGIN:|221-action|0|221-preAction
    /**
     * Performs an action assigned to the selected list element in the isBegin component.
     */
    public void isBeginAction() {//GEN-END:|221-action|0|221-preAction
        // enter pre-action user code here
        String __selectedString = getIsBegin().getString(getIsBegin().getSelectedIndex());//GEN-BEGIN:|221-action|1|225-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes")) {//GEN-END:|221-action|1|225-preAction
                // write pre-action user code here
                switchDisplayable(null, getPascal());//GEN-LINE:|221-action|2|225-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|221-action|3|226-preAction
                // write pre-action user code here
                switchDisplayable(null, getC());//GEN-LINE:|221-action|4|226-postAction
                // write post-action user code here
            }//GEN-BEGIN:|221-action|5|221-postAction
        }//GEN-END:|221-action|5|221-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|221-action|6|
    //</editor-fold>//GEN-END:|221-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: Pascal ">//GEN-BEGIN:|227-getter|0|227-preInit
    /**
     * Returns an initiliazed instance of Pascal component.
     * @return the initialized component instance
     */
    public List getPascal() {
        if (Pascal == null) {//GEN-END:|227-getter|0|227-preInit
            // write pre-init user code here
            Pascal = new List("Pascal?", Choice.IMPLICIT);//GEN-BEGIN:|227-getter|1|227-postInit
            Pascal.append("Yes!", null);
            Pascal.append("No", null);
            Pascal.setCommandListener(this);
            Pascal.setSelectedFlags(new boolean[] { false, false });//GEN-END:|227-getter|1|227-postInit
            // write post-init user code here
        }//GEN-BEGIN:|227-getter|2|
        return Pascal;
    }
    //</editor-fold>//GEN-END:|227-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: PascalAction ">//GEN-BEGIN:|227-action|0|227-preAction
    /**
     * Performs an action assigned to the selected list element in the Pascal component.
     */
    public void PascalAction() {//GEN-END:|227-action|0|227-preAction
        // enter pre-action user code here
        String __selectedString = getPascal().getString(getPascal().getSelectedIndex());//GEN-BEGIN:|227-action|1|231-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|227-action|1|231-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|227-action|2|231-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|227-action|3|232-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|227-action|4|232-postAction
                // write post-action user code here
            }//GEN-BEGIN:|227-action|5|227-postAction
        }//GEN-END:|227-action|5|227-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|227-action|6|
    //</editor-fold>//GEN-END:|227-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: C ">//GEN-BEGIN:|235-getter|0|235-preInit
    /**
     * Returns an initiliazed instance of C component.
     * @return the initialized component instance
     */
    public List getC() {
        if (C == null) {//GEN-END:|235-getter|0|235-preInit
            // write pre-init user code here
            C = new List("C?", Choice.IMPLICIT);//GEN-BEGIN:|235-getter|1|235-postInit
            C.append("Yes!", null);
            C.append("No", null);
            C.setCommandListener(this);
            C.setSelectedFlags(new boolean[] { false, false });//GEN-END:|235-getter|1|235-postInit
            // write post-init user code here
        }//GEN-BEGIN:|235-getter|2|
        return C;
    }
    //</editor-fold>//GEN-END:|235-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: CAction ">//GEN-BEGIN:|235-action|0|235-preAction
    /**
     * Performs an action assigned to the selected list element in the C component.
     */
    public void CAction() {//GEN-END:|235-action|0|235-preAction
        // enter pre-action user code here
        String __selectedString = getC().getString(getC().getSelectedIndex());//GEN-BEGIN:|235-action|1|239-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|235-action|1|239-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|235-action|2|239-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|235-action|3|240-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|235-action|4|240-postAction
                // write post-action user code here
            }//GEN-BEGIN:|235-action|5|235-postAction
        }//GEN-END:|235-action|5|235-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|235-action|6|
    //</editor-fold>//GEN-END:|235-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: isDB ">//GEN-BEGIN:|243-getter|0|243-preInit
    /**
     * Returns an initiliazed instance of isDB component.
     * @return the initialized component instance
     */
    public List getIsDB() {
        if (isDB == null) {//GEN-END:|243-getter|0|243-preInit
            // write pre-init user code here
            isDB = new List("Used in DBs?", Choice.IMPLICIT);//GEN-BEGIN:|243-getter|1|243-postInit
            isDB.append("Yes", null);
            isDB.append("No", null);
            isDB.setCommandListener(this);
            isDB.setSelectedFlags(new boolean[] { false, false });//GEN-END:|243-getter|1|243-postInit
            // write post-init user code here
        }//GEN-BEGIN:|243-getter|2|
        return isDB;
    }
    //</editor-fold>//GEN-END:|243-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: isDBAction ">//GEN-BEGIN:|243-action|0|243-preAction
    /**
     * Performs an action assigned to the selected list element in the isDB component.
     */
    public void isDBAction() {//GEN-END:|243-action|0|243-preAction
        // enter pre-action user code here
        String __selectedString = getIsDB().getString(getIsDB().getSelectedIndex());//GEN-BEGIN:|243-action|1|247-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes")) {//GEN-END:|243-action|1|247-preAction
                // write pre-action user code here
                switchDisplayable(null, getPLSQL());//GEN-LINE:|243-action|2|247-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|243-action|3|248-preAction
                // write pre-action user code here
                switchDisplayable(null, getMATLAB());//GEN-LINE:|243-action|4|248-postAction
                // write post-action user code here
            }//GEN-BEGIN:|243-action|5|243-postAction
        }//GEN-END:|243-action|5|243-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|243-action|6|
    //</editor-fold>//GEN-END:|243-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: PLSQL ">//GEN-BEGIN:|249-getter|0|249-preInit
    /**
     * Returns an initiliazed instance of PLSQL component.
     * @return the initialized component instance
     */
    public List getPLSQL() {
        if (PLSQL == null) {//GEN-END:|249-getter|0|249-preInit
            // write pre-init user code here
            PLSQL = new List("Is it PL/SQL?", Choice.IMPLICIT);//GEN-BEGIN:|249-getter|1|249-postInit
            PLSQL.append("Yes!", null);
            PLSQL.append("No", null);
            PLSQL.setCommandListener(this);
            PLSQL.setSelectedFlags(new boolean[] { false, false });//GEN-END:|249-getter|1|249-postInit
            // write post-init user code here
        }//GEN-BEGIN:|249-getter|2|
        return PLSQL;
    }
    //</editor-fold>//GEN-END:|249-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: PLSQLAction ">//GEN-BEGIN:|249-action|0|249-preAction
    /**
     * Performs an action assigned to the selected list element in the PLSQL component.
     */
    public void PLSQLAction() {//GEN-END:|249-action|0|249-preAction
        // enter pre-action user code here
        String __selectedString = getPLSQL().getString(getPLSQL().getSelectedIndex());//GEN-BEGIN:|249-action|1|252-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|249-action|1|252-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|249-action|2|252-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|249-action|3|253-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|249-action|4|253-postAction
                // write post-action user code here
            }//GEN-BEGIN:|249-action|5|249-postAction
        }//GEN-END:|249-action|5|249-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|249-action|6|
    //</editor-fold>//GEN-END:|249-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: MATLAB ">//GEN-BEGIN:|257-getter|0|257-preInit
    /**
     * Returns an initiliazed instance of MATLAB component.
     * @return the initialized component instance
     */
    public List getMATLAB() {
        if (MATLAB == null) {//GEN-END:|257-getter|0|257-preInit
            // write pre-init user code here
            MATLAB = new List("MATLAB?", Choice.IMPLICIT);//GEN-BEGIN:|257-getter|1|257-postInit
            MATLAB.append("Yes!", null);
            MATLAB.append("No", null);
            MATLAB.setCommandListener(this);
            MATLAB.setSelectedFlags(new boolean[] { false, false });//GEN-END:|257-getter|1|257-postInit
            // write post-init user code here
        }//GEN-BEGIN:|257-getter|2|
        return MATLAB;
    }
    //</editor-fold>//GEN-END:|257-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Method: MATLABAction ">//GEN-BEGIN:|257-action|0|257-preAction
    /**
     * Performs an action assigned to the selected list element in the MATLAB component.
     */
    public void MATLABAction() {//GEN-END:|257-action|0|257-preAction
        // enter pre-action user code here
        String __selectedString = getMATLAB().getString(getMATLAB().getSelectedIndex());//GEN-BEGIN:|257-action|1|261-preAction
        if (__selectedString != null) {
            if (__selectedString.equals("Yes!")) {//GEN-END:|257-action|1|261-preAction
                // write pre-action user code here
                switchDisplayable(null, getSuccess());//GEN-LINE:|257-action|2|261-postAction
                // write post-action user code here
            } else if (__selectedString.equals("No")) {//GEN-LINE:|257-action|3|262-preAction
                // write pre-action user code here
                switchDisplayable(null, getFail());//GEN-LINE:|257-action|4|262-postAction
                // write post-action user code here
            }//GEN-BEGIN:|257-action|5|257-postAction
        }//GEN-END:|257-action|5|257-postAction
        // enter post-action user code here
    }//GEN-BEGIN:|257-action|6|
    //</editor-fold>//GEN-END:|257-action|6|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: ticker1 ">//GEN-BEGIN:|164-getter|0|164-preInit
    /**
     * Returns an initiliazed instance of ticker1 component.
     * @return the initialized component instance
     */
    public Ticker getTicker1() {
        if (ticker1 == null) {//GEN-END:|164-getter|0|164-preInit
            // write pre-init user code here
            ticker1 = new Ticker("Does indentation significant in syntax?");//GEN-LINE:|164-getter|1|164-postInit
            // write post-init user code here
        }//GEN-BEGIN:|164-getter|2|
        return ticker1;
    }
    //</editor-fold>//GEN-END:|164-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: ticker2 ">//GEN-BEGIN:|266-getter|0|266-preInit
    /**
     * Returns an initiliazed instance of ticker2 component.
     * @return the initialized component instance
     */
    public Ticker getTicker2() {
        if (ticker2 == null) {//GEN-END:|266-getter|0|266-preInit
            // write pre-init user code here
            ticker2 = new Ticker("Is it widely used in Web?");//GEN-LINE:|266-getter|1|266-postInit
            // write post-init user code here
        }//GEN-BEGIN:|266-getter|2|
        return ticker2;
    }
    //</editor-fold>//GEN-END:|266-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: ticker3 ">//GEN-BEGIN:|267-getter|0|267-preInit
    /**
     * Returns an initiliazed instance of ticker3 component.
     * @return the initialized component instance
     */
    public Ticker getTicker3() {
        if (ticker3 == null) {//GEN-END:|267-getter|0|267-preInit
            // write pre-init user code here
            ticker3 = new Ticker("Is it runs on virtual machine?");//GEN-LINE:|267-getter|1|267-postInit
            // write post-init user code here
        }//GEN-BEGIN:|267-getter|2|
        return ticker3;
    }
    //</editor-fold>//GEN-END:|267-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: ticker4 ">//GEN-BEGIN:|268-getter|0|268-preInit
    /**
     * Returns an initiliazed instance of ticker4 component.
     * @return the initialized component instance
     */
    public Ticker getTicker4() {
        if (ticker4 == null) {//GEN-END:|268-getter|0|268-preInit
            // write pre-init user code here
            ticker4 = new Ticker("Is it created by Microsoft?");//GEN-LINE:|268-getter|1|268-postInit
            // write post-init user code here
        }//GEN-BEGIN:|268-getter|2|
        return ticker4;
    }
    //</editor-fold>//GEN-END:|268-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: ticker5 ">//GEN-BEGIN:|269-getter|0|269-preInit
    /**
     * Returns an initiliazed instance of ticker5 component.
     * @return the initialized component instance
     */
    public Ticker getTicker5() {
        if (ticker5 == null) {//GEN-END:|269-getter|0|269-preInit
            // write pre-init user code here
            ticker5 = new Ticker("Is it runs in browser?");//GEN-LINE:|269-getter|1|269-postInit
            // write post-init user code here
        }//GEN-BEGIN:|269-getter|2|
        return ticker5;
    }
    //</editor-fold>//GEN-END:|269-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: ticker6 ">//GEN-BEGIN:|270-getter|0|270-preInit
    /**
     * Returns an initiliazed instance of ticker6 component.
     * @return the initialized component instance
     */
    public Ticker getTicker6() {
        if (ticker6 == null) {//GEN-END:|270-getter|0|270-preInit
            // write pre-init user code here
            ticker6 = new Ticker("Has regexp in syntax?");//GEN-LINE:|270-getter|1|270-postInit
            // write post-init user code here
        }//GEN-BEGIN:|270-getter|2|
        return ticker6;
    }
    //</editor-fold>//GEN-END:|270-getter|2|

    //<editor-fold defaultstate="collapsed" desc=" Generated Getter: ticker7 ">//GEN-BEGIN:|271-getter|0|271-preInit
    /**
     * Returns an initiliazed instance of ticker7 component.
     * @return the initialized component instance
     */
    public Ticker getTicker7() {
        if (ticker7 == null) {//GEN-END:|271-getter|0|271-preInit
            // write pre-init user code here
            ticker7 = new Ticker("Is it have keywords \"begin\"/\"end\"?");//GEN-LINE:|271-getter|1|271-postInit
            // write post-init user code here
        }//GEN-BEGIN:|271-getter|2|
        return ticker7;
    }
    //</editor-fold>//GEN-END:|271-getter|2|

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
