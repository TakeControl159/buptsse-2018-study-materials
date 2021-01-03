import javax.xml.parsers.*;
import org.w3c.dom.*;

public class DOM_sample
{
    static String displayText[] = new String[1000];
    static int numberLines = 0;

    public static void main(String args[])
    {
        try {
            DocumentBuilderFactory factory =
                DocumentBuilderFactory.newInstance();

            DocumentBuilder builder = null;
            try {
                builder = factory.newDocumentBuilder();
            }
            catch (ParserConfigurationException e) {}

            Document document = null;
            document = builder.parse(args[0]);

            childLoop(document, "");

        } catch (Exception e) {
            e.printStackTrace(System.err);
        }

        for(int loopIndex = 0; loopIndex < numberLines; loopIndex++){
            System.out.println(displayText[loopIndex]) ;
        }
    }

    public static void childLoop(Node node, String indentation)
    {
        if (node == null) {
            return;
        }

        int type = node.getNodeType();

        switch (type) {
            case Node.DOCUMENT_NODE: {
                displayText[numberLines] = indentation;
                displayText[numberLines] +=
                    "<?xml version=\"1.0\" encoding=\""+
                  "UTF-8" + "\"?>";
                numberLines++;
                childLoop(((Document)node).getDocumentElement(), "");
                break;
             }

             case Node.ELEMENT_NODE: {
                 displayText[numberLines] = indentation;
                 displayText[numberLines] += "<";
                 displayText[numberLines] += node.getNodeName();

                 int length = (node.getAttributes() != null) ?
                     node.getAttributes().getLength() : 0;
                 Attr attributes[] = new Attr[length];
                 for (int loopIndex = 0; loopIndex < length; loopIndex++) {
                     attributes[loopIndex] =
                         (Attr)node.getAttributes().item(loopIndex);
                 }

                 for (int loopIndex = 0; loopIndex < attributes.length;
                     loopIndex++) {
                     Attr attribute = attributes[loopIndex];
                     displayText[numberLines] += " ";
                     displayText[numberLines] += attribute.getNodeName();
                     displayText[numberLines] += "=\"";
                     displayText[numberLines] += attribute.getNodeValue();
                     displayText[numberLines] += "\"";
                 }
                 displayText[numberLines] += ">";

                 numberLines++;

                 NodeList childNodes = node.getChildNodes();
                 if (childNodes != null) {
                     length = childNodes.getLength();
                     indentation += "    ";
                     for (int loopIndex = 0; loopIndex < length; loopIndex++ ) {
                        childLoop(childNodes.item(loopIndex), indentation);
                     }
                 }
                 break;
             }

             case Node.TEXT_NODE: {
                 displayText[numberLines] = indentation;
                 String trimmedText = node.getNodeValue().trim();
                 if(trimmedText.indexOf("\n") < 0 && trimmedText.length() > 0){
                     displayText[numberLines] += trimmedText;
                     numberLines++;
                 }
                 break;
             }

             case Node.PROCESSING_INSTRUCTION_NODE: {
                 displayText[numberLines] = indentation;
                 displayText[numberLines] += "<?";
                 displayText[numberLines] += node.getNodeName();
                 String text = node.getNodeValue();
                 if (text != null && text.length() > 0) {
                     displayText[numberLines] += text;
                 }
                 displayText[numberLines] += "?>";
                 numberLines++;
                 break;
             }

             case Node.CDATA_SECTION_NODE: {
                 displayText[numberLines] = indentation;
                 displayText[numberLines] += "<![CDATA[";
                 displayText[numberLines] += node.getNodeValue();
                 displayText[numberLines] += "]]>";
                 numberLines++;
                 break;
            }
        }

        if (type == Node.ELEMENT_NODE) {
            displayText[numberLines] = indentation.substring(0,
                indentation.length() - 4);
            displayText[numberLines] += "</";
            displayText[numberLines] += node.getNodeName();
            displayText[numberLines] += ">";
            numberLines++;
            indentation += "    ";
        }
    }
}

