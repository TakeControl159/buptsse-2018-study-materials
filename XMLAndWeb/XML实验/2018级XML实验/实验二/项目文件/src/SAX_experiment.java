import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

public class SAX_experiment {
    public static void main(String args[])
            throws Exception
    {
        // 创建解析器工厂
        SAXParserFactory factory = SAXParserFactory.newInstance();
        factory.setNamespaceAware(true);
        // 创建解析器
        SAXParser saxParser = factory.newSAXParser();
        XMLReader parser = saxParser.getXMLReader();
        // 创建处理器
        MySAXhandler mySAXhandler = new MySAXhandler();
        parser.setContentHandler(mySAXhandler);
        // 读取解析ipo.xml文件
        parser.parse("ipo.xml");
    }

}

// 自定义处理器
class MySAXhandler extends DefaultHandler{
    public void startElement(String namespaceURI, String locakName, String qualifiedName, Attributes attributes) throws SAXException {
        // 循环输出属性名和属性值<key:value>
        for (int i = 0; i < attributes.getLength(); i++) {
            System.out.println("<" + attributes.getLocalName(i) + ":" + attributes.getValue(i) + ">");
        }
    }
}