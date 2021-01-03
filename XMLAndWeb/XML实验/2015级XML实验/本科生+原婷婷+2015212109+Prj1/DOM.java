package xml;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.*;
import org.xml.sax.SAXException;

import com.sun.org.apache.xerces.internal.dom.*;

public class DOM {
	private static Document doc_ABC;
	private static Document doc_IBM;
	private static File file_ABC;
	private static File file_IBM;
	private static Element aOrders,aCom,aOrder,shipToA,billToA,itemsA,itemA;
	private static Element bOrders,bCom,bOrder,shipToB,billToB,itemsB,itemB;
	private static FileOutputStream aStr;
	private static FileOutputStream bStr;

	
	public static void main(String[] args){

		
	try {
		file_ABC=new File("src/xml/ABC_COMP.xml");
		file_IBM=new File("src/xml/IBM_COMP.xml");
        //得到dom解析器工厂fac  
        DocumentBuilderFactory fac=  DocumentBuilderFactory.newInstance();  
        //通过解析器工厂fac得到dom解析器  
        DocumentBuilder builder = fac.newDocumentBuilder();
		
        //通过dom解析器解析xml--》得到document对象
        Document doc = builder.parse("ipo.xml");
        //parser(doc);
        
       
		doc_ABC = new DocumentImpl();
		doc_IBM = new DocumentImpl();
		aOrders = doc_ABC.createElement("purchaseOrders");
		aCom = doc_ABC.createElement("ABC_COMP");
		doc_ABC.appendChild(aOrders);
		aOrders.appendChild(aCom);
		bOrders = doc_IBM.createElement("purchaseOrders");
		doc_IBM.appendChild(bOrders);
		bCom = doc_IBM.createElement("IBM_COMP");
		bOrders.appendChild(bCom);
		
		NodeList listorder= doc.getElementsByTagName("purchaseOrder");  
        for (int i = 0; i < listorder.getLength(); i++) {  
            //当前的order 
            Element order= (Element) listorder.item(i);  
            //取出 com_name为ABC的
            String name= order.getAttributes().item(0).getNodeValue();  
            if(name.equals("ABC")){  
            	list(listorder.item(i),doc_ABC, aCom, aOrder,
						shipToA, billToA, itemsA, itemA);
            }  
            else if(name.equals("IBM")) {
            	list(listorder.item(i),doc_IBM, bCom, bOrder,
						shipToB, billToB, itemsB, itemB);
            }
        }
        } catch (ParserConfigurationException |SAXException |IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}  
	try {		
		aStr = new FileOutputStream(file_ABC);
		bStr = new FileOutputStream(file_IBM);
		Transformer tran = TransformerFactory.newInstance().newTransformer();
		tran.setOutputProperty(OutputKeys.INDENT, "yes");
		tran.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
		tran.setOutputProperty(OutputKeys.METHOD, "xml");
		tran.transform(new DOMSource(doc_ABC), new StreamResult(aStr));

		tran.transform(new DOMSource(doc_IBM), new StreamResult(bStr));
       	} catch (FileNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	} catch (TransformerException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
}

	private static void list(Node node, Document doc, Element company, Element order, Element shipTo,
			Element billTo, Element items, Element item) {
		//int type=node.getNodeType();
		Text value;
		String v;
		NodeList listnode;
		order = doc.createElement("purchaseOrder");
		shipTo = doc.createElement("shipTo");
		billTo = doc.createElement("billTo");
		items = doc.createElement("Items");	
		company.appendChild(order);
		for (int i = 0; i < node.getChildNodes().getLength(); i++)
			if (node.getChildNodes().item(i).getNodeType() == Node.TEXT_NODE)
				continue;
			else if (node.getChildNodes().item(i).getNodeName().equals("shipTo")) {
				order.appendChild(shipTo);
				Element exportCode = doc.createElement("export-code");
				v = node.getChildNodes().item(i).getAttributes().item(0).getNodeValue();
				if (v == null)
					continue;
				value = doc.createTextNode(v);
				shipTo.appendChild(exportCode);
				exportCode.appendChild(value);
				Element t = doc.createElement("type");
				v = node.getChildNodes().item(i).getAttributes().item(1).getNodeValue();
				if (v == null)
					continue;
				value = doc.createTextNode(v);
				shipTo.appendChild(t);
				t.appendChild(value);
				listnode = node.getChildNodes().item(i).getChildNodes();

				for (int j = 0; j < listnode.getLength(); j++)
					if (listnode.item(j).getNodeType() != Node.TEXT_NODE) {
						Element c = doc.createElement(listnode.item(j).getNodeName().toString());
						v = listnode.item(j).getTextContent();
						if (v == null)
							continue;
						value = doc.createTextNode(v);
						shipTo.appendChild(c);
						c.appendChild(value);
					}
			}
			else if (node.getChildNodes().item(i).getNodeName().equals("billTo")) {
				order.appendChild(billTo);
				Element t = doc.createElement("type");
				v = node.getChildNodes().item(i).getAttributes().item(0).getNodeValue();
				if (v == null)
					continue;
				value = doc.createTextNode(v);
				t.appendChild(value);
				billTo.appendChild(t);
				listnode = node.getChildNodes().item(i).getChildNodes();
				for (int j = 0; j < listnode.getLength(); j++)
					if (listnode.item(j).getNodeType() != Node.TEXT_NODE) {
						Element c = doc.createElement(listnode.item(j)
								.getNodeName().toString());
						v = listnode.item(j).getTextContent();
						if (v == null)
							continue;
						value = doc.createTextNode(v);
						billTo.appendChild(c);
						c.appendChild(value);
					}
			}
			else if (node.getChildNodes().item(i).getNodeName().equals("Items")) {
				order.appendChild(items);
				NodeList itemList = node.getChildNodes().item(i).getChildNodes();

				for (int j = 0; j < itemList.getLength(); j++)
					if (itemList.item(j).getNodeType() == Node.TEXT_NODE)
						continue;
					else {
						item = doc.createElement("item");
						items.appendChild(item);
						Element patrNum = doc.createElement("partNum");
						v = itemList.item(j).getAttributes().item(0).getNodeValue();
						if (v == null)
							continue;
						value = doc.createTextNode(v);
						item.appendChild(patrNum);
						patrNum.appendChild(value); 
						listnode = itemList.item(j).getChildNodes();
						for (int k = 0; k < listnode.getLength(); k++)
							if (listnode.item(k).getNodeType() != Node.TEXT_NODE) {
								Element c = doc.createElement(listnode.item(k).getNodeName().toString());
								v = listnode.item(k).getTextContent();
								if (v == null)
									continue;
								value = doc.createTextNode(v);
								item.appendChild(c);
								c.appendChild(value);
							}
					}
			}
		}
		
}


