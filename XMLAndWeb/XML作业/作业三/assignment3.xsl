<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
<xsl:template match="/">
<html>
	<head>
		<center><font face="arial"><font color="red" face="黑体" size="6">特价商品列表</font></font></center>
	</head>
	<body>
	 <table align="center" border="1" bordercolor="black" cellpadding="1" cellspacing="1" width="1200">
			<tbody>
				<tr bgcolor="blue">
					<th valign="middle">商品号</th>
					<th valign="middle">商品名称</th>
					<th valign="middle">商品介绍</th>
					<th valign="middle">原价</th>
					<th valign="middle">现价</th>
					<th valign="middle">活动开始日期</th>
					<th valign="middle">活动结束日期</th>
					<th valign="middle">商场名称</th>
					<th valign="middle">商品地址</th>
					<th valign="middle">开业时间</th>
					<th valign="middle">打烊时间</th>
					<th valign="middle">商场联系电话</th>
				</tr>
				<xsl:for-each select="商品信息/特价商品">
				<tr>
					<td valign="middle" bgcolor="red"><xsl:value-of select="商品号"/></td>
					<td valign="middle"><xsl:value-of select="商品名称"/></td>
					<td valign="middle"><xsl:value-of select="商品介绍"/></td>
					<td valign="middle"><xsl:value-of select="原价"/></td>
					<td valign="middle"><xsl:value-of select="现价"/></td>
					<td valign="middle"><xsl:value-of select="活动开始日期"/></td>
					<td valign="middle"><xsl:value-of select="活动结束日期"/></td>
					<td valign="middle"><xsl:value-of select="商场名称"/></td>
					<td valign="middle"><xsl:value-of select="商场地址"/></td>
					<td valign="middle"><xsl:value-of select="开业时间"/></td>
					<td valign="middle"><xsl:value-of select="打烊时间"/></td>
					<td valign="middle"><a href="#"><xsl:value-of select="商场联系电话"/></a></td>
				</tr>
				</xsl:for-each>			
			</tbody>	
	     </table>	     
</body>
</html>
</xsl:template>
</xsl:stylesheet>
