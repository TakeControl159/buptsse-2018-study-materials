import javax.xml.parsers.*; // for both SAX and DOM
import org.xml.sax.*;
import org.xml.sax.helpers.*;

//为简单起见，我们让操作系统处理异常
//在“现实生活”中，这是糟糕的编程习惯
public class Sample {
	public static void main(String args[])
	     throws Exception
{
       //创建一个解析器工厂
       SAXParserFactory factory = SAXParserFactory.newInstance();
       //告诉工厂解析器必须了解名称空间
       factory.setNamespaceAware(true);
       // Make the parser
       SAXParser saxParser = factory.newSAXParser();
       XMLReader parser = saxParser.getXMLReader();
       // Create a handler
       Handler handler = new Handler();
       // Tell the parser to use this handler
       parser.setContentHandler(handler);
       // Finally, read and parse the document
       parser.parse("hello.xml");
    } // end of Sample class

}