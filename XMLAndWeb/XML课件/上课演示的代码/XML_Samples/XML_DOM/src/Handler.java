import javax.xml.parsers.*; // for both SAX and DOM
import org.xml.sax.*;
import org.xml.sax.helpers.*;
public class Handler extends DefaultHandler {

	// SAX在遇到开始标记时调用此方法
    public void startElement(String namespaceURI,  String localName, String qualifiedName, Attributes attributes)
    		throws SAXException
    {
    	System.out.println("startElement: " + qualifiedName);
	}
	    // SAX调用此方法以传递字符数据
    	public void characters(char ch[], int start, int length)
    		throws SAXException
    	{
    		System.out.println("characters: \"" +  new String(ch, start, length) + "\"");
    	}
        // SAX call this method when it encounters an end tag
        public void endElement(String namespaceURI, String localName, String qualifiedName)
        	throws SAXException
        {
				System.out.println("Element: /" + qualifiedName);
		}
  } // End of Handler class
