package sax;

import java.io.File;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class saxSample extends DefaultHandler{
		String Tag=null ;
		String nodeName=null;
		
		public void startElement(String uri,String localName,String qName,Attributes attr)
		          throws SAXException{
			if(attr.getLength() > 0){
				System.out.print("<" + qName + ">:  ");
				for(int i = 0; i < attr.getLength();i++){
					System.out.print(attr.getQName(i) + "=" + attr.getValue(i)+ "  ");
				}
				System.out.print('\n');
			}
			Tag = qName;
		} 
		
		 public static void main(String args[])
		    {
		        saxSample split = new saxSample();
		        SAXParserFactory factory = SAXParserFactory.newInstance();
		        try{
		        	SAXParser parser = factory.newSAXParser();
		        	parser.parse(new File("src/ipo.xml"), split);
		        }
		       catch(Exception exc){
		    	   exc.printStackTrace();
		       }
		    }
}
