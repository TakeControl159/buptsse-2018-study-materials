<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Fitness Center</TITLE>
            </HEAD>
            <BODY>
                16 / 2 = 
                <xsl:variable name="result">
                    <xsl:call-template name="NumDiv2">
                         <xsl:with-param name="N" select="16"/>
                    </xsl:call-template>
                </xsl:variable>
                <xsl:value-of select="$result"/>
            </BODY>
        </HTML>
    </xsl:template>

    <xsl:template name="NumDiv2">
        <xsl:param name="N"/>
        <xsl:value-of select="$N div 2"/>
    </xsl:template>

</xsl:stylesheet>