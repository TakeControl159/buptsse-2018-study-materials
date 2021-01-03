import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.*;


import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;

//import com.microsoft.jdbc.sqlserver.SQLServerConnection;
//import com.microsoft.jdbc.sqlserver.SQLServerConnection.*;
//import com.microsoft.jdbc.sqlserver.SQLServerImplStatement;

//import de.jeckle.RS2DOM.RS2DOM;

public class TestDriver {
	public static void main(String[] args) {
		try {
			Class.forName("com.microsoft.jdbc.sqlserver.SQLServerDriver");
		} catch (ClassNotFoundException e) {
			System.err.println("Driver class not found");
			e.printStackTrace();
		}
		Connection con = null;
                ResultSet results;
                String xmlfilestr = "xmloutput.xml";
                String xsdfilestr = "xsloutput.xsd";
		try {
			con = (Connection) DriverManager.getConnection
("jdbc:microsoft:sqlserver://localhost:1433;database=northwind;User=sa;Password=sa");
		} catch (SQLException e1) {
			System.err.println("Error establishing database connection");
			e1.printStackTrace();
		}


		try {

                       Statement stat = con.createStatement();
                       results = stat.executeQuery("SELECT * FROM  Orders;");

			//transfer ResultSet into XML Schema stored as DOM
			Document xsd = RS2DOM.ResultSet2XSDDOM(results);
                        results.close();
                        ResultSet results2 =  stat.executeQuery("SELECT * FROM Orders;");
			//transfer ResultSet into DOM
			Document d = RS2DOM.ResultSet2DOM(results2);
			//that's all ;-)

			try {
				Transformer myTransformer =
					(TransformerFactory.newInstance()).newTransformer();
				System.out.println(
					"XML Schema instance describing the document");
				myTransformer.transform(
					new DOMSource(xsd),
                                        new StreamResult(new FileOutputStream(xsdfilestr)));
					//new StreamResult(new FileOutputStream(FileDescriptor.out)));

				System.out.println(
					"\n\nXML document containing the result set");
				myTransformer.transform(
					new DOMSource(d),
                                        new StreamResult(new FileOutputStream(xmlfilestr)));
					//new StreamResult(new FileOutputStream(FileDescriptor.out)));
			} catch (Exception e) {
				e.printStackTrace();
			}

		} catch (SQLException e2) {
			System.err.println("Error creating SQL-Statement");
			e2.printStackTrace();
		}
	}
	
}
