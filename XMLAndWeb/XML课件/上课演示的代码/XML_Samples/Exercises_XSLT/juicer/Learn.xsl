<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:axsl="http://www.w3.org/1999/XSL/Transform/alias"
                xmlns:axsl="http://www.w3.org/1999/XSL/Transform/alias"
                xmlns:axsl2="http://www.w3.org/1999/XSL/Transform/alias2"
                xmlns:axsl2="http://www.w3.org/1999/XSL/Transform/alias2"
                version="1.0">
 
    <xsl:output method="xml"/>

    <xsl:namespace-alias stylesheet-prefix="axsl" result-prefix="xsl"/>
    <xsl:namespace-alias stylesheet-prefix="axsl2" result-prefix="axsl"/>
 
    <xsl:template match="/">
        <axsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                         xmlns:axsl="http://www.w3.org/1999/XSL/Transform/alias"
                         xmlns:axsl2="http://www.w3.org/1999/XSL/Transform/alias2"
                         version="1.0">
         
            <axsl:output method="xml"/>

            <axsl:namespace-alias stylesheet-prefix="axsl" result-prefix="xsl"/>
            <axsl:namespace-alias stylesheet-prefix="axsl2" result-prefix="axsl"/>
           
            <xsl:variable name="self" select="document('Learn.xsl')"/>
            <xsl:copy-of select="$self//xsl:template[@match='/']"/>
 
            <xsl:apply-templates/>

        </axsl:stylesheet>
    </xsl:template>

    <xsl:template match="*">
        <axsl:template>
            <xsl:attribute name="match"><xsl:value-of select="name()"/></xsl:attribute>
        </axsl:template>
        <xsl:apply-templates select="*"/>
    </xsl:template>

</xsl:stylesheet>