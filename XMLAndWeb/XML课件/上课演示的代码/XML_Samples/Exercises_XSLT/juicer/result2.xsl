<?xml version="1.0" encoding="UTF-8"?><xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:axsl2="http://www.w3.org/1999/XSL/Transform/alias2"><xsl:output method="xml"/><xsl:namespace-alias stylesheet-prefix="axsl" result-prefix="xsl"/><xsl:template match="/" xmlns:axsl="http://www.w3.org/1999/XSL/Transform/alias">
        <axsl:stylesheet version="1.0">
         
            <axsl:output method="xml"/>

            <axsl:namespace-alias stylesheet-prefix="axsl" result-prefix="xsl"/>
 
            <xsl:apply-templates/>

        </axsl:stylesheet>
    </xsl:template><xsl:template match="/*" xmlns:axsl="http://www.w3.org/1999/XSL/Transform/alias">
        <xsl:variable name="self" select="document('Learn.xsl')"/>
        <xsl:copy-of select="$self//xsl:template[@match='/']"/>
        <xsl:copy-of select="$self//xsl:template[@match='/*']"/>
    </xsl:template></xsl:stylesheet>