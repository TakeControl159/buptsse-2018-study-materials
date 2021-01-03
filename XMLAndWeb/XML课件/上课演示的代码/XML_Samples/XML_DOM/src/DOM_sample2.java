import javax.xml.parsers.*;
import org.xml.sax.SAXException;
import org.w3c.dom.*;
import javax.xml.validation.*;
import javax.xml.XMLConstants;
import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamSource;
import javax.xml.transform.dom.DOMSource;

import java.io.*;
public class DOM_sample2
{
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

        Document document = null; // 解析DOM.xml文档
            document = builder.parse("DOM.xml");

            childLoop(document);

        } catch (Exception e) {
            e.printStackTrace(System.err);
        } 
    	Thevalidating();
    }
    
    static void Thevalidating()
    {
   try{

	// parse an XML document into a DOM tree
	DocumentBuilder parser = DocumentBuilderFactory.newInstance().newDocumentBuilder();
	Document document = parser.parse( "shipOrder.xml");

	// create a SchemaFactory capable of understanding WXS schemas
	SchemaFactory factory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);

	// load a WXS schema, represented by a Schema instance
	Source schemaFile = new StreamSource(new File("shipOrder.xsd"));
	Schema schema = factory.newSchema(schemaFile);

	// create a Validator instance, which can be used to validate an instance document
	Validator validator = schema.newValidator();

	// validate the DOM tree

	validator.validate(new DOMSource(document));
	System.out.println("Validation succesful");

	}catch (SAXException e) {
	// instance document is invalid!
	e.printStackTrace();
	//System.out.println("Validation UnSuccesful");
	}catch(Exception e){
	e.printStackTrace();
	}
    }

    public static void childLoop(Node node)
    {
        Node textNode;
        Node sessionNode = ((Document)node).getDocumentElement();
        textNode = sessionNode.getFirstChild();
        Node committeeNode = textNode.getNextSibling();
        textNode = committeeNode.getLastChild();
        Node attendeesNode = textNode.getPreviousSibling();
        textNode = attendeesNode.getLastChild();
        Node senatorNode = textNode.getPreviousSibling();
        textNode = senatorNode.getFirstChild();
        Node firstNameNode = textNode.getNextSibling();
        textNode = firstNameNode.getNextSibling();
        Node lastNameNode = textNode.getNextSibling();

        System.out.println("Last senator: " +
            firstNameNode.getFirstChild().getNodeValue() + ' '
            + lastNameNode.getFirstChild().getNodeValue());
    }
}


