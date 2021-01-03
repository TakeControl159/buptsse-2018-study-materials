package DOM;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.io.FileOutputStream;
import java.util.Objects;

public class Segmentation {
    public static void main(String[] args) throws TransformerConfigurationException {
        File file = new File("./src/DOM/ipo.xml");
        segmentation(file);
    }


    public static void segmentation(File file) {
        try {
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(file);
            NodeList purchaseOrderList = doc.getElementsByTagName("purchaseOrder"); //get order list
            Element nodeABC = doc.createElement("ABC_COMP");
            Element nodeIBM = doc.createElement("IBM_COMP");
            FileOutputStream fileABC = new FileOutputStream("./src/DOM/ABC.xml");
            FileOutputStream fileIBM = new FileOutputStream("./src/DOM/IBM.xml");
            StreamResult resultABC = new StreamResult(fileABC);
            StreamResult resultIBM = new StreamResult(fileIBM);
            TransformerFactory tFactory = TransformerFactory.newInstance();
            Transformer transformer = tFactory.newTransformer();
            for (int i = purchaseOrderList.getLength()-1; i >= 0; i--) {
                Node purchaseOrderNode = purchaseOrderList.item(i);
                if (purchaseOrderNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element purchaseOrderElement = (Element) purchaseOrderNode;
                    PurchaseOrder purchaseOrder = new PurchaseOrder();
                    purchaseOrder.setComp_name(purchaseOrderElement.getAttribute("comp_name"));
                        //Seperate
                        if (Objects.equals(purchaseOrder.getComp_name(), "ABC")) {
                            nodeABC.appendChild(purchaseOrderNode);
                        } else if (Objects.equals(purchaseOrder.getComp_name(), "IBM")) {
                            nodeIBM.appendChild(purchaseOrderNode);
                        }
                }
            }
            DOMSource sourceABC = new DOMSource(nodeABC);
            DOMSource sourceIBM = new DOMSource(nodeIBM);
            //Output file
            transformer.transform(sourceABC, resultABC);
            transformer.transform(sourceIBM, resultIBM);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
