SELECT CustomerID,
ContactName
FROM Customers
FOR XML AUTO


SELECT Customers.CustomerID, ContactName,
OrderID, OrderDate
FROM Customers, Orders
WHERE Customers.CustomerID=Orders.CustomerID
ORDER BY Customers.CustomerID, OrderID
FOR XML AUTO, ELEMENTS


SELECT C.CustomerID, O.OrderID, O.OrderDate
FROM Customers C, Orders O
WHERE C.CustomerID = O.CustomerID
ORDER BY C.CustomerID, O.OrderID
FOR XML RAW, XMLDATA