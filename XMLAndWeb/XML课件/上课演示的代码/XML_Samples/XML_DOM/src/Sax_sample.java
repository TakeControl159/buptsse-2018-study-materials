import java.io.*;
import org.xml.sax.*;
import javax.xml.parsers.*;
import org.xml.sax.helpers.DefaultHandler;

public class Sax_sample extends DefaultHandler
{
    static int numberLines = 0;
    static String indentation = "";
    static String displayText[] = new String[1000];

    static boolean displayBoolean;
    static String findNode;

    public static void main(String args[])
    {
        Sax_sample obj = new Sax_sample();
        findNode = args[1];
        obj.childLoop("DOM.xml");

        for(int index = 0; index < numberLines; index++){
            System.out.println(displayText[index]);
        }
    }

    public void childLoop(String uri)
    {
        DefaultHandler saxHandler = this;
        SAXParserFactory saxFactory = SAXParserFactory.newInstance();
        try {
            SAXParser saxParser = saxFactory.newSAXParser();
            saxParser.parse(new File(uri), saxHandler);
        } catch (Throwable t) {}
    }

    public void startDocument()
    {
        if(displayBoolean){
            displayText[numberLines] = indentation;
            displayText[numberLines] += "<?xml version=\"1.0\" encoding=\""+
                "UTF-8" + "\"?>";
            numberLines++;
        }
    }

    public void processingInstruction(String target, String data)
    {
        if(displayBoolean){
            displayText[numberLines] = indentation;
            displayText[numberLines] += "<?";
            displayText[numberLines] += target;
            if (data != null && data.length() > 0) {
                displayText[numberLines] += ' ';
                displayText[numberLines] += data;
            }
            displayText[numberLines] += "?>";
            numberLines++;
        }
    }

    public void startElement(String uri, String localName,
        String qualifiedName, Attributes attributes)
    {
        if(qualifiedName.equals(findNode)) {
            displayBoolean=true;
        }

        if (displayBoolean){
            displayText[numberLines] = indentation;

            indentation += "    ";

            displayText[numberLines] += '<';
            displayText[numberLines] += qualifiedName;
            if (attributes != null) {
                int numberAttributes = attributes.getLength();
                for (int loopIndex = 0; loopIndex < numberAttributes;
                    loopIndex++) {
                    displayText[numberLines] += ' ';
                    displayText[numberLines] += attributes.getQName(loopIndex);
                    displayText[numberLines] += "=\"";
                    displayText[numberLines] += attributes.getValue(loopIndex);
                    displayText[numberLines] += '"';
                }
            }
            displayText[numberLines] += '>';
            numberLines++;
        }
    }

    public void characters(char characters[], int start, int length) {
        if(displayBoolean){
            String characterData =
                (new String(characters, start, length)).trim();
            if(characterData.indexOf("\n") < 0 && characterData.length() > 0) {
                displayText[numberLines] = indentation;
                displayText[numberLines] += characterData;
                numberLines++;
            }
        }
    }

    public void ignorableWhitespace(char characters[], int start, int length)
    {
        if(displayBoolean){
            //characters(ch, start, length);
        }
    }

    public void endElement(String uri, String localName, String qualifiedName)
    {
        if(displayBoolean){
            indentation = indentation.substring(0, indentation.length() - 4) ;
            displayText[numberLines] = indentation;
            displayText[numberLines] += "</";
            displayText[numberLines] += qualifiedName;
            displayText[numberLines] += '>';
            numberLines++;
        }
        if(qualifiedName.equals(findNode)){
            displayBoolean=false;
        }
    }

    public void warning(SAXParseException exception)
    {
        System.err.println("Warning: " +
            exception.getMessage());
    }

    public void error(SAXParseException exception)
    {
        System.err.println("Error: " +
            exception.getMessage());
    }

    public void fatalError(SAXParseException exception)
    {
        System.err.println("Fatal error: " +
            exception.getMessage());
    }
}

