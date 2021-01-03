SELECT Customers.CustomerID, ContactName,
OrderID, OrderDate
FROM Customers, Orders
WHERE Customers.CustomerID=Orders.CustomerID
ORDER BY Customers.CustomerID, OrderID
FOR XML AUTO, ELEMENTS