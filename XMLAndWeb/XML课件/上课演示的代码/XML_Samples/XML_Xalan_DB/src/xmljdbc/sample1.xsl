<?xml version="1.0"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"

                version="1.0"

                xmlns:sql="org.apache.xalan.lib.sql.XConnection"

                extension-element-prefixes="sql">
	<xsl:output method="xml" indent="yes"/>
	
	<xsl:param name="query" select=""/>
	<xsl:template match="/">
    	<xsl:variable name="db" select="sql:new()"/>

	    <!-- Connect to the database with minimal error detection -->
		<xsl:if test="not(sql:connect($db, 'sppixpool'))" >
	    	<xsl:message>Error Connecting to the Database</xsl:message>
	      	<xsl:copy-of select="sql:getError($db)/ext-error" />
	    </xsl:if>
	    <xsl:value-of select="sql:disableStreamingMode($db)" />
	    <data>
	     <xsl:value-of select="@column-label"/>
	      <xsl:variable name="table" select='sql:query($db, $query)'/>
	      
	      <!-- 
	      	Let's include Error Checking, the error is actually stored 
	        in the connection since $table will be either data or null
	      -->
	         
	      <xsl:if test="not($table)" >
	      	<xsl:message>Error in Query</xsl:message>
	        <xsl:copy-of select="sql:getError($db)/ext-error" />
	      </xsl:if>
	      <xsl:apply-templates select="$table/sql/row-set/row"/>
	    </data>
	    <xsl:value-of select="sql:close($db)"/>
	</xsl:template>
	
	<xsl:template match="row">
	  <row><xsl:apply-templates select="col"/></row>
	</xsl:template>
	
	<xsl:template match="col">
	  <value><xsl:attribute name="name"><xsl:value-of select="@column-label"/></xsl:attribute><xsl:value-of select="text()"/></value>
	</xsl:template>

</xsl:stylesheet>