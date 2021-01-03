SELECT C.CustomerID, O.OrderID, O.OrderDate
FROM Customers C, Orders O
WHERE C.CustomerID = O.CustomerID
ORDER BY C.CustomerID, O.OrderID
FOR XML RAW, XMLDATA