

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class RS2DOM {
	private static final String xsdns = "http://www.w3.org/2001/XMLSchema";

	/**
	 * @param JDBC
	 *            ResultSet to be transformed into a DOM instance containing an
	 *            XML Schema
	 * @return DOM instance conforming to W3C's Document interface containg the
	 *         schema
	 * @throws SQLException
	 */
	public static Document ResultSet2XSDDOM(ResultSet rs) throws SQLException {
		Document mySchema = null;
		try {
			mySchema =
				((DocumentBuilderFactory.newInstance()).newDocumentBuilder())
					.newDocument();
		} catch (ParserConfigurationException pce) {
			System.out.println("Cannot create DOM tree");
			pce.printStackTrace();
		}
		Element root = mySchema.createElementNS(xsdns, "xsd:schema");
		root.setAttribute("elementFormDefault", "qualified");
		root.setAttribute("attributeFormDefault", "unqualified");
		mySchema.appendChild(root);

		Element result = mySchema.createElementNS(xsdns, "xsd:element");
		result.setAttribute("name", "result");
		root.appendChild(result);

		Element ct = mySchema.createElementNS(xsdns, "xsd:complexType");
		result.appendChild(ct);

		Element seq = mySchema.createElementNS(xsdns, "xsd:sequence");
		ct.appendChild(seq);

		Element row = mySchema.createElementNS(xsdns, "xsd:element");
		row.setAttribute("name", "row");
		row.setAttribute("maxOccurs", "unbounded");
		seq.appendChild(row);

		ct = mySchema.createElementNS(xsdns, "xsd:complexType");
		row.appendChild(ct);

		seq = mySchema.createElementNS(xsdns, "xsd:sequence");
		ct.appendChild(seq);

		root = null;
		ct = null;
		Element element;

		ResultSetMetaData rsmd = rs.getMetaData();
		for (int i = 1; i <= rsmd.getColumnCount(); i++) {
			element = mySchema.createElementNS(xsdns, "xsd:element");
			if (rsmd.isNullable(i) == ResultSetMetaData.columnNullable) {
				element.setAttribute("nillable", "true");
			}
			element.setAttribute("name", rsmd.getColumnLabel(i));
			switch (rsmd.getColumnType(i)) {
				case java.sql.Types.BIGINT :
					element.setAttribute("type", "xsd:integer");
					break;
				case java.sql.Types.BIT :
					element.setAttribute("type", "xsd:string");
					break;
				case java.sql.Types.BOOLEAN :
					element.setAttribute("type", "xsd:boolean");
					break;
				case java.sql.Types.CHAR :
					element.setAttribute("type", "xsd:string");
					break;
				case java.sql.Types.DATE :
					element.setAttribute("type", "xsd:date");
					break;
				case java.sql.Types.DECIMAL :
					element.setAttribute("type", "xsd:integer");
					break;
				case java.sql.Types.DOUBLE :
					element.setAttribute("type", "xsd:double");
					break;
				case java.sql.Types.FLOAT :
					element.setAttribute("type", "xsd:float");
					break;
				case java.sql.Types.INTEGER :
					element.setAttribute("type", "xsd:integer");
					break;
				case java.sql.Types.LONGVARCHAR :
					element.setAttribute("type", "xsd:string");
					break;
				case java.sql.Types.NUMERIC :
					element.setAttribute("type", "xsd:decimal");
					break;
				case java.sql.Types.REAL :
					element.setAttribute("type", "xsd:double");
					break;
				case java.sql.Types.SMALLINT :
					element.setAttribute("type", "xsd:integer");
					break;
				case java.sql.Types.TIME :
					element.setAttribute("type", "xsd:time");
					break;
				case java.sql.Types.TIMESTAMP :
					element.setAttribute("type", "xsd:dateTime");
					break;
				case java.sql.Types.TINYINT :
					element.setAttribute("type", "xsd:byte");
					break;
				case java.sql.Types.VARCHAR :
					element.setAttribute("type", "xsd:string");
					break;
				default :
					System.out.println(
						"warning: don't know how to handle type "
							+ rsmd.getColumnType(i));
					element.setAttribute("type", "xsd:string");
			}

			seq.appendChild(element);
		}
		return mySchema;
	}
	/**
	 * @param JDBC
	 *            ResultSet to be transformed into a DOM instance
	 * @return DOM instance conforming to W3C's Document interface
	 * @throws SQLException
	 */
	public static Document ResultSet2DOM(ResultSet rs) throws SQLException {
		Document myDocument = null;
		try {
			myDocument =
				((DocumentBuilderFactory.newInstance()).newDocumentBuilder())
					.newDocument();
		} catch (ParserConfigurationException pce) {
			System.out.println("Cannot create DOM tree");
			pce.printStackTrace();
		}
		Element root = myDocument.createElement("result");
		//just a hack to make things easier
		root.setAttribute(
			"xmlns:xsi",
			"http://www.w3.org/2001/XMLSchema-instance");
		myDocument.appendChild(root);
               String str = rs.toString();
		ResultSetMetaData rsmd = rs.getMetaData();

		Element element, row;
		String value;
                int length = rs.getRow();
                if( rs.wasNull() == true ) return myDocument;
		//while (rs.isLast() == false) {
                while (rs.next()){
		//	rs.next();
			row = myDocument.createElement("row");
			root.appendChild(row);
			for (int i = 1; i <= rsmd.getColumnCount(); i++) {
				element = myDocument.createElement(rsmd.getColumnLabel(i));

				value = rs.getString(i);
				if (value == null) {
					element.setAttribute("xsi:nil", "true");
				} else {
					element.appendChild(
						myDocument.createTextNode(rs.getString(i)));
				}
				row.appendChild(element);
			}
		}
		return myDocument;
	}
}
