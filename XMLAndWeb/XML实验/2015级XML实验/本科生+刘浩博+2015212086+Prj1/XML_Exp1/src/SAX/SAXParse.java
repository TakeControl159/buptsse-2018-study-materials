package SAX;

import org.xml.sax.*;
import org.xml.sax.helpers.*;
import javax.xml.parsers.*;


public class SAXParse {

    public static class myParser extends DefaultHandler{
        @Override
        public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
            int len=attributes.getLength();
            for(int i=0;i<len;i++){
                System.out.println(attributes.getLocalName(i)+"->"+attributes.getValue(i));
            }
        }
    }

    public static void main(String[] args) throws Exception {
        SAXParserFactory factory=SAXParserFactory.newInstance();
        SAXParser saxParser=factory.newSAXParser();
        saxParser.parse("./src/SAX/ipo.xml",new myParser());
    }
}
